#pragma once

#include "IOctreeLoader.hpp"

class IGpuOctreeLoader : public IOctreeLoader
{
public:

	IGpuOctreeLoader();
	virtual ~IGpuOctreeLoader() {}
	virtual void profile(AdjacencyType edges) = 0;

	void setMaxBufferSize(uint64_t size);
	void setSpeculativeRatios(float potRatio, float silRatio);

protected:

	void _serializeDeepestLevelVoxels(std::vector<glm::vec3>& voxels);
	void _loadVoxels(const std::vector<glm::vec3>& voxels, uint32_t startingIndex, uint32_t batchSize);
	void _clearAtomicCounter();
	void _copyBuffer(std::shared_ptr<ge::gl::Buffer> buffer, void* destination, size_t size);
	void _calculateLowestLevelBufferOffsets(uint32_t nofEdges);

	std::shared_ptr<ge::gl::Buffer> _edges;
	std::shared_ptr<ge::gl::Buffer> _oppositeVertices;
	std::shared_ptr<ge::gl::Buffer> _voxels;
	std::shared_ptr<ge::gl::Buffer> _voxelPotentialEdges;
	std::shared_ptr<ge::gl::Buffer> _voxelSilhouetteEdges;
	std::shared_ptr<ge::gl::Buffer> _nofPotentialEdges;
	std::shared_ptr<ge::gl::Buffer> _nofSilhouetteEdges;
	std::shared_ptr<ge::gl::Buffer> _atomicCounter;

	std::shared_ptr<ge::gl::Program> _fillProgram;

	uint32_t _wgSize = 0;
	uint32_t _cacheSize = 0;
	uint32_t _potBufferOffset = 0;
	uint32_t _silBufferOffset = 0;

	float _speculativeRatioPot = 0.0f;
	float _speculativeRatioSil = 0.0f;

	std::vector<uint32_t> _bufferNofPotential;
	std::vector<uint32_t> _bufferNofSilhouette;

	uint64_t _maxBufferSizeBytes = 0;

private:
	void _createBuffers();
};