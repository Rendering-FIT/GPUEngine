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
	bool init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, unsigned int nofEdges) override;
	void profile(AdjacencyType edges) override;

protected:
	
	bool _createBottomFillProgram();
	
	void _allocateOutputBuffersAndVoxels(unsigned int voxelsPerBatch, unsigned int numEdges);

	void _bindBuffers();
	void _unbindBuffers();

	void _acquireGpuData(unsigned int startingVoxelAbsoluteIndex, unsigned int batchSize, unsigned int numEdges);

	void _testParticularVoxel(AdjacencyType edges, unsigned int voxelId, std::vector<unsigned int>& particularEdgeIndices);
};
