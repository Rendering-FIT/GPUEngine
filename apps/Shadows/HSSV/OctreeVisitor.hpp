#pragma once

#include "Octree.hpp"
#include "Edge.hpp"
#include "GeometryOperations.hpp"
#include <memory>
#include <set>

class OctreeVisitor
{
public:
	OctreeVisitor(std::shared_ptr<Octree> octree);

	void addEdge(const EDGE_TYPE& edgeInfo, int edgeID);
	void addEdges(const EDGE_CONTAINER_TYPE& _edges);

	void processPotentialEdges();

	void cleanEmptyNodes();

	int getLowestNodeIndexFromPoint(const glm::vec3& point) const;
	void getSilhouttePotentialEdgesFromNodeUp(std::vector<int>& potential, std::vector<int>& silhouette, unsigned int nodeID) const;

private:
	void _expandWholeOctree();
	void _storeEdgeIsAlwaysSilhouette(EdgeSilhouetness testResult, unsigned int nodeId, unsigned int edgeID);
	void _storeEdgeIsAlwaysSilhouette(unsigned int nodeId, int augmentedEdgeIdWithResult);
	void _storeEdgeIsPotentiallySilhouette(unsigned int nodeID, unsigned int edgeID);

	//void _unmarkEdgeAsPotentiallySilhouetteFromNodeUp(unsigned int edgeID, unsigned int nodeID);
	//void _removePotentiallySilhouetteEdgeFromNode(unsigned int edgeID, unsigned int nodeID);
	
	int	 _getFirstNodeIdInLevel(unsigned int level) const;

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

	void _addEdgesOnLowestLevel(std::vector< std::vector<Plane> >& edgePlanes, const EDGE_CONTAINER_TYPE& edges);
		void _addEdgesSyblingsParent(const std::vector< std::vector<Plane> >& edgePlanes, const EDGE_CONTAINER_TYPE& edges, unsigned int startingID);
		void _generateEdgePlanes(const EDGE_CONTAINER_TYPE& edges, std::vector< std::vector<Plane> >& planes) const;
		bool _doAllSilhouetteFaceTheSame(const int (&indices)[OCTREE_NUM_CHILDREN]) const;

	bool _isPointInsideNode(unsigned int nodeID, const glm::vec3& point) const;

	int _getChildNodeContainingPoint(unsigned int parent, const glm::vec3& point) const;

	std::shared_ptr<Octree> _octree;
};
