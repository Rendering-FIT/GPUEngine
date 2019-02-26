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

	void addEdges(const AdjacencyType edges, std::shared_ptr<GpuEdges> gpuEdges, bool useCompress, uint64_t bufferSizeMB, float speculativeRatioPot, float speculativeRatioSil);

	int getLowestNodeIndexFromPoint(const glm::vec3& point) const;
	void getSilhouttePotentialEdgesFromNodeUp(std::vector<uint32_t>& potential, std::vector<uint32_t>& silhouette, uint32_t nodeID) const;

	std::shared_ptr<Octree> getOctree() const { return _octree; }

	void shrinkOctree();

	uint32_t getNofAllIndicesInNode(uint32_t nodeID) const;

	void getMaxNofSubBuffersPotSil(uint32_t& pot, uint32_t& sil) const;

	void getNodeNofSubBuffersPotSil(uint32_t& pot, uint32_t& sil, uint32_t nodeID) const;
	void dumpOctreeLevel(uint32_t level, const char* filename);
private:

	void _addEdgesCpu(const AdjacencyType edges);
	void _propagateEdgesCpu();

	uint32_t _getCompressionIdWithinParent(uint32_t nodeId) const;

	void _sortLevel(uint32_t level);

	void _propagateEdgesGpu();
		void _propagateEdgesToUpperLevelsGpu(std::shared_ptr<GpuOctreeEdgePropagator> propagator, uint32_t startingLevel, bool propagatePotential);
	
	bool _isPointInsideNode(uint32_t nodeID, const glm::vec3& point) const;

	int _getChildNodeContainingPoint(uint32_t parent, const glm::vec3& point) const;

	uint32_t _getNodeIdWithinParent(uint32_t nodeId) const;

	void _getSilhouttePotentialEdgesFromNodeUpCompress2(std::vector<uint32_t>& potential, std::vector<uint32_t>& silhouette, uint32_t nodeID) const;

	void _getMaxNofSubBuffersInLevelPotSil(uint32_t& pot, uint32_t& sil, uint32_t level) const;

	std::shared_ptr<Octree> _octree;
};
