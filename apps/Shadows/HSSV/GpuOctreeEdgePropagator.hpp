#pragma once

#include <geGL/Buffer.h>
#include <geGL/Program.h>

#include "Octree.hpp"

enum class BufferType
{
	POTENTIAL,
	SILHOUETTE
};

class GpuOctreeEdgePropagator
{
public:

	void propagateEdgesToUpperLevel(uint32_t level, BufferType type);

	bool init(std::shared_ptr<Octree> octree, uint32_t subgroupSize, size_t maxBufferSizeMB);

	void profile();

protected:
	bool _createPropagateProgram(unsigned workgroupSize);
	void _createBuffers();
	void _clearAtomicCounter();
	void _allocateBuffers();
	void _deleteBuffers();

	void _bindBuffers();
	void _unbindBuffers();


	uint32_t _getLevelMaxNofVoxels(uint32_t level, BufferType type) const;

	void _loadVoxelEdgesStartingFrom(uint32_t startingVoxel, uint32_t endVoxel, BufferType type, std::vector<uint32_t>& sizes);
		size_t _getSyblingsBufferSizeAndMaximum(uint32_t startingId, BufferType type, uint32_t& maxSize);

	void _updateCpuData(uint32_t startingIndex, uint32_t batchSize, uint32_t maxEdgesPerVoxel, BufferType type, const std::vector<uint32_t>& sizePrefixSum);

	std::shared_ptr<ge::gl::Program> _propagateProgram;

	std::shared_ptr<ge::gl::Buffer> _indices;
	std::shared_ptr<ge::gl::Buffer> _numIndices;
	std::shared_ptr<ge::gl::Buffer> _outputIndices;
	std::shared_ptr<ge::gl::Buffer> _outputNumIndices;
	std::shared_ptr<ge::gl::Buffer> _parentIndices;
	std::shared_ptr<ge::gl::Buffer> _parentNumIndices;
	std::shared_ptr<ge::gl::Buffer> _atomicCounter;

	std::shared_ptr<Octree> _octree;

	uint32_t _wgSize = 0;
	size_t _maxBufferSize = 0;
};
