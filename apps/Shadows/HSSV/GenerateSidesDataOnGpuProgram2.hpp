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

std::string getCompressionIdWithinParentFunction(unsigned int compressionLevel)
{
	const std::string c1 = R".(
uint getCompressionIdWithinParent(uint nodeId, uint compressionParentId, uint compressionParentLevel)
{
	return nodeId - uint(getChildrenStartingId(compressionParentId, compressionParentLevel));
}
).";

	const std::string c2 = R".(
uint getCompressionIdWithinParent(uint nodeId, uint compressionParentId, uint compressionParentLevel)
{
	const uint depth = treeDepth - compressionParentLevel;
		if(depth!=COMPRESSION_LEVEL)
		return 0;
		int startingNode = compressionParentId;
	
	for(uint i = 0; i<depth; ++i)
		startingNode = getChildrenStartingId(startingNode, compressionParentLevel-i);
	
	return nodeId - uint(startingNode);
}
).";

	if (compressionLevel == 1)
		return c1;
	
	return c2;
}

std::string isCompressionIdPresentFunction(unsigned int compressionLevel)
{
	//Assumption is that id is 8-bit
	const std::string c1 = R".(
bool isCompressionIdPresent(uint nodeCompressionId, const uint startingIndexToCompressionId, uint currentLevel)
{
	return (nodeInfo[startingIndexToCompressionId + 0] & (1 << nodeCompressionId)) != 0;
}
).";

	//id is 64 bit and more
	const std::string c2 = R".(
bool isCompressionIdPresent(const uint nodeCompressionId, const uint startingIndexToCompressionId, uint currentLevel)
{
	if(currentLevel == (treeDepth-COMPRESSION_LEVEL))
	{
		const uint index = nodeCompressionId / 32;
		const uint compressionIndex = nodeCompressionId % 32;
	
		return (nodeInfo[startingIndexToCompressionId + index] & (1 << compressionIndex))!=0;
	}
	else
		return true;
}
).";

	if (compressionLevel == 1)
		return c1;

	return c2;
}

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

std::string genMain2Compress(unsigned int numBuffers)
{
	std::stringstream str;

	str << "void main()\n{\n";
	str << "	int currentNode = int(cellContainingLight);\n";
	str << "	int currentLevel = int(treeDepth);\n";
	str << "\n";
	str << "	int myNode = -1;\n";
	str << "	bool getPotential = true;\n";
	str << "	uint myStartingIndex = 0;\n";
	
	if(numBuffers>1)
		str << "	uint bufferIndex = 0;\n";

	str << "\n";
	str << "	while (currentLevel >= 0)\n";
	str << "	{\n";
	if (numBuffers>1)
		str << "		currentBufferIndex = getNodeBufferIndex(currentNode);\n";
	str << "\n";
	str << "		//Potential edges\n";
	str << "		const unsigned int startingIndexToNodeInfo = nodeInfoIndexing[currentNode];\n";
	str << "		const unsigned int nofSubBuffersPot = nodeInfo[startingIndexToNodeInfo + 0];\n";
	str << "\n";
	str << "		uint currentNofEdges = 0;\n";
	str << "\n";
	str << "		for (unsigned int subBufferIndex = 0; subBufferIndex<nofSubBuffersPot; ++subBufferIndex)\n";
	str << "		{\n";
	str << "			const uint compressionId = getCompressionIdWithinParent(cellContainingLight, currentNode, currentLevel);\n";
	str << "			if (!isCompressionIdPresent(compressionId, startingIndexToNodeInfo + NOF_UINTS_PER_NOF_SUBBUFFERS + NOF_UINTS_PER_NODE_INFO*subBufferIndex, currentLevel))\n";
	str << "			continue;\n";
	str << "\n";
	str << "			const uint bufferStart = nodeInfo[startingIndexToNodeInfo + 2 + NOF_UINTS_PER_NODE_INFO*subBufferIndex + NOF_UINTS_PER_COMPRESSION_ID];\n";
	str << "			const uint startPotentialCurrent = nofEdgesPrefixSum[bufferStart];\n";
	str << "			const uint endPotentialCurrent = nofEdgesPrefixSum[bufferStart + 1];\n";
	str << "			const uint numPotential = endPotentialCurrent - startPotentialCurrent;\n";
	str << "			currentNofEdges += numPotential;\n";
	str << "\n";
	str << "			if (currentNofEdges>gl_GlobalInvocationID.x)\n";
	str << "			{\n";
	str << "				myNode = int(currentNode);\n";
	str << "				getPotential = true;\n";
	str << "				myStartingIndex = startPotentialCurrent + (gl_GlobalInvocationID.x - currentNofEdges);\n";
	str << "				break;\n";
	str << "			}\n";
	str << "		}\n";
	str << "		//Silhouette edges\n";
	str << "		const unsigned int nofSubBuffersSil = nodeInfo[startingIndexToNodeInfo + 1];\n";
	str << "\n";
	str << "		if (myNode<0) for (unsigned int subBufferIndex = 0; subBufferIndex<nofSubBuffersSil; ++subBufferIndex)\n";
	str << "		{\n";
	str << "			const uint compressionId = getCompressionIdWithinParent(cellContainingLight, currentNode, currentLevel);\n";
	str << "			if (!isCompressionIdPresent(compressionId, startingIndexToNodeInfo + NOF_UINTS_PER_NOF_SUBBUFFERS + NOF_UINTS_PER_NODE_INFO*(subBufferIndex+nofSubBuffersPot), currentLevel))\n";
	str << "				continue;\n";
	str << "\n";
	str << "			const uint bufferStart = nodeInfo[startingIndexToNodeInfo + NOF_UINTS_PER_NOF_SUBBUFFERS + NOF_UINTS_PER_NODE_INFO*(subBufferIndex+nofSubBuffersPot) + NOF_UINTS_PER_COMPRESSION_ID];\n";
	str << "			const uint startSilhouetteCurrent = nofEdgesPrefixSum[bufferStart];\n";
	str << "			const uint endSilhouetteCurrent = nofEdgesPrefixSum[bufferStart + 1];\n";
	str << "			const uint numSilhouette = endSilhouetteCurrent - startSilhouetteCurrent;\n";
	str << "			currentNofEdges += numSilhouette;\n";
	str << "\n";
	str << "			if (currentNofEdges>gl_GlobalInvocationID.x)\n";
	str << "			{\n";
	str << "				myNode = int(currentNode);\n";
	str << "				getPotential = false;\n";
	str << "				myStartingIndex = startSilhouetteCurrent + (gl_GlobalInvocationID.x - currentNofEdges);\n";
	str << "				break;\n";
	str << "			}\n";
	str << "		}\n";
	str << "\n";
	str << "		if (myNode >= 0)\n";
	str << "		{\n";
	str << "			const uint64_t maskPotential = ballotARB(getPotential);\n";
	str << "			if (getPotential)\n";
	str << "			{\n";
	str << "				const uvec2 maskPotentialUnpack = unpackUint2x32(maskPotential);\n";
	str << "				const uint numPotential = bitCount(maskPotentialUnpack.x) + bitCount(maskPotentialUnpack.y);\n";
	str << "				const int firstSet = getLSB64(maskPotential);\n";
	str << "				const uint64_t andMask = (uint64_t(1) << gl_SubGroupInvocationARB) - uint64_t(1);\n";
	str << "				const uvec2 maskIdxPacked = unpackUint2x32(maskPotential & andMask);\n";
	str << "				const uint idxPotentialInWarp = bitCount(maskIdxPacked.x) + bitCount(maskIdxPacked.y);\n";
	str << "				unsigned int storeIndexPot;\n";
	str << "				if (gl_SubGroupInvocationARB == firstSet) storeIndexPot = atomicAdd(nofPotential, numPotential);\n";
	str << "				storeIndexPot = readInvocationARB(storeIndexPot, firstSet) + idxPotentialInWarp;\n";
	str << "\n";

	if (numBuffers > 1)
		str << "				potentialEdges[storeIndexPot] = getNodeFromBuffer(myStartingIndex, currentBufferIndex);\n";
	else
		str << "				potentialEdges[storeIndexPot] = edges0[myStartingIndex];\n";

	str << "				break;\n";
	str << "			}\n";
	str << "\n";
	str << "			const uint64_t maskSilhouette = ballotARB(!getPotential);\n";
	str << "			if (!getPotential)\n";
	str << "			{\n";
	str << "				const uvec2 maskSilhouetteUnpack = unpackUint2x32(maskSilhouette);\n";
	str << "				const uint numSilhouette = bitCount(maskSilhouetteUnpack.x) + bitCount(maskSilhouetteUnpack.y);\n";
	str << "				const int firstSet = getLSB64(maskSilhouette);\n";
	str << "				const uint64_t andMask = (uint64_t(1) << gl_SubGroupInvocationARB) - uint64_t(1);\n";
	str << "				const uvec2 maskIdxPacked = unpackUint2x32(maskSilhouette & andMask);\n";
	str << "				const uint idxSilhouetteInWarp = bitCount(maskIdxPacked.x) + bitCount(maskIdxPacked.y);\n";
	str << "				unsigned int storeIndexSil;\n";
	str << "				if (gl_SubGroupInvocationARB == firstSet) storeIndexSil = atomicAdd(nofSilhouette, numSilhouette);\n";
	str << "				storeIndexSil = readInvocationARB(storeIndexSil, firstSet) + idxSilhouetteInWarp;\n";
	str << "\n";

	if (numBuffers > 1)
		str << "				silhouetteEdges[storeIndexSil] = getNodeFromBuffer(myStartingIndex, currentBufferIndex);\n";
	else
		str << "				silhouetteEdges[storeIndexSil] = edges0[myStartingIndex];\n";

	str << "				break;\n";
	str << "			}\n";
	str << "		}\n";
	str << "	currentNode = getNodeParent(currentNode, currentLevel--);\n";
	str << "	}\n";
	str << "}\n";


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

std::string genTraversalComputeShader2Compress(const std::vector<uint32_t>& lastNodePerEdgeBuffer, std::shared_ptr<Octree> octree, unsigned int workgroupSize)
{
	const unsigned int compressionLevel = octree->getCompressionLevel();
	if (compressionLevel == 0)
		return genTraversalComputeShader2(lastNodePerEdgeBuffer, octree, workgroupSize);

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
	str << "layout(std430, binding = " << currentIndex++ << ") buffer _silhouette{ uint silhouetteEdges[]; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") buffer _nodeInfoBuffer {uint nodeInfo[]; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") buffer _nodeInfoBufferIndexing {uint nodeInfoIndexing[]; };\n";

	str << "uniform uint cellContainingLight;\n\n";

	str << "const uint treeDepth = " << octree->getDeepestLevel() << ";\n";
	str << "#define COMPRESSION_LEVEL " << compressionLevel << "\n";
	const unsigned int tmpNofUints = ipow(OCTREE_NUM_CHILDREN, compressionLevel) / 32;
	const unsigned int nofUintsPerCompressionId = tmpNofUints ? tmpNofUints : 1;
	const unsigned int nofUintsPerNodeInfo = nofUintsPerCompressionId + 1;
	str << "#define NOF_UINTS_PER_COMPRESSION_ID " << nofUintsPerCompressionId << "\n";
	str << "#define NOF_UINTS_PER_NODE_INFO " << nofUintsPerNodeInfo << "\n";
	str << "#define NOF_UINTS_PER_NOF_SUBBUFFERS 2\n\n";

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

	str << getCompressionIdWithinParentFunction(octree->getCompressionLevel());
	str << isCompressionIdPresentFunction(octree->getCompressionLevel());

	str << "\n\n";

	str << genMain2Compress(numBuffers);

	return str.str();
}