#pragma once

#include <geGL/Buffer.h>
#include <geGL/Program.h>

#include "AdjacencyEdgeWrapper.hpp"
#include "Octree.hpp"
#include "GpuEdges.hpp"
#include "IGpuOctreeLoader.hpp"


class GpuOctreeLoader : public IGpuOctreeLoader
{
public:
	void addEdgesOnLowestLevel(AdjacencyType edges) override;
	bool init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, uint32_t nofEdges) override;
	void profile(AdjacencyType edges) override;

protected:
	
	bool _createBottomFillProgram();
	
	void _allocateOutputBuffersAndVoxels(uint32_t voxelsPerBatch);

	void _bindBuffers();
	void _unbindBuffers();

	void _acquireGpuData(uint32_t startingVoxelAbsoluteIndex, uint32_t batchSize);

	void _testParticularVoxel(AdjacencyType edges, uint32_t voxelId, std::vector<uint32_t>& particularEdgeIndices);
};
