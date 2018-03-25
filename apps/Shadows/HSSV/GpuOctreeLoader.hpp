#pragma once

#include <geGL/Buffer.h>
#include <geGL/Program.h>

#include "AdjacencyEdgeWrapper.hpp"
#include "Octree.hpp"
#include "GpuEdges.hpp"

#define MAX_BUFFER_SIZE (1024ul*1024ul*1024ul)

class GpuOctreeLoader
{
public:
	
	void addEdgesOnLowestLevelGPU(AdjacencyType edges);
	
	bool init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, unsigned int subgroupSize);

	void profile(AdjacencyType edges, unsigned int subgroupSize);

protected:

	void _createBuffers();
	bool _createBottomFillProgram(unsigned int numSubgroupsPerWG, unsigned int subgroupSize, unsigned int shmSizePerSubgroup);

	void _serializeDeepestLevelVoxels(std::vector<glm::vec3>& voxels);

	void _allocateOutputBuffersAndVoxels(unsigned int voxelsPerBatch, unsigned int numEdges);
	void _clearAtomicCounter();

	void _loadVoxels(const std::vector<glm::vec3>& voxels, unsigned int startingIndex, unsigned int batchSize);

	void _bindBuffers();
	void _unbindBuffers();

	void _acquireGpuData(unsigned int startingVoxelAbsoluteIndex, unsigned int batchSize, unsigned int numEdges);
		void _copyBuffer(std::shared_ptr<ge::gl::Buffer> buffer, void* destination, size_t size);

	
	void _testParticularVoxel(AdjacencyType edges, unsigned int voxelId, std::vector<unsigned int>& particularEdgeIndices);

	std::shared_ptr<Octree> _octree;

	std::shared_ptr<ge::gl::Buffer> _edges;
	std::shared_ptr<ge::gl::Buffer> _oppositeVertices;
	std::shared_ptr<ge::gl::Buffer> _voxels;
	std::shared_ptr<ge::gl::Buffer> _voxelPotentialEdges;
	std::shared_ptr<ge::gl::Buffer> _voxelSilhouetteEdges;
	std::shared_ptr<ge::gl::Buffer> _nofPotentialEdges;
	std::shared_ptr<ge::gl::Buffer> _nofSilhouetteEdges;
	std::shared_ptr<ge::gl::Buffer> _atomicCounter;

	std::shared_ptr<ge::gl::Program> _fillProgram;

	std::vector<uint32_t> _bufferNofPotential;
	std::vector<uint32_t> _bufferNofSilhouette;
};
