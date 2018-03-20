#pragma once

#include "Octree.hpp"
#include "GeometryOperations.hpp"
#include <memory>
#include <set>

#include "AdjacencyEdgeWrapper.hpp"

class OctreeVisitor
{
public:
	OctreeVisitor(std::shared_ptr<Octree> octree);

	void addEdges(const AdjacencyType edges);
	void addEdgesGPU(const AdjacencyType edges, unsigned int subgroupSize);

	void processPotentialEdges();

	void cleanEmptyNodes();

	int getLowestNodeIndexFromPoint(const glm::vec3& point) const;
	void getSilhouttePotentialEdgesFromNodeUp(std::vector<unsigned int>& potential, std::vector<unsigned int>& silhouette, unsigned int nodeID) const;

private:
	void _expandWholeOctree();
	void _storeEdgeIsAlwaysSilhouette(unsigned int nodeId, int augmentedEdgeIdWithResult);
	void _storeEdgeIsPotentiallySilhouette(unsigned int nodeID, unsigned int edgeID);

	enum class TestResult
	{
		TRUE,
		FALSE,
		NON_EXISTING
	};

	void _sortLevel(unsigned int level);

	void _shrinkOctree();

	void _propagatePotentiallySilhouetteEdgesUpFromLevel(unsigned int startingLevel);
		TestResult _haveAllSyblingsEdgeAsPotential(unsigned int startingNodeID, unsigned int edgeID) const;
		void _processPotentialEdgesInLevel(unsigned int levelNum);
		void _getAllPotentialEdgesSyblings(unsigned int startingID, std::vector<unsigned int>& edges) const;
		void _assignPotentialEdgeToNodeParent(unsigned int node, unsigned int edge);
		void _removePotentialEdgeFromSyblings(unsigned int startingID, unsigned int edge);
	
	void _propagateSilhouetteEdgesUpFromLevel(unsigned int startingLevel);
		TestResult _haveAllSyblingsEdgeAsSilhouette(unsigned int startingNodeID, unsigned int edgeID) const;
		void _processSilhouetteEdgesInLevel(unsigned int level);
		void _assignSilhouetteEdgeToNodeParent(unsigned int node, int edge);
		void _getAllSilhouetteEdgesSyblings(unsigned int startingID, std::vector<unsigned int>& edges) const;
		void _removeSilhouetteEdgeFromSyblings(unsigned int startingID, unsigned int edge);

	void _processEmptyNodesInLevel(unsigned int level);
		void _processEmptyNodesSyblingsParent(unsigned int first);

	void _addEdgesOnLowestLevel(std::vector< std::vector<Plane> >& edgePlanes, AdjacencyType edges);
		void _addEdgesSyblingsParent(const std::vector< std::vector<Plane> >& edgePlanes, AdjacencyType edges, unsigned int startingID);
		void _generateEdgePlanes(const AdjacencyType edges, std::vector< std::vector<Plane> >& planes) const;
		bool _doAllSilhouetteFaceTheSame(const int (&indices)[OCTREE_NUM_CHILDREN]) const;
	
	bool _isPointInsideNode(unsigned int nodeID, const glm::vec3& point) const;

	int _getChildNodeContainingPoint(unsigned int parent, const glm::vec3& point) const;

	std::shared_ptr<Octree> _octree;
};
