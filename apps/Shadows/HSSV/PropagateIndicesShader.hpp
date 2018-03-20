#pragma once

#include <string>

const std::string propagationComputeShaderPrologue = R".(
#version 450 core
#extension GL_ARB_gpu_shader_int64: require
#extension GL_ARB_shader_ballot: require

).";


const std::string propagationComputeShaderBody = R".(

layout(std430, binding=0) readonly buffer _indices{
	uint voxelEdgeIndicesSorted[];};

layout(std430, binding=1) readonly buffer _numIndices{
	uint voxelNumIndices[];};

layout(std430, binding=2) readonly buffer _startingIndices{
	uint startingIndices[];};

layout(std430, binding=3) buffer _outputIndices{
	uint outputIndices[];};

layout(std430, binding=4) buffer _outputNumIndices{
	uint outputNumIndices[];};

layout(std430, binding=5) buffer _parentIndices{
	uint parentIndices[];};

layout(std430, binding=6) buffer _numParentIndices{
	uint parentNumIndices[];};

layout(std430, binding=7) buffer _atomicCounter{
	uint atomicCounter;};

uniform uint nofVoxels;
uniform uint maxNofEdges;

bool isEdgePresent(uint startingIndex, uint numEdges, uint edgeId)
{
	int L = 0;
	int R = int(numEdges)-1;

	while(L<=R)
	{
		const int middle = int(floor(float(L + R)/2.0f));
		
		const uint val = voxelEdgeIndicesSorted[startingIndex + uint(middle)];

		if(edgeId==val)
			return true;
		else if(val<edgeId)
			L = middle+1;
		else
			R = middle-1;
	}

	return false;
}

bool haveSyblingsAgreed(uint64_t ballotResult, uint syblingGroup)
{
	return ((ballotResult >> (syblingGroup*8)) & 0xFF) == 255;
}

void main()
{
	#define syblingGroup (gl_SubGroupInvocationARB/8)
	#define syblingInvocationId (gl_SubGroupInvocationARB%8)

	while(true)
	{
		//Acquire voxels
		uint startingVoxel = 0;
		
		if(gl_SubGroupInvocationARB==0)
			startingVoxel = atomicAdd(atomicCounter, gl_SubGroupSizeARB);
		
		startingVoxel = readFirstInvocationARB(startingVoxel);
		const uint currentVoxel = startingVoxel + gl_SubGroupInvocationARB;

		if(currentVoxel>=nofVoxels)
			return;

		const uint numEdgesInVoxel = voxelNumIndices[currentVoxel];
		const uint startingIndex = startingIndices[currentVoxel];
		const uint parentId = currentVoxel/8;
		const uint numEdgesInFirst = readInvocationARB(numEdgesInVoxel, syblingGroup*8);				

		uint numOutputEdges = 0;
		uint numParentOutputEdges = 0;
		
		for(unsigned int i = 0; i<numEdgesInFirst; ++i)
		{
			uint edgeIndex = 0;
			if(syblingInvocationId==0)
				edgeIndex = voxelEdgeIndicesSorted[startingIndex + i];
			
			edgeIndex = readInvocationARB(edgeIndex, syblingGroup*8);
			
			bool found = true;
			if(syblingInvocationId!=0)
				found = isEdgePresent(startingIndex, numEdgesInVoxel, edgeIndex);
			
			uint64_t allResults = ballotARB(found);
			
			if(haveSyblingsAgreed(allResults, syblingGroup))
				if(syblingInvocationId==0)
					parentIndices[maxNofEdges*(parentId) + numParentOutputEdges++] = edgeIndex;
			else
				outputIndices[startingIndex + numOutputEdges++] = edgeIndex;
		}
		
		outputNumIndices[currentVoxel] = numOutputEdges;
		
		if(syblingInvocationId==0)
			parentNumIndices[parentId] = numParentOutputEdges;
	}
}
).";


inline const std::string buildComputeShaderPropagate(unsigned int numSubgroupsPerWG, unsigned int subgroupSize)
{
	return propagationComputeShaderPrologue +
		"layout(local_size_x = " + std::to_string(numSubgroupsPerWG * subgroupSize) + ") in;\n\n" +
		propagationComputeShaderBody;
}