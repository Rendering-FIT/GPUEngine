#pragma once

#include "Octree.hpp"
#include <memory>

class CpuOctreeEdgePropagator
{
public:
	void propagateEdgesToUpperLevels(std::shared_ptr<Octree> octree);

protected:
	std::shared_ptr<Octree> _octree;

	enum class TestResultEdgeCommon
	{
		TRUE,
		FALSE,
		NON_EXISTING
	};

	void _propagateEdgesToUpperLevelsCpu(unsigned int startingLevel, bool propagatePotential);
		void _processEdgesInLevel(unsigned int levelNum, bool propagatePotential);
		TestResultEdgeCommon _haveAllSyblingsEdgeInCommon(unsigned int startingNodeID, unsigned int edgeID, bool propagatePotential, BitmaskType subBufferId) const;
		void _removeEdgeFromSyblings(unsigned int startingID, unsigned int edge, bool propagatePotential, BitmaskType subBufferId);
		void _assignEdgeToNodeParent(unsigned int node, unsigned int edge, bool propagatePotential, BitmaskType subBufferId);
		void _assignEdgeToNode(unsigned int node, unsigned int edge, bool propagatePotential, BitmaskType subBufferId);
};
