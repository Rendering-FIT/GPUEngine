#pragma once

#include <geGL/Buffer.h>
#include <geGL/Program.h>

#include "AdjacencyEdgeWrapper.hpp"
#include "Octree.hpp"
#include "GpuEdges.hpp"

#define USE_COMPRESS

#define MAX_BUFFER_SIZE (2816ull*1024ull*1024ull)

//if we propagate only those edges who have at least 3 bits set, 
//it makes 37 buffers (0, 1, 2 bits) unused
//So minimal amount of memory is 219 * chunkSize
#define MAX_NOF_USABLE_BUFFERS 219u

#define MAX_NOF_SUBBUFFERS 256u

#define MIN_SUBBUFFER_SIZE_UINTS 2u

#define MAX_NOF_CHUNKS 400u

//Empiracally determined max amount of edges, that will reside in one subbuffer
const float reductionRatio = 0.79f;

class GpuOctreeLoader
{
public:
	
	void addEdgesOnLowestLevelGPU(AdjacencyType edges);
	void addEdgesOnLowestLevelGPUCompress8(AdjacencyType edges);

	bool init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, unsigned int subgroupSize, unsigned int nofEdges);

	void profile(AdjacencyType edges, unsigned int subgroupSize);

	void profile1(AdjacencyType edges);

protected:
	//--
	void _allocateOutputBuffersCompress(unsigned voxelsPerBatch, unsigned nofEdges);
	//--

	void _createBuffers();
	bool _createBottomFillProgram(unsigned int numSubgroupsPerWG, unsigned int subgroupSize, unsigned int shmSizePerSubgroup);
	bool _createBottomFillProgramCompress(unsigned int nofEdges);
	
	unsigned int _findNearestHigherPow2(unsigned int val);

	void _calculateLimitsCompress(unsigned int nofEdges);

	void _serializeDeepestLevelVoxels(std::vector<glm::vec3>& voxels);

	void _allocateOutputBuffersAndVoxels(unsigned int voxelsPerBatch, unsigned int numEdges);
	void _clearAtomicCounter();

	void _loadVoxels(const std::vector<glm::vec3>& voxels, unsigned int startingIndex, unsigned int batchSize);

	void _bindBuffers();
	void _unbindBuffers();

	void _bindBuffersCompress();
	void _unbindBuffersCompress();
	void _clearCompressionBuffers();


	void _acquireGpuData(unsigned int startingVoxelAbsoluteIndex, unsigned int batchSize, unsigned int numEdges);
		void _copyBuffer(std::shared_ptr<ge::gl::Buffer> buffer, void* destination, size_t size);

	void _acquireGpuDataCompress(unsigned int startingVoxelAbsoluteIndex, unsigned int batchSize, unsigned int numEdges);
		bool _isChunkDescValid(uint16_t desc) const;
		void _copyChunk(const uint32_t* gpuData, uint32_t chunkStart, uint32_t* dstData, uint32_t chunkSize);
		unsigned int _getNextChunkSize(int remainingSize, unsigned int chunkSize) const;

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

	std::shared_ptr<ge::gl::Buffer> _shit;

	std::shared_ptr<ge::gl::Program> _fillProgram;

	std::vector<uint32_t> _bufferNofPotential;
	std::vector<uint32_t> _bufferNofSilhouette;

	unsigned int _wgSize = 0;
	unsigned int _cacheSize = 0;
};
