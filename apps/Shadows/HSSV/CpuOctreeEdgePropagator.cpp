#include "CpuOctreeEdgePropagator.hpp"
#include <omp.h>
#include "HighResolutionTimer.hpp"
#include <iostream>

void CpuOctreeEdgePropagator::propagateEdgesToUpperLevels(std::shared_ptr<Octree> octree)
{
	_octree = octree;

	HighResolutionTimer t;
	t.reset();
	const auto startingLevel = _octree->getDeepestLevel() - 1;
	_propagateEdgesToUpperLevelsCpu(startingLevel, true);
	auto dt = t.getElapsedTimeFromLastQueryMilliseconds();

	std::cout << "Propagate Potential edges took " << dt / 1000.0f << " sec\n";
	t.reset();

	_propagateEdgesToUpperLevelsCpu(startingLevel, false);

	dt = t.getElapsedTimeFromLastQueryMilliseconds();

	std::cout << "Propagate Silhouette edges took " << dt / 1000.0f << " sec\n";
}

void CpuOctreeEdgePropagator::_propagateEdgesToUpperLevelsCpu(unsigned int startingLevel, bool propagatePotential)
{
	for (int i = startingLevel; i > 0; --i)
		_processEdgesInLevel(i, propagatePotential);
}

void CpuOctreeEdgePropagator::_processEdgesInLevel(unsigned int level, bool propagatePotential)
{
	assert(level > 0);
	const int startingID = _octree->getLevelFirstNodeID(level);

	assert(startingID >= 0);

	const int stopId = ipow(OCTREE_NUM_CHILDREN, level) + startingID;

	int currentID = startingID;

#pragma omp parallel for
	for (currentID = startingID; currentID<stopId; currentID += OCTREE_NUM_CHILDREN)
	{
		auto firstNode = _octree->getNode(currentID);
		const auto edgesMap = propagatePotential ? firstNode->edgesMayCastMap : firstNode->edgesAlwaysCastMap;

		if (!edgesMap.empty())
		{
			auto it = edgesMap.find(BitmaskAllSet);
			if (it != edgesMap.end())
			{
				auto edgeSubBuffer = *it;
				for (const auto edge : edgeSubBuffer.second)
				{
					auto result = _haveAllSyblingsEdgeInCommon(currentID, edge, propagatePotential, edgeSubBuffer.first);

					if (result == TestResultEdgeCommon::TRUE)
					{
						_assignEdgeToNodeParent(currentID, edge, propagatePotential, edgeSubBuffer.first);
						_removeEdgeFromSyblings(currentID, edge, propagatePotential, edgeSubBuffer.first);
					}
				}
			}
		}
	}
}

CpuOctreeEdgePropagator::TestResultEdgeCommon CpuOctreeEdgePropagator::_haveAllSyblingsEdgeInCommon(unsigned int startingNodeID, unsigned int edgeID, bool propagatePotential, BitmaskType subBufferId) const
{
	TestResultEdgeCommon retval = TestResultEdgeCommon::NON_EXISTING;

	for (unsigned int i = 0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		const auto node = _octree->getNode(startingNodeID + i);

		if (!node)
			continue;

		if (propagatePotential)
		{
			if (node->edgesMayCastMap.find(subBufferId) == node->edgesMayCastMap.end() || !std::binary_search(node->edgesMayCastMap[subBufferId].begin(), node->edgesMayCastMap[subBufferId].end(), edgeID))
				return TestResultEdgeCommon::FALSE;
		}
		else
			if (node->edgesAlwaysCastMap.find(subBufferId) == node->edgesAlwaysCastMap.end() || !std::binary_search(node->edgesAlwaysCastMap[subBufferId].begin(), node->edgesAlwaysCastMap[subBufferId].end(), edgeID))
				return TestResultEdgeCommon::FALSE;

		retval = TestResultEdgeCommon::TRUE;
	}

	return retval;
}

void CpuOctreeEdgePropagator::_assignEdgeToNodeParent(unsigned int node, unsigned int edge, bool propagatePotential, BitmaskType subBufferId)
{
	const int parent = _octree->getNodeParent(node);

	assert(parent >= 0);

	_assignEdgeToNode(parent, edge, propagatePotential, subBufferId);
}

void CpuOctreeEdgePropagator::_assignEdgeToNode(unsigned int node, unsigned int edge, bool propagatePotential, BitmaskType subBufferId)
{
	auto n = _octree->getNode(node);

	if (n)
	{
		if (propagatePotential)
			n->edgesMayCastMap[subBufferId].push_back(edge);
		else
			n->edgesAlwaysCastMap[subBufferId].push_back(edge);
	}
}

void CpuOctreeEdgePropagator::_removeEdgeFromSyblings(unsigned int startingID, unsigned int edge, bool propagatePotential, BitmaskType subBufferId)
{
	for (unsigned int i = 0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		auto node = _octree->getNode(startingID + i);

		if (node)
		{
			if (propagatePotential)
				node->edgesMayCastMap[subBufferId].erase(std::lower_bound(node->edgesMayCastMap[subBufferId].begin(), node->edgesMayCastMap[subBufferId].end(), edge));
			else
				node->edgesAlwaysCastMap[subBufferId].erase(std::lower_bound(node->edgesAlwaysCastMap[subBufferId].begin(), node->edgesAlwaysCastMap[subBufferId].end(), edge));
		}
	}
}