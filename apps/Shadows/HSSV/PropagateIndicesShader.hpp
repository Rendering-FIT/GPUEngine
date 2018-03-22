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
	uint voxelNumIndicesExclusivePrefixSum[];};

layout(std430, binding=2) buffer _outputIndices{
	uint outputIndices[];};

layout(std430, binding=3) buffer _outputNumIndices{
	uint outputNumIndices[];};

layout(std430, binding=4) buffer _parentIndices{
	uint parentIndices[];};

layout(std430, binding=5) buffer _numParentIndices{
	uint parentNumIndices[];};

layout(std430, binding=6) buffer _atomicCounter{
	uint atomicCounter;};

bool haveSyblingsAgreed(uint64_t ballotResult, uint syblingGroup)
{
	return ((ballotResult >> (syblingGroup*8)) & 0xFF) == 255;
}

bool atLeastOne(uint64_t ballotResult, uint syblingGroup)
{
	return ((ballotResult >> (syblingGroup*8)) & 0xFF) != 0;
}


uniform uint nofVoxels;
uniform uint maxNofEdges;

void main()
{
	#define syblingGroup (gl_SubGroupInvocationARB/8)
	#define syblingInvocationId (gl_SubGroupInvocationARB%8)

	while(true)
	{
		uint startingVoxel = 0;
		
		if(gl_SubGroupInvocationARB==0)
			startingVoxel = atomicAdd(atomicCounter, gl_SubGroupSizeARB);
		
		startingVoxel = readFirstInvocationARB(startingVoxel);
		const uint currentVoxel = startingVoxel + gl_SubGroupInvocationARB;

		if(currentVoxel>=nofVoxels)
			return;

		//TODO - toto ziskanie prace dat do while, proste na spodnu smycku az ked maju vsetky sybling grupy nejaku pracu alokovanu
		const uint startingOutputIndex = voxelNumIndicesExclusivePrefixSum[currentVoxel];
		const uint numEdgesInVoxel = voxelNumIndicesExclusivePrefixSum[currentVoxel+1] - startingOutputIndex;
		const uint parentId = currentVoxel/8;
		const uint numEdgesInFirst = readInvocationARB(numEdgesInVoxel, syblingGroup*8);				

		uint numOutputEdges = 0;
		uint numParentOutputEdges = 0;
		
		uint cachedValue = 0;
		bool isCacheValid = false;
		uint positionInEdgeBuffer = 0;

		for(unsigned int i = 0; i<numEdgesInFirst; ++i)
		{
			//Cache a value
			if((!isCacheValid) && (positionInEdgeBuffer<numEdgesInVoxel))
			{
				cachedValue = voxelEdgeIndicesSorted[startingOutputIndex + positionInEdgeBuffer++];
				isCacheValid = true;
			}
			
			const uint referenceValue = readInvocationARB(cachedValue, syblingGroup * 8);
			
			//Write to output all indices less than reference value
			while(isCacheValid && (cachedValue<referenceValue))
			{
				outputIndices[startingOutputIndex + numOutputEdges++] = cachedValue;
				if(positionInEdgeBuffer<numEdgesInVoxel)
					cachedValue = voxelEdgeIndicesSorted[startingOutputIndex + positionInEdgeBuffer++];
				else
					isCacheValid = false;
			}
			
			const uint64_t refCompare = ballotARB(isCacheValid && (cachedValue == referenceValue));

			if(haveSyblingsAgreed(refCompare, syblingGroup))
			{
				if(syblingInvocationId==0)
					parentIndices[(maxNofEdges*parentId)+numParentOutputEdges++] = referenceValue;
				
				isCacheValid = false;
			}
			else if((cachedValue <= referenceValue) && isCacheValid)
			{
				outputIndices[startingOutputIndex + numOutputEdges++] = cachedValue;
				isCacheValid = false;
			}
		}
		
		if(isCacheValid)
			outputIndices[startingOutputIndex + numOutputEdges++] = cachedValue;

		//Write leftover edges
		for(unsigned int i = positionInEdgeBuffer; i<numEdgesInVoxel; ++i)
			outputIndices[startingOutputIndex + numOutputEdges++] = voxelEdgeIndicesSorted[startingOutputIndex + i];

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
