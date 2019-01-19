#pragma once

#include "IOctreeLoader.hpp"

#define MAX_BUFFER_SIZE (2816ull*1024ull*1024ull)

class IGpuOctreeLoader : public IOctreeLoader
{
public:

	IGpuOctreeLoader();
	virtual ~IGpuOctreeLoader() {}

	virtual void profile(AdjacencyType edges) = 0;

protected:

	void _serializeDeepestLevelVoxels(std::vector<glm::vec3>& voxels);
	void _loadVoxels(const std::vector<glm::vec3>& voxels, unsigned int startingIndex, unsigned int batchSize);
	void _clearAtomicCounter();
	void _copyBuffer(std::shared_ptr<ge::gl::Buffer> buffer, void* destination, size_t size);
	void _calculateLowestLevelBufferOffsets(unsigned int nofEdges, float potRatio, float silRatio);

	std::shared_ptr<ge::gl::Buffer> _edges;
	std::shared_ptr<ge::gl::Buffer> _oppositeVertices;
	std::shared_ptr<ge::gl::Buffer> _voxels;
	std::shared_ptr<ge::gl::Buffer> _voxelPotentialEdges;
	std::shared_ptr<ge::gl::Buffer> _voxelSilhouetteEdges;
	std::shared_ptr<ge::gl::Buffer> _nofPotentialEdges;
	std::shared_ptr<ge::gl::Buffer> _nofSilhouetteEdges;
	std::shared_ptr<ge::gl::Buffer> _atomicCounter;

	std::shared_ptr<ge::gl::Program> _fillProgram;

	unsigned int _wgSize = 0;
	unsigned int _cacheSize = 0;
	unsigned int _potBufferOffset = 0;
	unsigned int _silBufferOffset = 0;

	std::vector<uint32_t> _bufferNofPotential;
	std::vector<uint32_t> _bufferNofSilhouette;

private:
	void _createBuffers();
};