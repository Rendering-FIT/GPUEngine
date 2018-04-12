#pragma once
#include <string>

const std::string edgeTraversalShaderBody = R".(
#extension GL_ARB_gpu_shader_int64 : enable
#extension GL_AMD_gpu_shader_int64 : enable
#extension GL_ARB_shader_ballot : require

layout(local_size_x=WORKGROUP_SIZE_X) in;

layout(std430, binding=0) readonly buffer _edgeIndices{
	uint voxelIndices[];};

layout(std430, binding=1) readonly buffer _indicesPrefixSum{
	uint indicesCountPrefixSum[];};

layout(std430, binding=2) buffer _potential{
	uint potentialEdges[];};

layout(std430, binding=3) buffer _silhouette{
	uint silhouetteEdges[];};

layout(std430, binding=4) buffer _nofPotential{
	uint nofPotentialEdges;};

layout(std430, binding=5) buffer _nofSilhouette{
	uint nofSilhouetteEdges;};

uint ipow(uint x, uint y)
{
	return y==0 ? 1 : uint(pow(x, y));
}

#define OCTREE_NUM_CHILDREN 8
uint getNumNodesInPreviousLevels(int level)
{
	uint numCells = 0;
	for(unsigned int i = 0; i<level; ++i)
		numCells += ipow(OCTREE_NUM_CHILDREN, i);

	return numCells;
}

int getVoxelParent(uint nodeID, int currentLevel)
{
	if (nodeID == 0)
		return -1;

	const uint idInLevel = nodeID - getNumNodesInPreviousLevels(currentLevel);

	const uint parentRelativeID = idInLevel / OCTREE_NUM_CHILDREN;

	return int(parentRelativeID + getNumNodesInPreviousLevels(currentLevel - 1));
}

uniform uint voxelIndex;

void main()
{
	int currentVoxel =  int(voxelIndex);

	for(int level = int(DEEPEST_LEVEL); level>=0; --level)
	{
		const uint baseIndexPotential = indicesCountPrefixSum[2*currentVoxel + 0];
		const uint baseIndexSilhouette = indicesCountPrefixSum[2*currentVoxel + 1];
		const uint nofPotential =  indicesCountPrefixSum[2*currentVoxel+1] - indicesCountPrefixSum[2*currentVoxel+0];
		const uint nofSilhouette = indicesCountPrefixSum[2*currentVoxel+2] - indicesCountPrefixSum[2*currentVoxel+1];
		
		if(gl_GlobalInvocationID.x<nofPotential)
		{
			const uvec2 aliveThreads = unpackUint2x32(ballotARB(true));
			const uint numAlive = bitCount(aliveThreads.x) + bitCount(aliveThreads.y);

			uint potentialIndex = 0;
			if(gl_SubGroupInvocationARB==0)
				potentialIndex = atomicAdd(nofPotentialEdges, numAlive);
			potentialIndex = readFirstInvocationARB(potentialIndex) + gl_SubGroupInvocationARB;
			
			potentialEdges[potentialIndex] = voxelIndices[baseIndexPotential + gl_GlobalInvocationID.x];
		}
		
		if(gl_GlobalInvocationID.x<nofSilhouette)
		{
			const uvec2 aliveThreads = unpackUint2x32(ballotARB(true));
			const uint numAlive = bitCount(aliveThreads.x) + bitCount(aliveThreads.y);

			uint silhouetteIndex = 0;
			if(gl_SubGroupInvocationARB==0)
				silhouetteIndex = atomicAdd(nofSilhouetteEdges, numAlive);
			silhouetteIndex = readFirstInvocationARB(silhouetteIndex) + gl_SubGroupInvocationARB;

			silhouetteEdges[silhouetteIndex] = voxelIndices[baseIndexSilhouette + gl_GlobalInvocationID.x];
		}

		currentVoxel = getVoxelParent(currentVoxel, level);
	}
}).";