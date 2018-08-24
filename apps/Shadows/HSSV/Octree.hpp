#pragma once

#include "AABB.hpp"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>

#define OCTREE_NUM_CHILDREN 8

typedef uint64_t BitmaskType;
constexpr size_t BitmaskTypeSizeBits = 8*sizeof(BitmaskType);

int ipow(int base, int exp);

struct Node
{
	AABB volume;

	std::unordered_map<BitmaskType, std::vector<uint32_t>> edgesAlwaysCastMap;
	std::unordered_map<BitmaskType, std::vector<uint32_t>> edgesMayCastMap;

	bool isValid() const
	{
		return volume.isValid();
	}

	void clear()
	{
		edgesMayCastMap.clear();
		edgesAlwaysCastMap.clear();
		volume = AABB();
	}

	void shrinkEdgeVectors()
	{
		for(auto e : edgesMayCastMap)
			e.second.shrink_to_fit();

		for(auto e : edgesAlwaysCastMap)
			e.second.shrink_to_fit();
	}

	void sortEdgeVectors()
	{
		for (auto e : edgesMayCastMap)
			std::sort(e.second.begin(), e.second.end());

		for (auto e : edgesAlwaysCastMap)
			std::sort(e.second.begin(), e.second.end());
	}
};


class Octree
{
public:

	Octree(unsigned int maxRecursionDepth, const AABB& volume);

	AABB getNodeVolume(unsigned int index) const;

	int getNodeParent(unsigned int nodeID) const;
	int getNodeRecursionLevel(unsigned int nodeID) const;
	int getNodeIdInLevel(unsigned int nodeID) const;
	int getNodeIdInLevel(unsigned int nodeID, unsigned int level) const;
	int getNodeIndexWithinParent(unsigned int nodeID) const;
	int getNodeIndexWithinParent(unsigned int nodeID, unsigned int parent) const;
	int getChildrenStartingId(unsigned int nodeID) const;

	std::vector<unsigned int> getLevelSizeInclusiveSum() const { return _levelSizesInclusiveSum; }

	void splitNode(unsigned int nodeID);
	void deleteNode(unsigned int nodeID);
	void deleteNodeSubtree(unsigned int nodeID);

	Node* getNode(unsigned int nodeID);
	const Node* getNode(unsigned int nodeID) const;

	bool nodeExists(unsigned int nodeID) const;
	bool childrenExist(unsigned int nodeID) const;

	unsigned int getNumNodesInPreviousLevels(int level) const;
	unsigned int getDeepestLevel() const;
	unsigned int getTotalNumNodes() const;
	int getLevelFirstNodeID(unsigned int level) const;
	int getNumNodesInLevel(unsigned int level) const;

	uint64_t getOctreeSizeBytes() const;

	void makeNodesFit();

	void setCompressionRatio(unsigned int ratio) { _treeCompressionRatio = ratio; }
	unsigned int getCompressionRatio() const { return _treeCompressionRatio; }

private:
	unsigned int _deepestLevel;

	void _generateLevelSizes();
	void _init(const AABB& volume);
	void _expandWholeOctree();

	void _createChild(const AABB& parentSpace, unsigned int childID, unsigned int indexWithinParent);
	int _getCorrespondingChildIndexFromPoint(unsigned int nodeID, const glm::vec3& point) const;
	bool _isPointInsideOctree(const glm::vec3& point) const;

	std::vector<Node> _nodes;

	std::vector<unsigned int> _levelSizesInclusiveSum;

	unsigned int _treeCompressionRatio = 0;
};