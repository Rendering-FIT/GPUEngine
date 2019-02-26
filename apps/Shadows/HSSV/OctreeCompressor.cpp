#include "OctreeCompressor.hpp"

#include <unordered_set>
#include <iterator>

void OctreeCompressor::compressOctree(std::shared_ptr<OctreeVisitor> visitor, uint32_t compressLevelHeight_1or2)
{
	if (!visitor)
		return;

	_visitor = visitor;

	const int deepestLevel = _visitor->getOctree()->getDeepestLevel();
	const int levelSize = ipow(OCTREE_NUM_CHILDREN, deepestLevel);

	const int startingIndex = _visitor->getOctree()->getNumNodesInPreviousLevels(deepestLevel);
	const int stopIndex = _visitor->getOctree()->getTotalNumNodes();
	const int nofSyblings = ipow(OCTREE_NUM_CHILDREN, compressLevelHeight_1or2);

	#pragma omp parallel for 
	for (int index = startingIndex; index < stopIndex; index += nofSyblings)
	{
		_compressSyblings(index, true,  compressLevelHeight_1or2);
		_compressSyblings(index, false, compressLevelHeight_1or2);
	}
}

std::bitset<BitmaskTypeSizeBits> OctreeCompressor::checkEdgePresence(uint32_t edge, uint32_t startingId, bool checkPotential, uint32_t nofSyblings) const
{
	std::bitset<BitmaskTypeSizeBits> retval(0);
	auto octree = _visitor->getOctree();

	for (uint32_t i = 0; i<nofSyblings; ++i)
	{
		const auto node = octree->getNode(i + startingId);
		const auto& buffer = checkPotential ? node->edgesMayCastMap[BitmaskAllSet] : node->edgesAlwaysCastMap[BitmaskAllSet];
		if (std::binary_search(buffer.begin(), buffer.end(), edge))
			retval[i] = true;
	}

	return retval;
}

void OctreeCompressor::_compressSyblings(uint32_t startingID, bool processPotential, uint32_t compressLevelHeight_1or2)
{
	std::unordered_set<uint32_t> allEdgesSet;
	int parent = startingID;
	for (uint32_t i = 0; i < compressLevelHeight_1or2; ++i)
		parent = _visitor->getOctree()->getNodeParent(parent);

	const auto nofSyblings = ipow(OCTREE_NUM_CHILDREN, compressLevelHeight_1or2);

	for (int i = 0; i < nofSyblings; ++i)
	{
		const auto node = _visitor->getOctree()->getNode(startingID + i);
		const auto& buffer = processPotential ? node->edgesMayCastMap[BitmaskAllSet] : node->edgesAlwaysCastMap[BitmaskAllSet];
		std::copy(buffer.begin(), buffer.end(), std::inserter(allEdgesSet, allEdgesSet.end()));
	}

	for (const auto e : allEdgesSet)
	{
		const auto bitmask = checkEdgePresence(e, startingID, processPotential, nofSyblings);
		if (bitmask.count()>(1+ compressLevelHeight_1or2))
		{
			_assignEdgeToNode(parent, e, processPotential, bitmask.to_ullong());
			_removeEdgeFromSyblingsSparse(startingID, e, processPotential, bitmask, nofSyblings);
		}
	}
}

void OctreeCompressor::_removeEdgeFromSyblingsSparse(uint32_t startingID, uint32_t edge, bool checkPotential, const std::bitset<BitmaskTypeSizeBits>& bitmask, uint32_t nofSyblings)
{
	for (uint32_t i = 0; i<nofSyblings; ++i)
	{
		if (!bitmask[i])
			continue;

		auto node = _visitor->getOctree()->getNode(startingID + i);

		if (node)
		{
			if (checkPotential)
				node->edgesMayCastMap[BitmaskAllSet].erase(std::lower_bound(node->edgesMayCastMap[BitmaskAllSet].begin(), node->edgesMayCastMap[BitmaskAllSet].end(), edge));
			else
				node->edgesAlwaysCastMap[BitmaskAllSet].erase(std::lower_bound(node->edgesAlwaysCastMap[BitmaskAllSet].begin(), node->edgesAlwaysCastMap[BitmaskAllSet].end(), edge));
		}
	}
}

void OctreeCompressor::_assignEdgeToNodeParent(uint32_t node, uint32_t edge, bool propagatePotential, BitmaskType subBufferId)
{
	const int parent = _visitor->getOctree()->getNodeParent(node);

	assert(parent >= 0);

	_assignEdgeToNode(parent, edge, propagatePotential, subBufferId);
}

void OctreeCompressor::_assignEdgeToNode(uint32_t node, uint32_t edge, bool propagatePotential, BitmaskType subBufferId)
{
	auto n = _visitor->getOctree()->getNode(node);

	if (n)
	{
		if (propagatePotential)
			n->edgesMayCastMap[subBufferId].push_back(edge);
		else
			n->edgesAlwaysCastMap[subBufferId].push_back(edge);
	}
}
