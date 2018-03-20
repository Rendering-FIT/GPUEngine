#pragma once

#include <geGL/Buffer.h>
#include <geGL/Program.h>

#include "Octree.hpp"

enum class EdgesType
{
	POTENTIAL,
	SILHOUETTE
};

class GpuOctreeEdgePropagator
{
public:

	void propagateEdgesToUpperLevel(unsigned int level, EdgesType type);

	bool init(std::shared_ptr<Octree> octree, unsigned int subgroupSize);

	void profile(unsigned int subgroupSize);



protected:
	bool _createPropagateProgram(unsigned numSubgroupsPerWG, unsigned subgroupSize);
	void _createBuffers();

	std::shared_ptr<ge::gl::Program> _propagateProgram;


};
