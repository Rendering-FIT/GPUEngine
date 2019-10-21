#include <string>

#include "GpuOctreeLoaderCompress8.hpp"
#include "HighResolutionTimer.hpp"
#include "VoxelTestingShader.hpp"

#include <geGL/Program.h>
#include <geGL/StaticCalls.h>
#include "OmpConfig.h"

#define MAX_NOF_SUBBUFFERS 256u

#define MIN_SUBBUFFER_SIZE_UINTS 2u

//Experimentally determined
//If build crashes, this is the most probable case
#define MAX_NOF_CHUNKS 1000u
#define PARENT_INCREASED_NOF_EDGES 1.7f

bool GpuOctreeLoaderCompress8::init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, uint32_t nofEdges)
{
	assert(octree);
	assert(gpuEdges);

	_edges = gpuEdges->_edges;
	_oppositeVertices = gpuEdges->_oppositeVertices;
	_octree = octree;

	_calculateLimitsCompress(nofEdges);

	if (!_createBottomFillProgramCompress())
		return false;

	_createCompressionBuffers();

	return true;
}

#include <fstream>
bool GpuOctreeLoaderCompress8::_createBottomFillProgramCompress()
{
	//Determined by profiling
	_wgSize = 64;
	_cacheSize = 31744;

	const auto program = buildComputeShaderFillBottomLevel(_wgSize, _cacheSize, _limits.chunkSizeNofBits, _limits.maxChunksPerParent);
	/*
	std::ifstream t2("C:\\Users\\ikobrtek\\Desktop\\buildShader.glsl");
	std::string program((std::istreambuf_iterator<char>(t2)),
		std::istreambuf_iterator<char>());
	//*/
	_fillProgram = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, program));
	
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	return _fillProgram->isProgram();
}

void GpuOctreeLoaderCompress8::_createCompressionBuffers()
{
	_parentSubbuffCounter = std::make_shared<ge::gl::Buffer>();
	_chunkCounter = std::make_shared<ge::gl::Buffer>();
	_chunkDesc = std::make_shared<ge::gl::Buffer>();
	_currentChunkId = std::make_shared<ge::gl::Buffer>();
	_parentEdges = std::make_shared<ge::gl::Buffer>();
}

bool GpuOctreeLoaderCompress8::_isChunkDescValid(uint16_t desc) const
{
	const unsigned char* dptr = reinterpret_cast<const unsigned char*>(&desc);

	if (dptr[1] == 1 || dptr[1] == 0)
		return true;

	return false;
}

uint32_t GpuOctreeLoaderCompress8::_getNextChunkSize(int remainingSize, uint32_t chunkSize) const
{
	if ((remainingSize - int(chunkSize)) < 0)
		return remainingSize;

	return chunkSize;
}

void GpuOctreeLoaderCompress8::_copyChunk(const uint32_t* gpuData, uint32_t chunkStart, uint32_t* dstData, uint32_t chunkSize)
{
	memcpy(dstData, gpuData + chunkStart, chunkSize * sizeof(uint32_t));
}

void GpuOctreeLoaderCompress8::_allocateOutputBuffersCompress(unsigned voxelsPerBatch)
{
	std::cout << "Voxels per batch: " << voxelsPerBatch << std::endl;

	const uint32_t nofParents = voxelsPerBatch / OCTREE_NUM_CHILDREN;

	_voxelPotentialEdges->alloc(voxelsPerBatch * _potBufferOffset * sizeof(uint32_t));
	_voxelSilhouetteEdges->alloc(voxelsPerBatch * _silBufferOffset * sizeof(uint32_t));

	_nofPotentialEdges->alloc(voxelsPerBatch * sizeof(uint32_t));
	_nofSilhouetteEdges->alloc(voxelsPerBatch * sizeof(uint32_t));

	_voxels->alloc(voxelsPerBatch * 6 * sizeof(float));

	//TODO - potrebujem toto?
	_bufferNofPotential.resize(voxelsPerBatch);
	_bufferNofSilhouette.resize(voxelsPerBatch);

	_parentSubbuffCounter->alloc(2 * nofParents * MAX_NOF_SUBBUFFERS * sizeof(uint32_t));
	_chunkCounter->alloc(nofParents * sizeof(uint32_t));
	_chunkDesc->alloc(nofParents * MAX_NOF_CHUNKS * sizeof(uint32_t));
	_currentChunkId->alloc(nofParents * MAX_NOF_SUBBUFFERS * 2 * sizeof(uint32_t));

	const size_t chunkSizeUints = 1ull << _limits.chunkSizeNofBits;
	_parentEdges->alloc(nofParents * MAX_NOF_CHUNKS * chunkSizeUints * sizeof(uint32_t));
}

void GpuOctreeLoaderCompress8::_bindBuffersCompress()
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	uint32_t target = 0;

	_edges->bindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_voxels->bindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_voxelPotentialEdges->bindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_voxelSilhouetteEdges->bindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_nofPotentialEdges->bindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_nofSilhouetteEdges->bindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_atomicCounter->bindBase(GL_SHADER_STORAGE_BUFFER, target++);

	_parentSubbuffCounter->bindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_chunkCounter->bindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_chunkDesc->bindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_currentChunkId->bindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_parentEdges->bindBase(GL_SHADER_STORAGE_BUFFER, target++);

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeLoaderCompress8::_unbindBuffersCompress()
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	uint32_t target = 0;

	_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_oppositeVertices->unbindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_voxels->unbindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_voxelPotentialEdges->unbindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_voxelSilhouetteEdges->unbindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_nofPotentialEdges->unbindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_nofSilhouetteEdges->unbindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_atomicCounter->unbindBase(GL_SHADER_STORAGE_BUFFER, target++);

	_parentSubbuffCounter->unbindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_chunkCounter->unbindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_chunkDesc->unbindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_currentChunkId->unbindBase(GL_SHADER_STORAGE_BUFFER, target++);
	_parentEdges->unbindBase(GL_SHADER_STORAGE_BUFFER, target++);

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeLoaderCompress8::_clearCompressionBuffers()
{
	//Init necessary buffers with zeros
	_parentSubbuffCounter->clear(GL_R32UI, GL_RED, GL_UNSIGNED_INT, nullptr);
	_chunkCounter->clear(GL_R32UI, GL_RED, GL_UNSIGNED_INT, nullptr);
}

uint32_t GpuOctreeLoaderCompress8::_findNearestHigherPow2(uint32_t v) const
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;

	return v;
}

void GpuOctreeLoaderCompress8::_calculateLimitsCompress(uint32_t nofEdges)
{
	const int maxEdgesSubbuffer = std::max(MIN_SUBBUFFER_SIZE_UINTS, _findNearestHigherPow2(uint32_t(ceilf(PARENT_INCREASED_NOF_EDGES*float(nofEdges) / float(MAX_NOF_CHUNKS)))));
	//FFS https://www.geeksforgeeks.org/position-of-rightmost-set-bit/
	_limits.chunkSizeNofBits = static_cast<uint32_t>(log2f(float(maxEdgesSubbuffer & -maxEdgesSubbuffer)));
	_limits.maxChunksPerParent = MAX_NOF_CHUNKS;
}

void GpuOctreeLoaderCompress8::addEdgesOnLowestLevel(AdjacencyType edges)
{
	int const deepestLevel = _octree->getDeepestLevel();
	int const deepestLevelSize = ipow(OCTREE_NUM_CHILDREN, deepestLevel);
	int const startingNodeIndex = _octree->getLevelFirstNodeID(deepestLevel);
	uint32_t const nofEdges = uint32_t(edges->getNofEdges());

	_calculateLowestLevelBufferOffsets(nofEdges);

	auto const maxOffset = std::max(_potBufferOffset, _silBufferOffset);
	auto const allocatedSizeEdgeIndices = std::min(size_t(_maxBufferSizeBytes), size_t(deepestLevelSize) * size_t(maxOffset) * sizeof(uint32_t));

	std::vector<glm::vec3> voxels;
	_serializeDeepestLevelVoxels(voxels);

	uint32_t voxelBatchSize = uint32_t(allocatedSizeEdgeIndices / (maxOffset * sizeof(uint32_t)));
	voxelBatchSize = voxelBatchSize - (voxelBatchSize % OCTREE_NUM_CHILDREN);
	const uint32_t numBatches = (uint32_t)(ceil(float(deepestLevelSize) / float(voxelBatchSize)));

	_allocateOutputBuffersCompress(voxelBatchSize);

	_bindBuffersCompress();
	_fillProgram->use();
	_fillProgram->set1ui("nofEdges", nofEdges);
	_fillProgram->set1ui("potBufferOffset", _potBufferOffset);
	_fillProgram->set1ui("silBufferOffset", _silBufferOffset);

	std::cout << "Num batches: " << numBatches << "\n";
	HighResolutionTimer t;

	for (uint32_t i = 0; i<numBatches; ++i)
	{
		uint32_t const batchSize = uint32_t(std::min(voxelBatchSize, deepestLevelSize - (i*voxelBatchSize)));

		std::cout << "Batch " << i << " size " << batchSize << std::endl;

		_loadVoxels(voxels, i*voxelBatchSize, batchSize);
		_clearAtomicCounter();
		_clearCompressionBuffers();

		_fillProgram->set1ui("nofVoxels", batchSize);
		t.reset();
		ge::gl::glDispatchCompute(uint32_t(ceil(float(batchSize) / float(_wgSize))), 1, 1);
		ge::gl::glFinish();
		std::cout << "GPU Load: " << std::to_string(t.getElapsedTimeFromLastQuerySeconds()) << std::endl;

		_acquireGpuDataCompress(startingNodeIndex + i*voxelBatchSize, batchSize);
	}

	_unbindBuffersCompress();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeLoaderCompress8::_acquireGpuDataCompress(uint32_t startingVoxelAbsoluteIndex, uint32_t batchSize)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	const uint32_t numParents = batchSize / OCTREE_NUM_CHILDREN;

	_copyBuffer(_nofPotentialEdges, _bufferNofPotential.data(), batchSize * sizeof(uint32_t));
	_copyBuffer(_nofSilhouetteEdges, _bufferNofSilhouette.data(), batchSize * sizeof(uint32_t));

	//--POTENTIAL--
	//Do in sequence so the driver does not have to copy all the buffers to CPU at once
	const uint32_t* bPotential = reinterpret_cast<uint32_t*>(_voxelPotentialEdges->map(GL_READ_ONLY));
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	for (uint32_t i = 0; i<batchSize; ++i)
	{
		auto node = _octree->getNode(startingVoxelAbsoluteIndex + i);

		node->edgesMayCastMap[BitmaskAllSet].resize(_bufferNofPotential[i]);
		if (!node->edgesMayCastMap[BitmaskAllSet].empty())
			memcpy(node->edgesMayCastMap[BitmaskAllSet].data(), bPotential + (_potBufferOffset*i), _bufferNofPotential[i] * sizeof(uint32_t));
	}
	_voxelPotentialEdges->unmap();

	//--SILHOUETTE--
	const uint32_t* bSilhouette = reinterpret_cast<uint32_t*>(_voxelSilhouetteEdges->map(GL_READ_ONLY));
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	for (uint32_t i = 0; i<batchSize; ++i)
	{
		auto node = _octree->getNode(startingVoxelAbsoluteIndex + i);

		node->edgesAlwaysCastMap[BitmaskAllSet].resize(_bufferNofSilhouette[i]);
		if (!node->edgesAlwaysCastMap[BitmaskAllSet].empty())
			memcpy(node->edgesAlwaysCastMap[BitmaskAllSet].data(), bSilhouette + (_silBufferOffset*i), _bufferNofSilhouette[i] * sizeof(uint32_t));
	}
	_voxelSilhouetteEdges->unmap();

	//Parents with compression
	const uint32_t startingParent = _octree->getNodeParent(startingVoxelAbsoluteIndex);

	const uint32_t* parentData = reinterpret_cast<uint32_t*>(_parentEdges->map(GL_READ_ONLY));

	const uint32_t* chunkDescriptors = reinterpret_cast<uint32_t*>(_chunkDesc->map(GL_READ_ONLY));
	const uint32_t* edgeCounters = reinterpret_cast<uint32_t*>(_parentSubbuffCounter->map(GL_READ_ONLY));
	
	std::vector<uint32_t> nofChunksVec;
	nofChunksVec.resize(numParents);
	_chunkCounter->getData(nofChunksVec.data(), nofChunksVec.size() * sizeof(uint32_t));

#ifdef _DEBUG
	//std::ofstream str;
	//str.open("NumDump.txt");

	for (uint32_t q = 0; q<nofChunksVec.size(); ++q)
	{
		assert(nofChunksVec[q] <= _limits.maxChunksPerParent);
		//str << nofChunksVec[q] << std::endl;
	}
	//str.close();
#endif

	#pragma omp parallel for 
	for (int currentParent = 0; currentParent < int(numParents); ++currentParent)
	{
		//Get chunk descriptors and process them
		std::vector< std::vector<uint32_t> > chunkDescs[2];
		chunkDescs[0].resize(MAX_NOF_SUBBUFFERS);
		chunkDescs[1].resize(MAX_NOF_SUBBUFFERS);

		const uint32_t startingDesc = currentParent*MAX_NOF_CHUNKS;
		const uint32_t stopDesc = startingDesc + nofChunksVec[currentParent];
		for (uint32_t currentDesc = startingDesc; currentDesc < stopDesc; ++currentDesc)
		{
			const auto desc = chunkDescriptors[currentDesc];
			const unsigned char* dptr = reinterpret_cast<const unsigned char*>(&desc);

			chunkDescs[dptr[1]][dptr[0]].push_back(currentDesc - startingDesc);
		}

		const uint32_t chunkSize = 1 << _limits.chunkSizeNofBits;
		auto node = _octree->getNode(startingParent + currentParent);

		//--Silhouette
		for (uint32_t i = 0; i<MAX_NOF_SUBBUFFERS; ++i)
		{
			const auto& chunks = chunkDescs[1][i];
			if (chunks.size())
			{
				const auto nofEdges = edgeCounters[2 * (currentParent * MAX_NOF_SUBBUFFERS + i) + 1];
				const auto nofChunks = uint32_t(ceilf(float(nofEdges) / float(1 << _limits.chunkSizeNofBits)));

				assert(nofChunks == chunks.size());

				node->edgesAlwaysCastMap[BitmaskType(i)].resize(nofEdges);

				int remainingSize = nofEdges;
				for (uint32_t chunkNum = 0; chunkNum < nofChunks; ++chunkNum)
				{
					const auto chunk = chunks[chunkNum];
					const auto sz = _getNextChunkSize(remainingSize, chunkSize); //the last chunk might be less than chunkSize
					remainingSize -= sz;

					_copyChunk(parentData, currentParent * MAX_NOF_CHUNKS * chunkSize + chunkSize*chunk, node->edgesAlwaysCastMap[BitmaskType(i)].data() + chunkNum*chunkSize, sz);
				}
			}
		}

		//Copy data from subbuffers to octree
		//--potential
		for (uint32_t i = 0; i<MAX_NOF_SUBBUFFERS; ++i)
		{
			const auto& chunks = chunkDescs[0][i];
			if (chunks.size())
			{
				const auto nofEdges = edgeCounters[2 * (currentParent * MAX_NOF_SUBBUFFERS + i) + 0];
				const uint32_t nofChunks = uint32_t(ceilf(float(nofEdges) / float(1 << _limits.chunkSizeNofBits)));

				assert(nofChunks == chunks.size());

				node->edgesMayCastMap[BitmaskType(i)].resize(nofEdges);

				int remainingSize = nofEdges;
				for (uint32_t chunkNum = 0; chunkNum < nofChunks; ++chunkNum)
				{
					const auto chunk = chunks[chunkNum];
					const auto sz = _getNextChunkSize(remainingSize, chunkSize); //the last chunk might be less than chunkSize
					remainingSize -= sz;

					_copyChunk(parentData, currentParent * MAX_NOF_CHUNKS * chunkSize + chunkSize*chunk, node->edgesMayCastMap[BitmaskType(i)].data() + chunkNum*chunkSize, sz);
				}
			}
		}
	}

	_chunkDesc->unmap();
	_parentSubbuffCounter->unmap();
	_parentEdges->unmap();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

/*
void GpuOctreeLoaderCompress8::_acquireGpuDataCompress(uint32_t startingVoxelAbsoluteIndex, uint32_t batchSize)
{
	HighResolutionTimer timer;
	timer.reset();
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	const uint32_t numParents = batchSize / OCTREE_NUM_CHILDREN;

	_copyBuffer(_nofPotentialEdges, _bufferNofPotential.data(), batchSize * sizeof(uint32_t));
	_copyBuffer(_nofSilhouetteEdges, _bufferNofSilhouette.data(), batchSize * sizeof(uint32_t));

	//POT & SIL edges
	const uint32_t* bPotential = reinterpret_cast<uint32_t*>(_voxelPotentialEdges->map(GL_READ_ONLY));
	const uint32_t* bSilhouette = reinterpret_cast<uint32_t*>(_voxelSilhouetteEdges->map(GL_READ_ONLY));
	assert(ge::gl::glGetError() == GL_NO_ERROR);

#pragma omp parallel for 
	for (int i = 0; i<batchSize; ++i)
	{
		auto node = _octree->getNode(startingVoxelAbsoluteIndex + i);

		node->edgesMayCastMap[BitmaskAllSet].resize(_bufferNofPotential[i]);
		if (!node->edgesMayCastMap[BitmaskAllSet].empty())
			memcpy(node->edgesMayCastMap[BitmaskAllSet].data(), bPotential + (_potBufferOffset*i), _bufferNofPotential[i] * sizeof(uint32_t));

		node->edgesAlwaysCastMap[BitmaskAllSet].resize(_bufferNofSilhouette[i]);
		if (!node->edgesAlwaysCastMap[BitmaskAllSet].empty())
			memcpy(node->edgesAlwaysCastMap[BitmaskAllSet].data(), bSilhouette + (_silBufferOffset*i), _bufferNofSilhouette[i] * sizeof(uint32_t));
	}
	_voxelPotentialEdges->unmap();
	_voxelSilhouetteEdges->unmap();

	//Parents with compression
	const uint32_t startingParent = _octree->getNodeParent(startingVoxelAbsoluteIndex);

	const uint32_t* chunkDescriptors = reinterpret_cast<uint32_t*>(_chunkDesc->map(GL_READ_ONLY));
	const uint32_t* edgeCounters = reinterpret_cast<uint32_t*>(_parentSubbuffCounter->map(GL_READ_ONLY));
	const uint32_t* parentData = reinterpret_cast<uint32_t*>(_parentEdges->map(GL_READ_ONLY));

	std::vector<uint32_t> nofChunksVec;
	nofChunksVec.resize(numParents);
	_chunkCounter->getData(nofChunksVec.data(), nofChunksVec.size() * sizeof(uint32_t));

#ifdef _DEBUG
	for (uint32_t q = 0; q<nofChunksVec.size(); ++q)
	{
		assert(nofChunksVec[q] <= _limits.maxChunksPerParent);
	}
#endif

#pragma omp parallel for 
	for (int currentParent = 0; currentParent < int(numParents); ++currentParent)
	{
		//Get chunk descriptors and process them
		std::vector< std::vector<uint32_t> > chunkDescs[2];
		chunkDescs[0].resize(MAX_NOF_SUBBUFFERS);
		chunkDescs[1].resize(MAX_NOF_SUBBUFFERS);

		const uint32_t startingDesc = currentParent*MAX_NOF_CHUNKS;
		const uint32_t stopDesc = startingDesc + nofChunksVec[currentParent];
		for (uint32_t currentDesc = startingDesc; currentDesc < stopDesc; ++currentDesc)
		{
			const auto desc = chunkDescriptors[currentDesc];
			const unsigned char* dptr = reinterpret_cast<const unsigned char*>(&desc);

			chunkDescs[dptr[1]][dptr[0]].push_back(currentDesc - startingDesc);
		}

		const uint32_t chunkSize = 1 << _limits.chunkSizeNofBits;
		auto node = _octree->getNode(startingParent + currentParent);

		//--Silhouette
		for (uint32_t i = 0; i<MAX_NOF_SUBBUFFERS; ++i)
		{
			const auto& chunks = chunkDescs[1][i];
			if (chunks.size())
			{
				const auto nofEdges = edgeCounters[2 * (currentParent * MAX_NOF_SUBBUFFERS + i) + 1];
				const auto nofChunks = uint32_t(ceilf(float(nofEdges) / (1 << _limits.chunkSizeNofBits)));

				assert(nofChunks == chunks.size());

				node->edgesAlwaysCastMap[i].resize(nofEdges);

				int remainingSize = nofEdges;
				for (uint32_t chunkNum = 0; chunkNum < nofChunks; ++chunkNum)
				{
					const auto chunk = chunks[chunkNum];
					const auto sz = _getNextChunkSize(remainingSize, chunkSize); //the last chunk might be less than chunkSize
					remainingSize -= sz;

					_copyChunk(parentData, currentParent * MAX_NOF_CHUNKS * chunkSize + chunkSize*chunk, node->edgesAlwaysCastMap[i].data() + chunkNum*chunkSize, sz);
				}
			}
		}

		//Copy data from subbuffers to octree
		//--potential
		for (uint32_t i = 0; i<MAX_NOF_SUBBUFFERS; ++i)
		{
			const auto& chunks = chunkDescs[0][i];
			if (chunks.size())
			{
				const auto nofEdges = edgeCounters[2 * (currentParent * MAX_NOF_SUBBUFFERS + i) + 0];
				const uint32_t nofChunks = uint32_t(ceilf(float(nofEdges) / (1 << _limits.chunkSizeNofBits)));

				assert(nofChunks == chunks.size());

				node->edgesMayCastMap[i].resize(nofEdges);

				int remainingSize = nofEdges;
				for (uint32_t chunkNum = 0; chunkNum < nofChunks; ++chunkNum)
				{
					const auto chunk = chunks[chunkNum];
					const auto sz = _getNextChunkSize(remainingSize, chunkSize); //the last chunk might be less than chunkSize
					remainingSize -= sz;

					_copyChunk(parentData, currentParent * MAX_NOF_CHUNKS * chunkSize + chunkSize*chunk, node->edgesMayCastMap[i].data() + chunkNum*chunkSize, sz);
				}
			}
		}
	}

	_chunkDesc->unmap();
	_parentSubbuffCounter->unmap();
	_parentEdges->unmap();

	std::cout << "CPU Process: " << std::to_string(timer.getElapsedTimeSeconds()) << std::endl;

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}
*/

#include <iostream>
#include <fstream>

void GpuOctreeLoaderCompress8::profile(AdjacencyType edges)
{
	std::vector<glm::vec3> voxels;
	_serializeDeepestLevelVoxels(voxels);

	uint32_t const nofEdges = uint32_t(edges->getNofEdges());
	int const deepestLevel = _octree->getDeepestLevel();
	int const deepestLevelSize = ipow(OCTREE_NUM_CHILDREN, deepestLevel);

	uint32_t const wgSizeStart = 64;
	uint32_t const wgSizeLimit = 1024;

	uint32_t const cacheSizeStart = 1024;
	uint32_t const cacheSizeStep = 1024;
	uint32_t const cacheSizeLimit = 32768;

	uint32_t const bottomTestRepetitions = 3;

	HighResolutionTimer timer;

	_calculateLowestLevelBufferOffsets(nofEdges);

	const auto allocatedSizeEdgeIndices = std::min(size_t(_maxBufferSizeBytes), size_t(deepestLevelSize) * size_t(_potBufferOffset) * sizeof(uint32_t));

	//_potBufferOffset because there will be always more pot edges
	uint32_t voxelBatchSize = uint32_t(allocatedSizeEdgeIndices / (_potBufferOffset * sizeof(uint32_t)));
	voxelBatchSize = voxelBatchSize - (voxelBatchSize % OCTREE_NUM_CHILDREN);
	const uint32_t numBatches = (uint32_t)(ceil(float(deepestLevelSize) / float(voxelBatchSize)));

	_allocateOutputBuffersCompress(voxelBatchSize);

	_bindBuffersCompress();
	_fillProgram->use();
	_fillProgram->set1ui("nofEdges", nofEdges);
	_fillProgram->set1ui("potBufferOffset", _potBufferOffset);
	_fillProgram->set1ui("silBufferOffset", _silBufferOffset);

	for (uint32_t wgSize = wgSizeStart; wgSize <= wgSizeLimit; wgSize *= 2)
	{
		for (uint32_t cacheSize = cacheSizeStart; cacheSize <= cacheSizeLimit; cacheSize += cacheSizeStep)
		{
			_fillProgram.reset();
			_fillProgram = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, buildComputeShaderFillBottomLevel(wgSize, cacheSize, _limits.chunkSizeNofBits, _limits.maxChunksPerParent)));

			_fillProgram->use();
			_fillProgram->set1ui("nofEdges", uint32_t(nofEdges));
			_fillProgram->set1ui("potBufferOffset", _potBufferOffset);
			_fillProgram->set1ui("silBufferOffset", _silBufferOffset);

			_bindBuffersCompress();

			double time = 0;

			for (uint32_t test = 0; test<bottomTestRepetitions; ++test)
			{
				timer.reset();

				std::cout << "Round " << test << std::endl;

				for (uint32_t batch = 0; batch < numBatches; ++batch)
				{
					uint32_t const batchSize = uint32_t(std::min(voxelBatchSize, deepestLevelSize - (batch*voxelBatchSize)));
					_loadVoxels(voxels, batch*voxelBatchSize, batchSize);
					_clearAtomicCounter();
					_clearCompressionBuffers();
					_fillProgram->set1ui("nofVoxels", unsigned(batchSize));

					ge::gl::glDispatchCompute(uint32_t(ceil(float(batchSize) / float(_wgSize))), 1, 1);
					ge::gl::glFinish();
				}

				time += timer.getElapsedTimeFromLastQuerySeconds();
			}

			time /= bottomTestRepetitions;

			std::string msg;
			msg = std::to_string(wgSize) + " " + std::to_string(cacheSize) + " " + std::to_string(time) + "\n";
			std::cout << msg;
			std::ofstream file;
			file.open("testResults.txt", std::ios_base::app);
			file << msg;
			file.close();
		}
	}

	exit(0);
}