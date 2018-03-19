#include "GpuOctreeLoader.hpp"
#include "HighResolutionTimer.hpp"
#include "VoxelTestingShader.hpp"

#include <geGL/StaticCalls.h>

bool GpuOctreeLoader::init(std::shared_ptr<Octree> octree)
{
	_octree = octree;
	
	if (!_createProgram(4, 32, 2048))
		return false;

	_createBuffers();

	return true;
}

void GpuOctreeLoader::_createBuffers()
{
	_edges = std::make_shared<ge::gl::Buffer>();
	_oppositeVertices = std::make_shared<ge::gl::Buffer>();
	_voxels = std::make_shared<ge::gl::Buffer>();
	_voxelPotentialEdges = std::make_shared<ge::gl::Buffer>();
	_voxelSilhouetteEdges = std::make_shared<ge::gl::Buffer>();
	_nofPotentialEdges = std::make_shared<ge::gl::Buffer>();
	_nofSilhouetteEdges = std::make_shared<ge::gl::Buffer>();
	_atomicCounter = std::make_shared<ge::gl::Buffer>();
	_atomicCounter->alloc(sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
}

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

bool GpuOctreeLoader::_createProgram(unsigned int numSubgroupsPerWG, unsigned int subgroupSize, unsigned int shmSizePerSubgroup)
{
	assert(subgroupSize == 32 || subgroupSize == 64);
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	_program = std::make_shared<ge::gl::Program>(std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, buildComputeShader(numSubgroupsPerWG, subgroupSize, shmSizePerSubgroup)));

	assert(ge::gl::glGetError() == GL_NO_ERROR);
	return _program->isProgram();
}

void GpuOctreeLoader::addEdgesOnLowestLevelGPU(AdjacencyType edges)
{
	//--
	//_testParticularVoxel(edges, 8776);
	//return;
	//--
	
	const int deepestLevel = _octree->getDeepestLevel();
	const int deepestLevelSize = ipow(OCTREE_NUM_CHILDREN, deepestLevel);
	const int deepestLevelSizeAndParents = (9 * deepestLevelSize) / 8;

	const int startingNodeIndex = _octree->getLevelFirstNodeID(deepestLevel);
	const int stopIndex = _octree->getTotalNumNodes();

	assert(ge::gl::glGetError() == GL_NO_ERROR);

	_loadEdges(edges);

	const auto nofEdges = edges->getNofEdges();

	std::vector<glm::vec3> voxels;
	_serializeDeepestLevelVoxels(voxels);

	const auto allocatedSizeEdgeIndices = std::min((size_t)MAX_BUFFER_SIZE, deepestLevelSizeAndParents * nofEdges * sizeof(uint32_t));
	
	//Parents are taken into consideration, as they will also need output buffers
	//TODO TU extra pozor - zkrokovat
	auto voxelBatchSize = (8*allocatedSizeEdgeIndices)/(9 * nofEdges * sizeof(uint32_t));
	voxelBatchSize = voxelBatchSize - (voxelBatchSize % 8);
	const unsigned int numBatches = (unsigned int)(ceil(float(deepestLevelSize) / voxelBatchSize));

	_allocateOutputBuffersAndVoxels(voxelBatchSize, nofEdges);

	_bindBuffers();
	_program->use();
	_program->set1ui("nofEdges", nofEdges);

	std::cout << "Num batches: " << numBatches << "\n";

	for(unsigned int i = 0; i<numBatches; ++i)
	{
		const auto batchSize = std::min(voxelBatchSize, deepestLevelSize - (i*voxelBatchSize));
		
		std::cout << "Batch " << i << " size " << batchSize << std::endl;

		_loadVoxels(voxels, i*voxelBatchSize, batchSize);

		_clearAtomicCounter();
		_clearCountingBuffers();

		_program->set1ui("nofVoxels", batchSize);
		ge::gl::glDispatchCompute(16, 1, 1);

		ge::gl::glFinish();

		_acquireGpuData(startingNodeIndex + i*voxelBatchSize, batchSize, nofEdges);
	}

	_unbindBuffers();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void GpuOctreeLoader::_testParticularVoxel(AdjacencyType edges, unsigned int voxelId)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	const auto nofEdges = edges->getNofEdges();

	//Load edges
	_loadEdges(edges);

	//Alloc
	glm::vec3 voxelData[2] = {_octree->getNode(voxelId)->volume.getMinPoint(), _octree->getNode(voxelId)->volume.getMaxPoint()};
	_voxels->alloc(6 * sizeof(float));
	_voxels->setData(voxelData, 6 * sizeof(float));

	_voxelPotentialEdges->alloc(nofEdges * sizeof(uint32_t));
	_voxelSilhouetteEdges->alloc(nofEdges * sizeof(uint32_t));

	_nofPotentialEdges->alloc(sizeof(uint32_t));
	_nofSilhouetteEdges->alloc(sizeof(uint32_t));

	_bufferNofPotential.resize(1);
	_bufferNofSilhouette.resize(1);
	_clearBuffer.resize(1);
	memset(_clearBuffer.data(), int(0), _clearBuffer.size() * sizeof(uint32_t));

	_clearAtomicCounter();
	_clearCountingBuffers();

	_bindBuffers();
	_program->use();
	_program->set1ui("nofEdges", nofEdges);
	_program->set1ui("nofVoxels", 1);

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
	_clearBuffer.resize(nofVoxelsWithParents);

	memset(_clearBuffer.data(), int(0), _clearBuffer.size() * sizeof(uint32_t));
}


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

void GpuOctreeLoader::_clearCountingBuffers()
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);
	
	_nofPotentialEdges->setData(_clearBuffer.data(), _clearBuffer.size() * sizeof(uint32_t));
	_nofSilhouetteEdges->setData(_clearBuffer.data(), _clearBuffer.size() * sizeof(uint32_t));

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}
