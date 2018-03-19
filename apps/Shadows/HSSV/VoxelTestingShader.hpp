#pragma once

#include <string>

const std::string voxelComputeShaderPrologue = R".(
#version 450 core
#extension GL_ARB_gpu_shader_int64: require
#extension GL_ARB_shader_ballot: require

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
	uint nofPotentialEdgesPerVoxel[];};

layout(std430, binding=6) buffer _outputNofSilhouetteEdges{
	uint nofSilhouetteEdgesPerVoxel[];};
	
layout(std430, binding=7) buffer _atomicCounter{
	uint voxelAtomicCounter;};

//------------------UNIFORMS------------------

uniform uint nofEdges;
uniform uint nofVoxels;

//------------------SETTER/STORE FUNCTIONS------------------

void storePotentialEdge(uint edgeId, uint voxelId)
{
	voxelEdgesPotential[nofEdges * voxelId + nofPotentialEdgesPerVoxel[voxelId]] = edgeId;
	nofPotentialEdgesPerVoxel[voxelId]+=1;
}

void storeSilhouetteEdge(uint edgeId, uint voxelId)
{
	voxelEdgesSilhouette[nofEdges * voxelId + nofSilhouetteEdgesPerVoxel[voxelId]] = edgeId;
	nofSilhouetteEdgesPerVoxel[voxelId]+=1;
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
	points[2] = vec3(minPoint.x, minPoint.y, minPoint.z + extents.z);
	points[3] = vec3(minPoint.x + extents.y, minPoint.y, minPoint.z + extents.z);

	points[4] = vec3(minPoint.x, minPoint.y + extents.y, minPoint.z);
	points[5] = vec3(minPoint.x + extents.x, minPoint.y + extents.y, minPoint.z);
	points[6] = vec3(minPoint.x, minPoint.y + extents.y, minPoint.z + extents.z);
	points[7] = maxPoint;
}

float testPlanePoint(in vec4 plane, in vec3 point)
{
	return dot(plane, vec4(point, 1));
}

bool isPlaneIntersectingAabb(inout vec3 points[8], in vec4 plane)
{
	int result = int(sign(testPlanePoint(plane, points[0])));
	
	for(unsigned int i=1; i<8; ++i)
	{
		int r = int(sign(testPlanePoint(plane, points[i])));
		
		if(r!=result)
			return true;
	}
	
	return false;
}

 bool isEdgeSpaceAaabbIntersecting(
	in vec4 p1, 
	in vec4 p2, 
	in vec3 aabbLow,
	in vec3 aabbHigh)
{
	vec3 points[8];
	getAabbPoints(aabbLow, aabbHigh, points);
		
	bool result1 = isPlaneIntersectingAabb(points, p1);
	bool result2 = isPlaneIntersectingAabb(points, p2);

	return result1 || result2;
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
shared float wgSharedMemory[SHM_SIZE_FLOATS];

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
	//Get thread identifiers
	
	//Acquire work chunk voxels
	
	//for all edges
	
		//cache edges chunk to shm 
	
		//for all cached
	
			//test intersect
			//if not intersect
				//calc multiplicity
			
			//broadcast potential of first thread in syblings 4x ()
			//ballot potential
			//if potential ballot all in group of 8
				//store in parent
			//else
				//store in voxel
			
			//broadcast silhouette of first thread in syblings 4x ()
			//ballot is equal
			//if is equal to all in syblings
				//store in parent
			//else
				//store in voxel
	
	//Identifiers & constants
	#define numSubgroupsPerWG (gl_WorkGroupSize.x/gl_SubGroupSizeARB)
	#define subgroupIdWithinWG (gl_LocalInvocationIndex/gl_SubGroupSizeARB)
	#define syblingGroup (gl_SubGroupInvocationARB/8)
	#define syblingInvocationId (gl_SubGroupInvocationARB%8)
	#define shmEdgeCapacityPerSubgroup (SHARED_MEMORY_PER_SUBGROUP_FLOATS / EDGE_NUM_FLOATS)
	
	//Prepare shared memory
	const uint shmBaseOffset = subgroupIdWithinWG * SHARED_MEMORY_PER_SUBGROUP_FLOATS;
	
	while(true)
	{
		//Acquire voxels
		uint startingIndex = 0;
		
		if(gl_SubGroupInvocationARB==0)
			startingIndex = atomicAdd(voxelAtomicCounter, gl_SubGroupSizeARB);
			
		startingIndex = readFirstInvocationARB(startingIndex);
		const uint currentVoxel = startingIndex + gl_SubGroupInvocationARB;
		
		if(currentVoxel>=nofVoxels)
			return;
		
		const uint currentParent = currentVoxel/8;
		const uvec2 aliveThreads = uvec2(ballotARB(true));
		const uint numAlive = bitCount(aliveThreads.x) + bitCount(aliveThreads.y);
		uint currentStartingEdge = 0;
		
		while(currentStartingEdge < nofEdges)
		{
			//Cache edges
			const uint numCachedEdges = min(shmEdgeCapacityPerSubgroup, nofEdges - currentStartingEdge);
			const uint numIters = numCachedEdges / numAlive;
			
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
			const uint numLeftover = numCachedEdges - (numIters * numAlive);
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
				
				if(numOpposite==1)
				{
					//Store in parent
					//if(syblingInvocationId==0)
					//	storePotentialEdge(currentEdge, nofVoxels + currentParent);
					
					continue;
				}
				
				const uint oppositeVerticesStartingIndex = getEdgeOppositeVerticesStartingIndex(shmBaseOffset, cachedEdgeIndex);
				
				//Build edge planes
				const vec3 opposite1 = getOppositeVertex(oppositeVerticesStartingIndex, 0);
				const vec3 opposite2 = getOppositeVertex(oppositeVerticesStartingIndex, 1);
				
				vec4 p1 = createFromPointsCCW(edgeLower, opposite1, edgeHigher);
				vec4 p2 = createFromPointsCCW(edgeLower, opposite2, edgeHigher);
				
				//Get voxel AABB
				vec3 aabbLow, aabbHigh;
				getVoxel(currentVoxel, aabbLow, aabbHigh);
				
				const bool isPotentiallySilhouette = isEdgeSpaceAaabbIntersecting(p1, p2, aabbLow, aabbHigh);

				//TODO - in the future, here loop over all opposite vertices, here just fixed 2
				int multiplicity = currentMultiplicity(edgeLower, edgeHigher, opposite1, aabbLow);
				multiplicity += currentMultiplicity(edgeLower, edgeHigher, opposite2, aabbLow);
				
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
							storePotentialEdge(currentEdge, nofVoxels + currentParent);
					}
					else
						storePotentialEdge(currentEdge, currentVoxel);
					
				}
				else if(isSilhouette)
				{
					if(isSilhouetteInAllSyblings)
					{
						const uint reference = readInvocationARB(currentEdge, syblingGroup*8);
						const uint64_t result = ballotARB(reference==currentEdge);
						
						if(haveSyblingsAgreed(result, syblingGroup) && syblingInvocationId==0)
							storeSilhouetteEdge(currentEdge, nofVoxels + currentParent);
					}
					else
						storeSilhouetteEdge(currentEdge, currentVoxel);
				}
			}
			
			//Finish
			currentStartingEdge += numCachedEdges;
		}
	}
}

/*
void getEdge(in uint edgeId, inout vec3 lowerPoint, inout vec3 higherPoint)
{
	lowerPoint =  vec3(edges[EDGE_NUM_FLOATS*edgeId + 0], edges[EDGE_NUM_FLOATS*edgeId + 1], edges[EDGE_NUM_FLOATS*edgeId + 2]);
	higherPoint = vec3(edges[EDGE_NUM_FLOATS*edgeId + 3], edges[EDGE_NUM_FLOATS*edgeId + 4], edges[EDGE_NUM_FLOATS*edgeId + 5]);
}

uint getEdgeNofOppositeVertices(in uint edgeId)
{
	return floatBitsToUint(edges[EDGE_NUM_FLOATS*edgeId + 6]);
}

uint getEdgeOppositeVerticesStartingIndex(in uint edgeId)
{
	return floatBitsToUint(edges[EDGE_NUM_FLOATS*edgeId + 7]);
}


void main()
{
	//Identifiers & constants
	#define subgroupIdWithinWG (gl_LocalInvocationIndex/gl_SubGroupSizeARB)
	#define syblingGroup (gl_SubGroupInvocationARB/8)
	#define syblingInvocationId (gl_SubGroupInvocationARB%8)
	
	while(true)
	{
		//Acquire voxels
		uint startingIndex = 0;
		
		if(gl_SubGroupInvocationARB==0)
			startingIndex = atomicAdd(voxelAtomicCounter, gl_SubGroupSizeARB);
			
		startingIndex = readFirstInvocationARB(startingIndex);
		const uint currentVoxel = startingIndex + gl_SubGroupInvocationARB;
		
		if(currentVoxel>=nofVoxels)
			return;
		
		const uint currentParent = currentVoxel/8;
		const uvec2 aliveThreads = uvec2(ballotARB(true));
		const uint numAlive = bitCount(aliveThreads.x) + bitCount(aliveThreads.y);
		
		//Get voxel AABB
		vec3 aabbLow, aabbHigh;
		getVoxel(currentVoxel, aabbLow, aabbHigh);

		for(uint currentEdge=0; currentEdge < nofEdges; ++currentEdge)
		{
			//Get edge
			vec3 edgeLower = vec3(0);
			vec3 edgeHigher = vec3(0);
			uint workingEdge = currentEdge;				

			getEdge(workingEdge, edgeLower, edgeHigher);
			const uint numOpposite = getEdgeNofOppositeVertices(workingEdge);
				
			if(numOpposite==1)
				continue;
				
			const uint oppositeVerticesStartingIndex = getEdgeOppositeVerticesStartingIndex(workingEdge);
				
			//Build edge planes
			const vec3 opposite1 = getOppositeVertex(oppositeVerticesStartingIndex, 0);
			const vec3 opposite2 = getOppositeVertex(oppositeVerticesStartingIndex, 1);
				
			vec4 p1 = createFromPointsCCW(edgeLower, opposite1, edgeHigher);
			vec4 p2 = createFromPointsCCW(edgeLower, opposite2, edgeHigher);
								
			const bool isPotentiallySilhouette = isEdgeSpaceAaabbIntersecting(p1, p2, aabbLow, aabbHigh);

			//TODO - in the future, here loop over all opposite vertices, here just fixed 2
			int multiplicity = currentMultiplicity(edgeLower, edgeHigher, opposite1, aabbLow);
			multiplicity += currentMultiplicity(edgeLower, edgeHigher, opposite2, aabbLow);
				
			const bool isSilhouette = (!isPotentiallySilhouette) && (multiplicity!=0);

			if(isSilhouette)
				workingEdge = encodeEdgeMultiplicityToId(workingEdge, multiplicity);
				
			const uint64_t potential = ballotARB(isPotentiallySilhouette);
			const uint64_t silhouette = ballotARB(isSilhouette);
			
			const bool isPotentialInAllSyblings =  haveSyblingsAgreed(potential,  syblingGroup);
			const bool isSilhouetteInAllSyblings = haveSyblingsAgreed(silhouette, syblingGroup);
				
			if(isPotentiallySilhouette)
			{
				if(isPotentialInAllSyblings)
				{
					if(syblingInvocationId==0)
						storePotentialEdge(workingEdge, nofVoxels + currentParent);
				}
				else
					storePotentialEdge(workingEdge, currentVoxel);
					
			}
			else if(isSilhouette)
			{
				if(isSilhouetteInAllSyblings)
				{
					const uint reference = readInvocationARB(workingEdge, syblingGroup*8);
					const uint64_t result = ballotARB(reference==workingEdge);
					
					if(haveSyblingsAgreed(result, syblingGroup) && syblingInvocationId==0)
						storeSilhouetteEdge(workingEdge, nofVoxels + currentParent);
				}
				else
					storeSilhouetteEdge(workingEdge, currentVoxel);
			}
		}
	}

}
//*/
).";

inline const std::string buildComputeShader(unsigned int numSubgroupsPerWG, unsigned int subgroupSize, unsigned int shmPerSubgroup)
{
	return voxelComputeShaderPrologue + 
		"#define SHARED_MEMORY_PER_SUBGROUP_FLOATS " + std::to_string(shmPerSubgroup/sizeof(float)) + "\n" +
		"#define SHM_SIZE_FLOATS " + std::to_string(numSubgroupsPerWG * shmPerSubgroup / sizeof(float)) + "\n" +
		"layout(local_size_x = " + std::to_string(numSubgroupsPerWG * subgroupSize) + ") in;\n\n" +
		voxelComputeShaderBody;
}