#pragma once

#include <string>

const std::string propagationComputeShaderPrologue = R".(
#version 450 core
#extension GL_ARB_shader_ballot : enable
#extension GL_ARB_gpu_shader_int64 : enable
#extension GL_AMD_gpu_shader_int64 : enable

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
	uint numParentIndices[];};

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

	//while(true)
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
			numParentIndices[parentId] = numParentOutputEdges;
	}
}
).";

inline const std::string buildComputeShaderPropagate(unsigned int workgroupSize)
{
	return propagationComputeShaderPrologue +
		"layout(local_size_x = " + std::to_string(workgroupSize) + ") in;\n\n" +
		propagationComputeShaderBody;
}

/*
const std::string propagationComputeShaderBody2 = R".(

layout(std430, binding=0) readonly buffer _indices{
	uint voxelEdgeIndicesSorted[];};

layout(std430, binding=1) readonly buffer _numIndices{
	uint voxelNumIndicesExclusivePrefixSum[];};

layout(std430, binding=2) writeonly buffer _outputIndices{
	uint outputIndices[];};

layout(std430, binding=3) writeonly buffer _outputNumIndices{
	uint outputNumIndices[];};

layout(std430, binding=4) writeonly buffer _parentIndices{
	uint parentIndices[];};

layout(std430, binding=5) writeonly buffer _numParentIndices{
	uint numParentIndices[];};

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

uint positionInEdgeBuffer = 0;
uint cache[CACHE_SIZE];
uint cachePtr = 0;
uint nofCached = 0;

void loadCache(uint numToLoad, uint startingIndex)
{
	nofCached = numToLoad;
	for(uint i = 0; i<nofCached; ++i)
	{
		cache[i] = voxelEdgeIndicesSorted[startingIndex + positionInEdgeBuffer++];
	}
	cachePtr = 0;
}

bool isCacheValid()
{
	return (nofCached>0) && (cachePtr<nofCached);
}

bool isDataLeft(uint numEdgesInVoxel)
{
	return positionInEdgeBuffer < numEdgesInVoxel;
}

void main()
{
	#define syblingGroup (gl_SubGroupInvocationARB/8)
	#define syblingInvocationId (gl_SubGroupInvocationARB%8)

	uint startingVoxel = 0;
	
	if(gl_SubGroupInvocationARB==0)
		startingVoxel = atomicAdd(atomicCounter, gl_SubGroupSizeARB);
	
	startingVoxel = readFirstInvocationARB(startingVoxel);
	const uint currentVoxel = startingVoxel + gl_SubGroupInvocationARB;

	if(currentVoxel>=nofVoxels)
		return;

	const uint startingIndex = voxelNumIndicesExclusivePrefixSum[currentVoxel];
	const uint numEdgesInVoxel = voxelNumIndicesExclusivePrefixSum[currentVoxel+1] - startingIndex;
	const uint parentId = currentVoxel/8;
	const uint numEdgesInFirst = readInvocationARB(numEdgesInVoxel, syblingGroup*8);				

	uint numOutputEdges = 0;
	uint numParentOutputEdges = 0;

	for(unsigned int i = 0; i<numEdgesInFirst; ++i)
	{
		if(!isCacheValid())
			loadCache(min(numEdgesInVoxel-positionInEdgeBuffer, CACHE_SIZE), startingIndex);
		
		const uint referenceValue = readInvocationARB(cache[cachePtr], syblingGroup * 8);
		
		//Write to output all indices less than reference value
		while(true)
		{
			while(isCacheValid() && cache[cachePtr] < referenceValue)			
			{
				outputIndices[startingIndex + numOutputEdges++] = cache[cachePtr++];
			}
			
			const bool cacheValid = isCacheValid();
			const bool isDataLeft = positionInEdgeBuffer < numEdgesInVoxel;

			if(cacheValid || !isDataLeft)
			{
				break;
			}

			if(!cacheValid)
			{
				loadCache(min(numEdgesInVoxel-positionInEdgeBuffer, CACHE_SIZE), startingIndex);
			}
		}
		
		const uint64_t refCompare = ballotARB(isCacheValid() && (cache[cachePtr] == referenceValue));

		const bool goesToParent = haveSyblingsAgreed(refCompare, syblingGroup);
		if(goesToParent)
		{
			if(syblingInvocationId==0)
			{
				parentIndices[(maxNofEdges*parentId)+numParentOutputEdges++] = referenceValue;
			}
		}
		
		//Advance in cachePtr 
		//for 0th threads only - when edges was not agreed on
		//all - when edge was agreed
		if(isCacheValid() && ( goesToParent || syblingInvocationId==0))
		{
			++cachePtr;
		}
	}
	
	for(uint i = cachePtr; i<nofCached; ++i)
	{
		outputIndices[startingIndex + numOutputEdges++] = cache[i];
	}

	//Write leftover edges
	for(unsigned int i = positionInEdgeBuffer; i<numEdgesInVoxel; ++i)
		outputIndices[startingIndex + numOutputEdges++] = voxelEdgeIndicesSorted[startingIndex + i];

	outputNumIndices[currentVoxel] = numOutputEdges;
	
	if(syblingInvocationId==0)
		numParentIndices[parentId] = numParentOutputEdges;
}
).";

inline const std::string buildComputeShaderPropagate2(unsigned int workgroupSize, unsigned int cacheSize)
{
	return propagationComputeShaderPrologue +
		"layout(local_size_x = " + std::to_string(workgroupSize) + ") in;\n\n" +
		"#define CACHE_SIZE " + std::to_string(cacheSize) + "u\n\n" +
		propagationComputeShaderBody2;
}
*/