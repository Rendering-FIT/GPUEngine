#pragma once

#include "AABB.hpp"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>

#define OCTREE_NUM_CHILDREN 8


typedef unsigned char BitmaskType;
//typedef uint64_t BitmaskType;

constexpr size_t BitmaskTypeSizeBits = 8*sizeof(BitmaskType);
constexpr BitmaskType BitmaskAllSet = BitmaskType(-1);

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

	Octree(uint32_t maxRecursionDepth, const AABB& volume);

	AABB getNodeVolume(uint32_t index) const;

	int getNodeParent(uint32_t nodeID) const;
	int getNodeRecursionLevel(uint32_t nodeID) const;
	int getNodeIdInLevel(uint32_t nodeID) const;
	int getNodeIdInLevel(uint32_t nodeID, uint32_t level) const;
	int getNodeIndexWithinParent(uint32_t nodeID) const;
	int getNodeIndexWithinParent(uint32_t nodeID, uint32_t parent) const;
	int getChildrenStartingId(uint32_t nodeID) const;

	std::vector<uint32_t> getLevelSizeInclusiveSum() const { return _levelSizesInclusiveSum; }

	void splitNode(uint32_t nodeID);
	void deleteNode(uint32_t nodeID);
	void deleteNodeSubtree(uint32_t nodeID);

	Node* getNode(uint32_t nodeID);
	const Node* getNode(uint32_t nodeID) const;

	bool nodeExists(uint32_t nodeID) const;
	bool childrenExist(uint32_t nodeID) const;

	uint32_t getNumNodesInPreviousLevels(int level) const;
	uint32_t getDeepestLevel() const;
	uint32_t getTotalNumNodes() const;
	int getLevelFirstNodeID(uint32_t level) const;
	int getNumNodesInLevel(uint32_t level) const;

	uint64_t getOctreeSizeBytes() const;

	void makeNodesFit();

	void setCompressionLevel(uint32_t ratio) { _treeCompressionRatio = ratio; }
	uint32_t getCompressionLevel() const { return _treeCompressionRatio; }
	uint32_t getLevelSize(uint32_t level) const;

	void printNodePathToRoot(int nodeId) const;

private:
	uint32_t _deepestLevel;

	void _generateLevelSizes();
	void _init(const AABB& volume);
	void _expandWholeOctree();

	void _createChild(const AABB& parentSpace, uint32_t childID, uint32_t indexWithinParent);
	int _getCorrespondingChildIndexFromPoint(uint32_t nodeID, const glm::vec3& point) const;
	bool _isPointInsideOctree(const glm::vec3& point) const;

	std::vector<Node> _nodes;

	std::vector<uint32_t> _levelSizesInclusiveSum;

	uint32_t _treeCompressionRatio = 0;
};