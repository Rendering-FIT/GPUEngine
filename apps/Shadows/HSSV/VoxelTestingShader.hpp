#pragma once

#include <string>

const std::string voxelComputeShaderPrologue = R".(
#version 450 core

).";


const std::string voxelComputeShaderBody = R".(
//------------------BUFFERS------------------
//vec3 lowerPoint, vec3 higherPoint, uint numOpposite, uint oppositeStartingIndex
layout(std430, binding=0) readonly buffer _edges{
	float edges[]; };

layout(std430, binding=1) readonly buffer _oppositeVertices{
	float oppositeVertices[];};

layout(std430, binding=2) readonly buffer _voxels{
	float voxels[];};

layout(std430, binding=3) buffer _potential{
	uint voxelEdgesPotential[];};

layout(std430, binding=4) buffer _silhouette{
	uint voxelEdgesSilhouette[];};

layout(std430, binding=5) buffer _outputNofPotentialEdges{
	volatile uint nofPotentialEdgesPerVoxel[];};

layout(std430, binding=6) buffer _outputNofSilhouetteEdges{
	volatile uint nofSilhouetteEdgesPerVoxel[];};
	
layout(std430, binding=7) buffer _atomicCounter{
	uint voxelAtomicCounter;};

//------------------UNIFORMS------------------

uniform uint nofEdges;
uniform uint nofVoxels;

//------------------SETTER/STORE FUNCTIONS------------------

void storePotentialEdge(uint edgeId, uint voxelId, uint position)
{
	voxelEdgesPotential[nofEdges * voxelId + position] = edgeId;
}

void storeSilhouetteEdge(uint edgeId, uint voxelId, uint position)
{
	voxelEdgesSilhouette[nofEdges * voxelId + position] = edgeId;
}

//------------------MULTIPLICITY FUNCTIONS------------------

int greaterVec(vec3 a,vec3 b)
{
	return int(dot(ivec3(sign(a-b)),ivec3(4,2,1)));
}

int computeMult(vec3 A,vec3 B,vec3 C,vec3 L)
{
	vec3 n=cross(C-A,L-A);
	return int(sign(dot(n,B-A)));
}

int currentMultiplicity(vec3 A, vec3 B, vec3 O, vec3 L)
{
	if(greaterVec(A,O)>0)
		return computeMult(O,A,B,L);
	
	if(greaterVec(B,O)>0)
		return -computeMult(A,O,B,L);
	
	return computeMult(A,B,O,L);
}

uint encodeEdgeMultiplicityToId(uint edgeID, int multiplicity)
{
	uint val = edgeID;

	val |= multiplicity < 0 ? (1 << 31) : 0;
	val |= abs(multiplicity) == 2 ? (1 << 30) : 0;

	return val;
}

//------------------GEOMETRY FUNCTIONS------------------

void getAabbPoints(
	in vec3 minPoint,
	in vec3 maxPoint,
	inout vec3 points[8])
{
	vec3 extents = maxPoint - minPoint;
	
	points[0] = minPoint;
	points[1] = vec3(minPoint.x + extents.x, minPoint.y, minPoint.z);
	points[2] = vec3(minPoint.x,             minPoint.y, minPoint.z + extents.z);
	points[3] = vec3(minPoint.x + extents.x, minPoint.y, minPoint.z + extents.z);

	points[4] = vec3(minPoint.x,             minPoint.y + extents.y, minPoint.z);
	points[5] = vec3(minPoint.x + extents.x, minPoint.y + extents.y, minPoint.z);
	points[6] = vec3(minPoint.x,             minPoint.y + extents.y, minPoint.z + extents.z);
	points[7] = maxPoint;
}

float testPlanePoint(in vec4 plane, in vec3 point)
{
	return dot(plane, vec4(point, 1));
}

bool isPlaneIntersectingAabb(inout vec3 points[8], in vec4 plane)
{
	const int result = int(sign(testPlanePoint(plane, points[0])));
	
	for(unsigned int i=1; i<8; ++i)
	{
		const int r = int(sign(testPlanePoint(plane, points[i])));
		
		if(r!=result)
			return true;
	}
	
	return false;
}

vec4 createFromPointsCCW(in vec3 v1, in vec3 v2, in vec3 v3)
{
	vec3 normal = normalize(cross(normalize(v3 - v2), normalize(v1 - v2)));

	return vec4(normal, -v2.x*normal.x - v2.y*normal.y - v2.z*normal.z);
}

//------------------MISC------------------

bool haveSyblingsAgreed(uint64_t ballotResult, uint syblingGroup)
{
	return ((ballotResult >> (syblingGroup*8)) & 0xFF) == 255;
}

//------------------SHARED MEMORY------------------

//Must be multiple of sizeof(edge), which is 32 bytes
shared float wgSharedMemory[SHARED_MEMORY_FLOATS];

//------------------GETTER FUNCTIONS------------------

//6x vertex, 2x uint - count and start of opposite vertices
#define EDGE_NUM_FLOATS 8

vec3 getOppositeVertex(uint startingIndex, uint vertexId)
{
	return vec3(oppositeVertices[startingIndex + 3*vertexId + 0], oppositeVertices[startingIndex + 3*vertexId + 1], oppositeVertices[startingIndex + 3*vertexId + 2]);
}

void getVoxel(in uint voxelId, out vec3 lowerPoint, out vec3 higherPoint)
{
	lowerPoint =  vec3(voxels[6*voxelId + 0], voxels[6*voxelId + 1], voxels[6*voxelId + 2]);
	higherPoint = vec3(voxels[6*voxelId + 3], voxels[6*voxelId + 4], voxels[6*voxelId + 5]);
}


void getEdge(in uint shmBaseOffset, in uint edgeId, inout vec3 lowerPoint, inout vec3 higherPoint)
{
	lowerPoint =  vec3(wgSharedMemory[shmBaseOffset + EDGE_NUM_FLOATS*edgeId + 0], wgSharedMemory[shmBaseOffset + EDGE_NUM_FLOATS*edgeId + 1], wgSharedMemory[shmBaseOffset + EDGE_NUM_FLOATS*edgeId + 2]);
	higherPoint = vec3(wgSharedMemory[shmBaseOffset + EDGE_NUM_FLOATS*edgeId + 3], wgSharedMemory[shmBaseOffset + EDGE_NUM_FLOATS*edgeId + 4], wgSharedMemory[shmBaseOffset + EDGE_NUM_FLOATS*edgeId + 5]);
}

uint getEdgeNofOppositeVertices(in uint shmBaseOffset, in uint edgeId)
{
	return floatBitsToUint(wgSharedMemory[shmBaseOffset + EDGE_NUM_FLOATS*edgeId + 6]);
}

uint getEdgeOppositeVerticesStartingIndex(in uint shmBaseOffset, in uint edgeId)
{
	return floatBitsToUint(wgSharedMemory[shmBaseOffset + EDGE_NUM_FLOATS*edgeId + 7]);
}


//------------------MAIN------------------

void main()
{
	//---THE PROGRAM---
	//Get thread identifiers
	
	//Acquire work chunk voxels
	
	//for all edges
	
		//cache edges chunk to shm 
	
		//for all cached
	
			//test intersect
			//calc multiplicity
			
			//broadcast potential of first thread in syblings
			//ballot potential
			//if potential ballot all in group of 8
				//store in parent
			//else
				//store in voxel
			
			//broadcast silhouette of first thread in syblings
			//ballot is equal to first sybling
			//if is equal to all in syblings
				//store in parent
			//else
				//store in voxel
	
	//Identifiers & constants
	#define subgroupIdWithinWG (gl_LocalInvocationIndex/gl_SubGroupSizeARB)
	#define syblingGroup (gl_SubGroupInvocationARB/8)
	#define syblingInvocationId (gl_SubGroupInvocationARB%8)
	#define shmEdgeCapacityPerSubgroup (SHARED_MEMORY_FLOATS / EDGE_NUM_FLOATS)
	
	//Prepare shared memory
	const uint shmBaseOffset = subgroupIdWithinWG * SHARED_MEMORY_FLOATS;
	
	//while(true)
	//{
		//Acquire voxels
		uint startingIndex = 0;
		
		if(gl_SubGroupInvocationARB==0)
			startingIndex = atomicAdd(voxelAtomicCounter, gl_SubGroupSizeARB);
			
		startingIndex = readFirstInvocationARB(startingIndex);
		const uint currentVoxel = startingIndex + gl_SubGroupInvocationARB;
		
		if(currentVoxel>=nofVoxels)
			return;
		
		//Get voxel AABB
		vec3 aabbLow, aabbHigh;
		getVoxel(currentVoxel, aabbLow, aabbHigh);
		vec3 aabbPoints[8];
		getAabbPoints(aabbLow, aabbHigh, aabbPoints);

		const uint currentParent = currentVoxel/8;
		const uvec2 aliveThreads = unpackUint2x32(ballotARB(true));
		const uint numAlive = bitCount(aliveThreads.x) + bitCount(aliveThreads.y);
		
		uint currentStartingEdge = 0;
			
		uint currentNumPotential = 0;
		uint currentNumSilhouette = 0;
		uint parentNumPotential = 0;
		uint parentNumSilhouette = 0;
		
		while(currentStartingEdge < nofEdges)
		{
			//Cache edges
			const uint numCachedEdges = min(shmEdgeCapacityPerSubgroup, nofEdges - currentStartingEdge);
			const uint numIters = numCachedEdges / numAlive;
			const uint numLeftover = numCachedEdges % numAlive;

			for(unsigned int i=0; i<numIters; ++i)
			{
				const uint offset = (i * numAlive + gl_SubGroupInvocationARB) * EDGE_NUM_FLOATS;
				wgSharedMemory[shmBaseOffset + offset + 0] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 0];
				wgSharedMemory[shmBaseOffset + offset + 1] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 1];
				wgSharedMemory[shmBaseOffset + offset + 2] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 2];
				wgSharedMemory[shmBaseOffset + offset + 3] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 3];
				wgSharedMemory[shmBaseOffset + offset + 4] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 4];
				wgSharedMemory[shmBaseOffset + offset + 5] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 5];
				wgSharedMemory[shmBaseOffset + offset + 6] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 6];
				wgSharedMemory[shmBaseOffset + offset + 7] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 7];
			}
			
			//Cache leftover edges
			if(gl_SubGroupInvocationARB < numLeftover)
			{
				const uint offset = (numIters * numAlive + gl_SubGroupInvocationARB) * EDGE_NUM_FLOATS;
				wgSharedMemory[shmBaseOffset + offset + 0] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 0];
				wgSharedMemory[shmBaseOffset + offset + 1] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 1];
				wgSharedMemory[shmBaseOffset + offset + 2] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 2];
				wgSharedMemory[shmBaseOffset + offset + 3] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 3];
				wgSharedMemory[shmBaseOffset + offset + 4] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 4];
				wgSharedMemory[shmBaseOffset + offset + 5] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 5];
				wgSharedMemory[shmBaseOffset + offset + 6] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 6];
				wgSharedMemory[shmBaseOffset + offset + 7] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 7];
			}
			
			for(uint cachedEdgeIndex = 0; cachedEdgeIndex < numCachedEdges; ++cachedEdgeIndex)
			{
				//Get edge
				vec3 edgeLower = vec3(0);
				vec3 edgeHigher = vec3(0);
				
				getEdge(shmBaseOffset, cachedEdgeIndex, edgeLower, edgeHigher);
				const uint numOpposite = getEdgeNofOppositeVertices(shmBaseOffset, cachedEdgeIndex);
				uint currentEdge = currentStartingEdge + cachedEdgeIndex;
				const uint oppositeVerticesStartingIndex = getEdgeOppositeVerticesStartingIndex(shmBaseOffset, cachedEdgeIndex);
				
				bool isIntersectingPlanes = false;
				int multiplicity = 0;
				for(uint oppositeIndex = 0; oppositeIndex < numOpposite; ++oppositeIndex)
				{
					const vec3 opposite = getOppositeVertex(oppositeVerticesStartingIndex, oppositeIndex);
					vec4 p = createFromPointsCCW(edgeLower, opposite, edgeHigher);

					isIntersectingPlanes = isIntersectingPlanes || isPlaneIntersectingAabb(aabbPoints, p);
					multiplicity += currentMultiplicity(edgeLower, edgeHigher, opposite, aabbPoints[0]);
				}
				
				const bool isPotentiallySilhouette = isIntersectingPlanes;
				const bool isSilhouette = (!isPotentiallySilhouette) && (multiplicity!=0);				

				if(isSilhouette)
					currentEdge = encodeEdgeMultiplicityToId(currentEdge, multiplicity);
				
				const uint64_t potential = ballotARB(isPotentiallySilhouette);
				const uint64_t silhouette = ballotARB(isSilhouette);
				
				const bool isPotentialInAllSyblings =  haveSyblingsAgreed(potential,  syblingGroup);
				const bool isSilhouetteInAllSyblings = haveSyblingsAgreed(silhouette, syblingGroup);
				
				if(isPotentiallySilhouette)
				{
					if(isPotentialInAllSyblings)
					{
						if(syblingInvocationId==0)
							storePotentialEdge(currentEdge, nofVoxels + currentParent, parentNumPotential++);
					}
					else
						storePotentialEdge(currentEdge, currentVoxel, currentNumPotential++);
					
				}
				
				if(isSilhouette)
				{
					if(isSilhouetteInAllSyblings)
					{
						const uint reference = readInvocationARB(currentEdge, syblingGroup*8);
						const uint64_t result = ballotARB(reference==currentEdge);
						
						if(haveSyblingsAgreed(result, syblingGroup) && syblingInvocationId==0)
							storeSilhouetteEdge(currentEdge, nofVoxels + currentParent, parentNumSilhouette++);
					}
					else
						storeSilhouetteEdge(currentEdge, currentVoxel, currentNumSilhouette++);
				}
			}
			
			//Finish
			currentStartingEdge += numCachedEdges;
		}
		
		nofPotentialEdgesPerVoxel[currentVoxel] = currentNumPotential;
		nofSilhouetteEdgesPerVoxel[currentVoxel] = currentNumSilhouette;

		if(syblingInvocationId==0)
		{
			nofPotentialEdgesPerVoxel[nofVoxels + currentParent] = parentNumPotential;
			nofSilhouetteEdgesPerVoxel[nofVoxels + currentParent] = parentNumSilhouette;
		}
	//}
}).";

inline const std::string buildComputeShaderFillBottomLevel(unsigned int workgroupSize, unsigned int shmSizeBytes)
{
	return voxelComputeShaderPrologue +
		"#extension GL_ARB_gpu_shader_int64 : enable\n" + 
		"#extension GL_AMD_gpu_shader_int64 : enable\n" +
		"#extension GL_ARB_shader_ballot : require\n" +
		"#define SHARED_MEMORY_FLOATS " + std::to_string(shmSizeBytes / sizeof(float)) + "\n" +
		"layout(local_size_x = " + std::to_string(workgroupSize) + ") in;\n\n" +
		voxelComputeShaderBody;
}

const std::string voxelComputeShaderBody2 = R".(
//------------------BUFFERS------------------
//vec3 lowerPoint, vec3 higherPoint, uint numOpposite, uint oppositeStartingIndex
layout(std430, binding=0) readonly buffer _edges{
	float edges[]; };

layout(std430, binding=1) readonly buffer _oppositeVertices{
	float oppositeVertices[];};

layout(std430, binding=2) readonly buffer _voxels{
	float voxels[];};

layout(std430, binding=3) buffer _potential{
	uint voxelEdgesPotential[];};

layout(std430, binding=4) buffer _silhouette{
	uint voxelEdgesSilhouette[];};

layout(std430, binding=5) buffer _outputNofPotentialEdges{
	volatile uint nofPotentialEdgesPerVoxel[];};

layout(std430, binding=6) buffer _outputNofSilhouetteEdges{
	volatile uint nofSilhouetteEdgesPerVoxel[];};
	
layout(std430, binding=7) buffer _atomicCounter{
	uint voxelAtomicCounter;};

layout(std430, binding=8) buffer _parentSubbuffCounter{
	uvec2 parentSubbuffCounter[];};

layout(std430, binding=9) buffer _chunkCounter{
	uint parentChunkCounter[];};

layout(std430, binding=10) buffer _chunkDesc{
	uint16_t chunkDesc[];};

layout(std430, binding=11) buffer _currentChunkId{
	u16vec2 currentChunkId[];};

layout(std430, binding=12) buffer _parentEdges{
	uint parentEdges[];};

//------------------UNIFORMS------------------

uniform uint nofEdges;
uniform uint nofVoxels;

//------------------SETTER/STORE FUNCTIONS------------------

void storePotentialEdge(uint edgeId, uint voxelId, uint position)
{
	voxelEdgesPotential[nofEdges * voxelId + position] = edgeId;
}

void storeSilhouetteEdge(uint edgeId, uint voxelId, uint position)
{
	voxelEdgesSilhouette[nofEdges * voxelId + position] = edgeId;
}

//------------------MULTIPLICITY FUNCTIONS------------------

int greaterVec(vec3 a,vec3 b)
{
	return int(dot(ivec3(sign(a-b)),ivec3(4,2,1)));
}

int computeMult(vec3 A,vec3 B,vec3 C,vec3 L)
{
	vec3 n=cross(C-A,L-A);
	return int(sign(dot(n,B-A)));
}

int currentMultiplicity(vec3 A, vec3 B, vec3 O, vec3 L)
{
	if(greaterVec(A,O)>0)
		return computeMult(O,A,B,L);
	
	if(greaterVec(B,O)>0)
		return -computeMult(A,O,B,L);
	
	return computeMult(A,B,O,L);
}

uint encodeEdgeMultiplicityToId(uint edgeID, int multiplicity)
{
	uint val = edgeID;

	val |= multiplicity < 0 ? (1 << 31) : 0;
	val |= abs(multiplicity) == 2 ? (1 << 30) : 0;

	return val;
}

//------------------GEOMETRY FUNCTIONS------------------

void getAabbPoints(
	in vec3 minPoint,
	in vec3 maxPoint,
	inout vec3 points[8])
{
	vec3 extents = maxPoint - minPoint;
	
	points[0] = minPoint;
	points[1] = vec3(minPoint.x + extents.x, minPoint.y, minPoint.z);
	points[2] = vec3(minPoint.x,             minPoint.y, minPoint.z + extents.z);
	points[3] = vec3(minPoint.x + extents.x, minPoint.y, minPoint.z + extents.z);

	points[4] = vec3(minPoint.x,             minPoint.y + extents.y, minPoint.z);
	points[5] = vec3(minPoint.x + extents.x, minPoint.y + extents.y, minPoint.z);
	points[6] = vec3(minPoint.x,             minPoint.y + extents.y, minPoint.z + extents.z);
	points[7] = maxPoint;
}

float testPlanePoint(in vec4 plane, in vec3 point)
{
	return dot(plane, vec4(point, 1));
}

bool isPlaneIntersectingAabb(inout vec3 points[8], in vec4 plane)
{
	const int result = int(sign(testPlanePoint(plane, points[0])));
	
	for(unsigned int i=1; i<8; ++i)
	{
		const int r = int(sign(testPlanePoint(plane, points[i])));
		
		if(r!=result)
			return true;
	}
	
	return false;
}

vec4 createFromPointsCCW(in vec3 v1, in vec3 v2, in vec3 v3)
{
	vec3 normal = normalize(cross(normalize(v3 - v2), normalize(v1 - v2)));

	return vec4(normal, -v2.x*normal.x - v2.y*normal.y - v2.z*normal.z);
}

//------------------MISC------------------

uint getSyblingGroupMaskFromBallot(uint64_t ballotResult, uint syblingGroup)
{
	return uint((ballotResult >> (syblingGroup*8)) & 0xFF);
}

bool shouldStoreInParent(uint syblingGroupMask)
{
	return bitCount(syblingGroupMask) > 3;
}


//------------------SHARED MEMORY------------------

//Must be multiple of sizeof(edge), which is 32 bytes
shared float wgSharedMemory[SHARED_MEMORY_FLOATS];

//------------------GETTER FUNCTIONS------------------

//6x vertex, 2x uint - count and start of opposite vertices
#define EDGE_NUM_FLOATS 8

vec3 getOppositeVertex(uint startingIndex, uint vertexId)
{
	return vec3(oppositeVertices[startingIndex + 3*vertexId + 0], oppositeVertices[startingIndex + 3*vertexId + 1], oppositeVertices[startingIndex + 3*vertexId + 2]);
}

void getVoxel(in uint voxelId, out vec3 lowerPoint, out vec3 higherPoint)
{
	lowerPoint =  vec3(voxels[6*voxelId + 0], voxels[6*voxelId + 1], voxels[6*voxelId + 2]);
	higherPoint = vec3(voxels[6*voxelId + 3], voxels[6*voxelId + 4], voxels[6*voxelId + 5]);
}


void getEdge(in uint edgeId, inout vec3 lowerPoint, inout vec3 higherPoint)
{
	lowerPoint =  vec3(wgSharedMemory[EDGE_NUM_FLOATS*edgeId + 0], wgSharedMemory[EDGE_NUM_FLOATS*edgeId + 1], wgSharedMemory[EDGE_NUM_FLOATS*edgeId + 2]);
	higherPoint = vec3(wgSharedMemory[EDGE_NUM_FLOATS*edgeId + 3], wgSharedMemory[EDGE_NUM_FLOATS*edgeId + 4], wgSharedMemory[EDGE_NUM_FLOATS*edgeId + 5]);
}

uint getEdgeNofOppositeVertices(uint edgeId)
{
	return floatBitsToUint(wgSharedMemory[EDGE_NUM_FLOATS*edgeId + 6]);
}

uint getEdgeOppositeVerticesStartingIndex(in uint edgeId)
{
	return floatBitsToUint(wgSharedMemory[EDGE_NUM_FLOATS*edgeId + 7]);
}

shared unsigned int numAliveWG;

#define MAX_NOF_SUBBUFFERS 256

//------------------MAIN------------------

void main()
{
	//---THE PROGRAM---
	//Get thread identifiers
	
	//Acquire work chunk voxels
	
	//for all edges
	
		//cache edges chunk to shm 
	
		//for all cached
	
			//test intersect
			//calc multiplicity
			
			//broadcast potential of first thread in syblings
			//ballot potential
			//if potential ballot all in group of 8
				//store in parent
			//else
				//store in voxel
			
			//broadcast silhouette of first thread in syblings
			//ballot is equal to first sybling
			//if is equal to all in syblings
				//store in parent
			//else
				//store in voxel
	
	//Identifiers & constants
	#define syblingGroup (gl_SubGroupInvocationARB/8)
	#define syblingInvocationId (gl_SubGroupInvocationARB%8)
	#define shmEdgeCapacity (SHARED_MEMORY_FLOATS / EDGE_NUM_FLOATS)
	
	//while(true)
	//{
		//Acquire voxels
		//barrier();
		if(gl_LocalInvocationID.x==0)
		{
			numAliveWG = atomicAdd(voxelAtomicCounter, gl_WorkGroupSize.x);
		}
		barrier();
		const uint currentVoxel =  numAliveWG + gl_LocalInvocationID.x;

		if(currentVoxel>=nofVoxels)
			return;
	
		//Get voxel AABB
		vec3 aabbLow, aabbHigh;
		getVoxel(currentVoxel, aabbLow, aabbHigh);
		vec3 aabbPoints[8];
		getAabbPoints(aabbLow, aabbHigh, aabbPoints);

		const uint currentParent = currentVoxel/8;
		const uvec2 aliveThreads = unpackUint2x32(ballotARB(true));
		
		const uint numAlive = bitCount(aliveThreads.x) + bitCount(aliveThreads.y);
		
		barrier();
		if(gl_LocalInvocationID.x==0)
		{
			numAliveWG = 0;
		}
		barrier();

		if(gl_SubGroupInvocationARB==0)
			atomicAdd(numAliveWG, numAlive);
		barrier();

		uint currentStartingEdge = 0;
			
		uint currentNumPotential = 0;
		uint currentNumSilhouette = 0;
		uint parentNumPotential = 0;
		uint parentNumSilhouette = 0;
		
		while(currentStartingEdge < nofEdges)
		{
			//Cache edges
			const uint numCachedEdges = min(shmEdgeCapacity, nofEdges - currentStartingEdge);
			const uint numIters = numCachedEdges / numAliveWG;
			const uint numLeftover = numCachedEdges % numAliveWG;
			
			barrier();			

			for(unsigned int i=0; i<numIters; ++i)
			{
				const uint offset = (i * numAliveWG + gl_LocalInvocationID.x) * EDGE_NUM_FLOATS;
				wgSharedMemory[offset + 0] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 0];
				wgSharedMemory[offset + 1] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 1];
				wgSharedMemory[offset + 2] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 2];
				wgSharedMemory[offset + 3] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 3];
				wgSharedMemory[offset + 4] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 4];
				wgSharedMemory[offset + 5] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 5];
				wgSharedMemory[offset + 6] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 6];
				wgSharedMemory[offset + 7] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 7];
			}
			
			//Cache leftover edges
			if(gl_LocalInvocationID.x < numLeftover)
			{
				const uint offset = (numIters * numAliveWG + gl_LocalInvocationID.x) * EDGE_NUM_FLOATS;
				wgSharedMemory[offset + 0] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 0];
				wgSharedMemory[offset + 1] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 1];
				wgSharedMemory[offset + 2] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 2];
				wgSharedMemory[offset + 3] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 3];
				wgSharedMemory[offset + 4] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 4];
				wgSharedMemory[offset + 5] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 5];
				wgSharedMemory[offset + 6] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 6];
				wgSharedMemory[offset + 7] = edges[currentStartingEdge*EDGE_NUM_FLOATS + offset + 7];
			}
			
			barrier();

			for(uint cachedEdgeIndex = 0; cachedEdgeIndex < numCachedEdges; ++cachedEdgeIndex)
			{
				//Get edge
				vec3 edgeLower = vec3(0);
				vec3 edgeHigher = vec3(0);
				
				getEdge(cachedEdgeIndex, edgeLower, edgeHigher);
				const uint numOpposite = getEdgeNofOppositeVertices(cachedEdgeIndex);
				uint currentEdge = currentStartingEdge + cachedEdgeIndex;
				const uint oppositeVerticesStartingIndex = getEdgeOppositeVerticesStartingIndex(cachedEdgeIndex);
				
				bool isIntersectingPlanes = false;
				int multiplicity = 0;
				for(uint oppositeIndex = 0; oppositeIndex < numOpposite; ++oppositeIndex)
				{
					const vec3 opposite = getOppositeVertex(oppositeVerticesStartingIndex, oppositeIndex);
					vec4 p = createFromPointsCCW(edgeLower, opposite, edgeHigher);

					isIntersectingPlanes = isIntersectingPlanes || isPlaneIntersectingAabb(aabbPoints, p);
					multiplicity += currentMultiplicity(edgeLower, edgeHigher, opposite, aabbPoints[0]);
				}
				
				const bool isPotentiallySilhouette = isIntersectingPlanes;
				const bool isSilhouette = (!isPotentiallySilhouette) && (multiplicity!=0);				

				if(isSilhouette)
					currentEdge = encodeEdgeMultiplicityToId(currentEdge, multiplicity);
				
				const uint64_t potential = ballotARB(isPotentiallySilhouette);
				const uint64_t silhouette = ballotARB(isSilhouette);
				
				const uint syblingMaskPot = getSyblingGroupMaskFromBallot(potential,  syblingGroup);
				const uint syblingMaskSil = getSyblingGroupMaskFromBallot(silhouette, syblingGroup);

				const bool isStoredToParentPot = shouldStoreInParent(syblingMaskPot);
				const bool isStoredToParentSil = shouldStoreInParent(syblingMaskSil);

				if(isPotentiallySilhouette)
				{
					if(isStoredToParentPot)
					{
						//Choose pivot thread
						const int pivot = findLSB(syblingMaskPot);
						if(syblingInvocationId==pivot)
						{
							//Increment buffer based on mask
							const uint storeIndex = parentSubbuffCounter[currentParent*MAX_NOF_SUBBUFFERS + syblingMaskPot].x++;
							
							//If per buffer counter is zero - get next buffer
							uint16_t chunkId = uint16_t(0);
							const uint startingIndex = storeIndex & CHUNK_MASK;
							
							//Translate chunk from local sequence to global ID
							if(startingIndex==0)
							{
								//Allocate next chunk
								const uint newChunkId = parentChunkCounter[currentParent]++;
									
								//Fill chunk desc
								const uint16_t desc = uint16_t(syblingMaskPot); //highest bit is zero -> is potential
								chunkDesc[MAX_CHUNKS_PARENT * currentParent + newChunkId] = desc;

								chunkId = uint16_t(newChunkId);
								currentChunkId[currentParent * MAX_NOF_SUBBUFFERS + syblingMaskPot].x = uint16_t(newChunkId);
							}
							else
							{
								chunkId = currentChunkId[currentParent * MAX_NOF_SUBBUFFERS + syblingMaskPot].x;
							}
		
							//Store
							const uint previousParentsSize = currentParent * MAX_CHUNKS_PARENT * CHUNK_SIZE;
							const uint currentChunkStart = uint(chunkId) * CHUNK_SIZE;
							parentEdges[previousParentsSize + currentChunkStart + startingIndex] = currentEdge;
						}
					}
					else
						storePotentialEdge(currentEdge, currentVoxel, currentNumPotential++);
					
				}
				else if(isSilhouette)
				{
					if(isStoredToParentSil)
					{
						//Choose pivot thread
						const int pivot = findLSB(syblingMaskSil);
						if(syblingInvocationId==pivot)
						{
							//Increment buffer based on mask
							const uint storeIndex = parentSubbuffCounter[currentParent*MAX_NOF_SUBBUFFERS + syblingMaskSil].y++;

							//If per buffer counter is zero - get next buffer
							uint16_t chunkId = uint16_t(0);
							const uint startingIndex = storeIndex & CHUNK_MASK;
							
							//Translate chunk from local sequence to global ID
							if(startingIndex==0)
							{
								//Allocate next chunk
								const uint newChunkId = parentChunkCounter[currentParent]++;
									
								//Fill chunk desc
								uint16_t desc = uint16_t(syblingMaskSil);
								desc |= uint16_t(0x0100); //mark it silhouette
								chunkDesc[MAX_CHUNKS_PARENT * currentParent + newChunkId] = desc;
								
								chunkId = uint16_t(newChunkId);
								currentChunkId[currentParent * MAX_NOF_SUBBUFFERS + syblingMaskSil].y = uint16_t(newChunkId);
							}
							else
							{
								chunkId = currentChunkId[currentParent * MAX_NOF_SUBBUFFERS + syblingMaskSil].y;
							}
		
							//Store edge
							const uint previousParentsSize = currentParent * MAX_CHUNKS_PARENT * CHUNK_SIZE;
							const uint currentChunkStart = uint(chunkId) * CHUNK_SIZE;
							parentEdges[previousParentsSize + currentChunkStart + startingIndex] = currentEdge;
						}
					}
					else
						storeSilhouetteEdge(currentEdge, currentVoxel, currentNumSilhouette++);
				}
			}
			
			//Finish
			currentStartingEdge += numCachedEdges;
		}
		
		nofPotentialEdgesPerVoxel[currentVoxel] = currentNumPotential;
		nofSilhouetteEdgesPerVoxel[currentVoxel] = currentNumSilhouette;

		/* BUFFER MOZNO SKRATIT O PARENTOV
		if(syblingInvocationId==0)
		{
			nofPotentialEdgesPerVoxel[nofVoxels + currentParent] = parentNumPotential;
			nofSilhouetteEdgesPerVoxel[nofVoxels + currentParent] = parentNumSilhouette;
		}
		*/
	//}
}).";

inline const std::string buildComputeShaderFillBottomLevel2(unsigned int workgroupSize, unsigned int shmSizeBytes, unsigned int nofBitsCounter, unsigned int maxChunksParent)
{
	return 
	std::string("#version 450 core\n") +
		"#extension GL_ARB_gpu_shader_int64 : enable\n" +
		"#extension GL_AMD_gpu_shader_int64 : enable\n" +
		"#extension GL_ARB_shader_ballot : enable\n" +
		"#extension GL_NV_gpu_shader5 : enable\n" + //16-bit int
		"#extension GL_AMD_gpu_shader_int16 : enable\n" +
		"#define SHARED_MEMORY_FLOATS " + std::to_string(shmSizeBytes / sizeof(float)) + "\n" +
		"#define MAX_CHUNKS_PARENT " + std::to_string(maxChunksParent) + "\n" +
		"#define CHUNK_SIZE " + std::to_string(1 << nofBitsCounter) + "\n" + "\n" +
		"#define CHUNK_MASK " + std::to_string(uint32_t(1 << nofBitsCounter) - 1) + "u\n" +
		"layout(local_size_x = " + std::to_string(workgroupSize) + ") in;\n\n" +
		voxelComputeShaderBody2;
}