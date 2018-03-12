#include "Octree.hpp"

#include "GeometryOperations.hpp"

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

Octree::Octree(unsigned int deepestLevel, const AABB& volume)
{
	_deepestLevel = deepestLevel;

	_generateLevelSizes();

	_init(volume);
}

void Octree::_generateLevelSizes()
{
	_levelSizesInclusiveSum.clear();

	unsigned int prefixSum = 0;

	for(unsigned int i=0; i<= _deepestLevel; ++i)
	{
		const unsigned int levelSize = ipow(OCTREE_NUM_CHILDREN, i);
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
}

Node* Octree::getNode(unsigned int nodeID)
{
	if (nodeID > getTotalNumNodes() || !_nodes[nodeID].volume.isValid())
		return nullptr;

	return &(_nodes[nodeID]);
}

const Node* Octree::getNode(unsigned int nodeID) const
{
	if (nodeID > getTotalNumNodes() || !_nodes[nodeID].volume.isValid())
		return nullptr;

	return &(_nodes[nodeID]);
}

AABB Octree::getNodeVolume(unsigned int nodeID) const
{
	assert(nodeExists(nodeID));
	
	const auto n = getNode(nodeID);

	if (n)
		return n->volume;

	return AABB();
}

int Octree::getNodeParent(unsigned int nodeID) const
{
	if (nodeID == 0)
		return -1;
	
	const int nodeLevel = getNodeRecursionLevel(nodeID);
	
	assert(nodeLevel >= 0);

	const int idInLevel = getNodeIdInLevel(nodeID, nodeLevel);

	const int parentRelativeID = idInLevel / OCTREE_NUM_CHILDREN;

	return parentRelativeID + getNumNodesInPreviousLevels(nodeLevel - 1);
}

int Octree::getNodeRecursionLevel(unsigned int nodeID) const
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

int Octree::getNodeIdInLevel(unsigned int nodeID) const
{
	int level = getNodeRecursionLevel(nodeID);

	return level > 0 ? getNodeIdInLevel(nodeID, level) : -1;
}

int Octree::getNodeIdInLevel(unsigned int nodeID, unsigned int level) const
{
	return nodeID - getNumNodesInPreviousLevels(level);
}

int Octree::getLowestLevelCellIndexFromPointInSpace(const glm::vec3& point)
{
	if (!_isPointInsideOctree(point))
		return -1;

	unsigned int currentLevel = 0;
	unsigned int currentNode = 0;
	
	while(currentLevel <= _deepestLevel)
	{
		const int startingChild = getChildrenStartingId(currentNode);

		if (!nodeExists(startingChild))
			break;

		const int childIndex = _getCorrespondingChildIndexFromPoint(currentNode, point);

		currentNode = startingChild + childIndex;
		++currentLevel;
	}

	return currentNode;
}

int Octree::_getCorrespondingChildIndexFromPoint(unsigned int nodeID, const glm::vec3& point) const
{
	const glm::vec3 centerPoint = getNodeVolume(nodeID).getCenterPoint();

	int r = (point.x >= centerPoint.x) + 2 * (point.y >= centerPoint.y) + 4 * (point.z >= centerPoint.z);
	return r;
}

bool Octree::nodeExists(unsigned int nodeID) const
{
	return (nodeID < getTotalNumNodes()) && _nodes[nodeID].volume.isValid();
}

bool Octree::childrenExist(unsigned int nodeID) const
{
	int startID = getChildrenStartingId(nodeID);

	if (startID < 0)
		return false;

	return nodeExists(startID);
}

void Octree::splitNode(unsigned int nodeID)
{
	AABB nodeVolume = getNodeVolume(nodeID);

	const int startingIndex = getChildrenStartingId(nodeID);

	for(unsigned int i=0; i<OCTREE_NUM_CHILDREN; ++i)
		_createChild(nodeVolume, startingIndex + i, i);
}

void Octree::deleteNode(unsigned int nodeID)
{
	_nodes[nodeID].clear();
}

void Octree::deleteNodeSubtree(unsigned nodeID)
{
	_nodes[nodeID].clear();

	const int level = getNodeRecursionLevel(nodeID);

	if(level!=_deepestLevel)
	{
		const unsigned int startingChild = getChildrenStartingId(nodeID);

		for (unsigned int i = startingChild; i < (startingChild + OCTREE_NUM_CHILDREN); ++i)
			deleteNodeSubtree(i);
	}
}

unsigned int Octree::getNumNodesInPreviousLevels(int level) const
{
	const int l = level - 1;

	assert(l < int(_levelSizesInclusiveSum.size()));

	if (l < 0 || l> (int)_deepestLevel)
		return 0;

	return _levelSizesInclusiveSum[l];
}

int Octree::getChildrenStartingId(unsigned int nodeID) const
{
	const int nodeLevel = getNodeRecursionLevel(nodeID);

	if (nodeLevel > _deepestLevel)
		return -1;

	assert((nodeLevel >= 0) && nodeLevel<=(int)_deepestLevel);

	const int idInLevel = getNodeIdInLevel(nodeID, nodeLevel);

	assert(idInLevel >= 0);

	return OCTREE_NUM_CHILDREN*idInLevel + _levelSizesInclusiveSum[nodeLevel];
}

void Octree::_createChild(const AABB& parentSpace, unsigned int newNodeId, unsigned int indexWithinParent)
{
	assert(!nodeExists(newNodeId));

	Node n;
	glm::vec3 minPoint = parentSpace.getMinPoint();

	const bool isInPlusX = (indexWithinParent & 1) != 0;
	const bool isInPlusY = (indexWithinParent & 2) != 0;
	const bool isInPlusZ = (indexWithinParent & 4) != 0;

	float parentHalfExtentX, parentHalfExtentY, parentHalfExtentZ;
	parentSpace.getExtents(parentHalfExtentX, parentHalfExtentY,parentHalfExtentZ);

	parentHalfExtentX /= 2.0f;
	parentHalfExtentY /= 2.0f;
	parentHalfExtentZ /= 2.0f;

	glm::vec3 minPointOffset = glm::vec3(isInPlusX * parentHalfExtentX, isInPlusY * parentHalfExtentY, isInPlusZ * parentHalfExtentZ);

	minPoint = minPoint + minPointOffset;
	glm::vec3 maxPoint = minPoint + glm::vec3(parentHalfExtentX, parentHalfExtentY, parentHalfExtentZ);

	n.volume = AABB(minPoint, maxPoint);

	_nodes[newNodeId] = n;
}

int Octree::getNodeIndexWithinParent(unsigned int nodeID) const
{
	const int parent = getNodeParent(nodeID);

	assert(parent >= 0);

	return getNodeIndexWithinParent(nodeID, parent);
}

int Octree::getNodeIndexWithinParent(unsigned int nodeID, unsigned int parent) const
{
	const int startID = getChildrenStartingId(parent);

	return nodeID - startID;
}

bool Octree::_isPointInsideOctree(const glm::vec3& point) const
{
	return GeometryOps::testAabbPointIsInsideOrOn(_nodes[0].volume, point);
}

unsigned int Octree::getDeepestLevel() const
{
	return _deepestLevel;
}

unsigned int Octree::getTotalNumNodes() const
{
	return _levelSizesInclusiveSum[_deepestLevel];
}

int Octree::getLevelFirstNodeID(unsigned int level) const
{
	if (level > _deepestLevel)
		return -1;

	if (level == 0)
		return 0;

	return _levelSizesInclusiveSum[level - 1];
}

int Octree::getNumNodesInLevel(unsigned int level) const
{
	if (level > _deepestLevel)
		return -1;

	return ipow(OCTREE_NUM_CHILDREN, level);
}

uint64_t Octree::getOctreeSizeBytes() const
{
	uint64_t sz = 0;

	sz += _nodes.size() * sizeof(AABB);

	uint64_t numIndices = 0;
	for(const auto& node : _nodes)
	{
		numIndices += node.edgesAlwaysCast.size();
		numIndices += node.edgesMayCast.size();
	}

	sz += sizeof(int) * numIndices;

	return sz;
}

void Octree::makeNodesFit()
{
	_nodes.shrink_to_fit();
}