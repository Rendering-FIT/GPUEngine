#include "GpuOctreeLoader.hpp"
#include "HighResolutionTimer.hpp"
#include "VoxelTestingShader.hpp"

#include <geGL/StaticCalls.h>
#include "MultiplicityCoding.hpp"

#include <iostream>
#include <fstream>

bool GpuOctreeLoader::init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, uint32_t nofEdges)
{
	assert(octree);
	assert(gpuEdges);

	_edges = gpuEdges->_edges;
	_oppositeVertices = gpuEdges->_oppositeVertices;

	_octree = octree;

	if (!_createBottomFillProgram())
		return false;

	return true;
}

//NOT WORKING
void GpuOctreeLoader::profile(AdjacencyType edges)
{
	//_loadEdges(edges);
	/*

	std::vector<glm::vec3> voxels;
	_serializeDeepestLevelVoxels(voxels);

	const auto nofEdges = edges->getNofEdges();
	const int deepestLevel = _octree->getDeepestLevel();
	const int deepestLevelSize = ipow(OCTREE_NUM_CHILDREN, deepestLevel);
	const int deepestLevelSizeAndParents = (9 * deepestLevelSize) / 8;

	//const size_t bufferSizeStart = 512ul * 1024ul * 1024ul;
	//const size_t bufferSizeStep = 512ul * 1024ul * 1024ul;
	//const size_t bufferSizeLimit = 2ul * 1024ul * 1024ul * 1024ul;

	const uint32_t numSubgroupsStart = 4;
	const uint32_t numSubgroupsStep = 4;
	const uint32_t numSubgroupsLimit = 32;

	const uint32_t cacheSizeStart = 1024;
	const uint32_t cacheSizeStep = 1024;
	const uint32_t cacheSizeLimit = 8192;

	//const uint32_t numWGsStart = 2;
	//const uint32_t numWGsStep = 2;
	//const uint32_t numWGsLimit = 32;

	const uint32_t bottomTestRepetitions = 3;

	HighResolutionTimer timer;

	//for(size_t bufferSize = bufferSizeStart; bufferSize<= bufferSizeLimit; bufferSize += bufferSizeStep)
	//{
	const size_t bufferSize = MAX_BUFFER_SIZE;
	const auto allocatedSizeEdgeIndices = std::min(bufferSize, size_t(deepestLevelSizeAndParents) * size_t(nofEdges) * sizeof(uint32_t));
	auto voxelBatchSize = (8ul * allocatedSizeEdgeIndices) / (9ul * nofEdges * sizeof(uint32_t));
	voxelBatchSize = voxelBatchSize - (voxelBatchSize % 8ul);
	const uint32_t numBatches = (uint32_t)(ceil(float(deepestLevelSize) / voxelBatchSize));

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
	
	for(uint32_t numSG = numSubgroupsStart; numSG<=numSubgroupsLimit; numSG += numSubgroupsStep)
	{
		for(uint32_t cacheSize = cacheSizeStart; cacheSize <= cacheSizeLimit; cacheSize += cacheSizeStep)
		{
			if ((numSG * cacheSize) > (32 * 1024 * 1024))
				continue;

			_fillProgram.reset();
			_fillProgram = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, buildComputeShaderFillBottomLevel(numSG, subgroupSize, cacheSize)));

			_fillProgram->use();
			_fillProgram->set1ui("nofEdges", nofEdges);

			_bindBuffers();

			double time = 0;

			for (uint32_t test=0; test<bottomTestRepetitions; ++test)
			{
				timer.reset();

				std::cout << "Round " << test << std::endl;

				for(uint32_t batch = 0; batch < numBatches; ++batch)
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
	*/
}



bool GpuOctreeLoader::_createBottomFillProgram()
{
	_wgSize = 64;
	_cacheSize = 31744;
	
	const auto program = buildComputeShaderFillBottomLevel(_wgSize, _cacheSize, 0, 0);
	
	_fillProgram = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, program));

	assert(ge::gl::glGetError() == GL_NO_ERROR);
	return _fillProgram->isProgram();
}

void GpuOctreeLoader::addEdgesOnLowestLevel(AdjacencyType edges)
{
	//--
	/*
	std::vector<uint32_t> selected;
	_testParticularVoxel(edges, 16838, selected);
	return;
	//*/
	//--

	const int deepestLevel = _octree->getDeepestLevel();
	const int deepestLevelSize = ipow(OCTREE_NUM_CHILDREN, deepestLevel);
	const int deepestLevelSizeAndParents = ((OCTREE_NUM_CHILDREN + 1) * deepestLevelSize) / OCTREE_NUM_CHILDREN;

	const int startingNodeIndex = _octree->getLevelFirstNodeID(deepestLevel);

	assert(ge::gl::glGetError() == GL_NO_ERROR);

	const auto nofEdges = edges->getNofEdges();

	_calculateLowestLevelBufferOffsets(nofEdges);

	std::vector<glm::vec3> voxels;
	_serializeDeepestLevelVoxels(voxels);
	const auto allocatedSizeEdgeIndices = std::min(_maxBufferSizeBytes, size_t(deepestLevelSizeAndParents) * size_t(_potBufferOffset) * sizeof(uint32_t));
	
	//Parents are taken into consideration, as they will also need output buffers
	//TODO TU extra pozor - zkrokovat
	auto voxelBatchSize = (OCTREE_NUM_CHILDREN*allocatedSizeEdgeIndices)/((OCTREE_NUM_CHILDREN+1) * _potBufferOffset * sizeof(uint32_t));
	voxelBatchSize = voxelBatchSize - (voxelBatchSize % OCTREE_NUM_CHILDREN);
	const uint32_t numBatches = (uint32_t)(ceil(float(deepestLevelSize) / voxelBatchSize));

	_allocateOutputBuffersAndVoxels(voxelBatchSize);

	_bindBuffers();
	_fillProgram->use();
	_fillProgram->set1ui("nofEdges", nofEdges);
	_fillProgram->set1ui("potBufferOffset", _potBufferOffset);
	_fillProgram->set1ui("silBufferOffset", _silBufferOffset);

	std::cout << "Num batches: " << numBatches << "\n";
	HighResolutionTimer t;

	for(uint32_t i = 0; i<numBatches; ++i)
	{
		const auto batchSize = std::min(voxelBatchSize, deepestLevelSize - (i*voxelBatchSize));
		
		std::cout << "Batch " << i << " size " << batchSize << std::endl;
		
		t.reset();
		_loadVoxels(voxels, i*voxelBatchSize, batchSize);
		_clearAtomicCounter();

		_fillProgram->set1ui("nofVoxels", batchSize);

		ge::gl::glDispatchCompute(uint32_t(ceil(float(batchSize)/ _wgSize)), 1, 1);
		ge::gl::glFinish();

		_acquireGpuData(startingNodeIndex + i*voxelBatchSize, batchSize);
	}

	_unbindBuffers();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

//NOT WORKING
void GpuOctreeLoader::_testParticularVoxel(AdjacencyType edges, uint32_t voxelId, std::vector<uint32_t>& particularEdgeIndices)
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

			const uint32_t nofOpposite = edges->getNofOpposite(edgeIndex);
			const uint32_t starting_index = serializedOppositeVertices.size() * 3;

			serializedEdges.push_back(v1.x); serializedEdges.push_back(v1.y); serializedEdges.push_back(v1.z);
			serializedEdges.push_back(v2.x); serializedEdges.push_back(v2.y); serializedEdges.push_back(v2.z);
			serializedEdges.push_back(*((float*)&nofOpposite));
			serializedEdges.push_back(*((float*)&starting_index));

			for (uint32_t i = 0; i<nofOpposite; ++i)
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

	_acquireGpuData(voxelId, 1);

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeLoader::_allocateOutputBuffersAndVoxels(unsigned voxelsPerBatch)
{
	const auto nofVoxelsWithParents = (voxelsPerBatch * (OCTREE_NUM_CHILDREN+1)) / OCTREE_NUM_CHILDREN;
	
	std::cout << "Voxels per batch: " << voxelsPerBatch << ", with parents: " << nofVoxelsWithParents << std::endl;

	_voxelPotentialEdges->alloc(nofVoxelsWithParents * _potBufferOffset * sizeof(uint32_t));
	_voxelSilhouetteEdges->alloc(nofVoxelsWithParents * _silBufferOffset * sizeof(uint32_t));

	_nofPotentialEdges->alloc(nofVoxelsWithParents * sizeof(uint32_t));
	_nofSilhouetteEdges->alloc(nofVoxelsWithParents * sizeof(uint32_t));

	_voxels->alloc(voxelsPerBatch * 6 * sizeof(float));

	_bufferNofPotential.resize(nofVoxelsWithParents);
	_bufferNofSilhouette.resize(nofVoxelsWithParents);
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

void GpuOctreeLoader::_acquireGpuData(uint32_t startingVoxelAbsoluteIndex, uint32_t batchSize)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	const uint32_t numParents = batchSize / OCTREE_NUM_CHILDREN;
	
	_copyBuffer(_nofPotentialEdges, _bufferNofPotential.data(), (batchSize + numParents)*sizeof(uint32_t));
	_copyBuffer(_nofSilhouetteEdges, _bufferNofSilhouette.data(), (batchSize + numParents)*sizeof(uint32_t));

	//--POTENTIAL--
	//Do in sequence so the driver does not have to copy all the buffers to CPU at once
	const uint32_t* bPotential =  reinterpret_cast<uint32_t*>(_voxelPotentialEdges->map(GL_READ_ONLY));
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	
	for(uint32_t i=0; i<batchSize; ++i)
	{
		auto node = _octree->getNode(startingVoxelAbsoluteIndex + i);

		node->edgesMayCastMap[BitmaskAllSet].resize(_bufferNofPotential[i]);
		if (!node->edgesMayCastMap[BitmaskAllSet].empty())
			memcpy(node->edgesMayCastMap[BitmaskAllSet].data(), bPotential + (_potBufferOffset*i), _bufferNofPotential[i] * sizeof(uint32_t));
	}

	// Process parents
	const uint32_t startingParent = _octree->getNodeParent(startingVoxelAbsoluteIndex);
	for(uint32_t i = 0; i<numParents; ++i)
	{
		auto node = _octree->getNode(startingParent + i);
		const uint32_t parentIndex = batchSize + i;

		node->edgesMayCastMap[BitmaskAllSet].resize(_bufferNofPotential[parentIndex]);
		memcpy(node->edgesMayCastMap[BitmaskAllSet].data(), bPotential + (_potBufferOffset*parentIndex), _bufferNofPotential[parentIndex] * sizeof(uint32_t));
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

	// Process parents
	for (uint32_t i = 0; i<numParents; ++i)
	{
		auto node = _octree->getNode(startingParent + i);
		const uint32_t parentIndex = batchSize + i;

		node->edgesAlwaysCastMap[BitmaskAllSet].resize(_bufferNofSilhouette[parentIndex]);
		if (!node->edgesAlwaysCastMap[BitmaskAllSet].empty())
			memcpy(node->edgesAlwaysCastMap[BitmaskAllSet].data(), bSilhouette + (_silBufferOffset*parentIndex), _bufferNofSilhouette[parentIndex] * sizeof(uint32_t));
	}
	
	_voxelSilhouetteEdges->unmap();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

