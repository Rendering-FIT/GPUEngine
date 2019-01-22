#pragma once

#include "IGpuOctreeLoader.hpp"

class GpuOctreeLoaderCompress8 : public IGpuOctreeLoader
{
public:
	void addEdgesOnLowestLevel(AdjacencyType edges) override;
	bool init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, unsigned int nofEdges) override;
	void profile(AdjacencyType edges) override;

protected:
	void _createCompressionBuffers();
	void _allocateOutputBuffersCompress(unsigned voxelsPerBatch);
	void _calculateLimitsCompress(unsigned int nofEdges);

	bool _createBottomFillProgramCompress();

	void _acquireGpuDataCompress(unsigned int startingVoxelAbsoluteIndex, unsigned int batchSize);
		bool _isChunkDescValid(uint16_t desc) const;
		void _copyChunk(const uint32_t* gpuData, uint32_t chunkStart, uint32_t* dstData, uint32_t chunkSize);
		unsigned int _getNextChunkSize(int remainingSize, unsigned int chunkSize) const;

	void _bindBuffersCompress();
	void _unbindBuffersCompress();
	
	void _clearCompressionBuffers();

	unsigned int _findNearestHigherPow2(unsigned int val) const;

private:

	//Compression stuff
	struct Limits
	{
		unsigned int chunkSizeNofBits;
		unsigned int maxChunksPerParent;

	};

	Limits _limits;

	std::shared_ptr<ge::gl::Buffer> _parentSubbuffCounter;	//uvec2
	std::shared_ptr<ge::gl::Buffer> _chunkCounter;			//uint32_t
	std::shared_ptr<ge::gl::Buffer> _chunkDesc;				//uint16_t
	std::shared_ptr<ge::gl::Buffer> _currentChunkId;		//u16vec2
	std::shared_ptr<ge::gl::Buffer> _parentEdges;
};