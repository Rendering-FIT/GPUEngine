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

	void propagateEdgesToUpperLevel(unsigned int level, BufferType type);

	bool init(std::shared_ptr<Octree> octree, unsigned int subgroupSize, size_t maxBufferSizeMB);

	void profile();

protected:
	bool _createPropagateProgram(unsigned workgroupSize);
	void _createBuffers();
	void _clearAtomicCounter();
	void _allocateBuffers();
	void _deleteBuffers();

	void _bindBuffers();
	void _unbindBuffers();


	unsigned int _getLevelMaxNofVoxels(unsigned int level, BufferType type) const;

	void _loadVoxelEdgesStartingFrom(unsigned int startingVoxel, unsigned int endVoxel, BufferType type, std::vector<uint32_t>& sizes);
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

	unsigned int _wgSize = 0;
	size_t _maxBufferSize = 0;
};
