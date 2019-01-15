#pragma once
#include "IOctreeLoader.hpp"
#include "Plane.hpp"

class CpuOctreeLoader : public IOctreeLoader
{
public:
	void addEdgesOnLowestLevel(AdjacencyType edges) override;
	bool init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, unsigned int nofEdges) override;

protected:

	void _addEdgesOnLowestLevel(std::vector< std::vector<Plane> >& edgePlanes, AdjacencyType edges);
		void _addEdgesSyblingsParent(const std::vector< std::vector<Plane> >& edgePlanes, AdjacencyType edges, unsigned int startingID);
		void _generateEdgePlanes(const AdjacencyType edges, std::vector< std::vector<Plane> >& planes) const;
		bool _doAllSilhouetteFaceTheSame(const int(&indices)[OCTREE_NUM_CHILDREN]) const;

	void _storeEdgeIsAlwaysSilhouette(unsigned int nodeId, unsigned int augmentedEdgeIdWithResult, const BitmaskType subarrayIndex);
	void _storeEdgeIsPotentiallySilhouette(unsigned int nodeID, unsigned int edgeID, const BitmaskType subarrayIndex);
	
};
