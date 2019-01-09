#include "GpuOctreeLoader.hpp"
#include "HighResolutionTimer.hpp"
#include "VoxelTestingShader.hpp"

#include <geGL/StaticCalls.h>
#include "MultiplicityCoding.hpp"

#include <iostream>
#include <fstream>

bool GpuOctreeLoader::init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, unsigned int subgroupSize, unsigned int nofEdges)
{
	assert(octree);
	assert(gpuEdges);

	_edges = gpuEdges->_edges;
	_oppositeVertices = gpuEdges->_oppositeVertices;

	_octree = octree;
#ifdef USE_COMPRESS
	_calculateLimitsCompress(nofEdges);
#endif
	if (!_createBottomFillProgram(4, subgroupSize, 4096))
		return false;

	_createBuffers();

	return true;
}

void GpuOctreeLoader::profile(AdjacencyType edges, unsigned int subgroupSize)
{
	//_loadEdges(edges);

	std::vector<glm::vec3> voxels;
	_serializeDeepestLevelVoxels(voxels);

	const auto nofEdges = edges->getNofEdges();
	const int deepestLevel = _octree->getDeepestLevel();
	const int deepestLevelSize = ipow(OCTREE_NUM_CHILDREN, deepestLevel);
	const int deepestLevelSizeAndParents = (9 * deepestLevelSize) / 8;

	//const size_t bufferSizeStart = 512ul * 1024ul * 1024ul;
	//const size_t bufferSizeStep = 512ul * 1024ul * 1024ul;
	//const size_t bufferSizeLimit = 2ul * 1024ul * 1024ul * 1024ul;

	const unsigned int numSubgroupsStart = 4;
	const unsigned int numSubgroupsStep = 4;
	const unsigned int numSubgroupsLimit = 32;

	const unsigned int cacheSizeStart = 1024;
	const unsigned int cacheSizeStep = 1024;
	const unsigned int cacheSizeLimit = 8192;

	//const unsigned int numWGsStart = 2;
	//const unsigned int numWGsStep = 2;
	//const unsigned int numWGsLimit = 32;

	const unsigned int bottomTestRepetitions = 3;

	HighResolutionTimer timer;

	//for(size_t bufferSize = bufferSizeStart; bufferSize<= bufferSizeLimit; bufferSize += bufferSizeStep)
	//{
	const size_t bufferSize = MAX_BUFFER_SIZE;
	const auto allocatedSizeEdgeIndices = std::min(bufferSize, size_t(deepestLevelSizeAndParents) * size_t(nofEdges) * sizeof(uint32_t));
	auto voxelBatchSize = (8ul * allocatedSizeEdgeIndices) / (9ul * nofEdges * sizeof(uint32_t));
	voxelBatchSize = voxelBatchSize - (voxelBatchSize % 8ul);
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
	
	for(unsigned int numSG = numSubgroupsStart; numSG<=numSubgroupsLimit; numSG += numSubgroupsStep)
	{
		for(unsigned int cacheSize = cacheSizeStart; cacheSize <= cacheSizeLimit; cacheSize += cacheSizeStep)
		{
			if ((numSG * cacheSize) > (32 * 1024 * 1024))
				continue;

			_fillProgram.reset();
			_fillProgram = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, buildComputeShaderFillBottomLevel(numSG, subgroupSize, cacheSize)));

			_fillProgram->use();
			_fillProgram->set1ui("nofEdges", nofEdges);

			_bindBuffers();

			double time = 0;

			for (unsigned int test=0; test<bottomTestRepetitions; ++test)
			{
				timer.reset();

				std::cout << "Round " << test << std::endl;

				for(unsigned int batch = 0; batch < numBatches; ++batch)
				{
					const auto batchSize = std::min(voxelBatchSize, deepestLevelSize - (batch*voxelBatchSize));
					_loadVoxels(voxels, batch*voxelBatchSize, batchSize);
					_clearAtomicCounter();
					_fillProgram->set1ui("nofVoxels", unsigned(batchSize));

					ge::gl::glDispatchCompute(1, 1, 1);
					ge::gl::glFinish();
				}
				
				time += timer.getElapsedTimeFromLastQuerySeconds();
			}

			time /= bottomTestRepetitions;

			std::string msg;
			msg = std::to_string(bufferSize / 1024ul / 1024ul) + " " + std::to_string(numSG) + " " + std::to_string(cacheSize) + " " +std::to_string(time) + "\n";
			std::cout << msg;
			std::ofstream file;
			file.open("testResults.txt", std::ios_base::app);
			file << msg;
			file.close();
		}
	}
	//}

	exit(0);
}
/*
void GpuOctreeLoader::profile1(AdjacencyType edges)
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
			_fillProgram = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, buildComputeShaderFillBottomLevel(wgSize, cacheSize)));

			_fillProgram->use();
			_fillProgram->set1ui("nofEdges", nofEdges);

			_bindBuffers();

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

					ge::gl::glDispatchCompute((65536/ wgSize)*14, 1, 1);
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
*/
void GpuOctreeLoader::_createBuffers()
{
	_voxels = std::make_shared<ge::gl::Buffer>();
	_voxelPotentialEdges = std::make_shared<ge::gl::Buffer>();
	_voxelSilhouetteEdges = std::make_shared<ge::gl::Buffer>();
	_nofPotentialEdges = std::make_shared<ge::gl::Buffer>();
	_nofSilhouetteEdges = std::make_shared<ge::gl::Buffer>();
	_atomicCounter = std::make_shared<ge::gl::Buffer>();
	_atomicCounter->alloc(sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);

	if (std::is_same<unsigned char, BitmaskType>::value)
	{
		_parentSubbuffCounter = std::make_shared<ge::gl::Buffer>();
		_chunkCounter = std::make_shared<ge::gl::Buffer>();
		_chunkDesc = std::make_shared<ge::gl::Buffer>();
		_currentChunkId = std::make_shared<ge::gl::Buffer>();
		_parentEdges = std::make_shared<ge::gl::Buffer>();
	}

	_shit = std::make_shared<ge::gl::Buffer>();
}

/*
void GpuOctreeLoader::_serializeEdges(AdjacencyType edges, std::vector<float>& serializedEdges, std::vector<glm::vec3>& serializedOppositeVertices)
{
	const auto nofEdges = edges->getNofEdges();

	const glm::vec3* vertices = reinterpret_cast<const glm::vec3*>(edges->getVertices());

	for (size_t edgeIndex = 0; edgeIndex<nofEdges; ++edgeIndex)
	{
		glm::vec3 v1 = vertices[edges->getEdgeVertexA(edgeIndex) / 3];
		glm::vec3 v2 = vertices[edges->getEdgeVertexB(edgeIndex) / 3];

		const unsigned int nofOpposite = edges->getNofOpposite(edgeIndex);
		const unsigned int starting_index = serializedOppositeVertices.size() * 3;

		serializedEdges.push_back(v1.x); serializedEdges.push_back(v1.y); serializedEdges.push_back(v1.z);
		serializedEdges.push_back(v2.x); serializedEdges.push_back(v2.y); serializedEdges.push_back(v2.z);
		serializedEdges.push_back(*((float*)&nofOpposite));
		serializedEdges.push_back(*((float*)&starting_index));

		for (unsigned int i = 0; i<nofOpposite; ++i)
			serializedOppositeVertices.push_back(vertices[edges->getOpposite(edgeIndex, i) / 3]);
	}
}
*/

bool GpuOctreeLoader::_createBottomFillProgramCompress(unsigned int nofEdges)
{
	_wgSize = 64;
	_cacheSize = 31744;

	_fillProgram = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, buildComputeShaderFillBottomLevel2(_wgSize, _cacheSize, _limits.chunkSizeNofBits, _limits.maxChunksPerParent)));
	
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	return _fillProgram->isProgram();
}

void GpuOctreeLoader::_calculateLimitsCompress(unsigned int nofEdges)
{
	const int maxEdgesSubbuffer = std::max(MIN_SUBBUFFER_SIZE_UINTS, _findNearestHigherPow2(unsigned int(ceilf(nofEdges / float(MAX_NOF_CHUNKS)))));
	//FFS https://www.geeksforgeeks.org/position-of-rightmost-set-bit/
	_limits.chunkSizeNofBits = log2(maxEdgesSubbuffer & -maxEdgesSubbuffer);
	_limits.maxChunksPerParent = MAX_NOF_CHUNKS; // *0.8
}

unsigned int GpuOctreeLoader::_findNearestHigherPow2(unsigned int v)
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

void GpuOctreeLoader::_serializeDeepestLevelVoxels(std::vector<glm::vec3>& voxels)
{
	const int deepestLevelSize = ipow(OCTREE_NUM_CHILDREN, _octree->getDeepestLevel());
	const int startingIndex = _octree->getLevelFirstNodeID(_octree->getDeepestLevel());
	const int stopIndex = startingIndex + deepestLevelSize;

	voxels.resize(2 * deepestLevelSize);

	#pragma omp parallel for
	for (int i = 0; i<deepestLevelSize; ++i)
	{
		const auto bbox = _octree->getNodeVolume(startingIndex+i);

		voxels[2 * i + 0] = bbox.getMinPoint();
		voxels[2 * i + 1] = bbox.getMaxPoint();
	}
}

bool GpuOctreeLoader::_createBottomFillProgram(unsigned int numSubgroupsPerWG, unsigned int subgroupSize, unsigned int shmSizePerSubgroup)
{
#ifndef USE_COMPRESS
	_wgSize = subgroupSize * numSubgroupsPerWG;
	_cacheSize = shmSizePerSubgroup * numSubgroupsPerWG;
	/*
	std::ifstream t2("C:\\Users\\ikobrtek\\Desktop\\loaderDefault.glsl");
	std::string program((std::istreambuf_iterator<char>(t2)),
		std::istreambuf_iterator<char>());
	//*/
	std::string program = buildComputeShaderFillBottomLevel(numSubgroupsPerWG, subgroupSize, shmSizePerSubgroup);
	_fillProgram = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, program));
#else
	_wgSize = 64;
	_cacheSize = 31744;
	
	const auto program = buildComputeShaderFillBottomLevel2(_wgSize, _cacheSize, _limits.chunkSizeNofBits, _limits.maxChunksPerParent);
	/*
	std::ifstream t2("C:\\Users\\ikobrtek\\Desktop\\loaderCompress.glsl");
	std::string program((std::istreambuf_iterator<char>(t2)),
		std::istreambuf_iterator<char>());
	//*/
	_fillProgram = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, program));
#endif
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	return _fillProgram->isProgram();
}

void GpuOctreeLoader::addEdgesOnLowestLevelGPU(AdjacencyType edges)
{
	//--
	/*
	std::vector<unsigned int> selected;
	_testParticularVoxel(edges, 16838, selected);
	return;
	//*/
	//--
#ifdef USE_COMPRESS
	addEdgesOnLowestLevelGPUCompress8(edges);
	return;
#endif


	const int deepestLevel = _octree->getDeepestLevel();
	const int deepestLevelSize = ipow(OCTREE_NUM_CHILDREN, deepestLevel);
	const int deepestLevelSizeAndParents = ((OCTREE_NUM_CHILDREN + 1) * deepestLevelSize) / OCTREE_NUM_CHILDREN;

	const int startingNodeIndex = _octree->getLevelFirstNodeID(deepestLevel);

	assert(ge::gl::glGetError() == GL_NO_ERROR);

	//_loadEdges(edges);

	const auto nofEdges = edges->getNofEdges();

	std::vector<glm::vec3> voxels;
	_serializeDeepestLevelVoxels(voxels);
	const auto allocatedSizeEdgeIndices = std::min(size_t(MAX_BUFFER_SIZE), size_t(deepestLevelSizeAndParents) * size_t(nofEdges) * sizeof(uint32_t));
	
	//Parents are taken into consideration, as they will also need output buffers
	//TODO TU extra pozor - zkrokovat
	auto voxelBatchSize = (OCTREE_NUM_CHILDREN*allocatedSizeEdgeIndices)/((OCTREE_NUM_CHILDREN+1) * nofEdges * sizeof(uint32_t));
	voxelBatchSize = voxelBatchSize - (voxelBatchSize % OCTREE_NUM_CHILDREN);
	const unsigned int numBatches = (unsigned int)(ceil(float(deepestLevelSize) / voxelBatchSize));

	_allocateOutputBuffersAndVoxels(voxelBatchSize, nofEdges);

	_bindBuffers();
	_fillProgram->use();
	_fillProgram->set1ui("nofEdges", nofEdges);

	std::cout << "Num batches: " << numBatches << "\n";
	HighResolutionTimer t;

	for(unsigned int i = 0; i<numBatches; ++i)
	{
		const auto batchSize = std::min(voxelBatchSize, deepestLevelSize - (i*voxelBatchSize));
		
		std::cout << "Batch " << i << " size " << batchSize << std::endl;
		
		t.reset();
		_loadVoxels(voxels, i*voxelBatchSize, batchSize);
		_clearAtomicCounter();

		_fillProgram->set1ui("nofVoxels", batchSize);

		ge::gl::glDispatchCompute(100*unsigned int(ceil(float(batchSize)/ _wgSize)), 1, 1);
		ge::gl::glFinish();

		_acquireGpuData(startingNodeIndex + i*voxelBatchSize, batchSize, nofEdges);
	}

	_unbindBuffers();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeLoader::_allocateOutputBuffersCompress(unsigned voxelsPerBatch, unsigned nofEdges)
{
	std::cout << "Voxels per batch: " << voxelsPerBatch << std::endl;

	const unsigned int nofParents = voxelsPerBatch / OCTREE_NUM_CHILDREN;

	//TODO - sem mozne dat reduction factor
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

	_shit->alloc(10*nofEdges * sizeof(uint32_t));
}

void GpuOctreeLoader::_bindBuffersCompress()
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
	_shit->bindBase(GL_SHADER_STORAGE_BUFFER, target++);

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeLoader::_unbindBuffersCompress()
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
	_shit->unbindBase(GL_SHADER_STORAGE_BUFFER, target++);

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeLoader::_clearCompressionBuffers()
{
	//Init necessary buffers with zeros
	_parentSubbuffCounter->clear(GL_R32UI, GL_RED, GL_UNSIGNED_INT, nullptr);
	_chunkCounter->clear(GL_R32UI, GL_RED, GL_UNSIGNED_INT, nullptr);
	
	const uint16_t val = -1;
	_chunkDesc->clear(GL_R16UI, GL_RED, GL_UNSIGNED_SHORT, &val);
}

void GpuOctreeLoader::addEdgesOnLowestLevelGPUCompress8(AdjacencyType edges)
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
	const unsigned int numBatches = (unsigned int)(ceil(float(deepestLevelSize) / voxelBatchSize));

	_allocateOutputBuffersCompress(voxelBatchSize, nofEdges);

	_bindBuffersCompress();
	_fillProgram->use();
	_fillProgram->set1ui("nofEdges", nofEdges);

	std::cout << "Num batches: " << numBatches << "\n";
	HighResolutionTimer t;

	for (unsigned int i = 0; i<numBatches; ++i)
	{
		const auto batchSize = std::min(voxelBatchSize, deepestLevelSize - (i*voxelBatchSize));

		std::cout << "Batch " << i << " size " << batchSize << std::endl;

		t.reset();
		_loadVoxels(voxels, i*voxelBatchSize, batchSize);
		_clearAtomicCounter();
		_clearCompressionBuffers();

		_fillProgram->set1ui("nofVoxels", batchSize);

		ge::gl::glDispatchCompute(unsigned int(ceil(float(batchSize) / _wgSize)), 1, 1);
		ge::gl::glFinish();
		std::cout << "GPU Load: " << std::to_string(t.getElapsedTimeFromLastQuerySeconds()) << std::endl;

		_acquireGpuDataCompress(startingNodeIndex + i*voxelBatchSize, batchSize, nofEdges);
	}

	_unbindBuffersCompress();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}


void GpuOctreeLoader::_testParticularVoxel(AdjacencyType edges, unsigned int voxelId, std::vector<unsigned int>& particularEdgeIndices)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	auto nofEdges = edges->getNofEdges();
	const bool loadParticularEdges = !particularEdgeIndices.empty();

	if(loadParticularEdges)
	{
		nofEdges = particularEdgeIndices.size();

		const glm::vec3* vertices = reinterpret_cast<const glm::vec3*>(edges->getVertices());

		std::vector<float> serializedEdges;
		std::vector<glm::vec3> serializedOppositeVertices;

		for (size_t edgeIndex : particularEdgeIndices)
		{
			glm::vec3 v1 = vertices[edges->getEdgeVertexA(edgeIndex) / 3];
			glm::vec3 v2 = vertices[edges->getEdgeVertexB(edgeIndex) / 3];

			const unsigned int nofOpposite = edges->getNofOpposite(edgeIndex);
			const unsigned int starting_index = serializedOppositeVertices.size() * 3;

			serializedEdges.push_back(v1.x); serializedEdges.push_back(v1.y); serializedEdges.push_back(v1.z);
			serializedEdges.push_back(v2.x); serializedEdges.push_back(v2.y); serializedEdges.push_back(v2.z);
			serializedEdges.push_back(*((float*)&nofOpposite));
			serializedEdges.push_back(*((float*)&starting_index));

			for (unsigned int i = 0; i<nofOpposite; ++i)
				serializedOppositeVertices.push_back(vertices[edges->getOpposite(edgeIndex, i) / 3]);
		}

		_edges->alloc(serializedEdges.size() * sizeof(float), serializedEdges.data(), GL_STATIC_READ);
		_oppositeVertices->alloc(serializedOppositeVertices.size() * 3 * sizeof(float), serializedOppositeVertices.data(), GL_STATIC_READ);
	}
	//else
		//_loadEdges(edges);
	

	//Alloc
	glm::vec3 voxelData[2] = {_octree->getNode(voxelId)->volume.getMinPoint(), _octree->getNode(voxelId)->volume.getMaxPoint()};
	_voxels->alloc(6 * sizeof(float));
	_voxels->setData(voxelData, 6 * sizeof(float));

	_voxelPotentialEdges->alloc(nofEdges * sizeof(uint32_t));
	_voxelSilhouetteEdges->alloc(nofEdges * sizeof(uint32_t));

	//2 - for parent as well, just in case 
	_nofPotentialEdges->alloc(2*sizeof(uint32_t));
	_nofSilhouetteEdges->alloc(2*sizeof(uint32_t));

	_bufferNofPotential.resize(2);
	_bufferNofSilhouette.resize(2);

	_clearAtomicCounter();

	_bindBuffers();
	_fillProgram->use();
	_fillProgram->set1ui("nofEdges", nofEdges);
	_fillProgram->set1ui("nofVoxels", 1);

	ge::gl::glDispatchCompute(1, 1, 1);

	ge::gl::glFinish();

	_acquireGpuData(voxelId, 1, nofEdges);

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeLoader::_allocateOutputBuffersAndVoxels(unsigned voxelsPerBatch, unsigned nofEdges)
{
	const auto nofVoxelsWithParents = (voxelsPerBatch * (OCTREE_NUM_CHILDREN+1)) / OCTREE_NUM_CHILDREN;
	
	std::cout << "Voxels per batch: " << voxelsPerBatch << ", with parents: " << nofVoxelsWithParents << std::endl;

	_voxelPotentialEdges->alloc(nofVoxelsWithParents * nofEdges * sizeof(uint32_t));
	_voxelSilhouetteEdges->alloc(nofVoxelsWithParents * nofEdges * sizeof(uint32_t));

	_nofPotentialEdges->alloc(nofVoxelsWithParents * sizeof(uint32_t));
	_nofSilhouetteEdges->alloc(nofVoxelsWithParents * sizeof(uint32_t));

	_voxels->alloc(voxelsPerBatch * 6 * sizeof(float));

	_bufferNofPotential.resize(nofVoxelsWithParents);
	_bufferNofSilhouette.resize(nofVoxelsWithParents);
}

/*
void GpuOctreeLoader::_loadEdges(AdjacencyType edges)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	std::vector<float> serializedEdges;
	std::vector<glm::vec3> serializedOppositeVertices;

	_serializeEdges(edges, serializedEdges, serializedOppositeVertices);

	_edges->alloc(serializedEdges.size() * sizeof(float), serializedEdges.data(), GL_STATIC_READ);
	_oppositeVertices->alloc(serializedOppositeVertices.size() * 3 * sizeof(float), serializedOppositeVertices.data(), GL_STATIC_READ);
	assert(ge::gl::glGetError() == GL_NO_ERROR);
}
*/

void GpuOctreeLoader::_clearAtomicCounter()
{
	assert(_atomicCounter);
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	uint32_t zero = 0;
	_atomicCounter->setData(&zero, sizeof(uint32_t));
	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeLoader::_loadVoxels(const std::vector<glm::vec3>& voxels, unsigned int startingIndex, unsigned int batchSize)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	_voxels->setData((voxels.data() + (2 * startingIndex)), 6 * sizeof(float) * batchSize);
	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeLoader::_bindBuffers()
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_voxels->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_voxelPotentialEdges->bindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_voxelSilhouetteEdges->bindBase(GL_SHADER_STORAGE_BUFFER, 4);
	_nofPotentialEdges->bindBase(GL_SHADER_STORAGE_BUFFER, 5);
	_nofSilhouetteEdges->bindBase(GL_SHADER_STORAGE_BUFFER, 6);
	_atomicCounter->bindBase(GL_SHADER_STORAGE_BUFFER, 7);

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeLoader::_unbindBuffers()
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_oppositeVertices->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_voxels->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_voxelPotentialEdges->unbindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_voxelSilhouetteEdges->unbindBase(GL_SHADER_STORAGE_BUFFER, 4);
	_nofPotentialEdges->unbindBase(GL_SHADER_STORAGE_BUFFER, 5);
	_nofSilhouetteEdges->unbindBase(GL_SHADER_STORAGE_BUFFER, 6);
	_atomicCounter->unbindBase(GL_SHADER_STORAGE_BUFFER, 7);

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeLoader::_acquireGpuData(unsigned int startingVoxelAbsoluteIndex, unsigned int batchSize, unsigned int numEdges)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	const unsigned int numParents = batchSize / OCTREE_NUM_CHILDREN;
	
	_copyBuffer(_nofPotentialEdges, _bufferNofPotential.data(), (batchSize + numParents)*sizeof(uint32_t));
	_copyBuffer(_nofSilhouetteEdges, _bufferNofSilhouette.data(), (batchSize + numParents)*sizeof(uint32_t));

	//--POTENTIAL--
	//Do in sequence so the driver does not have to copy all the buffers to CPU at once
	const uint32_t* bPotential =  reinterpret_cast<uint32_t*>(_voxelPotentialEdges->map(GL_READ_ONLY));
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	
	for(unsigned int i=0; i<batchSize; ++i)
	{
		auto node = _octree->getNode(startingVoxelAbsoluteIndex + i);

		node->edgesMayCastMap[BitmaskAllSet].resize(_bufferNofPotential[i]);
		if (!node->edgesMayCastMap[BitmaskAllSet].empty())
			memcpy(node->edgesMayCastMap[BitmaskAllSet].data(), bPotential + (numEdges*i), _bufferNofPotential[i] * sizeof(uint32_t));
	}

	// Process parents
	const unsigned int startingParent = _octree->getNodeParent(startingVoxelAbsoluteIndex);
	for(unsigned int i = 0; i<numParents; ++i)
	{
		auto node = _octree->getNode(startingParent + i);
		const unsigned int parentIndex = batchSize + i;

		node->edgesMayCastMap[BitmaskAllSet].resize(_bufferNofPotential[parentIndex]);
		memcpy(node->edgesMayCastMap[BitmaskAllSet].data(), bPotential + (numEdges*parentIndex), _bufferNofPotential[parentIndex] * sizeof(uint32_t));
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

	// Process parents
	for (unsigned int i = 0; i<numParents; ++i)
	{
		auto node = _octree->getNode(startingParent + i);
		const unsigned int parentIndex = batchSize + i;

		node->edgesAlwaysCastMap[BitmaskAllSet].resize(_bufferNofSilhouette[parentIndex]);
		if (!node->edgesAlwaysCastMap[BitmaskAllSet].empty())
			memcpy(node->edgesAlwaysCastMap[BitmaskAllSet].data(), bSilhouette + (numEdges*parentIndex), _bufferNofSilhouette[parentIndex] * sizeof(uint32_t));
	}
	
	_voxelSilhouetteEdges->unmap();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

bool GpuOctreeLoader::_isChunkDescValid(uint16_t desc) const
{
	const unsigned char* dptr = reinterpret_cast<const unsigned char*>(&desc);

	if (dptr[1] == 1 || dptr[1] == 0)
		return true;

	return false;
}

unsigned int GpuOctreeLoader::_getNextChunkSize(int remainingSize, unsigned int chunkSize) const
{
	if ((remainingSize - int(chunkSize)) < 0)
		return remainingSize;

	return chunkSize;
}

void GpuOctreeLoader::_copyChunk(const uint32_t* gpuData, uint32_t chunkStart, uint32_t* dstData, uint32_t chunkSize)
{
	memcpy(dstData, gpuData + chunkStart, chunkSize * sizeof(uint32_t));
}

void GpuOctreeLoader::_acquireGpuDataCompress(unsigned int startingVoxelAbsoluteIndex, unsigned int batchSize, unsigned int numEdges)
{
	HighResolutionTimer timer;
	timer.reset();
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	const unsigned int numParents = batchSize / OCTREE_NUM_CHILDREN;

	_copyBuffer(_nofPotentialEdges, _bufferNofPotential.data(), batchSize  * sizeof(uint32_t));
	_copyBuffer(_nofSilhouetteEdges, _bufferNofSilhouette.data(), batchSize  * sizeof(uint32_t));

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

	std::vector<uint32_t> ec;
	ec.resize(2 * numParents * MAX_NOF_SUBBUFFERS);
	_parentSubbuffCounter->getData(ec.data(), ec.size() * sizeof(uint32_t));

	std::vector<uint32_t> chi;
	chi.resize(numParents * MAX_NOF_CHUNKS * (1 << _limits.chunkSizeNofBits));
	_parentEdges->getData(chi.data(), chi.size() * sizeof(uint32_t));

	const uint16_t* chunkDescriptors =	reinterpret_cast<uint16_t*>(_chunkDesc->map(GL_READ_ONLY));
	const uint32_t* edgeCounters =		reinterpret_cast<uint32_t*>(_parentSubbuffCounter->map(GL_READ_ONLY));
	const uint32_t* parentData =		reinterpret_cast<uint32_t*>(_parentEdges->map(GL_READ_ONLY));

	std::vector<int32_t> shitData;
	shitData.resize(10*numEdges);
	_shit->getData(shitData.data(), shitData.size() * sizeof(uint32_t));

	std::vector<unsigned int> counts;
	counts.resize(numParents);
	_chunkCounter->getData(counts.data(), counts.size() * sizeof(uint32_t));

	auto P = _octree->getChildrenStartingId(731);

	#pragma omp parallel for
	for (int currentParent = 0; currentParent < numParents; ++currentParent)
	{
		//Get chunk descriptors and process them
		std::vector< std::vector<unsigned int> > chunkDescs[2];
		chunkDescs[0].resize(MAX_NOF_SUBBUFFERS);
		chunkDescs[1].resize(MAX_NOF_SUBBUFFERS);

		const unsigned int startingDesc = currentParent*MAX_NOF_CHUNKS;
		const unsigned int stopDesc = startingDesc + MAX_NOF_CHUNKS;
		for(unsigned int currentDesc = startingDesc; currentDesc < stopDesc; ++currentDesc)
		{
			const auto desc = chunkDescriptors[currentDesc];
			const unsigned char* dptr = reinterpret_cast<const unsigned char*>(&desc);

			if(_isChunkDescValid(desc))
			{
				chunkDescs[dptr[1]][dptr[0]].push_back(currentDesc - startingDesc);
			}
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
		for(unsigned int i=0; i<MAX_NOF_SUBBUFFERS; ++i)
		{
			const auto& chunks = chunkDescs[0][i];
			if(chunks.size())
			{
				const auto nofEdges = edgeCounters[2*(currentParent * MAX_NOF_SUBBUFFERS + i) + 0];
				const unsigned int nofChunks = unsigned int(ceilf(float(nofEdges) / (1<<_limits.chunkSizeNofBits)));

				assert(nofChunks == chunks.size());

				node->edgesMayCastMap[i].resize(nofEdges);

				int remainingSize = nofEdges;
				for(unsigned int chunkNum = 0; chunkNum < nofChunks; ++ chunkNum)
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

void GpuOctreeLoader::_copyBuffer(std::shared_ptr<ge::gl::Buffer> buffer, void* destination, size_t size)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	const auto source = buffer->map(GL_READ_ONLY);

	memcpy(destination, source, size);

	buffer->unmap();
	assert(ge::gl::glGetError() == GL_NO_ERROR);
}
