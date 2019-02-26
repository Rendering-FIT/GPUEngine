#pragma once

#include "IGpuOctreeLoader.hpp"

class GpuOctreeLoaderCompress8 : public IGpuOctreeLoader
{
public:
	void addEdgesOnLowestLevel(AdjacencyType edges) override;
	bool init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, uint32_t nofEdges) override;
	void profile(AdjacencyType edges) override;

protected:
	void _createCompressionBuffers();
	void _allocateOutputBuffersCompress(unsigned voxelsPerBatch);
	void _calculateLimitsCompress(uint32_t nofEdges);

	bool _createBottomFillProgramCompress();

	void _acquireGpuDataCompress(uint32_t startingVoxelAbsoluteIndex, uint32_t batchSize);
		bool _isChunkDescValid(uint16_t desc) const;
		void _copyChunk(const uint32_t* gpuData, uint32_t chunkStart, uint32_t* dstData, uint32_t chunkSize);
		uint32_t _getNextChunkSize(int remainingSize, uint32_t chunkSize) const;

	void _bindBuffersCompress();
	void _unbindBuffersCompress();
	
	void _clearCompressionBuffers();

	uint32_t _findNearestHigherPow2(uint32_t val) const;

private:

	//Compression stuff
	struct Limits
	{
		uint32_t chunkSizeNofBits;
		uint32_t maxChunksPerParent;
	};

	Limits _limits;

	std::shared_ptr<ge::gl::Buffer> _parentSubbuffCounter;	//uvec2
	std::shared_ptr<ge::gl::Buffer> _chunkCounter;			//uint32_t
	std::shared_ptr<ge::gl::Buffer> _chunkDesc;				//uint16_t
	std::shared_ptr<ge::gl::Buffer> _currentChunkId;		//u16vec2
	std::shared_ptr<ge::gl::Buffer> _parentEdges;
};