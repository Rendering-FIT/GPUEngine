#pragma once

#include "AdjacencyEdgeWrapper.hpp"
#include "Octree.hpp"
#include "GpuEdges.hpp"


class IOctreeLoader
{
public:
	virtual ~IOctreeLoader() {}

	virtual bool init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, unsigned int nofEdges) = 0;
	virtual void addEdgesOnLowestLevel(AdjacencyType edges) = 0;

protected:
	std::shared_ptr<Octree> _octree;
};
