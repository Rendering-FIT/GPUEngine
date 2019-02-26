#include "GpuOctreeEdgePropagator.hpp"
#include "PropagateIndicesShader.hpp"

#include <geGL/StaticCalls.h>
#include "HighResolutionTimer.hpp"

#include <cstring>
#include <iterator>


bool GpuOctreeEdgePropagator::init(std::shared_ptr<Octree> octree, unsigned workgroupSize, size_t maxBufferSizeMB)
{
	_wgSize = workgroupSize;
	_octree = octree;
	_maxBufferSize = maxBufferSizeMB * 1024ull * 1024ull;

	if (!_createPropagateProgram(_wgSize))
		return false;

	_createBuffers();
	_allocateBuffers();

	return true;
}

bool GpuOctreeEdgePropagator::_createPropagateProgram(uint32_t workgroupSize)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	auto programSource = buildComputeShaderPropagate(workgroupSize);
	
	_propagateProgram = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, programSource));

	assert(ge::gl::glGetError() == GL_NO_ERROR);
	return _propagateProgram->isProgram();
}

void GpuOctreeEdgePropagator::_createBuffers()
{
	_indices = std::make_shared<ge::gl::Buffer>();
	_numIndices = std::make_shared<ge::gl::Buffer>();
	_outputIndices = std::make_shared<ge::gl::Buffer>();
	_outputNumIndices = std::make_shared<ge::gl::Buffer>();
	_parentIndices = std::make_shared<ge::gl::Buffer>();
	_parentNumIndices = std::make_shared<ge::gl::Buffer>();

	_atomicCounter = std::make_shared<ge::gl::Buffer>(sizeof(uint32_t), nullptr, GL_DYNAMIC_COPY);
}

void GpuOctreeEdgePropagator::_deleteBuffers()
{
	_indices.reset();
	_numIndices.reset();
	_outputIndices.reset();
	_outputNumIndices.reset();
	_parentIndices.reset();
	_parentNumIndices.reset();
	_atomicCounter.reset();
}

void GpuOctreeEdgePropagator::_clearAtomicCounter()
{
	assert(_atomicCounter);
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	uint32_t zero = 0;
	_atomicCounter->setData(&zero, sizeof(uint32_t));
	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeEdgePropagator::_allocateBuffers()
{
	//Depest level is already sorted
	const size_t secondDeepestLevelSize = ipow(OCTREE_NUM_CHILDREN, _octree->getDeepestLevel()-1);
	
	_indices->alloc(_maxBufferSize, nullptr);
	_numIndices->alloc((secondDeepestLevelSize + 1) * sizeof(uint32_t), nullptr);
	_outputIndices->alloc(_maxBufferSize, nullptr);
	_outputNumIndices->alloc((secondDeepestLevelSize + 1) * sizeof(uint32_t), nullptr); //+1 cos its exclusive sum, last item has to know it's range
	_parentIndices->alloc(_maxBufferSize /8ull, nullptr);
	_parentNumIndices->alloc((secondDeepestLevelSize /8ull)*sizeof(uint32_t), nullptr);

	std::cout << "Total allocated size (Edge Propagator): " << (2 * _maxBufferSize + 2 * (secondDeepestLevelSize + 1) * sizeof(uint32_t) + _maxBufferSize / 8ull + secondDeepestLevelSize / 8ull) / 1024ull / 1024ull << "MB\n";
}

uint32_t GpuOctreeEdgePropagator::_getLevelMaxNofVoxels(uint32_t level, BufferType type) const
{
	const auto startId = _octree->getLevelFirstNodeID(level);
	const auto levelSize = _octree->getLevelSize(level);

	uint32_t maxSize = 0;

	for (uint32_t i = 0; i < levelSize; ++i)
	{
		const auto node = _octree->getNode(startId + i);
		const auto& buffer = type == BufferType::POTENTIAL ? node->edgesMayCastMap[BitmaskAllSet] : node->edgesAlwaysCastMap[BitmaskAllSet];

		maxSize = std::max(maxSize, static_cast<uint32_t>(buffer.size()));
	}

	return maxSize;
}

void GpuOctreeEdgePropagator::propagateEdgesToUpperLevel(unsigned level, BufferType type)
{
	assert(level <= _octree->getDeepestLevel());
	
	const auto levelSize = unsigned(ipow(OCTREE_NUM_CHILDREN, level));
	const auto startingIndex = _octree->getLevelFirstNodeID(level);

	uint32_t numProcessed = 0;
	std::vector<uint32_t> sizePrefixSum;

	_propagateProgram->use();
	_bindBuffers();
	
	const uint32_t maxEdgesPerVoxel = _getLevelMaxNofVoxels(level, type);

	while(numProcessed<levelSize)
	{
		_loadVoxelEdgesStartingFrom(startingIndex+numProcessed, startingIndex + levelSize, type, sizePrefixSum);

		const auto numLoaded = sizePrefixSum.size() - 1;
		assert((numLoaded%OCTREE_NUM_CHILDREN) == 0);

		const uint64_t parentIdicesRequiredSize = maxEdgesPerVoxel * (numLoaded / OCTREE_NUM_CHILDREN) * sizeof(uint32_t);
		if(_parentIndices->getSize() < parentIdicesRequiredSize)
		{
			_parentIndices->unbindBase(GL_SHADER_STORAGE_BUFFER, 4);
			_parentIndices.reset();
			_parentIndices = std::make_shared<ge::gl::Buffer>();
			_parentIndices->alloc(parentIdicesRequiredSize);
			_parentIndices->bindBase(GL_SHADER_STORAGE_BUFFER, 4);
		}

		_clearAtomicCounter();
		_propagateProgram->set1ui("nofVoxels", unsigned(numLoaded));
		_propagateProgram->set1ui("maxNofEdges", maxEdgesPerVoxel);

		ge::gl::glDispatchCompute(ceilf(float(numLoaded)/_wgSize), 1, 1);
		ge::gl::glFinish();

		_updateCpuData(startingIndex + numProcessed, unsigned(numLoaded), maxEdgesPerVoxel, type, sizePrefixSum);

		numProcessed += unsigned(numLoaded);
	}

	_unbindBuffers();
}


void GpuOctreeEdgePropagator::_loadVoxelEdgesStartingFrom(
	uint32_t startingVoxel, 
	uint32_t endVoxel, 
	BufferType type, 
	std::vector<uint32_t>& sizesPrefixSum)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	
	size_t usedCapacity = 0;
	const uint32_t stopIndex = endVoxel;// startingVoxel + levelSize;
	const uint32_t remainingSize = endVoxel - startingVoxel;
	uint32_t currentIndex = startingVoxel;

	sizesPrefixSum.clear();
	sizesPrefixSum.push_back(0);

	uint8_t* indicesPtr = (uint8_t*)_indices->map(GL_WRITE_ONLY);

	uint32_t numLoaded = 0;
	while(numLoaded<remainingSize)
	{
		const uint32_t currentIndex = startingVoxel + numLoaded;

		uint32_t maxSz;
		const auto sz = _getSyblingsBufferSizeAndMaximum(currentIndex, type, maxSz);

		if ((usedCapacity + sz * sizeof(uint32_t)) > _maxBufferSize)
			break;

		for (uint32_t i = 0; i < OCTREE_NUM_CHILDREN; ++i)
		{
			auto node = _octree->getNode(currentIndex + i);
			std::vector<uint32_t>& edges = type == BufferType::POTENTIAL ? node->edgesMayCastMap[BitmaskAllSet] : node->edgesAlwaysCastMap[BitmaskAllSet];
			if(!edges.empty())
				memcpy(indicesPtr + usedCapacity, edges.data(), edges.size() * sizeof(uint32_t));
			usedCapacity += edges.size()*sizeof(uint32_t);

			sizesPrefixSum.push_back(sizesPrefixSum[sizesPrefixSum.size() - 1] + unsigned(edges.size()));
		}

		numLoaded += OCTREE_NUM_CHILDREN;
	}

	auto numIndicesPtr = _numIndices->map(GL_WRITE_ONLY);
	memcpy(numIndicesPtr, sizesPrefixSum.data(), sizesPrefixSum.size() * sizeof(uint32_t));

	_indices->unmap();
	_numIndices->unmap();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

size_t GpuOctreeEdgePropagator::_getSyblingsBufferSizeAndMaximum(uint32_t startingID, BufferType type, uint32_t& maxSize)
{
	size_t sz = 0;
	maxSize = 0;
	for(uint32_t i=0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		auto node = _octree->getNode(startingID+i);
		std::vector<uint32_t>& edges = type == BufferType::POTENTIAL ? node->edgesMayCastMap[BitmaskAllSet] : node->edgesAlwaysCastMap[BitmaskAllSet];

		sz += edges.size();
		maxSize = std::max(maxSize, (uint32_t)edges.size());
	}

	return sz;
}

void GpuOctreeEdgePropagator::_updateCpuData(unsigned startingIndex, unsigned batchSize, unsigned maxEdgesPerVoxel, BufferType type, const std::vector<uint32_t>& sizePrefixSum)
{
	std::vector<uint32_t> numIndices;
	numIndices.resize(batchSize);

	auto ni = _outputNumIndices->map(GL_READ_ONLY);
	memcpy(numIndices.data(), ni, numIndices.size() * sizeof(uint32_t));
	_outputNumIndices->unmap();

	const uint32_t* indices = reinterpret_cast<const uint32_t*>(_outputIndices->map(GL_READ_ONLY));

	//Process children
	#pragma omp parallel for num_threads(4)
	for(int i = 0; i<batchSize; ++i)
	{
		auto node = _octree->getNode(startingIndex + i);
		std::vector<uint32_t>& edges = type == BufferType::POTENTIAL ? node->edgesMayCastMap[BitmaskAllSet] : node->edgesAlwaysCastMap[BitmaskAllSet];
		edges.resize(numIndices[i]);

		if (numIndices[i] != 0)
			memcpy(edges.data(), indices + sizePrefixSum[i], numIndices[i]*sizeof(uint32_t));
	}
	_outputIndices->unmap();


	//Process parents
	const auto nofParents = batchSize / OCTREE_NUM_CHILDREN;
	numIndices.resize(nofParents);

	auto pni = _parentNumIndices->map(GL_READ_ONLY);
	memcpy(numIndices.data(), pni, numIndices.size() * sizeof(uint32_t));
	_parentNumIndices->unmap();

	const uint32_t startingParent = _octree->getNodeParent(startingIndex);
	const uint32_t* parentIndices = reinterpret_cast<const uint32_t*>(_parentIndices->map(GL_READ_ONLY));

	#pragma omp parallel for num_threads(4)
	for(int i=0; i<nofParents; ++i)
	{
		auto node = _octree->getNode(startingParent + i);
		std::vector<uint32_t>& edges = type == BufferType::POTENTIAL ? node->edgesMayCastMap[BitmaskAllSet] : node->edgesAlwaysCastMap[BitmaskAllSet];
		edges.resize(numIndices[i]);

		if (numIndices[i] != 0)
			memcpy(edges.data(), parentIndices + i*maxEdgesPerVoxel, numIndices[i] * sizeof(uint32_t));
	}

	_parentIndices->unmap();
}


void GpuOctreeEdgePropagator::_bindBuffers()
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	_indices->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_numIndices->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_outputIndices->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_outputNumIndices->bindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_parentIndices->bindBase(GL_SHADER_STORAGE_BUFFER, 4);
	_parentNumIndices->bindBase(GL_SHADER_STORAGE_BUFFER, 5);
	_atomicCounter->bindBase(GL_SHADER_STORAGE_BUFFER, 6);
	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeEdgePropagator::_unbindBuffers()
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	_indices->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_numIndices->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_outputIndices->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_outputNumIndices->unbindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_parentIndices->unbindBase(GL_SHADER_STORAGE_BUFFER, 4);
	_parentNumIndices->unbindBase(GL_SHADER_STORAGE_BUFFER, 5);
	_atomicCounter->unbindBase(GL_SHADER_STORAGE_BUFFER, 6);
	assert(ge::gl::glGetError() == GL_NO_ERROR);
}


#include <fstream>
#include <ostream>
void GpuOctreeEdgePropagator::profile()
{
	const uint32_t level = _octree->getDeepestLevel() - 1;
	const BufferType type = BufferType::POTENTIAL;
	const auto levelSize = unsigned(ipow(OCTREE_NUM_CHILDREN, level));
	const auto startingIndex = _octree->getLevelFirstNodeID(level);
	const uint32_t repetitions = 10;

	const uint32_t maxEdgesPerVoxel = _getLevelMaxNofVoxels(level, type);

	std::vector<uint32_t> sizePrefixSum;

	uint32_t wgSize = 32;

	struct ProfRes
	{
		uint32_t wg;
		uint32_t buff;
		double time;
	};

	std::vector<ProfRes> profResults;

	HighResolutionTimer timer;
	for(wgSize; wgSize<=1024; wgSize *=2)
	{
		_propagateProgram.reset();
		_createPropagateProgram(wgSize);

		_propagateProgram->use();
		
		size_t bufferSizeMB = 64;
		for(bufferSizeMB; bufferSizeMB < 4096ull; bufferSizeMB*=2ull)
		{
			_maxBufferSize = bufferSizeMB * 1024ull * 1024ull;
			_unbindBuffers();
			_deleteBuffers();
			_createBuffers();
			_allocateBuffers();
			_bindBuffers();

			HighResolutionTimer t;
			double time = 0;

			for (uint32_t i = 0; i<repetitions; ++i)
			{
				uint32_t numProcessed = 0;

				while (numProcessed < levelSize)
				{
					_loadVoxelEdgesStartingFrom(startingIndex + numProcessed, startingIndex + levelSize, type, sizePrefixSum);

					const auto numLoaded = sizePrefixSum.size() - 1;

					const uint64_t parentIdicesRequiredSize = maxEdgesPerVoxel * (numLoaded / OCTREE_NUM_CHILDREN) * sizeof(uint32_t);
					if (_parentIndices->getSize() < parentIdicesRequiredSize)
					{
						_parentIndices->unbindBase(GL_SHADER_STORAGE_BUFFER, 4);
						_parentIndices.reset();
						_parentIndices = std::make_shared<ge::gl::Buffer>();
						_parentIndices->alloc(parentIdicesRequiredSize);
						_parentIndices->bindBase(GL_SHADER_STORAGE_BUFFER, 4);
					}

					_clearAtomicCounter();
					_propagateProgram->set1ui("nofVoxels", unsigned(numLoaded));
					_propagateProgram->set1ui("maxNofEdges", maxEdgesPerVoxel);

					ge::gl::glFinish();
					timer.reset();
					ge::gl::glDispatchCompute(ceilf(float(numLoaded) / wgSize), 1, 1);
					ge::gl::glFinish();
					time += timer.getElapsedTimeMilliseconds();

					numProcessed += unsigned(numLoaded);
				}
			}

			profResults.push_back({ wgSize, static_cast<uint32_t>(bufferSizeMB), time / repetitions });			
		}
	}

	std::sort(profResults.begin(), profResults.end(), [](const ProfRes& a, const ProfRes&b)->bool {return a.time < b.time; });

	std::ofstream file;
	file.open("profilePropagate.txt", std::ios_base::app);

	for(const auto& res : profResults)
	{
		std::string msg;
		msg = "WG: " + std::to_string(res.wg) + " BUF: " + std::to_string(res.buff) + "   " + std::to_string(res.time) + "\n";
		file << msg;
	}
	file << "\n";
	file.close();

	std::cout << "---End of profiling---\n";
	exit(0);
}

