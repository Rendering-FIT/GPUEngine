#pragma once

#include "Octree.hpp"
#include <memory>
#include <bitset>
#include "OctreeVisitor.hpp"

class OctreeCompressor
{
public:
	void compressOctree(std::shared_ptr<OctreeVisitor> octreeVisitor, uint32_t compressLevelHeight_1or2);

protected:
	std::bitset<BitmaskTypeSizeBits> checkEdgePresence(uint32_t edge, uint32_t startingId, bool checkPotential, uint32_t nofSyblings) const;
	void _compressSyblings(uint32_t startingID, bool processPotential, uint32_t compressLevelHeight_1or2);
	void _removeEdgeFromSyblingsSparse(uint32_t startingId, uint32_t edge, bool checkPotential, const std::bitset<BitmaskTypeSizeBits>& bitmask, uint32_t nofSyblings);

	void _assignEdgeToNodeParent(uint32_t node, uint32_t edge, bool propagatePotential, BitmaskType subBufferId);
	void _assignEdgeToNode(uint32_t node, uint32_t edge, bool propagatePotential, BitmaskType subBufferId);
private:
	std::shared_ptr<OctreeVisitor> _visitor;
};
