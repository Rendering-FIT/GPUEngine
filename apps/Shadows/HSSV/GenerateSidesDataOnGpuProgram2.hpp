#pragma once
#include "GenerateSidesDataOnGpuProgram.hpp"

//Nie je uplne dokonala, neriesi ze "num" moze byt nula
const std::string findLsbFunction = R".(
int getLSB64(uint64_t num)
{
	const uvec2 v = unpackUint2x32(num);
	const int lowPos = findLSB(v.x);
	
	return (lowPos<0) ? 32 + findLSB(v.y) : lowPos;
}

).";

std::string genMain2(unsigned int numBuffers)
{
	std::stringstream str;

	str << "void main()\n{\n";
	str << "int currentNode = int(cellContainingLight);\n";
	str << "int currentLevel = int(treeDepth);\n";

	str << "uint prefixSum = 0;\n\n";
	str << "int myNode = -1;\n";
	str << "bool getPotential = true\n;";
	str << "uint myStartingIndex = 0;\n";

	if (numBuffers > 1)
		str << "uint bufferIndex = 0;\n";

	str << "while(currentLevel>=0)\n{\n";
	if (numBuffers > 1)
	{
		str << "bufferIndex = getNodeBufferIndex(currentNode);\n";
		str << "const uint startPotential = nofEdgesPrefixSum[2 * currentNode + bufferIndex + 0];\n";
		str << "const uint startSilhouette = nofEdgesPrefixSum[2 * currentNode + bufferIndex + 1];\n";
		str << "const uint endSilhouette = nofEdgesPrefixSum[2 * currentNode + bufferIndex + 2];\n";
	}
	else
	{
		str << "const uint startPotential = nofEdgesPrefixSum[2 * currentNode + 0];\n";
		str << "const uint startSilhouette = nofEdgesPrefixSum[2 * currentNode + 1];\n";
		str << "const uint endSilhouette = nofEdgesPrefixSum[2 * currentNode + 2];\n";
	}

	str << "const uint numPotential = startSilhouette - startPotential;\n";
	str << "const uint numSilhouette = endSilhouette - startSilhouette;\n";

	str << "if((prefixSum + numPotential) > gl_GlobalInvocationID.x) { myNode = int(currentNode); getPotential = true; myStartingIndex = startPotential + (gl_GlobalInvocationID.x - prefixSum); break;}\n";
	str << "prefixSum += numPotential;\n";
	str << "if((prefixSum + numSilhouette) > gl_GlobalInvocationID.x) { myNode = int(currentNode); getPotential = false; myStartingIndex = startSilhouette + (gl_GlobalInvocationID.x - prefixSum); break;}\n";
	str << "prefixSum += numSilhouette;\n";
	str << "currentNode = getNodeParent(currentNode, currentLevel--);\n";
	str << "}\n\n";

	str << "if(myNode<0) return;\n";

	str << "const uint64_t maskPotential = ballotARB(getPotential);\n";
	str << "if(getPotential)\n{\n";
	str << "\tconst uvec2 maskPotentialUnpack = unpackUint2x32(maskPotential);\n";
	str << "\tconst uint numPotential = bitCount(maskPotentialUnpack.x) + bitCount(maskPotentialUnpack.y);\n";
	str << "\tconst int firstSet = getLSB64(maskPotential);\n";
	str << "\tconst uint64_t andMask = (uint64_t(1)<<gl_SubGroupInvocationARB)-uint64_t(1);\n";
	str << "\tconst uvec2 maskIdxPacked = unpackUint2x32(maskPotential & andMask);\n";
	str << "\tconst uint idxPotentialInWarp = bitCount(maskIdxPacked.x) + bitCount(maskIdxPacked.y);\n";
	str << "\tunsigned int storeIndexPot;\n";
	str << "\tif(gl_SubGroupInvocationARB==firstSet) storeIndexPot = atomicAdd(nofPotential, numPotential);\n";
	str << "\tstoreIndexPot = readInvocationARB(storeIndexPot, firstSet) + idxPotentialInWarp;\n";
	if (numBuffers > 1)
		str << "\tpotentialEdges[storeIndexPot] = getNodeFromBuffer(myStartingIndex, bufferIndex);\n";
	else
		str << "\tpotentialEdges[storeIndexPot] = edges0[myStartingIndex];\n";
	str << "}\n\n";

	str << "const uint64_t maskSilhouette = ballotARB(!getPotential);\n";
	str << "if(!getPotential)\n{\n";
	str << "\tconst uvec2 maskSilhouetteUnpack = unpackUint2x32(maskSilhouette);\n";
	str << "\tconst uint numSilhouette = bitCount(maskSilhouetteUnpack.x) + bitCount(maskSilhouetteUnpack.y);\n";
	str << "\tconst int firstSet = getLSB64(maskSilhouette);\n";
	str << "\tconst uint64_t andMask = (uint64_t(1)<<gl_SubGroupInvocationARB)-uint64_t(1);\n";
	str << "\tconst uvec2 maskIdxPacked = unpackUint2x32(maskSilhouette & andMask);\n";
	str << "\tconst uint idxSilhouetteInWarp = bitCount(maskIdxPacked.x) + bitCount(maskIdxPacked.y);\n";
	str << "\tunsigned int storeIndexSil;\n";
	str << "\tif(gl_SubGroupInvocationARB==firstSet) storeIndexSil = atomicAdd(nofSilhouette, numSilhouette);\n";
	str << "\tstoreIndexSil = readInvocationARB(storeIndexSil, firstSet) + idxSilhouetteInWarp;\n";
	if (numBuffers > 1)
		str << "\tsilhouetteEdges[storeIndexSil] = getNodeFromBuffer(myStartingIndex, bufferIndex);\n";

	else
		str << "\tsilhouetteEdges[storeIndexSil] = edges0[myStartingIndex];\n";

	str << "}\n\n";

	str << "}";

	return str.str();
}

std::string genTraversalComputeShader2(const std::vector<uint32_t>& lastNodePerEdgeBuffer, std::shared_ptr<Octree> octree, unsigned int workgroupSize)
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

	str << "layout(std430, binding = " << currentIndex++ << ") buffer _nofPotential{ uint nofPotential; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") buffer _nofSilhouette{ uint nofSilhouette; };\n";
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

	str << findLsbFunction;

	if (numBuffers > 1)
	{
		str << genFindBufferFunc();
		str << genGetNodeFromBuffer(numBuffers);
	}
	
	str << genMain2(numBuffers);

	return str.str();
}