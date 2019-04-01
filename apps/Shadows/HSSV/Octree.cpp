#include "Octree.hpp"

#include "GeometryOperations.hpp"
#include <stack>
#include <iostream>
#include <string>

int ipow(int base, int exp)
{
	int result = 1;
	while (exp)
	{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		base *= base;
	}

	return result;
}

Octree::Octree(uint32_t deepestLevel, const AABB& volume)
{
	_deepestLevel = deepestLevel;

	_generateLevelSizes();

	_init(volume);
}

void Octree::_generateLevelSizes()
{
	_levelSizesInclusiveSum.clear();

	uint32_t prefixSum = 0;

	for(uint32_t i=0; i<= _deepestLevel; ++i)
	{
		const uint32_t levelSize = ipow(OCTREE_NUM_CHILDREN, i);
		_levelSizesInclusiveSum.push_back(levelSize + prefixSum);
		prefixSum += levelSize;
	}
}

void Octree::_init(const AABB& volume)
{
	Node n;
	n.volume = volume;

	_nodes.resize(getTotalNumNodes());
	_nodes[0] = n;

	_expandWholeOctree();
}

Node* Octree::getNode(uint32_t nodeID)
{
	if (nodeID > getTotalNumNodes() || !_nodes[nodeID].volume.isValid())
		return nullptr;

	return &(_nodes[nodeID]);
}

const Node* Octree::getNode(uint32_t nodeID) const
{
	if (nodeID > getTotalNumNodes() || !_nodes[nodeID].volume.isValid())
		return nullptr;

	return &(_nodes[nodeID]);
}

AABB Octree::getNodeVolume(uint32_t nodeID) const
{
	assert(nodeExists(nodeID));
	
	const auto n = getNode(nodeID);

	if (n)
		return n->volume;

	return AABB();
}

int Octree::getNodeParent(uint32_t nodeID) const
{
	if (nodeID == 0)
		return -1;
	
	const int nodeLevel = getNodeRecursionLevel(nodeID);
	
	assert(nodeLevel >= 0);

	const int idInLevel = getNodeIdInLevel(nodeID, nodeLevel);

	const int parentRelativeID = idInLevel / OCTREE_NUM_CHILDREN;

	return parentRelativeID + getNumNodesInPreviousLevels(nodeLevel - 1);
}

int Octree::getNodeRecursionLevel(uint32_t nodeID) const
{
	int level = 0;
	for(auto size : _levelSizesInclusiveSum)
	{
		if (nodeID < size)
			return level;

		++level;
	}

	return -1;
}

int Octree::getNodeIdInLevel(uint32_t nodeID) const
{
	int level = getNodeRecursionLevel(nodeID);

	return level > 0 ? getNodeIdInLevel(nodeID, level) : -1;
}

int Octree::getNodeIdInLevel(uint32_t nodeID, uint32_t level) const
{
	return nodeID - getNumNodesInPreviousLevels(level);
}

int Octree::_getCorrespondingChildIndexFromPoint(uint32_t nodeID, const glm::vec3& point) const
{
	const glm::vec3 centerPoint = getNodeVolume(nodeID).getCenterPoint();

	int r = (point.x >= centerPoint.x) + 2 * (point.y >= centerPoint.y) + 4 * (point.z >= centerPoint.z);
	return r;
}

bool Octree::nodeExists(uint32_t nodeID) const
{
	return (nodeID < getTotalNumNodes()) && _nodes[nodeID].volume.isValid();
}

bool Octree::childrenExist(uint32_t nodeID) const
{
	int startID = getChildrenStartingId(nodeID);

	if (startID < 0)
		return false;

	return nodeExists(startID);
}

void Octree::splitNode(uint32_t nodeID)
{
	AABB nodeVolume = getNodeVolume(nodeID);

	const int startingIndex = getChildrenStartingId(nodeID);

	for(uint32_t i=0; i<OCTREE_NUM_CHILDREN; ++i)
		_createChild(nodeVolume, startingIndex + i, i);
}

void Octree::deleteNode(uint32_t nodeID)
{
	_nodes[nodeID].clear();
}

void Octree::deleteNodeSubtree(unsigned nodeID)
{
	_nodes[nodeID].clear();

	const int level = getNodeRecursionLevel(nodeID);

	if(level!=int(_deepestLevel))
	{
		const uint32_t startingChild = getChildrenStartingId(nodeID);

		for (uint32_t i = startingChild; i < (startingChild + OCTREE_NUM_CHILDREN); ++i)
			deleteNodeSubtree(i);
	}
}

uint32_t Octree::getNumNodesInPreviousLevels(int level) const
{
	const int l = level - 1;

	assert(l < int(_levelSizesInclusiveSum.size()));

	if (l < 0 || l> (int)_deepestLevel)
		return 0;

	return _levelSizesInclusiveSum[l];
}

int Octree::getChildrenStartingId(uint32_t nodeID) const
{
	const int nodeLevel = getNodeRecursionLevel(nodeID);

	if (nodeLevel > int(_deepestLevel))
		return -1;

	assert((nodeLevel >= 0) && nodeLevel<=(int)_deepestLevel);

	const int idInLevel = getNodeIdInLevel(nodeID, nodeLevel);

	assert(idInLevel >= 0);

	return OCTREE_NUM_CHILDREN*idInLevel + _levelSizesInclusiveSum[nodeLevel];
}

void Octree::_createChild(const AABB& parentSpace, uint32_t newNodeId, uint32_t indexWithinParent)
{
	assert(!nodeExists(newNodeId));

	Node n;
	glm::vec3 minPoint = parentSpace.getMinPoint();

	glm::vec3 isInPlus;
	isInPlus.x = (indexWithinParent & 1u) != 0 ? 1.0f : 0.f;
	isInPlus.y = (indexWithinParent & 2u) != 0 ? 1.0f : 0.f;
	isInPlus.z = (indexWithinParent & 4u) != 0 ? 1.0f : 0.f;

	glm::vec3 parentHalfExtents = parentSpace.getExtents() / glm::vec3(2.0f);

	glm::vec3 minPointOffset = isInPlus * parentHalfExtents;

	minPoint += minPointOffset;
	glm::vec3 maxPoint = minPoint + parentHalfExtents;

	n.volume = AABB(minPoint, maxPoint);

	_nodes[newNodeId] = n;
}

int Octree::getNodeIndexWithinParent(uint32_t nodeID) const
{
	const int parent = getNodeParent(nodeID);

	assert(parent >= 0);

	return getNodeIndexWithinParent(nodeID, parent);
}

int Octree::getNodeIndexWithinParent(uint32_t nodeID, uint32_t parent) const
{
	const int startID = getChildrenStartingId(parent);

	return nodeID - startID;
}

bool Octree::_isPointInsideOctree(const glm::vec3& point) const
{
	return GeometryOps::testAabbPointIsInsideOrOn(_nodes[0].volume, point);
}

uint32_t Octree::getDeepestLevel() const
{
	return _deepestLevel;
}

uint32_t Octree::getTotalNumNodes() const
{
	return _levelSizesInclusiveSum[_deepestLevel];
}

int Octree::getLevelFirstNodeID(uint32_t level) const
{
	if (level > _deepestLevel)
		return -1;

	if (level == 0)
		return 0;

	return _levelSizesInclusiveSum[level - 1];
}

int Octree::getNumNodesInLevel(uint32_t level) const
{
	if (level > _deepestLevel)
		return -1;

	return ipow(OCTREE_NUM_CHILDREN, level);
}

uint64_t Octree::getOctreeSizeBytes() const
{
	uint64_t numIndices = 0;
	for(const auto& node : _nodes)
	{
		for(const auto& item : node.edgesAlwaysCastMap)
			numIndices += item.second.size();

		for (const auto& item : node.edgesMayCastMap)
			numIndices += item.second.size();
	}

	return sizeof(uint32_t) * numIndices;
}

void Octree::makeNodesFit()
{
	_nodes.shrink_to_fit();
}

void Octree::_expandWholeOctree()
{
	std::stack<uint32_t> nodeStack;

	nodeStack.push(0);

	const int deepestLevel = getDeepestLevel();

	while (!nodeStack.empty())
	{
		const auto node = nodeStack.top();
		nodeStack.pop();

		splitNode(node);

		const auto level = getNodeRecursionLevel(node);

		if (level < (deepestLevel - 1))
		{
			const auto startingChild = getChildrenStartingId(node);
			for (int i = 0; i < OCTREE_NUM_CHILDREN; ++i)
				nodeStack.push(startingChild + i);
		}
	}

	makeNodesFit();
}

uint32_t Octree::getLevelSize(uint32_t level) const
{
	if (level > getDeepestLevel())
		return 0;

	return ipow(OCTREE_NUM_CHILDREN, level);
}

void Octree::printNodePathToRoot(int nodeId) const
{
	std::cout << "Node path: ";
	while (nodeId >= 0)
	{
		std::cout << std::to_string(nodeId);
		nodeId = getNodeParent(nodeId);
		if (nodeId >= 0)
			std::cout << " -> ";
	}

	std::cout << std::endl;
}