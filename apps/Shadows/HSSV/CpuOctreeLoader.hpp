#pragma once
#include "IOctreeLoader.hpp"
#include "Plane.hpp"

class CpuOctreeLoader : public IOctreeLoader
{
public:
	void addEdgesOnLowestLevel(AdjacencyType edges) override;
	bool init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, uint32_t nofEdges) override;

protected:

	void _addEdgesOnLowestLevel(std::vector< std::vector<Plane> >& edgePlanes, AdjacencyType edges);
		void _addEdgesSyblingsParentCompress8(const std::vector< std::vector<Plane> >& edgePlanes, AdjacencyType edges, uint32_t startingID);
		void _generateEdgePlanes(const AdjacencyType edges, std::vector< std::vector<Plane> >& planes) const;
		bool _doAllSilhouetteFaceTheSame(const int(&indices)[OCTREE_NUM_CHILDREN]) const;

	void _storeEdgeIsAlwaysSilhouette(uint32_t nodeId, uint32_t augmentedEdgeIdWithResult, const BitmaskType subarrayIndex);
	void _storeEdgeIsPotentiallySilhouette(uint32_t nodeID, uint32_t edgeID, const BitmaskType subarrayIndex);
	
};
