#pragma once

#include "Octree.hpp"
#include <memory>
#include <bitset>

class OctreeCompressor
{
public:
	void compressOctree(std::shared_ptr<Octree> octree, unsigned int compressLevelHeight_1or2);

protected:
	std::bitset<BitmaskTypeSize> checkEdgePresence(unsigned int edge, unsigned int startingId, bool checkPotential) const;
	void _compressSyblings(unsigned int startingID, bool processPotential);
	void _removeEdgeFromSyblingsSparse(unsigned int startingId, unsigned int edge, bool checkPotential, const std::bitset<OCTREE_NUM_CHILDREN>& bitmask);

private:
	std::shared_ptr<Octree> _octree;
};
