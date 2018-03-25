#pragma once
#include <string>

const std::string generateSidesCS = R".(
layout(local_size_x=WORKGROUP_SIZE_X) in;

//vec3 lowerPoint, vec3 higherPoint, uint numOpposite, uint oppositeStartingIndex
layout(std430, binding=0) readonly buffer _edges{
	float edges[]; };

layout(std430, binding=1) readonly buffer _edgeIdsToGenerate{
	uint edgesIdToGenerate[]; };

layout(std430, binding=2) buffer _generatedSideEdges{
	vec4 sideEdges[]; };

layout(std430, binding=3) buffer _drawIndirectBuffer{
	uint drawIndirect[4]; };

//6x vertex, 2x uint - count and start of opposite vertices
#define EDGE_NUM_FLOATS 8

void getEdge(in uint edgeId, inout vec3 lowerPoint, inout vec3 higherPoint)
{
	lowerPoint =  vec3(edges[EDGE_NUM_FLOATS*edgeId + 0], edges[EDGE_NUM_FLOATS*edgeId + 1], edges[EDGE_NUM_FLOATS*edgeId + 2]);
	higherPoint = vec3(edges[EDGE_NUM_FLOATS*edgeId + 3], edges[EDGE_NUM_FLOATS*edgeId + 4], edges[EDGE_NUM_FLOATS*edgeId + 5]);
}

int decodeEdgeMultiplicityFromId(uint edgeWithEncodedMultiplicity)
{
	int val = 1;

	const int sign = (int(edgeWithEncodedMultiplicity) & (1<<31)) != 0 ? -1 : 1;
	const int isTwo = (int(edgeWithEncodedMultiplicity) & (1<<30)) != 0 ? 1 : 0;

	return (val + isTwo)*sign;
}

uint decodeEdgeFromEncoded(uint edgeWithEncodedMultiplicity)
{
	return (edgeWithEncodedMultiplicity & 0x3FFFFFFF);
}

void pushEdge(int multiplicity, uint startingIndex, vec3 L, vec3 H)
{
	const uint absMultiplicity = abs(multiplicity);

	if(multiplicity<0)
	{
		for(uint i = 0; i<absMultiplicity; ++i)
		{
			sideEdges[startingIndex + 2*i + 0] = vec4(L, 1);
			sideEdges[startingIndex + 2*i + 1] = vec4(H, 1);
		}
	}
	else
	{
		for(uint i = 0; i<absMultiplicity; ++i)
		{
			sideEdges[startingIndex + 2*i + 0] = vec4(H, 1);
			sideEdges[startingIndex + 2*i + 1] = vec4(L, 1);
		}
	}
}

uniform uint nofEdgesToGenerate;

void main()
{
	const uint gid = gl_GlobalInvocationID.x;
	if(gid>=nofEdgesToGenerate) return;
	
	vec3 h = vec3(0);
	vec3 l = vec3(0);
	
	const uint encodedEdge = edgesIdToGenerate[gid];

	const int multiplicity = decodeEdgeMultiplicityFromId(encodedEdge);
	const uint edge = decodeEdgeFromEncoded(encodedEdge);
	getEdge(edge, l, h);

	const uint outputStartingPos = atomicAdd(drawIndirect[0], 2*abs(multiplicity));
	
	pushEdge(multiplicity, outputStartingPos, l, h);
}
).";


const std::string testAndGenerateSidesCS = R".(
layout(local_size_x=WORKGROUP_SIZE_X) in;

//vec3 lowerPoint, vec3 higherPoint, uint numOpposite, uint oppositeStartingIndex
layout(std430, binding=0) readonly buffer _edges{
	float edges[]; };

layout(std430, binding=1) readonly buffer _oppositeVertices{
	float oppositeVertices[];};

layout(std430, binding=2) readonly buffer _edgeIdsToGenerate{
	uint edgesIdToTest[]; };

layout(std430, binding=3) buffer _generatedSideEdges{
	vec4 sideEdges[]; };

layout(std430, binding=4) buffer _drawIndirectBuffer{
	uint drawIndirect[4]; };

//------------------MULTIPLICITY------------------
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

//------------------EDGE------------------
//6x vertex, 2x uint - count and start of opposite vertices
#define EDGE_NUM_FLOATS 8

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

vec3 getOppositeVertex(uint startingIndex, uint vertexId)
{
	return vec3(oppositeVertices[startingIndex + 3*vertexId + 0], oppositeVertices[startingIndex + 3*vertexId + 1], oppositeVertices[startingIndex + 3*vertexId + 2]);
}

void pushEdge(int multiplicity, uint startingIndex, vec3 L, vec3 H)
{
	const uint absMultiplicity = abs(multiplicity);

	if(multiplicity<0)
	{
		for(uint i = 0; i<absMultiplicity; ++i)
		{
			sideEdges[startingIndex + 2*i + 0] = vec4(L, 1);
			sideEdges[startingIndex + 2*i + 1] = vec4(H, 1);
		}
	}
	else
	{
		for(uint i = 0; i<absMultiplicity; ++i)
		{
			sideEdges[startingIndex + 2*i + 0] = vec4(H, 1);
			sideEdges[startingIndex + 2*i + 1] = vec4(L, 1);
		}
	}
}

uniform uint nofEdgesToTest;
uniform vec4 lightPos;

void main()
{
	const uint gid = gl_GlobalInvocationID.x;
	if(gid>=nofEdgesToTest)return;

	const uint edge = edgesIdToTest[gid];
	vec3 h = vec3(0);
	vec3 l = vec3(0);
	getEdge(edge, l, h);
	const uint nofOpposite = getEdgeNofOppositeVertices(edge);
	const uint oppositeStartingIndex = getEdgeOppositeVerticesStartingIndex(edge);

	int multiplicity = 0;

	for(unsigned int i=0; i<nofOpposite; ++i)
	{
		const vec3 opposite = getOppositeVertex(oppositeStartingIndex, i);
		multiplicity += currentMultiplicity(l, h, opposite, vec3(lightPos));
	}

	const uint startingPos = atomicAdd(drawIndirect[0], 2*abs(multiplicity));

	pushEdge(multiplicity, startingPos, l, h);
}
).";