#pragma once

#include "Octree.hpp"
#include <memory>
#include <bitset>
#include "OctreeVisitor.hpp"

class OctreeCompressor
{
public:
	void compressOctree(std::shared_ptr<OctreeVisitor> octreeVisitor, unsigned int compressLevelHeight_1or2);

protected:
	std::bitset<BitmaskTypeSizeBits> checkEdgePresence(unsigned int edge, unsigned int startingId, bool checkPotential, unsigned int nofSyblings) const;
	void _compressSyblings(unsigned int startingID, bool processPotential, unsigned int compressLevelHeight_1or2);
	void _removeEdgeFromSyblingsSparse(unsigned int startingId, unsigned int edge, bool checkPotential, const std::bitset<BitmaskTypeSizeBits>& bitmask, unsigned int nofSyblings);

private:
	std::shared_ptr<OctreeVisitor> _visitor;
};
