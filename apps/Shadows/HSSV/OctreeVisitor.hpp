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
	void addEdgesGPU(const AdjacencyType edges);

	void processPotentialEdges();

	void cleanEmptyNodes();

	int getLowestNodeIndexFromPoint(const glm::vec3& point) const;
	void getSilhouttePotentialEdgesFromNodeUp(std::vector<unsigned int>& potential, std::vector<unsigned int>& silhouette, unsigned int nodeID) const;

private:
	void _expandWholeOctree();
	void _storeEdgeIsAlwaysSilhouette(unsigned int nodeId, int augmentedEdgeIdWithResult);
	void _storeEdgeIsPotentiallySilhouette(unsigned int nodeID, unsigned int edgeID);

	void _getEdgesOneOpposite(AdjacencyType edges, std::vector<unsigned int>& edgesWithSingleOV);

	//int	 _getFirstNodeIdInLevel(unsigned int level) const;

	void _propagatePotentiallySilhouetteEdgesUpFromLevel(unsigned int startingLevel);
		enum class TestResult
		{
			TRUE,
			FALSE,
			NON_EXISTING
		};

		TestResult _haveAllSyblingsEdgeAsPotential(unsigned int startingNodeID, unsigned int edgeID) const;
		void _processPotentialEdgesInLevel(unsigned int levelNum);
		void _getAllPotentialEdgesSyblings(unsigned int startingID, std::set<unsigned int>& edges) const;
		void _assignPotentialEdgeToNodeParent(unsigned int node, unsigned int edge);
		void _removePotentialEdgeFromSyblings(unsigned int startingID, unsigned int edge);
	
	void _propagateSilhouetteEdgesUpFromLevel(unsigned int startingLevel);
		void _processSilhouetteEdgesInLevel(unsigned int level);
		void _assignSilhouetteEdgeToNodeParent(unsigned int node, int edge);
		void _getAllSilhouetteEdgesSyblings(unsigned int startingID, std::set<int>& edges) const;
		void _removeSilhouetteEdgeFromSyblings(unsigned int startingID, int edge);

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
