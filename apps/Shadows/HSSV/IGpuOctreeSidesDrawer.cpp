#include "IGpuOctreeSidesDrawer.hpp"
#include "OctreeVisitor.hpp"

IGpuOctreeSidesDrawer::IGpuOctreeSidesDrawer(std::shared_ptr<OctreeVisitor> visitor) : ISidesDrawer(visitor)
{
	m_compressionLevel = _visitor->getOctree()->getCompressionLevel();
}

void IGpuOctreeSidesDrawer::_loadOctreeToGpu()
{
	const uint32_t nofVoxels = _visitor->getOctree()->getTotalNumNodes();

	uint64_t remainingSize = _visitor->getOctree()->getOctreeSizeBytes();
	const uint64_t maxBufferSize = 2ull * 1024ull * 1024ull * 1024ull; //2GB
	uint32_t currentNode = 0;

	std::vector<uint32_t> nofEdgesPrefixSums;
	std::vector<uint32_t> compressedNodesInfo;
	std::vector<uint32_t> compressedNodesInfoIndexing;

	nofEdgesPrefixSums.reserve(nofVoxels + 1);
	compressedNodesInfoIndexing.reserve(nofVoxels);

	auto octree = _visitor->getOctree();

	while (remainingSize>0)
	{
		const uint64_t currentSize = remainingSize > maxBufferSize ? maxBufferSize : remainingSize;

		nofEdgesPrefixSums.push_back(0);

		std::shared_ptr<ge::gl::Buffer> buffer = std::make_shared<ge::gl::Buffer>(currentSize, nullptr);

		std::vector<uint32_t> dataVector;
		dataVector.resize(currentSize / sizeof(uint32_t));
		uint32_t* dataPtr = dataVector.data();

		uint64_t currentNumIndices = 0;

		while (currentNode<nofVoxels)
		{
			auto node = octree->getNode(currentNode);

			uint64_t sz = _visitor->getNofAllIndicesInNode(currentNode);

			if ((sz + currentNumIndices) * sizeof(uint32_t) > currentSize)
				break;

			currentNode++;

			compressedNodesInfoIndexing.push_back(uint32_t(compressedNodesInfo.size()));
			compressedNodesInfo.push_back(uint32_t(node->edgesMayCastMap.size()));
			compressedNodesInfo.push_back(uint32_t(node->edgesAlwaysCastMap.size()));

			for (const auto& subBuffer : node->edgesMayCastMap)
				_processSubBuffer(subBuffer, compressedNodesInfo, nofEdgesPrefixSums, dataPtr);

			for (const auto& subBuffer : node->edgesAlwaysCastMap)
				_processSubBuffer(subBuffer, compressedNodesInfo, nofEdgesPrefixSums, dataPtr);

			currentNumIndices += sz;
		}

		buffer->setData(dataPtr, dataVector.size() * sizeof(uint32_t));
		remainingSize -= currentNumIndices * sizeof(uint32_t);
		m_gpuOctreeBuffers.push_back(buffer);
		m_lastNodePerEdgebuffer.push_back(currentNode);
	}

	m_voxelNofPotentialSilhouetteEdgesPrefixSum = std::make_shared<ge::gl::Buffer>(nofEdgesPrefixSums.size() * sizeof(uint32_t), nofEdgesPrefixSums.data());
	m_compressedNodesInfoBuffer->alloc(compressedNodesInfo.size() * sizeof(uint32_t));
	m_compressedNodesInfoBuffer->setData(compressedNodesInfo.data());
	m_compressedNodesInfoIndexingBuffer->setData(compressedNodesInfoIndexing.data());
}



void IGpuOctreeSidesDrawer::_loadOctreeToGpu8BitOrNoCompress()
{
	const uint32_t nofVoxels = _visitor->getOctree()->getTotalNumNodes();

	uint64_t remainingSize = _visitor->getOctree()->getOctreeSizeBytes();
	const uint64_t maxBufferSize = 2ull * 1024ull * 1024ull * 1024ull; //2GB
	uint32_t currentNode = 0;

	std::vector<uint32_t> nofEdgesPrefixSums;

	auto octree = _visitor->getOctree();
	auto const compressionLevel = _visitor->getOctree()->getCompressionLevel();

	m_nofTotalSubbuffers = compressionLevel == 0 ? 1 : 249;
	m_subBufferCorrection = compressionLevel == 0 ? 0 : 7; //we skip 0-6 as they have less then 3 bits set
	nofEdgesPrefixSums.reserve(2 * nofVoxels *m_nofTotalSubbuffers);

	while (remainingSize>0)
	{
		const uint64_t currentSize = remainingSize > maxBufferSize ? maxBufferSize : remainingSize;

		nofEdgesPrefixSums.push_back(0);

		std::shared_ptr<ge::gl::Buffer> buffer = std::make_shared<ge::gl::Buffer>(currentSize, nullptr);

		std::vector<uint32_t> dataVector;
		dataVector.resize(currentSize / sizeof(uint32_t));
		uint32_t* dataPtr = dataVector.data();

		uint64_t currentNumIndices = 0;
		while (currentNode < nofVoxels)
		{
			auto node = octree->getNode(currentNode);

			uint64_t sz = _visitor->getNofAllIndicesInNode(currentNode);

			if ((sz + currentNumIndices) * sizeof(uint32_t) > currentSize)
				break;

			if (compressionLevel != 0)
			{
				//Pot edges
				for (uint32_t b = m_subBufferCorrection; b <= BitmaskAllSet; ++b)
				{
					BitmaskType bm = BitmaskType(b);
					auto ret = node->edgesMayCastMap.find(bm);
					if (ret != node->edgesMayCastMap.end() && node->edgesMayCastMap[bm].size()>0)
					{
						uint32_t const subbufferSize = uint32_t(node->edgesMayCastMap[bm].size());

						auto const lastOffset = nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1];

						memcpy(dataPtr + lastOffset, node->edgesMayCastMap[bm].data(), subbufferSize * sizeof(uint32_t));

						nofEdgesPrefixSums.push_back(lastOffset + subbufferSize);
					}
					else
					{
						nofEdgesPrefixSums.push_back(nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1]);
					}
				}

				//Sil edges
				for (uint32_t b = m_subBufferCorrection; b <= BitmaskAllSet; ++b)
				{
					BitmaskType bm = BitmaskType(b);
					auto ret = node->edgesAlwaysCastMap.find(bm);
					if (ret != node->edgesAlwaysCastMap.end() && node->edgesAlwaysCastMap[bm].size()>0)
					{
						uint32_t const subbufferSize = uint32_t(node->edgesAlwaysCastMap[bm].size());
						auto const lastOffset = nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1];
						memcpy(dataPtr + lastOffset, node->edgesAlwaysCastMap[bm].data(), subbufferSize * sizeof(uint32_t));
						nofEdgesPrefixSums.push_back(lastOffset + subbufferSize);
					}
					else
					{
						nofEdgesPrefixSums.push_back(nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1]);
					}
				}
			}
			else
			{
				BitmaskType bm = BitmaskAllSet;
				//pot
				{
					auto ret = node->edgesMayCastMap.find(bm);
					if (ret != node->edgesMayCastMap.end() && node->edgesMayCastMap[bm].size()>0)
					{
						uint32_t const subbufferSize = uint32_t(node->edgesMayCastMap[bm].size());
						auto const lastOffset = nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1];
						memcpy(dataPtr + lastOffset, node->edgesMayCastMap[bm].data(), subbufferSize * sizeof(uint32_t));
						nofEdgesPrefixSums.push_back(lastOffset + subbufferSize);
					}
					else
					{
						nofEdgesPrefixSums.push_back(nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1]);
					}
				}

				{
					//sil
					auto ret = node->edgesAlwaysCastMap.find(bm);
					if (ret != node->edgesAlwaysCastMap.end() && node->edgesAlwaysCastMap[bm].size() > 0)
					{
						uint32_t const subbufferSize = uint32_t(node->edgesAlwaysCastMap[bm].size());
						auto const lastOffset = nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1];
						memcpy(dataPtr + lastOffset, node->edgesAlwaysCastMap[bm].data(), subbufferSize * sizeof(uint32_t));
						nofEdgesPrefixSums.push_back(lastOffset + subbufferSize);
					}
					else
					{
						nofEdgesPrefixSums.push_back(nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1]);
					}
				}
			}

			currentNumIndices += sz;
			currentNode++;
		}

		buffer->setData(dataPtr, dataVector.size() * sizeof(uint32_t));
		remainingSize -= currentNumIndices * sizeof(uint32_t);
		m_gpuOctreeBuffers.push_back(buffer);
		m_lastNodePerEdgebuffer.push_back(currentNode);
	}

	m_voxelNofPotentialSilhouetteEdgesPrefixSum = std::make_shared<ge::gl::Buffer>(nofEdgesPrefixSums.size() * sizeof(uint32_t), nofEdgesPrefixSums.data());
}

void IGpuOctreeSidesDrawer::_processSubBuffer(
	const std::unordered_map<BitmaskType, std::vector<uint32_t>>::value_type& subBuffer,
	std::vector<uint32_t>& compressedNodesInfo,
	std::vector<uint32_t>& nofEdgesPrefixSums,
	uint32_t* gpuMappedBuffer
)
{
	const auto subBufferSize = subBuffer.second.size();
	assert(subBufferSize != 0);

	memcpy(gpuMappedBuffer + nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1], subBuffer.second.data(), subBufferSize * sizeof(uint32_t));

	const auto startIndex = nofEdgesPrefixSums.size() - 1;

	nofEdgesPrefixSums.push_back(nofEdgesPrefixSums[nofEdgesPrefixSums.size() - 1] + uint32_t(subBufferSize));

	//Push compression ID
	_breakCompressionIdToUintsAndPush(subBuffer.first, compressedNodesInfo);

	//Push starting index
	compressedNodesInfo.push_back(uint32_t(startIndex));
}

void IGpuOctreeSidesDrawer::_breakCompressionIdToUintsAndPush(const BitmaskType& id, std::vector<uint32_t>& vectorToStore) const
{
	if (std::is_same<unsigned char, BitmaskType>::value)
		vectorToStore.push_back(id);
	else
	{
		const uint32_t nofUints = BitmaskTypeSizeBits / 32;
		const uint32_t* val = reinterpret_cast<const uint32_t*>(&id);

		for (uint32_t i = 0; i < nofUints; ++i)
			vectorToStore.push_back(val[i]);
	}
}

void IGpuOctreeSidesDrawer::_getMaxPossibleEdgeCountInTraversal(size_t& potential, size_t& silhouette, size_t& maxInVoxel, size_t& maxPath) const
{
	potential = 0;
	silhouette = 0;
	maxInVoxel = 0;
	maxPath = 0;

	const uint32_t maxLevel = _visitor->getOctree()->getDeepestLevel();
	for (uint32_t i = 0; i <= maxLevel; ++i)
	{
		size_t pot = 0, silh = 0;
		_getMaximumNofEdgesInLevel(i, pot, silh);

		maxInVoxel = std::max(pot, maxInVoxel);
		maxInVoxel = std::max(silh, maxInVoxel);

		maxPath += pot;
		maxPath += silh;

		potential += pot;
		silhouette += silh;
	}
}

void IGpuOctreeSidesDrawer::_getNofEdgesInNode(uint32_t nodeId, size_t& potential, size_t& silhouette) const
{
	potential = silhouette = 0;
	const auto node = _visitor->getOctree()->getNode(nodeId);
	for (const auto& buffer : node->edgesAlwaysCastMap)
		silhouette += buffer.second.size();

	for (const auto& buffer : node->edgesMayCastMap)
		potential += buffer.second.size();
}

void IGpuOctreeSidesDrawer::_getMaximumNofEdgesInLevel(uint32_t level, size_t& potential, size_t& silhouette) const
{
	potential = 0;
	silhouette = 0;

	const auto startingIndex = _visitor->getOctree()->getLevelFirstNodeID(level);
	const auto levelSize = ipow(OCTREE_NUM_CHILDREN, level);

	for (int i = 0; i<levelSize; ++i)
	{
		size_t nodePot = 0, nodeSil = 0;
		_getNofEdgesInNode(startingIndex + i, nodePot, nodeSil);
		potential = std::max(potential, nodePot);
		silhouette = std::max(silhouette, nodeSil);
	}
}

uint32_t IGpuOctreeSidesDrawer::_getNofIndicesPerBitmask() const
{
	//m_bitMasks[0].size() - because all bitmask arrays are of same size
	return m_bitMasks[0].size();
}

void IGpuOctreeSidesDrawer::_calcBitMasks8(unsigned int minBits)
{
	m_bitMasks.resize(8);

	for (uint32_t i = 1; i<256; ++i)
	{
		std::bitset<8> num = i;
		if (num.count() < minBits)
			continue;

		for (uint32_t b = 0; b<8; ++b)
		{
			if (num[b])
				m_bitMasks[b].push_back(BitmaskType(num.to_ulong()));
		}
	}
}