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
		uint startingNode = compressionParentId;
	
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
	return (currentLevel!=(treeDepth-COMPRESSION_LEVEL)) || ((nodeInfo[startingIndexToCompressionId + 0] & (1 << nodeCompressionId)) != 0);
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

std::string genCompressGlobals(unsigned int nofBuffers)
{
	std::string str(R".(
//Globals
int myNode = -1;
bool getPotential = true;
uint myStartingIndex = 0;
uint currentNofEdges = 0;
int currentNode = int(cellContainingLight);
int currentLevel = int(treeDepth);
).");

	if (nofBuffers > 1)
		return str + "uint bufferIndex = 0;\n";
	else
		return str;
}

std::string genProcessAllSubbuffersInBlock()
{
	return std::string(R".(
void processAllSubbuffersInBlock(
	const uint nofSubBuffers, 
	const uint startingIndexToNodeInfo, 
	const uint nofSubbuffersInPotentialSubblock,
	const bool isPotential)
{
	for (uint subBufferIndex = 0; subBufferIndex<nofSubBuffers; ++subBufferIndex)
	{
		const uint compressionId = getCompressionIdWithinParent(cellContainingLight, currentNode, currentLevel);
		
		if (isCompressionIdPresent(compressionId, startingIndexToNodeInfo + NOF_UINTS_PER_NOF_SUBBUFFERS + NOF_UINTS_PER_SUBBUFFER_INFO*(subBufferIndex+nofSubbuffersInPotentialSubblock), currentLevel))
		{
			const uint bufferStart = nodeInfo[startingIndexToNodeInfo + NOF_UINTS_PER_NOF_SUBBUFFERS + NOF_UINTS_PER_SUBBUFFER_INFO*(subBufferIndex+nofSubbuffersInPotentialSubblock) + NOF_UINTS_PER_COMPRESSION_ID];
			const uint startCurrent = nofEdgesPrefixSum[bufferStart];
			const uint endCurrent = nofEdgesPrefixSum[bufferStart + 1];
			const uint numEdges = endCurrent - startCurrent;
			
			if (gl_GlobalInvocationID.x < (currentNofEdges+numEdges))
			{
				myNode = int(currentNode);
				getPotential = isPotential; //bool(nofSubbuffersInPotentialSubblock);
				myStartingIndex = startCurrent + (gl_GlobalInvocationID.x - currentNofEdges);
				break;
			}
			
			currentNofEdges += numEdges;
		}
	}
}
)."
);
}

std::string genStoreEdge(unsigned int nofBuffers)
{
	std::stringstream str;

	str << "void storeEdge(\n";
	str << "	uint64_t voteMask,\n";
	str << "	bool storePotential)\n";
	str << "{\n";
	str << "	const uvec2 maskUnpack = unpackUint2x32(voteMask);\n";
	str << "	const uint numEdges = bitCount(maskUnpack.x) + bitCount(maskUnpack.y);\n";
	str << "	const int firstSet = getLSB64(voteMask);\n";
	str << "	const uint64_t andMask = (uint64_t(1) << gl_SubGroupInvocationARB) - uint64_t(1);\n";
	str << "	const uvec2 maskIdxPacked = unpackUint2x32(voteMask & andMask);\n";
	str << "	const uint idxInWarp = bitCount(maskIdxPacked.x) + bitCount(maskIdxPacked.y);\n";
	str << "	unsigned int storeIndex;\n";
	str << "\n";
	str << "	if (gl_SubGroupInvocationARB == firstSet)\n";
	str << "	{\n";
	str << "		if (storePotential)\n";
	str << "			storeIndex = atomicAdd(nofPotential, numEdges);\n";
	str << "\n";
	str << "		if (!storePotential)\n";
	str << "			storeIndex = atomicAdd(nofSilhouette, numEdges);\n";
	str << "	}\n";
	str << "	storeIndex = readInvocationARB(storeIndex, firstSet) + idxInWarp;\n";
	str << "\n";
	str << "	if (storePotential)\n";
	if (nofBuffers > 1)
		str << "		potentialEdges[storeIndex] = getNodeFromBuffer(myStartingIndex, bufferIndex);\n";
	else
		str << "		potentialEdges[storeIndex] = edges0[myStartingIndex];\n";
	str << "	else\n";
	if (nofBuffers > 1)
		str << "		silhouetteEdges[storeIndex] = getNodeFromBuffer(myStartingIndex, bufferIndex);\n";
	else
		str << "		silhouetteEdges[storeIndex] = edges0[myStartingIndex];\n";
	str << "}\n";

	return str.str();
}

std::string genPrologue(unsigned int workgroupSize)
{
	std::stringstream str;
	str << "#version 450 core\n";
	str << "#extension GL_ARB_shader_ballot : enable\n";
	str << "#extension GL_ARB_gpu_shader_int64 : enable\n";
	str << "#extension GL_AMD_gpu_shader_int64 : enable\n\n";
	str << "layout(local_size_x=" << workgroupSize << ") in;\n\n";

	return str.str();
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

	str << "void main()\n";
	str << "{\n";
	str << "	while (currentLevel >= 0 && myNode<0)\n";
	str << "	{\n";
	str << "		//Potential edges\n";
	if (numBuffers>1)
		str << "bufferIndex = getNodeBufferIndex(currentNode);\n";
	str << "		const uint startingIndexToNodeInfo = nodeInfoIndexing[currentNode];\n";
	str << "		const uint nofSubBuffersPot = nodeInfo[startingIndexToNodeInfo + 0];\n";
	str << "\n";
	str << "		processAllSubbuffersInBlock(nofSubBuffersPot, startingIndexToNodeInfo, 0, true);\n";
	str << "		//Silhouette edges\n";
	str << "		const uint nofSubBuffersSil = nodeInfo[startingIndexToNodeInfo + 1];\n";
	str << "\n";
	str << "		if (myNode<0)\n";
	str << "		{\n";
	str << "			processAllSubbuffersInBlock(nofSubBuffersSil, startingIndexToNodeInfo, nofSubBuffersPot, false);\n";
	str << "\n";
	str << "			if (myNode<0)\n";
	str << "				currentNode = getNodeParent(currentNode, currentLevel--);\n";
	str << "		}\n";
	str << "	}\n";
	str << "	if (myNode < 0) return;\n";
	str << "\n";
	str << "	//Store edges\n";
	str << "	const uint64_t maskPotential = ballotARB(getPotential);\n";
	str << "	if (getPotential)\n";
	str << "		storeEdge(maskPotential, true);\n";
	str << "\n";
	str << "	const uint64_t maskSilhouette = ballotARB(!getPotential);\n";
	str << "	if (!getPotential)\n";
	str << "		storeEdge(maskSilhouette, false);\n";
	str << "}\n";
	return str.str();
}

std::string genTraversalComputeShader2(const std::vector<uint32_t>& lastNodePerEdgeBuffer, std::shared_ptr<Octree> octree, unsigned int workgroupSize)
{
	const unsigned int numBuffers = lastNodePerEdgeBuffer.size();
	assert(numBuffers > 0);

	std::stringstream str;

	str << genPrologue(workgroupSize);

	for (unsigned int i = 0; i < numBuffers; ++i)
		str << genBuffer(i);

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

	str << genPrologue(workgroupSize);

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
	str << "#define NOF_UINTS_PER_SUBBUFFER_INFO " << nofUintsPerNodeInfo << "\n";
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

	str << genCompressGlobals(numBuffers);
	str << genProcessAllSubbuffersInBlock();
	str << genStoreEdge(numBuffers);

	str << genMain2Compress(numBuffers);

	return str.str();
}

std::string genGetSubBufferId()
{
	const unsigned int tmp = BitmaskTypeSizeBits / 32;
	const unsigned int nofUints = tmp ? tmp : 1;

	std::stringstream str;

	str << "uint[NOF_UINTS_PER_COMPRESSION_ID] getBufferId(uint subBufferIndex)\n";
	str << "{\n";
	str << "	uint retval[NOF_UINTS_PER_COMPRESSION_ID];\n";

	for (unsigned int i = 0; i < nofUints; ++i)
	{
		str << "	retval[" << i << "] = nodeInfo[shm_startingIndexToNodeInfo + NOF_UINTS_PER_NOF_SUBBUFFERS + NOF_UINTS_PER_SUBBUFFER_INFO*(subBufferIndex) + " << i << "];\n";
	}

	str << "	return retval;\n";
	str << "}\n\n";

	return str.str();
}

std::string genStoreBufferID(unsigned int nofBuffers)
{
	std::stringstream str;

	str << "void storeBufferInfo(\n";
	str << "	uint64_t voteMask, \n";
	str << "	bool storePotential, \n";
	str << "    unsigned int startingBufferIndex, \n";
	if (nofBuffers>1)
		str << "	unsigned int bufferIndex,\n";
	str << "    unsigned int bufferSize)\n";
	str << "{\n";
	str << "	const uvec2 maskUnpack = unpackUint2x32(voteMask);\n";
	str << "	const uint numBuffers = bitCount(maskUnpack.x) + bitCount(maskUnpack.y);\n";
	str << "	const int firstSet = getLSB64(voteMask);\n";
	str << "	const uint64_t andMask = (uint64_t(1) << gl_SubGroupInvocationARB) - uint64_t(1);\n";
	str << "	const uvec2 maskIdxPacked = unpackUint2x32(voteMask & andMask);\n";
	str << "	const uint idxInWarp = bitCount(maskIdxPacked.x) + bitCount(maskIdxPacked.y);\n";
	str << "	unsigned int storeIndex;\n";
	str << "	\n";
	str << "	if (gl_SubGroupInvocationARB == firstSet)\n";
	str << "	{\n";
	str << "		if (storePotential)\n";
	str << "		{\n";
	str << "			storeIndex = atomicAdd(nofPotSilBuffers[0], numBuffers); \n";
	str << "		}\n";
	str << "	\n";
	str << "		if (!storePotential)\n";
	str << "		{\n";
	str << "			storeIndex = atomicAdd(nofPotSilBuffers[1], numBuffers);\n";
	str << "		}\n";
	str << "	}\n";
	str << "	\n";
	str << "	storeIndex = NOF_UINTS_BUFFER_INFO*(readInvocationARB(storeIndex, firstSet) + idxInWarp);\n";
	str << "	\n";
	str << "	if (storePotential)\n";
	str << "	{\n";
	str << "		potentialBuffers[storeIndex + 0] = bufferSize;\n";
	str << "		potentialBuffers[storeIndex + 1] = startingBufferIndex;\n";
	if(nofBuffers>1)
		str << "		potentialBuffers[storeIndex + 2] = bufferIndex;\n";
	str << "		atomicAdd(nofPotEdges, bufferSize);\n";
    str << "	}\n";
	str << "	else\n";
    str << "	{\n";
	str << "		silhouetteBuffers[storeIndex + 0] = bufferSize;\n";
	str << "		silhouetteBuffers[storeIndex + 1] = startingBufferIndex;\n";
	if (nofBuffers>1)
		str << "		silhouetteBuffers[storeIndex + 2] = bufferIndex;\n";
	str << "		atomicAdd(nofSilEdges, bufferSize);\n";
    str << "	}\n";
	str << "}\n";

	return str.str();
}

std::string genBufferPreprocessShader(const std::vector<uint32_t>& lastNodePerEdgeBuffer, std::shared_ptr<Octree> octree, unsigned int workgroupSize)
{
	const unsigned int numBuffers = lastNodePerEdgeBuffer.size();
	const unsigned int compressionLevel = octree->getCompressionLevel();

	std::stringstream str;

	str << genPrologue(workgroupSize);

	str << "\n";

	unsigned int currentIndex = 0;

	str << "layout(std430, binding = " << currentIndex++ << ") readonly buffer _nofEdgesPrefixSum{ uint nofEdgesPrefixSum[]; };\n";

	str << "layout(std430, binding = " << currentIndex++ << ") buffer _potential{ uint potentialBuffers[]; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") buffer _silhouette{ uint silhouetteBuffers[]; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") buffer _nofPotSilBuffers{ uint nofPotSilBuffers[2]; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") buffer _nofPotEdges{ uint nofPotEdges; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") buffer _nofSilEdges{ uint nofSilEdges; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") readonly buffer _nodeInfoBuffer {uint nodeInfo[]; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") readonly buffer _nodeInfoBufferIndexing {uint nodeInfoIndexing[]; };\n";

	str << "uniform uint cellContainingLight;\n\n";

	str << "const uint treeDepth = " << octree->getDeepestLevel() << ";\n";
	str << "#define COMPRESSION_LEVEL " << compressionLevel << "\n";
	const unsigned int tmpNofUints = ipow(OCTREE_NUM_CHILDREN, compressionLevel) / 32;
	const unsigned int nofUintsPerCompressionId = tmpNofUints ? tmpNofUints : 1;
	const unsigned int nofUintsPerNodeInfo = nofUintsPerCompressionId + 1;
	str << "#define NOF_UINTS_PER_COMPRESSION_ID " << nofUintsPerCompressionId << "\n";
	str << "#define NOF_UINTS_PER_SUBBUFFER_INFO " << nofUintsPerNodeInfo << "\n";
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

	if (numBuffers > 1)
	{
		str << genFindBufferFunc();
	}

	const unsigned int nofUintsPerSubbufferInfo = (numBuffers > 1) ? 4 : 2;
	str << "#define NOF_UINTS_BUFFER_INFO " << nofUintsPerSubbufferInfo << "\n";

	str << traversalSupportFunctions;

	str << findLsbFunction;

	str << genStoreBufferID(numBuffers);

	str << getCompressionIdWithinParentFunction(octree->getCompressionLevel());
	str << isCompressionIdPresentFunction(octree->getCompressionLevel());

	//Shared memory
	str << "shared uint shm_nofPotSilBuffers[2];\n";
	str << "shared uint shm_startingIndexToNodeInfo;\n\n";
	
	str << genGetSubBufferId();

	//main
str << "void main()\n";
str << "{\n";
str << "	int currentNode = int(cellContainingLight);\n";
str << "	for(int currentLevel = int(treeDepth); currentLevel >=0; --currentLevel)\n";
str << "	{\n";
str << "		//First in warp - get info\n";
str << "		if(gl_LocalInvocationIndex==0)\n";
str << "		{\n";
str << "			shm_startingIndexToNodeInfo = nodeInfoIndexing[currentNode];\n";
str << "			shm_nofPotSilBuffers[0] = nodeInfo[shm_startingIndexToNodeInfo + 0];\n";
str << "			shm_nofPotSilBuffers[1] = nodeInfo[shm_startingIndexToNodeInfo + 1];\n";
str << "		}\n";
str << "\n";
str << "		barrier();\n";
str << "\n";
str << "		//Check if pot/sil\n";
str << "		const uint nofPot = shm_nofPotSilBuffers[0];\n";
str << "		const uint nofSil = shm_nofPotSilBuffers[1];\n";
str << "		const bool isActive = gl_GlobalInvocationID.x < (nofPot + nofSil);\n";
str << "		const bool isPotential = gl_GlobalInvocationID.x < nofPot;\n";
str << "\n";
str << "		if(isActive)\n";
str << "		{\n";
str << "			const uint compressionId = getCompressionIdWithinParent(cellContainingLight, currentNode, currentLevel);\n";
str << "\n";
str << "			if (isCompressionIdPresent(compressionId, shm_startingIndexToNodeInfo + NOF_UINTS_PER_NOF_SUBBUFFERS + NOF_UINTS_PER_SUBBUFFER_INFO*(gl_GlobalInvocationID.x), currentLevel))\n";
str << "			{\n";
str << "				uint subbufferId[NOF_UINTS_PER_COMPRESSION_ID] = getBufferId(gl_GlobalInvocationID.x);\n";
if (numBuffers > 1)
	str << "				const uint bufferNum = getNodeBufferIndex(currentNode);\n";
str << "				const uint bufferStart = nodeInfo[shm_startingIndexToNodeInfo + NOF_UINTS_PER_NOF_SUBBUFFERS + NOF_UINTS_PER_SUBBUFFER_INFO*(gl_GlobalInvocationID.x) + NOF_UINTS_PER_COMPRESSION_ID];\n";
str << "				const uint startCurrent = nofEdgesPrefixSum[bufferStart];\n";
str << "				const uint endCurrent = nofEdgesPrefixSum[bufferStart + 1];\n";
str << "				const uint numEdges = endCurrent - startCurrent;\n";
str << "\n";
str << "				//Store\n";
str << "				const uint64_t votePotential = ballotARB(isPotential);\n";
str << "				const uint64_t voteSilhouette = ballotARB(!isPotential);\n";
str << "				const uint64_t voteRes = isPotential ? votePotential : voteSilhouette;\n";
if (numBuffers > 1)
	str << "				storeBufferInfo(voteRes, isPotential, startCurrent, bufferNum, numEdges);\n";
else
	str << "				storeBufferInfo(voteRes, isPotential, startCurrent, numEdges);\n";
str << "			}\n";
str << "		}\n";
str << "		currentNode = getNodeParent(currentNode, currentLevel);\n";
str << "		barrier();\n";
str << "	}\n";
str << "}\n";

	return str.str();
}

std::string genCopyShader(const std::vector<uint32_t>& lastNodePerEdgeBuffer, std::shared_ptr<Octree> octree, unsigned int workgroupSize)
{
	std::stringstream str;
	const unsigned int numBuffers = lastNodePerEdgeBuffer.size();
	str << genPrologue(workgroupSize);

	for (unsigned int i = 0; i < numBuffers; ++i)
		str << genBuffer(i);

	str << "\n";

	unsigned int currentIndex = numBuffers;

	const unsigned int nofUintsPerSubbufferInfo = (numBuffers > 1) ? 4 : 2;

	str << "layout(std430, binding = " << currentIndex++ << ") readonly buffer _inPot{ uint inPotential[]; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") readonly buffer _inSil{ uint inSilhouette[]; };\n";

	str << "layout(std430, binding = " << currentIndex++ << ") readonly buffer _inNofPotBuffers{ uint nofPotSilBuffers[2]; };\n";

	str << "layout(std430, binding = " << currentIndex++ << ") readonly buffer _nofPotential{ uint nofPotential; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") readonly buffer _nofSilhouette{ uint nofSilhouette; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") buffer _potential{ uint potentialEdges[]; };\n";
	str << "layout(std430, binding = " << currentIndex++ << ") buffer _silhouette{ uint silhouetteEdges[]; };\n";

	str << "\nshared uint shm[" << workgroupSize * nofUintsPerSubbufferInfo << "];\n\n";

	str << "#define NOF_UINTS_BUFFER_INFO " << nofUintsPerSubbufferInfo << "\n";

	str << findLsbFunction;

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

	if (numBuffers > 1)
	{
		str << genFindBufferFunc();
		str << genGetNodeFromBuffer(numBuffers);
	}

	str << R".(
	
uint countBitsUint64(const uint64_t num)
{
	uvec2 a = unpackUint2x32(num);
	return bitCount(a.x) + bitCount(a.y);
}

uint findFirstSet(const uvec2 v)
{
	const int lowPos = findLSB(v.x);
	return (lowPos<0) ? 32 + findLSB(v.y) : lowPos;
}
).";

str << "void processEdges(bool isPotential, uint nofBuffs, uint nofPotEdges, uint shmStart)\n";
str << "{\n";
str << "	bool isFound = false;\n";
str << "	uint buffersProcessed = 0;\n";
str << "	uint currentSum = nofPotEdges;\n";
str << "	uint resultIndex = 0;\n";

if (numBuffers > 1)
	str << "	uint bufferIndex = 0;\n";
str << "\n";
str << "	while(!isFound && (buffersProcessed<nofBuffs))\n";
str << "	{\n";
str << "		uint nofLoaded = 0;\n";
str << "\n";
str << "		//Load to shared memory\n";
str << "		{\n";
str << "			const uint64_t mask = ballotARB(true);\n";
str << "			const uvec2 maskUnpack = unpackUint2x32(mask);\n";
str << "			const uint64_t andMask = (uint64_t(1)<<gl_SubGroupInvocationARB)-uint64_t(1);\n";
str << "			const uvec2 maskIdxPacked = unpackUint2x32(mask & andMask);\n";
str << "			uint idxInWarp = bitCount(maskIdxPacked.x) + bitCount(maskIdxPacked.y);\n";
str << "\n";
str << "			nofLoaded =  bitCount(maskUnpack.x) + bitCount(maskUnpack.y);\n";
str << "			if((buffersProcessed + nofLoaded) >= nofBuffs)\n";
str << "			{\n";
str << "				nofLoaded = nofBuffs - buffersProcessed;\n";
str << "			}\n";
str << "\n";
str << "			if(idxInWarp < nofLoaded)\n";
str << "			{\n";
str << "				if(isPotential)\n";
str << "				{\n";
str << "					shm[shmStart + NOF_UINTS_BUFFER_INFO*idxInWarp + 0] = inPotential[NOF_UINTS_BUFFER_INFO*(buffersProcessed + idxInWarp) + 0];\n";
str << "					shm[shmStart + NOF_UINTS_BUFFER_INFO*idxInWarp + 1] = inPotential[NOF_UINTS_BUFFER_INFO*(buffersProcessed + idxInWarp) + 1];\n";
if (numBuffers > 1)
	str << "					shm[shmStart + NOF_UINTS_BUFFER_INFO*idxInWarp + 2] = inPotential[NOF_UINTS_BUFFER_INFO * (buffersProcessed + idxInWarp) + 2]; \n";
str << "				}\n";
str << "				else\n";
str << "				{\n";
str << "					shm[shmStart + NOF_UINTS_BUFFER_INFO*idxInWarp + 0] = inSilhouette[NOF_UINTS_BUFFER_INFO*(buffersProcessed + idxInWarp) + 0];\n";
str << "					shm[shmStart + NOF_UINTS_BUFFER_INFO*idxInWarp + 1] = inSilhouette[NOF_UINTS_BUFFER_INFO*(buffersProcessed + idxInWarp) + 1];\n";
if (numBuffers > 1)
	str << "					shm[shmStart + NOF_UINTS_BUFFER_INFO*idxInWarp + 2] = inSilhouette[NOF_UINTS_BUFFER_INFO*(buffersProcessed + idxInWarp) + 2];\n";
str << "				}\n";
str << "			}\n";
str << "\n";
str << "			buffersProcessed += nofLoaded;\n";
str << "			\n";
str << "		}\n";
str << "\n";
str << "		//Process shm\n";
str << "		for(unsigned int i=0; i<nofLoaded; ++i)\n";
str << "		{\n";
str << "			const uint currentBufferSize = shm[shmStart + NOF_UINTS_BUFFER_INFO*i + 0];\n";
str << "			if((currentSum + currentBufferSize)>gl_GlobalInvocationID.x)\n";
str << "			{\n";
str << "				isFound = true;\n";
str << "				resultIndex = shm[shmStart + NOF_UINTS_BUFFER_INFO*i + 1] + (gl_GlobalInvocationID.x - currentSum);\n";
if (numBuffers > 1)
	str << "				bufferIndex = shm[shmStart + NOF_UINTS_BUFFER_INFO*i + 2];\n";
str << "				break;\n";
str << "			}\n";
str << "			\n";
str << "			currentSum += currentBufferSize;\n";
str << "		}\n";
str << "	}\n";
str << "\n";
str << "	if(isFound)\n";
str << "	{	\n";
str << "		if(isPotential)\n";
str << "		{\n";
if (numBuffers > 1)
	str << "			potentialEdges[gl_GlobalInvocationID.x] = getNodeFromBuffer(resultIndex, bufferIndex);\n";
else
	str << "			potentialEdges[gl_GlobalInvocationID.x] = edges0[resultIndex];\n";
str << "		}\n";
str << "		else\n";
str << "		{\n";
str << "			const uint storeIndex = gl_GlobalInvocationID.x - nofPotEdges;\n";
if (numBuffers > 1)
	str << "			silhouetteEdges[storeIndex] = getNodeFromBuffer(resultIndex, bufferIndex);\n";
else
	str << "			silhouetteEdges[storeIndex] = edges0[resultIndex];\n";
str << "		}\n";
str << "	}\n";
str << "}\n";


str << "void main()\n";
str << "{\n";
str << "	uint nofPotEdges = 0;\n";
str << "	uint nofSilEdges = 0;\n";
str << "	if (gl_SubGroupInvocationARB == 0)\n";
str << "	{\n";
str << "		nofPotEdges = nofPotential;\n";
str << "		nofSilEdges = nofSilhouette;\n";
str << "	}\n";
str << "\n";
str << "	nofPotEdges = readFirstInvocationARB(nofPotEdges);\n";
str << "	nofSilEdges = readFirstInvocationARB(nofSilEdges);\n";
str << "\n";
str << "	if(gl_GlobalInvocationID.x>=(nofPotEdges + nofSilEdges))\n";
str << "		return;\n";
str << "\n";
str << "	uint nofPotBufs = 0;\n";
str << "	uint nofSilBufs = 0;\n";
str << "	if(gl_SubGroupInvocationARB==0)\n";
str << "	{\n";
str << "		nofPotBufs = nofPotSilBuffers[0];\n";
str << "		nofSilBufs = nofPotSilBuffers[1];\n";
str << "	}\n";
str << "\n";
str << "	nofPotBufs = readFirstInvocationARB(nofPotBufs);\n";
str << "	nofSilBufs = readFirstInvocationARB(nofSilBufs);\n";
str << "\n";
str << "	const bool isPot = gl_GlobalInvocationID.x<nofPotEdges;\n";
str << "\n";
str << "	const uint shmStart = NOF_UINTS_BUFFER_INFO * (gl_LocalInvocationID.x/gl_SubGroupSizeARB) * gl_SubGroupSizeARB;\n";
str << "\n";

str << "	processEdges(isPot, isPot? nofPotBufs : nofSilBufs, uint(!isPot) * nofPotEdges, shmStart);\n";

str << "}\n";

	return str.str();
}