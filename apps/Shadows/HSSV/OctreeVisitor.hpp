#pragma once

#include <memory>
#include <bitset>

#include "Octree.hpp"
#include "GeometryOperations.hpp"
#include "AdjacencyEdgeWrapper.hpp"
#include "GpuEdges.hpp"

class OctreeVisitor
{
public:
	OctreeVisitor(std::shared_ptr<Octree> octree);

	void addEdges(const AdjacencyType edges);
	void addEdgesGPU(const AdjacencyType edges, std::shared_ptr<GpuEdges> gpuEdges, unsigned int subgroupSize);

	int getLowestNodeIndexFromPoint(const glm::vec3& point) const;
	void getSilhouttePotentialEdgesFromNodeUp(std::vector<unsigned int>& potential, std::vector<unsigned int>& silhouette, unsigned int nodeID) const;

	std::shared_ptr<Octree> getOctree() { return _octree; }

	void shrinkOctree();

	void assignEdgeToNodeParent(unsigned int node, unsigned int edge, bool propagatePotential, BitmaskType subBufferId);
	void assignEdgeToNode(unsigned int node, unsigned int edge, bool propagatePotential, BitmaskType subBufferId);

	unsigned int getNofAllIndicesInNode(unsigned int nodeID) const;

	unsigned int getMaxNofSubBuffers() const;
	unsigned int getNodeNofSubBuffers(unsigned int nodeID) const;

private:
	
	void _storeEdgeIsAlwaysSilhouette(unsigned int nodeId, unsigned int augmentedEdgeIdWithResult, const BitmaskType subarrayIndex);
	void _storeEdgeIsPotentiallySilhouette(unsigned int nodeID, unsigned int edgeID, const BitmaskType subarrayIndex);

	unsigned int _getCompressionIdWithinParent(unsigned int nodeId) const;

	enum class TestResult
	{
		TRUE,
		FALSE,
		NON_EXISTING
	};

	void _sortLevel(unsigned int level);

	void _propagateEdgesUpFromLevel(unsigned int startingLevel, bool propagatePotential, unsigned int subgroupSize);
		TestResult _haveAllSyblingsEdgeInCommon(unsigned int startingNodeID, unsigned int edgeID, bool propagatePotential, BitmaskType subBufferId) const;
		void _processEdgesInLevel(unsigned int levelNum, bool propagatePotential);
		//void _assignEdgeToNodeParent(unsigned int node, unsigned int edge, bool propagatePotential, BitmaskType subBufferId);
		void _removeEdgeFromSyblings(unsigned int startingID, unsigned int edge, bool propagatePotential, BitmaskType subBufferId);

	void _addEdgesOnLowestLevel(std::vector< std::vector<Plane> >& edgePlanes, AdjacencyType edges);
		void _addEdgesSyblingsParent(const std::vector< std::vector<Plane> >& edgePlanes, AdjacencyType edges, unsigned int startingID);
		void _generateEdgePlanes(const AdjacencyType edges, std::vector< std::vector<Plane> >& planes) const;
		bool _doAllSilhouetteFaceTheSame(const int (&indices)[OCTREE_NUM_CHILDREN]) const;
	
	bool _isPointInsideNode(unsigned int nodeID, const glm::vec3& point) const;

	int _getChildNodeContainingPoint(unsigned int parent, const glm::vec3& point) const;

	unsigned int _getNodeIdWithinParent(unsigned int nodeId) const;

	void _getSilhouttePotentialEdgesFromNodeUpCompress2(std::vector<unsigned int>& potential, std::vector<unsigned int>& silhouette, unsigned int nodeID) const;

	unsigned int _getMaxNofSubBuffersInLevel(unsigned int level) const;

	std::shared_ptr<Octree> _octree;
};
