#pragma once
#include <string>

const std::string edgeFunctions = R".(
#define EDGE_NUM_FLOATS 8
void getEdge(in uint edgeId, inout vec3 lowerPoint, inout vec3 higherPoint)
{
	lowerPoint =  vec3(edges[EDGE_NUM_FLOATS*edgeId + 0], edges[EDGE_NUM_FLOATS*edgeId + 1], edges[EDGE_NUM_FLOATS*edgeId + 2]);
	higherPoint = vec3(edges[EDGE_NUM_FLOATS*edgeId + 3], edges[EDGE_NUM_FLOATS*edgeId + 4], edges[EDGE_NUM_FLOATS*edgeId + 5]);
}

int decodeEdgeMultiplicityFromId(uint edgeWithEncodedMultiplicity)
{
	const int sign = (edgeWithEncodedMultiplicity & (1u<<31)) != 0 ? -1 : 1;
	const int isTwo = (edgeWithEncodedMultiplicity & (1u<<30)) != 0 ? 1 : 0;

	return (1 + isTwo)*sign;
}

uint decodeEdgeFromEncoded(uint edgeWithEncodedMultiplicity)
{
	return (edgeWithEncodedMultiplicity & 0x3FFFFFFF);
}

).";

const std::string oppositeVertexFunctions = R".(
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

).";

const std::string multiplicityFunctions = R".(
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

).";

const std::string pushEdgeFunction = R".(
void pushEdge(uint absMultiplicity, uint startingIndex, vec3 L, vec3 H)
{
	for(uint i = 0; i<absMultiplicity; ++i)
	{
		sideEdges[startingIndex + 2*i + 0] = vec4(L, 1);
		sideEdges[startingIndex + 2*i + 1] = vec4(H, 1);
	}
}
).";

const std::string sidesVS = R".(
#version 450 core
void main(){
}).";

const std::string sidesTCS = R".(
#version 450 core
layout(vertices=1)out;
void main()
{
	gl_TessLevelOuter[0]=1;
	gl_TessLevelOuter[1]=1;
	gl_TessLevelOuter[2]=1;
    gl_TessLevelOuter[3]=1;
    gl_TessLevelInner[0]=1;
    gl_TessLevelInner[1]=1;
}).";

const std::string silhouetteSidesTES = R".(
#version 450 core
layout(quads)in;

layout(std430, binding=0) readonly buffer _edges{
	float edges[]; };

layout(std430, binding=1) readonly buffer _edgeIdsToGenerate{
	uint edgesIdToGenerate[]; };
)."
+ edgeFunctions +
R".(
uniform mat4 mvp           = mat4(1)            ;
uniform vec4 lightPosition = vec4(100,100,100,1);

out flat uint multiplicity;

void main()
{
	const uint encodedEdge = edgesIdToGenerate[gl_PrimitiveID];
	const uint edgeId = decodeEdgeFromEncoded(encodedEdge);
	const int mult = decodeEdgeMultiplicityFromId(encodedEdge);
	multiplicity = abs(mult);

	vec3 edgeVertices[2];
	edgeVertices[0] = vec3(0);
	edgeVertices[1] = vec3(0);

	getEdge(edgeId, edgeVertices[0], edgeVertices[1]);
	
	const uint swapVertices = uint(mult>0);

	vec4 outPos;
	outPos.xyz = edgeVertices[uint(gl_TessCoord.x<0.5f) ^ swapVertices]-lightPosition.xyz*float(gl_TessCoord.y<0.5f);
	outPos.w = float(gl_TessCoord.y>0.5f);

	gl_Position = mvp * outPos;
}).";


const std::string sidesGS = R".(
layout(triangles)in;
layout(triangle_strip,max_vertices=MAX_VERTICES)out;

in flat uint multiplicity[];

void main()
{
	for(uint i=0; i<multiplicity[0]; ++i) 
	{
		gl_Position = gl_in[0].gl_Position;
		EmitVertex();					  
		gl_Position = gl_in[1].gl_Position;
		EmitVertex();					  
		gl_Position = gl_in[2].gl_Position;
		EmitVertex();
		EndPrimitive();
	}
}).";


const std::string silhouetteSidesGS = R".(
layout(points)in;
layout(invocations=2)in;
layout(triangle_strip,max_vertices=MAX_VERTICES)out;

layout(std430, binding=0) readonly buffer _edges{
	float edges[]; };

layout(std430, binding=1) readonly buffer _edgeIdsToGenerate{
	uint edgesIdToGenerate[]; };

)."
+ edgeFunctions +
R".(
uniform mat4 mvp           = mat4(1)            ;
uniform vec4 lightPosition = vec4(100,100,100,1);

void main()
{
	const uint encodedEdge = edgesIdToGenerate[gl_PrimitiveIDIn];
	const uint edgeId = decodeEdgeFromEncoded(encodedEdge);
	const int mult = decodeEdgeMultiplicityFromId(encodedEdge);
	const uint absMultiplicity = abs(mult);

	vec3 edgeVertices[2];
	edgeVertices[0] = vec3(0);
	edgeVertices[1] = vec3(0);

	getEdge(edgeId, edgeVertices[0], edgeVertices[1]);
	
	const uint swapVertices = uint(mult>0);

	if(gl_InvocationID==0)
	{
		uint i=0;
		for(i=0; i<absMultiplicity; ++i)
		{
			gl_Position = mvp * vec4(edgeVertices[0^swapVertices], 1);
			EmitVertex();
			gl_Position = mvp * vec4(edgeVertices[1^swapVertices] - lightPosition.xyz, 0);
			EmitVertex();
			gl_Position = mvp * vec4(edgeVertices[0^swapVertices] - lightPosition.xyz, 0);
			EmitVertex();
			EndPrimitive();
		}
	}
	else
	{
		uint i=0;
		for(i=0; i<absMultiplicity; ++i)
		{
			gl_Position = mvp * vec4(edgeVertices[1^swapVertices] - lightPosition.xyz, 0);
			EmitVertex();
			gl_Position = mvp * vec4(edgeVertices[0^swapVertices], 1);
			EmitVertex();
			gl_Position = mvp * vec4(edgeVertices[1^swapVertices], 1);
			EmitVertex();
			EndPrimitive();
		}
	}
}).";


//-------------------POTENTIAL EDGES------------------

const std::string potentialSidesTES = R".(
#version 450 core
layout(quads)in;

layout(std430, binding=0) readonly buffer _edges{
	float edges[]; };

layout(std430, binding=1) readonly buffer _oppositeVertices{
	float oppositeVertices[];};

layout(std430, binding=2) readonly buffer _edgeIdsToTest{
	uint edgesIdToTest[]; };

)."
+ edgeFunctions + oppositeVertexFunctions + multiplicityFunctions + 
R".(
uniform mat4 mvp           = mat4(1)            ;
uniform vec4 lightPosition = vec4(100,100,100,1);

out flat uint multiplicity;

void main()
{
	const uint edgeID = edgesIdToTest[gl_PrimitiveID];
	const uint nofOpposite = getEdgeNofOppositeVertices(edgeID);
	const uint oppositeStartingIndex = getEdgeOppositeVerticesStartingIndex(edgeID);

	vec3 edgeVertices[2];
	edgeVertices[0] = vec3(0);
	edgeVertices[1] = vec3(0);
	getEdge(edgeID, edgeVertices[0], edgeVertices[1]);
	
	uint i = 0;
	int mult = 0;
	for(i=0; i<nofOpposite; ++i)
		mult += currentMultiplicity(edgeVertices[0], edgeVertices[1], getOppositeVertex(oppositeStartingIndex, i), lightPosition.xyz);
	
	multiplicity = abs(mult);
	if(mult==0)
		return;
	
	const uint swapVertices = uint(mult>0);

	vec4 outPos;
	outPos.xyz = edgeVertices[uint(gl_TessCoord.x<0.5f) ^ swapVertices]-lightPosition.xyz*float(gl_TessCoord.y<0.5f);
	outPos.w = float(gl_TessCoord.y>0.5f);

	gl_Position = mvp * outPos;
}).";

const std::string potentialSidesGS = R".(
layout(points)in;
layout(invocations=2)in;
layout(triangle_strip,max_vertices=MAX_VERTICES)out;

layout(std430, binding=0) readonly buffer _edges{
	float edges[]; };

layout(std430, binding=1) readonly buffer _oppositeVertices{
	float oppositeVertices[];};

layout(std430, binding=2) readonly buffer _edgeIdsToTest{
	uint edgesIdToTest[]; };

)."
+ edgeFunctions + oppositeVertexFunctions + multiplicityFunctions +
R".(
uniform mat4 mvp           = mat4(1)            ;
uniform vec4 lightPosition = vec4(100,100,100,1);

void main()
{
	const uint edgeID = edgesIdToTest[gl_PrimitiveIDIn];
	const uint nofOpposite = getEdgeNofOppositeVertices(edgeID);
	const uint oppositeStartingIndex = getEdgeOppositeVerticesStartingIndex(edgeID);

	vec3 edgeVertices[2];
	edgeVertices[0] = vec3(0);
	edgeVertices[1] = vec3(0);
	getEdge(edgeID, edgeVertices[0], edgeVertices[1]);
	
	uint oppositeIndex = 0;
	int mult = 0;
	for(oppositeIndex=0; oppositeIndex<nofOpposite; ++oppositeIndex)
		mult +=  currentMultiplicity(edgeVertices[0], edgeVertices[1], getOppositeVertex(oppositeStartingIndex, oppositeIndex), lightPosition.xyz);
	
	const uint swapVertices = uint(mult>0);
	const uint absMultiplicity = abs(mult);

	if(gl_InvocationID==0)
	{
		uint i=0;
		for(i=0; i<absMultiplicity; ++i)
		{
			gl_Position = mvp * vec4(edgeVertices[0^swapVertices], 1);
			EmitVertex();
			gl_Position = mvp * vec4(edgeVertices[1^swapVertices] - lightPosition.xyz, 0);
			EmitVertex();
			gl_Position = mvp * vec4(edgeVertices[0^swapVertices] - lightPosition.xyz, 0);
			EmitVertex();
			EndPrimitive();
		}
	}
	else
	{
		uint i=0;
		for(i=0; i<absMultiplicity; ++i)
		{
			gl_Position = mvp * vec4(edgeVertices[1^swapVertices] - lightPosition.xyz, 0);
			EmitVertex();
			gl_Position = mvp * vec4(edgeVertices[0^swapVertices], 1);
			EmitVertex();
			gl_Position = mvp * vec4(edgeVertices[1^swapVertices], 1);
			EmitVertex();
			EndPrimitive();
		}
	}
}).";


const std::string testAndGenerateSidesCS = R".(
#extension GL_ARB_shader_ballot : enable
#extension GL_ARB_gpu_shader_int64 : enable
#extension GL_AMD_gpu_shader_int64 : enable

layout(local_size_x=WORKGROUP_SIZE_X) in;

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

//TODO - previezt na UBO
layout(std430, binding=5) readonly buffer _nofEdgesToTest{
	uint nofEdgesToTest; };

)."
+ edgeFunctions + oppositeVertexFunctions + multiplicityFunctions + pushEdgeFunction +
R".(

uniform vec4 lightPosition;

//Just wildly dividing by 32
//Lazy to exactly speciffy
shared uint shm[WORKGROUP_SIZE_X/32];

void main()
{
	const uint gid = gl_GlobalInvocationID.x;
	if(gid>=nofEdgesToTest)
		return;
	
	const uint subgroupId = gl_LocalInvocationIndex/gl_SubGroupSizeARB;
	if(gl_SubGroupInvocationARB==0)
		shm[subgroupId]=0;

	const uint edgeID = edgesIdToTest[gid];
	vec3 edgeVertices[2];
	edgeVertices[0] = vec3(0);
	edgeVertices[1] = vec3(0);
	getEdge(edgeID, edgeVertices[0], edgeVertices[1]);

	const uint nofOpposite = getEdgeNofOppositeVertices(edgeID);
	const uint oppositeStartingIndex = getEdgeOppositeVerticesStartingIndex(edgeID);

	int multiplicity = 0;

	for(uint i=0; i<nofOpposite; ++i)
		multiplicity += currentMultiplicity(edgeVertices[0], edgeVertices[1], getOppositeVertex(oppositeStartingIndex, i), vec3(lightPosition));

	const uint swapVertices = uint(multiplicity>0);
	const uint absMultiplicity = abs(multiplicity);

	//Prefer local atomics
	const uint startingPosLocal = atomicAdd(shm[subgroupId], 2*absMultiplicity);
	uint startingPosGlobal = 0;
	if(gl_SubGroupInvocationARB==0)
		startingPosGlobal = atomicAdd(drawIndirect[0], shm[subgroupId]);
	startingPosGlobal = readInvocationARB(startingPosGlobal, 0);

	pushEdge(absMultiplicity, startingPosGlobal + startingPosLocal, edgeVertices[0^swapVertices], edgeVertices[1^swapVertices]);
}
).";

const std::string generateSidesCS = R".(
#extension GL_ARB_shader_ballot : enable
#extension GL_ARB_gpu_shader_int64 : enable
#extension GL_AMD_gpu_shader_int64 : enable
layout(local_size_x=WORKGROUP_SIZE_X) in;

layout(std430, binding=0) readonly buffer _edges{
	float edges[]; };

layout(std430, binding=1) readonly buffer _edgeIdsToGenerate{
	uint edgesIdToGenerate[]; };

layout(std430, binding=2) buffer _generatedSideEdges{
	vec4 sideEdges[]; };

layout(std430, binding=3) buffer _drawIndirectBuffer{
	uint drawIndirect[4]; };

layout(std430, binding=5) readonly buffer _nofEdgesToGenerate{
	uint nofEdgesToGenerate; };

)."
+ edgeFunctions + pushEdgeFunction + 
R".(

shared uint shm[WORKGROUP_SIZE_X/32];

void main()
{
	const uint gid = gl_GlobalInvocationID.x;
	if(gid>=nofEdgesToGenerate) return;
	
	const uint subgroupId = gl_LocalInvocationIndex/gl_SubGroupSizeARB;
	if(gl_SubGroupInvocationARB==0)
		shm[subgroupId]=0;

	const uint encodedEdge = edgesIdToGenerate[gid];
	const int multiplicity = decodeEdgeMultiplicityFromId(encodedEdge);
	const uint edgeID = decodeEdgeFromEncoded(encodedEdge);
	
	vec3 edgeVertices[2];
	edgeVertices[0] = vec3(0);
	edgeVertices[1] = vec3(0);
	getEdge(edgeID, edgeVertices[0], edgeVertices[1]);
	
	const uint swapVertices = uint(multiplicity>0);
	const uint absMultiplicity = abs(multiplicity);

	//Prefer local atomics
	const uint startingPosLocal = atomicAdd(shm[subgroupId], 2*absMultiplicity);
	uint startingPosGlobal = 0;
	if(gl_SubGroupInvocationARB==0)
		startingPosGlobal = atomicAdd(drawIndirect[0], shm[subgroupId]);
	startingPosGlobal = readInvocationARB(startingPosGlobal, 0);

	pushEdge(absMultiplicity, startingPosGlobal + startingPosLocal, edgeVertices[0^swapVertices], edgeVertices[1^swapVertices]);
}).";