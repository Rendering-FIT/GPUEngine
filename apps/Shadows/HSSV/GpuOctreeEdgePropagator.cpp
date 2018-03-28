#include "GpuOctreeEdgePropagator.hpp"
#include "PropagateIndicesShader.hpp"

#include <geGL/StaticCalls.h>
#include "HighResolutionTimer.hpp"

#include <cstring>

bool GpuOctreeEdgePropagator::init(std::shared_ptr<Octree> octree, unsigned subgroupSize)
{
	if (!_createPropagateProgram(2, subgroupSize))
		return false;

	_octree = octree;

	_createBuffers();
	_allocateBuffers();

	return true;
}

bool GpuOctreeEdgePropagator::_createPropagateProgram(unsigned numSubgroupsPerWG, unsigned subgroupSize)
{
	assert(subgroupSize == 32 || subgroupSize == 64);
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	_propagateProgram = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, buildComputeShaderPropagate(numSubgroupsPerWG, subgroupSize)));

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
	//Depest level is already sorted out
	const unsigned int secondDeepestLevelSize = ipow(OCTREE_NUM_CHILDREN, _octree->getDeepestLevel()-1);
	
	_indices->alloc(MAX_BUFFER_SIZE_PROPAGATE, nullptr);
	_numIndices->alloc((secondDeepestLevelSize + 1) * sizeof(uint32_t), nullptr);
	_outputIndices->alloc(MAX_BUFFER_SIZE_PROPAGATE, nullptr);
	_outputNumIndices->alloc((secondDeepestLevelSize + 1) * sizeof(uint32_t), nullptr); //+1 cos its exclusive sum, last item has to know it's range
	_parentIndices->alloc(MAX_BUFFER_SIZE_PROPAGATE/8ul, nullptr);
	_parentNumIndices->alloc((secondDeepestLevelSize /8ul)*sizeof(uint32_t), nullptr);

	std::cout << "Total allocated size (Edge Propagator): " << (2 * MAX_BUFFER_SIZE_PROPAGATE + 2 * (secondDeepestLevelSize + 1) * sizeof(uint32_t) + MAX_BUFFER_SIZE_PROPAGATE / 8ul + secondDeepestLevelSize / 8ul) / 1024ul / 1024ul << "MB\n";
}

void GpuOctreeEdgePropagator::propagateEdgesToUpperLevel(unsigned level, BufferType type)
{
	assert(level <= _octree->getDeepestLevel());
	
	const auto levelSize = ipow(OCTREE_NUM_CHILDREN, level);
	const auto startingIndex = _octree->getLevelFirstNodeID(level);

	unsigned int numProcessed = 0;
	std::vector<unsigned int> sizePrefixSum;

	_propagateProgram->use();
	_bindBuffers();
	
	while(numProcessed<levelSize)
	{
		unsigned int maxEdgesPerVoxel = 0;

		_loadVoxelEdgesStartingFrom_returnNofLoaded(startingIndex+numProcessed, startingIndex + levelSize, type, maxEdgesPerVoxel, sizePrefixSum);

		const auto numLoaded = sizePrefixSum.size() - 1;

		_clearAtomicCounter();
		_propagateProgram->set1ui("nofVoxels", numLoaded);
		_propagateProgram->set1ui("maxNofEdges", maxEdgesPerVoxel);

		ge::gl::glDispatchCompute(16, 1, 1);
		ge::gl::glFinish();

		_updateCpuData(startingIndex + numProcessed, numLoaded, maxEdgesPerVoxel, type, sizePrefixSum);

		numProcessed += numLoaded;
	}

	_unbindBuffers();
}


void GpuOctreeEdgePropagator::_loadVoxelEdgesStartingFrom_returnNofLoaded(
	unsigned int startingVoxel, 
	unsigned int endVoxel, 
	BufferType type, 
	unsigned int& outMaxEdges, 
	std::vector<uint32_t>& sizesPrefixSum)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	
	size_t usedCapacity = 0;
	const unsigned int stopIndex = endVoxel;// startingVoxel + levelSize;
	const unsigned int remainingSize = endVoxel - startingVoxel;
	unsigned int currentIndex = startingVoxel;

	sizesPrefixSum.clear();
	sizesPrefixSum.push_back(0);

	uint8_t* indicesPtr = (uint8_t*)_indices->map(GL_WRITE_ONLY);

	outMaxEdges = 0;
	unsigned int numLoaded = 0;
	while(numLoaded<remainingSize)
	{
		const unsigned int currentIndex = startingVoxel + numLoaded;

		unsigned int maxSz;
		const auto sz = _getSyblingsBufferSizeAndMaximum(currentIndex, type, maxSz);

		if ((usedCapacity + sz * sizeof(uint32_t)) > MAX_BUFFER_SIZE_PROPAGATE)
			break;
		
		outMaxEdges = std::max(maxSz, outMaxEdges);

		for (unsigned int i = 0; i < OCTREE_NUM_CHILDREN; ++i)
		{
			auto node = _octree->getNode(currentIndex + i);
			std::vector<unsigned int>& edges = type == BufferType::POTENTIAL ? node->edgesMayCast : node->edgesAlwaysCast;
			if(!edges.empty())
				memcpy(indicesPtr + usedCapacity, edges.data(), edges.size() * sizeof(uint32_t));
			usedCapacity += edges.size()*sizeof(uint32_t);

			sizesPrefixSum.push_back(sizesPrefixSum[sizesPrefixSum.size() - 1] + edges.size());
		}

		numLoaded += OCTREE_NUM_CHILDREN;
	}

	auto numIndicesPtr = _numIndices->map(GL_WRITE_ONLY);
	memcpy(numIndicesPtr, sizesPrefixSum.data(), sizesPrefixSum.size() * sizeof(uint32_t));

	_indices->unmap();
	_numIndices->unmap();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

size_t GpuOctreeEdgePropagator::_getSyblingsBufferSizeAndMaximum(unsigned int startingID, BufferType type, unsigned int& maxSize)
{
	size_t sz = 0;
	maxSize = 0;
	for(unsigned int i=0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		auto node = _octree->getNode(startingID+i);
		std::vector<unsigned int>& edges = type == BufferType::POTENTIAL ? node->edgesMayCast : node->edgesAlwaysCast;

		sz += edges.size();
		maxSize = std::max(maxSize, (unsigned int)edges.size());
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
	for(unsigned int i = 0; i<batchSize; ++i)
	{
		auto node = _octree->getNode(startingIndex + i);
		std::vector<unsigned int>& edges = type == BufferType::POTENTIAL ? node->edgesMayCast : node->edgesAlwaysCast;
		edges.resize(numIndices[i]);

		if (numIndices[i] != 0)
			memcpy(edges.data(), indices + sizePrefixSum[i], numIndices[i]*sizeof(uint32_t));

		i += 0;
	}
	_outputIndices->unmap();


	//Process parents
	const auto nofParents = batchSize / 8;
	numIndices.resize(nofParents);

	auto pni = _parentNumIndices->map(GL_READ_ONLY);
	memcpy(numIndices.data(), pni, numIndices.size() * sizeof(uint32_t));
	_parentNumIndices->unmap();

	const unsigned int startingParent = _octree->getNodeParent(startingIndex);
	const uint32_t* parentIndices = reinterpret_cast<const uint32_t*>(_parentIndices->map(GL_READ_ONLY));

	for(unsigned int i=0; i<nofParents; ++i)
	{
		auto node = _octree->getNode(startingParent + i);
		std::vector<unsigned int>& edges = type == BufferType::POTENTIAL ? node->edgesMayCast : node->edgesAlwaysCast;
		edges.resize(numIndices[i]);

		if (numIndices[i] != 0)
			memcpy(edges.data(), parentIndices + i*maxEdgesPerVoxel, numIndices[i] * sizeof(uint32_t));

		i += 0;
	}
	/*
	{
		const unsigned int ls = ipow(OCTREE_NUM_CHILDREN, 3);
		const unsigned int st = _octree->getLevelFirstNodeID(3);
		for (unsigned int i = st; i < (st + ls); ++i)
			std::cout << _octree->getNode(i)->edgesAlwaysCast.size() << std::endl;
	}
	std::cout << "\n\n-------------------------------------------------------------------------\n";
	{
		const unsigned int ls = ipow(OCTREE_NUM_CHILDREN, 4);
		const unsigned int st = _octree->getLevelFirstNodeID(4);
		for (unsigned int i = st; i < (st + ls); ++i)
			std::cout << _octree->getNode(i)->edgesAlwaysCast.size() << std::endl;
	}
	*/
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
