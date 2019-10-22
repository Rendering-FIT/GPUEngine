#pragma once
#include "ISidesDrawer.hpp"
#include <unordered_map>
#include "Octree.hpp"

class IGpuOctreeSidesDrawer : public ISidesDrawer
{
protected:
	IGpuOctreeSidesDrawer(std::shared_ptr<OctreeVisitor> visitor);
	virtual ~IGpuOctreeSidesDrawer() {}

	void _loadOctreeToGpu();
	void _loadOctreeToGpu8BitOrNoCompress();

	void _processSubBuffer(
		const std::unordered_map<BitmaskType, std::vector<uint32_t>>::value_type& subBuffer,
		std::vector<uint32_t>& compressedNodesInfo,
		std::vector<uint32_t>& nofEdgesPrefixSums,
		uint32_t* gpuMappedBuffer
	);

	void _breakCompressionIdToUintsAndPush(const BitmaskType& id, std::vector<uint32_t>& vectorToStore) const;

	void _getMaxPossibleEdgeCountInTraversal(size_t& potentialPath, size_t& silhouettePath, size_t& maxInVoxel, size_t& maxPath) const;
	void _getMaximumNofEdgesInLevel(uint32_t level, size_t& potential, size_t& silhouette) const;
	void _getNofEdgesInNode(uint32_t nodeId, size_t& potential, size_t& silhouette) const;

	uint32_t _getNofIndicesPerBitmask() const;
	void _calcBitMasks8(unsigned int minBits);

protected:
	std::vector<std::shared_ptr<ge::gl::Buffer>> m_gpuOctreeBuffers;
	std::vector<uint32_t> m_lastNodePerEdgebuffer;
	std::vector< std::vector<uint32_t> > m_bitMasks;

	std::shared_ptr<ge::gl::Buffer> m_compressedNodesInfoBuffer = nullptr;
	std::shared_ptr<ge::gl::Buffer> m_compressedNodesInfoIndexingBuffer = nullptr;
	std::shared_ptr<ge::gl::Buffer> m_voxelNofPotentialSilhouetteEdgesPrefixSum = nullptr;

	uint32_t m_nofTotalSubbuffers = 0;
	uint32_t m_subBufferCorrection = 0;
	uint32_t m_compressionLevel = 0;
};
