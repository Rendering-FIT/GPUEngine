#pragma once

#include <memory>
#include <bitset>

#include "Octree.hpp"
#include "GeometryOperations.hpp"
#include "AdjacencyEdgeWrapper.hpp"
#include "GpuEdges.hpp"

class GpuOctreeEdgePropagator;

class OctreeVisitor
{
public:
	OctreeVisitor(std::shared_ptr<Octree> octree);

	void addEdges(const AdjacencyType edges, std::shared_ptr<GpuEdges> gpuEdges);

	int getLowestNodeIndexFromPoint(const glm::vec3& point) const;
	void getSilhouttePotentialEdgesFromNodeUp(std::vector<unsigned int>& potential, std::vector<unsigned int>& silhouette, unsigned int nodeID) const;

	std::shared_ptr<Octree> getOctree() const { return _octree; }

	void shrinkOctree();

	unsigned int getNofAllIndicesInNode(unsigned int nodeID) const;

	void getMaxNofSubBuffersPotSil(unsigned int& pot, unsigned int& sil) const;

	void getNodeNofSubBuffersPotSil(unsigned int& pot, unsigned int& sil, unsigned int nodeID) const;
	void dumpOctreeLevel(unsigned int level, const char* filename);
private:

	void _addEdgesCpu(const AdjacencyType edges);
	void _propagateEdgesCpu();

	unsigned int _getCompressionIdWithinParent(unsigned int nodeId) const;

	void _sortLevel(unsigned int level);

	void _propagateEdgesGpu();
		void _propagateEdgesToUpperLevelsGpu(std::shared_ptr<GpuOctreeEdgePropagator> propagator, unsigned int startingLevel, bool propagatePotential);
	
	bool _isPointInsideNode(unsigned int nodeID, const glm::vec3& point) const;

	int _getChildNodeContainingPoint(unsigned int parent, const glm::vec3& point) const;

	unsigned int _getNodeIdWithinParent(unsigned int nodeId) const;

	void _getSilhouttePotentialEdgesFromNodeUpCompress2(std::vector<unsigned int>& potential, std::vector<unsigned int>& silhouette, unsigned int nodeID) const;

	void _getMaxNofSubBuffersInLevelPotSil(unsigned int& pot, unsigned int& sil, unsigned int level) const;

	std::shared_ptr<Octree> _octree;
};
