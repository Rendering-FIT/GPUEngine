#include <omp.h>
#include <string>

#include "GpuOctreeLoaderCompress8.hpp"
#include "HighResolutionTimer.hpp"
#include "VoxelTestingShader.hpp"

#include <geGL/Program.h>
#include "geGL/StaticCalls.h"

bool GpuOctreeLoaderCompress8::init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, unsigned int nofEdges)
{
	assert(octree);
	assert(gpuEdges);

	_edges = gpuEdges->_edges;
	_oppositeVertices = gpuEdges->_oppositeVertices;
	_octree = octree;

	_calculateLimitsCompress(nofEdges);

	if (!_createBottomFillProgramCompress(nofEdges))
		return false;

	_createCompressionBuffers();

	return true;
}

bool GpuOctreeLoaderCompress8::_createBottomFillProgramCompress(unsigned int nofEdges)
{
	_wgSize = 64;
	_cacheSize = 31744;

	const auto program = buildComputeShaderFillBottomLevel(_wgSize, _cacheSize, _limits.chunkSizeNofBits, _limits.maxChunksPerParent);
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

unsigned int GpuOctreeLoaderCompress8::_getNextChunkSize(int remainingSize, unsigned int chunkSize) const
{
	if ((remainingSize - int(chunkSize)) < 0)
		return remainingSize;

	return chunkSize;
}

void GpuOctreeLoaderCompress8::_copyChunk(const uint32_t* gpuData, uint32_t chunkStart, uint32_t* dstData, uint32_t chunkSize)
{
	memcpy(dstData, gpuData + chunkStart, chunkSize * sizeof(uint32_t));
}

void GpuOctreeLoaderCompress8::_allocateOutputBuffersCompress(unsigned voxelsPerBatch, unsigned nofEdges)
{
	std::cout << "Voxels per batch: " << voxelsPerBatch << std::endl;

	const unsigned int nofParents = voxelsPerBatch / OCTREE_NUM_CHILDREN;

	//TODO - sem mozne dat reduction factor - treba do shadera dat offsety
	//Potom treba do shaderov spravne offsety (= velkosti na jeden voxel)
	_voxelPotentialEdges->alloc(voxelsPerBatch * nofEdges * sizeof(uint32_t));
	_voxelSilhouetteEdges->alloc(voxelsPerBatch * nofEdges * sizeof(uint32_t));

	_nofPotentialEdges->alloc(voxelsPerBatch * sizeof(uint32_t));
	_nofSilhouetteEdges->alloc(voxelsPerBatch * sizeof(uint32_t));

	_voxels->alloc(voxelsPerBatch * 6 * sizeof(float));

	//TODO - potrebujem toto?
	_bufferNofPotential.resize(voxelsPerBatch);
	_bufferNofSilhouette.resize(voxelsPerBatch);

	_parentSubbuffCounter->alloc(2 * nofParents * MAX_NOF_SUBBUFFERS * sizeof(uint32_t));
	_chunkCounter->alloc(nofParents * sizeof(uint32_t));
	_chunkDesc->alloc(nofParents * MAX_NOF_CHUNKS * sizeof(uint16_t));
	_currentChunkId->alloc(nofParents * MAX_NOF_SUBBUFFERS * 2 * sizeof(uint16_t));

	const size_t chunkSizeUints = 1 << _limits.chunkSizeNofBits;
	_parentEdges->alloc(nofParents * MAX_NOF_CHUNKS * chunkSizeUints * sizeof(uint32_t));
}

void GpuOctreeLoaderCompress8::_bindBuffersCompress()
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	unsigned int target = 0;

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
	unsigned int target = 0;

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

	const uint16_t val = -1;
	_chunkDesc->clear(GL_R16UI, GL_RED, GL_UNSIGNED_SHORT, &val);
}

unsigned int GpuOctreeLoaderCompress8::_findNearestHigherPow2(unsigned int v) const
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

void GpuOctreeLoaderCompress8::_calculateLimitsCompress(unsigned int nofEdges)
{
	const int maxEdgesSubbuffer = std::max(MIN_SUBBUFFER_SIZE_UINTS, _findNearestHigherPow2(unsigned int(ceilf(nofEdges / float(MAX_NOF_CHUNKS)))));
	//FFS https://www.geeksforgeeks.org/position-of-rightmost-set-bit/
	_limits.chunkSizeNofBits = log2(maxEdgesSubbuffer & -maxEdgesSubbuffer);
	_limits.maxChunksPerParent = MAX_NOF_CHUNKS; // *0.8
}

void GpuOctreeLoaderCompress8::addEdgesOnLowestLevel(AdjacencyType edges)
{
	const int deepestLevel = _octree->getDeepestLevel();
	const int deepestLevelSize = ipow(OCTREE_NUM_CHILDREN, deepestLevel);
	const int startingNodeIndex = _octree->getLevelFirstNodeID(deepestLevel);
	const auto nofEdges = edges->getNofEdges();

	const auto allocatedSizeEdgeIndices = std::min(size_t(MAX_BUFFER_SIZE), size_t(deepestLevelSize) * size_t(nofEdges) * sizeof(uint32_t));

	std::vector<glm::vec3> voxels;
	_serializeDeepestLevelVoxels(voxels);

	//TODO - sem zohladnit statistiku a prepocitat spotrebu pamate
	//V childoch toho uz vela neostava
	//Inteligentnejsie pouzivam pamat teraz, viac ide do parentov
	auto voxelBatchSize = allocatedSizeEdgeIndices / (nofEdges * sizeof(uint32_t));
	voxelBatchSize = voxelBatchSize - (voxelBatchSize % OCTREE_NUM_CHILDREN);
	const unsigned int numBatches = (unsigned int)(ceil(float(deepestLevelSize) / voxelBatchSize));

	_allocateOutputBuffersCompress(voxelBatchSize, nofEdges);

	_bindBuffersCompress();
	_fillProgram->use();
	_fillProgram->set1ui("nofEdges", nofEdges);

	std::cout << "Num batches: " << numBatches << "\n";
	HighResolutionTimer t;

	const auto nofF = _octree->getTotalNumNodes();

	for (unsigned int i = 0; i<numBatches; ++i)
	{
		const auto batchSize = std::min(voxelBatchSize, deepestLevelSize - (i*voxelBatchSize));

		std::cout << "Batch " << i << " size " << batchSize << std::endl;

		_loadVoxels(voxels, i*voxelBatchSize, batchSize);
		_clearAtomicCounter();
		_clearCompressionBuffers();

		_fillProgram->set1ui("nofVoxels", batchSize);
		
		t.reset();
		ge::gl::glDispatchCompute(unsigned int(ceil(float(batchSize) / _wgSize)), 1, 1);
		ge::gl::glFinish();
		std::cout << "GPU Load: " << std::to_string(t.getElapsedTimeFromLastQuerySeconds()) << std::endl;

		_acquireGpuDataCompress(startingNodeIndex + i*voxelBatchSize, batchSize, nofEdges);
	}

	_unbindBuffersCompress();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeLoaderCompress8::_acquireGpuDataCompress(unsigned int startingVoxelAbsoluteIndex, unsigned int batchSize, unsigned int numEdges)
{
	HighResolutionTimer timer;
	timer.reset();
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	const unsigned int numParents = batchSize / OCTREE_NUM_CHILDREN;

	_copyBuffer(_nofPotentialEdges, _bufferNofPotential.data(), batchSize * sizeof(uint32_t));
	_copyBuffer(_nofSilhouetteEdges, _bufferNofSilhouette.data(), batchSize * sizeof(uint32_t));

	//--POTENTIAL--
	//Do in sequence so the driver does not have to copy all the buffers to CPU at once
	const uint32_t* bPotential = reinterpret_cast<uint32_t*>(_voxelPotentialEdges->map(GL_READ_ONLY));
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	for (unsigned int i = 0; i<batchSize; ++i)
	{
		auto node = _octree->getNode(startingVoxelAbsoluteIndex + i);

		node->edgesMayCastMap[BitmaskAllSet].resize(_bufferNofPotential[i]);
		if (!node->edgesMayCastMap[BitmaskAllSet].empty())
			memcpy(node->edgesMayCastMap[BitmaskAllSet].data(), bPotential + (numEdges*i), _bufferNofPotential[i] * sizeof(uint32_t));
	}
	_voxelPotentialEdges->unmap();

	//--SILHOUETTE--
	const uint32_t* bSilhouette = reinterpret_cast<uint32_t*>(_voxelSilhouetteEdges->map(GL_READ_ONLY));
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	for (unsigned int i = 0; i<batchSize; ++i)
	{
		auto node = _octree->getNode(startingVoxelAbsoluteIndex + i);

		node->edgesAlwaysCastMap[BitmaskAllSet].resize(_bufferNofSilhouette[i]);
		if (!node->edgesAlwaysCastMap[BitmaskAllSet].empty())
			memcpy(node->edgesAlwaysCastMap[BitmaskAllSet].data(), bSilhouette + (numEdges*i), _bufferNofSilhouette[i] * sizeof(uint32_t));
	}
	_voxelSilhouetteEdges->unmap();

	//Parents with compression
	const unsigned int startingParent = _octree->getNodeParent(startingVoxelAbsoluteIndex);

	const uint16_t* chunkDescriptors = reinterpret_cast<uint16_t*>(_chunkDesc->map(GL_READ_ONLY));
	const uint32_t* edgeCounters = reinterpret_cast<uint32_t*>(_parentSubbuffCounter->map(GL_READ_ONLY));
	const uint32_t* parentData = reinterpret_cast<uint32_t*>(_parentEdges->map(GL_READ_ONLY));
	
	std::vector<unsigned int> nofChunks;
	nofChunks.resize(numParents);
	_chunkCounter->getData(nofChunks.data(), nofChunks.size() * sizeof(uint32_t));

#pragma omp parallel for
	for (int currentParent = 0; currentParent < numParents; ++currentParent)
	{
		//Get chunk descriptors and process them
		std::vector< std::vector<unsigned int> > chunkDescs[2];
		chunkDescs[0].resize(MAX_NOF_SUBBUFFERS);
		chunkDescs[1].resize(MAX_NOF_SUBBUFFERS);

		const unsigned int startingDesc = currentParent*MAX_NOF_CHUNKS;
		const unsigned int stopDesc = startingDesc + nofChunks[currentParent];
		for (unsigned int currentDesc = startingDesc; currentDesc < stopDesc; ++currentDesc)
		{
			const auto desc = chunkDescriptors[currentDesc];
			const unsigned char* dptr = reinterpret_cast<const unsigned char*>(&desc);

			//if (_isChunkDescValid(desc))
			//{
				chunkDescs[dptr[1]][dptr[0]].push_back(currentDesc - startingDesc);
			//}
		}

		const unsigned int chunkSize = 1 << _limits.chunkSizeNofBits;
		auto node = _octree->getNode(startingParent + currentParent);

		//--Silhouette
		for (unsigned int i = 0; i<MAX_NOF_SUBBUFFERS; ++i)
		{
			const auto& chunks = chunkDescs[1][i];
			if (chunks.size())
			{
				const auto nofEdges = edgeCounters[2 * (currentParent * MAX_NOF_SUBBUFFERS + i) + 1];
				const auto nofChunks = unsigned int(ceilf(float(nofEdges) / (1 << _limits.chunkSizeNofBits)));

				assert(nofChunks == chunks.size());

				node->edgesAlwaysCastMap[i].resize(nofEdges);

				int remainingSize = nofEdges;
				for (unsigned int chunkNum = 0; chunkNum < nofChunks; ++chunkNum)
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
		for (unsigned int i = 0; i<MAX_NOF_SUBBUFFERS; ++i)
		{
			const auto& chunks = chunkDescs[0][i];
			if (chunks.size())
			{
				const auto nofEdges = edgeCounters[2 * (currentParent * MAX_NOF_SUBBUFFERS + i) + 0];
				const unsigned int nofChunks = unsigned int(ceilf(float(nofEdges) / (1 << _limits.chunkSizeNofBits)));

				assert(nofChunks == chunks.size());

				node->edgesMayCastMap[i].resize(nofEdges);

				int remainingSize = nofEdges;
				for (unsigned int chunkNum = 0; chunkNum < nofChunks; ++chunkNum)
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

	std::cout << "CPU Process: " << std::to_string(timer.getElapsedTimeFromLastQuerySeconds()) << std::endl;

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

#include <iostream>
#include <fstream>
void GpuOctreeLoaderCompress8::profile(AdjacencyType edges)
{
	std::vector<glm::vec3> voxels;
	_serializeDeepestLevelVoxels(voxels);

	const auto nofEdges = edges->getNofEdges();
	const int deepestLevel = _octree->getDeepestLevel();
	const int deepestLevelSize = ipow(OCTREE_NUM_CHILDREN, deepestLevel);
	const int deepestLevelSizeAndParents = (9 * deepestLevelSize) / 8;

	const unsigned int wgSizeStart = 64;
	const unsigned int wgSizeLimit = 1024;

	const unsigned int cacheSizeStart = 1024;
	const unsigned int cacheSizeStep = 1024;
	const unsigned int cacheSizeLimit = 32768;

	const unsigned int bottomTestRepetitions = 3;

	HighResolutionTimer timer;

	const size_t bufferSize = MAX_BUFFER_SIZE;
	const auto allocatedSizeEdgeIndices = std::min(bufferSize, size_t(deepestLevelSizeAndParents) * size_t(nofEdges) * sizeof(uint32_t));
	auto voxelBatchSize = (8 * allocatedSizeEdgeIndices) / (9 * nofEdges * sizeof(uint32_t));
	voxelBatchSize = voxelBatchSize - (voxelBatchSize % 8);
	const unsigned int numBatches = (unsigned int)(ceil(float(deepestLevelSize) / voxelBatchSize));

	const auto nofVoxelsWithParents = (voxelBatchSize * 9) / 8;

	_voxelPotentialEdges.reset();
	_voxelSilhouetteEdges.reset();
	_nofPotentialEdges.reset();
	_nofSilhouetteEdges.reset();
	_voxels.reset();

	_voxelPotentialEdges = std::make_shared<ge::gl::Buffer>(nofVoxelsWithParents * nofEdges * sizeof(uint32_t));
	_voxelSilhouetteEdges = std::make_shared<ge::gl::Buffer>(nofVoxelsWithParents * nofEdges * sizeof(uint32_t));
	_nofPotentialEdges = std::make_shared<ge::gl::Buffer>(nofVoxelsWithParents * sizeof(uint32_t));
	_nofSilhouetteEdges = std::make_shared<ge::gl::Buffer>(nofVoxelsWithParents * sizeof(uint32_t));
	_voxels = std::make_shared<ge::gl::Buffer>(voxelBatchSize * 6 * sizeof(float));

	for (unsigned int wgSize = wgSizeStart; wgSize <= wgSizeLimit; wgSize *= 2)
	{
		for (unsigned int cacheSize = cacheSizeStart; cacheSize <= cacheSizeLimit; cacheSize += cacheSizeStep)
		{
			_fillProgram.reset();
			_fillProgram = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, buildComputeShaderFillBottomLevel(wgSize, cacheSize, 0, 0)));

			_fillProgram->use();
			_fillProgram->set1ui("nofEdges", nofEdges);

			_bindBuffersCompress();

			double time = 0;

			for (unsigned int test = 0; test<bottomTestRepetitions; ++test)
			{
				timer.reset();

				std::cout << "Round " << test << std::endl;

				for (unsigned int batch = 0; batch < numBatches; ++batch)
				{
					const auto batchSize = std::min(voxelBatchSize, deepestLevelSize - (batch*voxelBatchSize));
					_loadVoxels(voxels, batch*voxelBatchSize, batchSize);
					_clearAtomicCounter();
					_fillProgram->set1ui("nofVoxels", unsigned(batchSize));

					ge::gl::glDispatchCompute((65536 / wgSize) * 14, 1, 1);
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