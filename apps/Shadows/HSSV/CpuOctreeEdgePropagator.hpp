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

	void _propagateEdgesToUpperLevelsCpu(uint32_t startingLevel, bool propagatePotential);
		void _processEdgesInLevel(uint32_t levelNum, bool propagatePotential);
		TestResultEdgeCommon _haveAllSyblingsEdgeInCommon(uint32_t startingNodeID, uint32_t edgeID, bool propagatePotential, BitmaskType subBufferId) const;
		void _removeEdgeFromSyblings(uint32_t startingID, uint32_t edge, bool propagatePotential, BitmaskType subBufferId);
		void _assignEdgeToNodeParent(uint32_t node, uint32_t edge, bool propagatePotential, BitmaskType subBufferId);
		void _assignEdgeToNode(uint32_t node, uint32_t edge, bool propagatePotential, BitmaskType subBufferId);
};
