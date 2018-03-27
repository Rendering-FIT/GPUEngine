#include "GpuOctreeLoader.hpp"
#include "HighResolutionTimer.hpp"
#include "VoxelTestingShader.hpp"

#include <geGL/StaticCalls.h>
#include "MultiplicityCoding.hpp"

#include <iostream>
#include <fstream>
bool GpuOctreeLoader::init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, unsigned int subgroupSize)
{
	assert(octree);
	assert(gpuEdges);

	_edges = gpuEdges->_edges;
	_oppositeVertices = gpuEdges->_oppositeVertices;

	_octree = octree;
	
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
					_fillProgram->set1ui("nofVoxels", batchSize);

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

void GpuOctreeLoader::_createBuffers()
{
	//_edges = std::make_shared<ge::gl::Buffer>();
	//_oppositeVertices = std::make_shared<ge::gl::Buffer>();
	_voxels = std::make_shared<ge::gl::Buffer>();
	_voxelPotentialEdges = std::make_shared<ge::gl::Buffer>();
	_voxelSilhouetteEdges = std::make_shared<ge::gl::Buffer>();
	_nofPotentialEdges = std::make_shared<ge::gl::Buffer>();
	_nofSilhouetteEdges = std::make_shared<ge::gl::Buffer>();
	_atomicCounter = std::make_shared<ge::gl::Buffer>();
	_atomicCounter->alloc(sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
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

void GpuOctreeLoader::_serializeDeepestLevelVoxels(std::vector<glm::vec3>& voxels)
{
	const unsigned int deepestLevelSize = ipow(OCTREE_NUM_CHILDREN, _octree->getDeepestLevel());
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
	assert(subgroupSize == 32 || subgroupSize == 64);
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	_fillProgram = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, buildComputeShaderFillBottomLevel(numSubgroupsPerWG, subgroupSize, shmSizePerSubgroup)));

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
	
	const int deepestLevel = _octree->getDeepestLevel();
	const int deepestLevelSize = ipow(OCTREE_NUM_CHILDREN, deepestLevel);
	const int deepestLevelSizeAndParents = (9 * deepestLevelSize) / 8;

	const int startingNodeIndex = _octree->getLevelFirstNodeID(deepestLevel);
	const int stopIndex = _octree->getTotalNumNodes();

	assert(ge::gl::glGetError() == GL_NO_ERROR);

	//_loadEdges(edges);

	const auto nofEdges = edges->getNofEdges();

	std::vector<glm::vec3> voxels;
	_serializeDeepestLevelVoxels(voxels);
	const uint64_t a = MAX_BUFFER_SIZE;
	const auto allocatedSizeEdgeIndices = std::min(size_t(MAX_BUFFER_SIZE), size_t(deepestLevelSizeAndParents) * size_t(nofEdges) * sizeof(uint32_t));
	
	//Parents are taken into consideration, as they will also need output buffers
	//TODO TU extra pozor - zkrokovat
	auto voxelBatchSize = (8*allocatedSizeEdgeIndices)/(9 * nofEdges * sizeof(uint32_t));
	voxelBatchSize = voxelBatchSize - (voxelBatchSize % 8);
	const unsigned int numBatches = (unsigned int)(ceil(float(deepestLevelSize) / voxelBatchSize));

	_allocateOutputBuffersAndVoxels(voxelBatchSize, nofEdges);

	_bindBuffers();
	_fillProgram->use();
	_fillProgram->set1ui("nofEdges", nofEdges);

	std::cout << "Num batches: " << numBatches << "\n";

	for(unsigned int i = 0; i<numBatches; ++i)
	{
		const auto batchSize = std::min(voxelBatchSize, deepestLevelSize - (i*voxelBatchSize));
		
		std::cout << "Batch " << i << " size " << batchSize << std::endl;

		_loadVoxels(voxels, i*voxelBatchSize, batchSize);
		_clearAtomicCounter();

		_fillProgram->set1ui("nofVoxels", batchSize);
		ge::gl::glDispatchCompute(16, 1, 1);

		ge::gl::glFinish();

		_acquireGpuData(startingNodeIndex + i*voxelBatchSize, batchSize, nofEdges);
	}

	_unbindBuffers();

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
	const auto nofVoxelsWithParents = (voxelsPerBatch * 9) / 8;
	
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
	const unsigned int numParents = batchSize / 8;
	
	_copyBuffer(_nofPotentialEdges, _bufferNofPotential.data(), (batchSize + numParents)*sizeof(uint32_t));
	_copyBuffer(_nofSilhouetteEdges, _bufferNofSilhouette.data(), (batchSize + numParents)*sizeof(uint32_t));

	const uint32_t* bPotential =  reinterpret_cast<uint32_t*>(_voxelPotentialEdges->map(GL_READ_ONLY));
	const uint32_t* bSilhouette = reinterpret_cast<uint32_t*>(_voxelSilhouetteEdges->map(GL_READ_ONLY));
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	std::vector<unsigned int> tmp;
	for(unsigned int i=0; i<batchSize; ++i)
	{
		auto node = _octree->getNode(startingVoxelAbsoluteIndex + i);

		node->edgesMayCast.resize(_bufferNofPotential[i]);
		if (!node->edgesMayCast.empty())
			memcpy(node->edgesMayCast.data(), bPotential + (numEdges*i), _bufferNofPotential[i] * sizeof(uint32_t));

		node->edgesAlwaysCast.resize(_bufferNofSilhouette[i]);
		if(!node->edgesAlwaysCast.empty())
			memcpy(node->edgesAlwaysCast.data(), bSilhouette + (numEdges*i), _bufferNofSilhouette[i] * sizeof(uint32_t));
	}

	//Process parents
	const unsigned int startingParent = _octree->getNodeParent(startingVoxelAbsoluteIndex);
	for(unsigned int i = 0; i<numParents; ++i)
	{
		auto node = _octree->getNode(startingParent + i);
		const unsigned int parentIndex = batchSize + i;

		node->edgesMayCast.resize(_bufferNofPotential[parentIndex]);
		memcpy(node->edgesMayCast.data(), bPotential + (numEdges*parentIndex), _bufferNofPotential[parentIndex] * sizeof(uint32_t));

		node->edgesAlwaysCast.resize(_bufferNofSilhouette[parentIndex]);
		if (!node->edgesAlwaysCast.empty())
			memcpy(node->edgesAlwaysCast.data(), bSilhouette + (numEdges*parentIndex), _bufferNofSilhouette[parentIndex] * sizeof(uint32_t));
	}
	
	_voxelPotentialEdges->unmap();
	_voxelSilhouetteEdges->unmap();

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
