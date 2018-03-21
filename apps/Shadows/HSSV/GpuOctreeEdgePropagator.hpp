#pragma once

#include <geGL/Buffer.h>
#include <geGL/Program.h>

#include "Octree.hpp"

#define MAX_BUFFER_SIZE_PROPAGATE (1024ul*1024ul*1024ul)

enum class BufferType
{
	POTENTIAL,
	SILHOUETTE
};

class GpuOctreeEdgePropagator
{
public:

	void propagateEdgesToUpperLevel(unsigned int level, BufferType type);

	bool init(std::shared_ptr<Octree> octree, unsigned int subgroupSize);

	void profile(unsigned int subgroupSize);

	

protected:

	bool _createPropagateProgram(unsigned numSubgroupsPerWG, unsigned subgroupSize);
	void _createBuffers();
	void _clearAtomicCounter();
	void _allocateBuffers();

	void _bindBuffers();
	void _unbindBuffers();

	void _loadVoxelEdgesStartingFrom_returnNofLoaded(unsigned int startingVoxel, unsigned int levelSize, BufferType type, unsigned int& outMaxEdges, std::vector<unsigned int>& sizes);
		size_t _getSyblingsBufferSizeAndMaximum(unsigned int startingId, BufferType type, unsigned int& maxSize);

	void _updateCpuData(unsigned int startingIndex, unsigned int batchSize, unsigned int maxEdgesPerVoxel, BufferType type, const std::vector<unsigned int>& sizePrefixSum);

	std::shared_ptr<ge::gl::Program> _propagateProgram;

	std::shared_ptr<ge::gl::Buffer> _indices;
	std::shared_ptr<ge::gl::Buffer> _numIndices;
	std::shared_ptr<ge::gl::Buffer> _outputIndices;
	std::shared_ptr<ge::gl::Buffer> _outputNumIndices;
	std::shared_ptr<ge::gl::Buffer> _parentIndices;
	std::shared_ptr<ge::gl::Buffer> _parentNumIndices;
	std::shared_ptr<ge::gl::Buffer> _atomicCounter;

	std::shared_ptr<Octree> _octree;
};
