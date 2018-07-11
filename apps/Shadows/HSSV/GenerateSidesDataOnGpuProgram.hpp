#pragma once
#include <string>
#include <iostream>
#include <sstream>

#include "Octree.hpp"
#include <memory>

const std::string traversalSupportFunctions = R".(

uint getNumNodesInPreviousLevels(int level)
{
	const int l = level - 1;

	if (l < 0 || l> int(treeDepth))
		return 0;

	return levelSizesInclusiveSum[l];
}

int getNodeIdInLevel(uint nodeID, uint level)
{
	return int(nodeID) - int(getNumNodesInPreviousLevels(int(level)));
}

int getNodeParent(unsigned int nodeID, uint nodeLevel)
{
	if (nodeID == 0)
		return -1;

	const int idInLevel = getNodeIdInLevel(nodeID, nodeLevel);
	const int parentRelativeID = idInLevel / 8;

	return parentRelativeID + int(getNumNodesInPreviousLevels(int(nodeLevel) - 1));
}
).";

//In iterative manner
//Not expecting to have a lot of buffers
const std::string genGetNodeFromBuffer(unsigned int numBuffers)
{
	std::stringstream str;

	str << "uint getNodeFromBuffer(uint nodeIndex, uint bufferId)\n";
	str << "{\n";

	for(unsigned int i = 0; i<numBuffers; ++i)
	{
		str << "\tif(bufferId==" << i << ") return edges" << i << "[nodeIndex];\n";
	}
	str << "\treturn 0;\n";
	str << "}\n\n";

	return str.str();
}

std::string genBuffer(unsigned int i)
{
	std::stringstream str;
	str << "layout(std430, binding = " << i << ") readonly buffer _edges" << i << "{uint edges" << i << "[]; };\n";
	return str.str();
}

std::string genFindBufferFunc()
{
	std::stringstream str;
	str << "uint getNodeBufferIndex(uint nodeId)\n{\n";
	str << "\tuint index = 0;\n";
	str << "\twhile(nodeId>edgeBuffersMapping[index]) ++index;\n";
	str << "\treturn index;\n}\n";

	return str.str();
}

std::string genMain(unsigned int numBuffers)
{
	std::stringstream str;

	str << "void main()\n{\n";
	str << "int currentNode = int(cellContainingLight);\n";
	str << "int currentLevel = int(treeDepth);\n";
	str << "while(currentLevel>=0)\n{\n";

	if(numBuffers==1)
	{
		//No need for buffer indexing when a single buffer is used
		str << "const uint startPotential = nofEdgesPrefixSum[2 * currentNode + 0];\n";		
		str << "const uint startSilhouette = nofEdgesPrefixSum[2 * currentNode + 1];\n";
		str << "const uint endSilhouette = nofEdgesPrefixSum[2 * currentNode + 2];\n";

		str << "const uint numPotential = startSilhouette - startPotential;\n";
		str << "const uint numSilhouette = endSilhouette - startSilhouette;\n";
		
		//Potential edges
		str << "const uvec2 participThreadsPot = unpackUint2x32(ballotARB(gl_GlobalInvocationID.x<numPotential));\n";
		str << "const uint numParticipatingPotential = bitCount(participThreadsPot.x) + bitCount(participThreadsPot.y);\n";

		str << "uint currentStartPotential = 0;\n";
		str << "if (gl_SubGroupInvocationARB == 0) currentStartPotential = atomicAdd(nofPotential[0], numParticipatingPotential);\n";
		str << "currentStartPotential = readFirstInvocationARB(currentStartPotential);\n";

		str << "if(gl_GlobalInvocationID.x<numPotential) potentialEdges[currentStartPotential + gl_SubGroupInvocationARB] = edges0[startPotential + gl_GlobalInvocationID.x];\n";
		
		//Silhouette edges
		str << "const uvec2 participThreadsSil = unpackUint2x32(ballotARB(gl_GlobalInvocationID.x<numSilhouette));\n";
		str << "const uint numParticipatingSil = bitCount(participThreadsSil.x) + bitCount(participThreadsSil.y);\n";

		str << "uint currentStartSilhouette = 0;\n";
		str << "if (gl_SubGroupInvocationARB == 0) currentStartSilhouette = atomicAdd(nofSilhouette[0], numParticipatingSil);\n";
		str << "currentStartSilhouette = readFirstInvocationARB(currentStartSilhouette);\n";

		str << "if(gl_GlobalInvocationID.x<numSilhouette) silhouetteEdges[currentStartSilhouette + gl_SubGroupInvocationARB] = edges0[startSilhouette + gl_GlobalInvocationID.x];\n";

		str << "currentNode = getNodeParent(currentNode, currentLevel--);\n";
	}
	else
	{
		str << "const uint bufferNum = getNodeBufferIndex(currentNode);\n";
		str << "const uint startPotential = nofEdgesPrefixSum[2 * currentNode + bufferNum + 0];\n";
		str << "const uint startSilhouette = nofEdgesPrefixSum[2 * currentNode + bufferNum + 1];\n";
		str << "const uint endSilhouette = nofEdgesPrefixSum[2 * currentNode + bufferNum + 2];\n";

		str << "const uint numPotential = startSilhouette - startPotential;\n";
		str << "const uint numSilhouette = endSilhouette - startSilhouette;\n";

		//Potential edges
		str << "const uvec2 participThreadsPot = unpackUint2x32(ballotARB(gl_GlobalInvocationID.x<numPotential));\n";
		str << "const uint numParticipatingPotential = bitCount(participThreadsPot.x) + bitCount(participThreadsPot.y);\n";

		str << "uint currentStartPotential = 0;\n";
		str << "if (gl_SubGroupInvocationARB == 0) currentStartPotential = atomicAdd(nofPotential[0], numParticipatingPotential);\n";
		str << "currentStartPotential = readFirstInvocationARB(currentStartPotential);\n";

		str << "if(gl_GlobalInvocationID.x<numPotential) potentialEdges[currentStartPotential + gl_SubGroupInvocationARB] = getNodeFromBuffer(startPotential + gl_GlobalInvocationID.x, bufferNum);\n";

		//Silhouette edges
		str << "const uvec2 participThreadsSil = unpackUint2x32(ballotARB(gl_GlobalInvocationID.x<numSilhouette));\n";
		str << "const uint numParticipatingSil = bitCount(participThreadsSil.x) + bitCount(participThreadsSil.y);\n";

		str << "uint currentStartSilhouette = 0;\n";
		str << "if (gl_SubGroupInvocationARB == 0) currentStartSilhouette = atomicAdd(nofSilhouette[0], numParticipatingSil);\n";
		str << "currentStartSilhouette = readFirstInvocationARB(currentStartSilhouette);\n";

		str << "if(gl_GlobalInvocationID.x<numSilhouette) silhouetteEdges[currentStartSilhouette + gl_SubGroupInvocationARB] = getNodeFromBuffer(startSilhouette + gl_GlobalInvocationID.x, bufferNum);\n";

		str << "currentNode = getNodeParent(currentNode, currentLevel--);\n";
	}

	str << "}\n"; //end while
	str << "}\n"; //end function

	return str.str();
}

std::string genTraversalComputeShader(const std::vector<uint32_t>& lastNodePerEdgeBuffer, std::shared_ptr<Octree> octree, unsigned int workgroupSize)
{
	const unsigned int numBuffers = lastNodePerEdgeBuffer.size();
	assert(numBuffers > 0);
	
	std::stringstream str;
	str << "#version 450 core\n";
	str << "#extension GL_ARB_shader_ballot : enable\n";
	str << "#extension GL_ARB_gpu_shader_int64 : enable\n";
	str << "#extension GL_AMD_gpu_shader_int64 : enable\n\n";
	str << "layout(local_size_x=" << workgroupSize << ") in;\n";

	for (unsigned int i = 0; i < numBuffers; ++i)
		str << genBuffer(i);

	str << "\n";

	unsigned int currentIndex = numBuffers;
	str << "layout(std430, binding = " << currentIndex++ << ") readonly buffer _nofEdgesPrefixSum{ uint nofEdgesPrefixSum[]; };\n";

	str << "layout(std430, binding = " << currentIndex++ << ") buffer _nofPotential{ uint nofPotential[]; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") buffer _nofSilhouette{ uint nofSilhouette[]; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") buffer _potential{ uint potentialEdges[]; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") buffer _silhouette{ uint silhouetteEdges[]; };\n\n";

	str << "uniform uint cellContainingLight;\n\n";

	str << "const uint treeDepth = " << octree->getDeepestLevel() << ";\n";

	
	str << "const uint levelSizesInclusiveSum[" << octree->getDeepestLevel() + 1 << "] = uint[" << octree->getDeepestLevel() + 1 << "](";
	const std::vector<unsigned int> ls = octree->getLevelSizeInclusiveSum();
	for (unsigned int i = 0; i < ls.size(); ++i)
	{
		str << ls[i];
		if (i != (ls.size() - 1))
			str << ", ";
	}
	str << ");\n";

	if (numBuffers > 1)
	{
		str << "const uint edgeBuffersMapping[" << numBuffers << "] = uint[" << numBuffers << "](";
		for (unsigned int i = 0; i < numBuffers; ++i)
		{
			str << lastNodePerEdgeBuffer[i];
			if (i != (numBuffers - 1))
				str << ", ";
		}
		str << ");\n";
	}

	str << traversalSupportFunctions;

	if (numBuffers > 1)
	{
		str << genFindBufferFunc();
		str << genGetNodeFromBuffer(numBuffers);
	}
	
	str << genMain(numBuffers);

	return str.str();
}