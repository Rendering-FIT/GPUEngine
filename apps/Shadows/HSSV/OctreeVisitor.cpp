#include "OctreeVisitor.hpp"
#include "Plane.hpp"
#include "GeometryOperations.hpp"

#include <iostream>
#include <bitset>
#include <set>

#include "OmpConfig.h"
#include "HighResolutionTimer.hpp"
#include "MultiplicityCoding.hpp"
#include "GpuOctreeLoader.hpp"
#include "GpuOctreeEdgePropagator.hpp"
#include <iterator>
#include <functional>
#include "GpuOctreeLoaderCompress8.hpp"
#include "CpuOctreeLoader.hpp"
#include "CpuOctreeEdgePropagator.hpp"

OctreeVisitor::OctreeVisitor(std::shared_ptr<Octree> octree)
{
	_octree = octree;
}

void OctreeVisitor::_propagateEdgesGpu()
{
	std::shared_ptr<GpuOctreeEdgePropagator> edgePropagator = std::make_shared<GpuOctreeEdgePropagator>();

	//edgePropagator->init(_octree, 256, 128);
	edgePropagator->init(_octree, 32, 64); //determined by profiling
	const auto startingLevel = _octree->getDeepestLevel() - 1;

	//--
	/*
	edgePropagator->profile();
	return;
	//*/
	//--

	HighResolutionTimer t;
	t.reset();

	_propagateEdgesToUpperLevelsGpu(edgePropagator, startingLevel, true);
	
	float dt = t.getElapsedTimeFromLastQuerySeconds();
	std::cout << "Propagate Potential edges took " << dt << " sec\n";

	_propagateEdgesToUpperLevelsGpu(edgePropagator, startingLevel, false);
	dt = t.getElapsedTimeFromLastQuerySeconds();

	std::cout << "Propagate Silhouette edges took " << dt << " sec\n";
}

void OctreeVisitor::addEdges(const AdjacencyType edges, std::shared_ptr<GpuEdges> gpuEdges, bool useCompress, uint64_t bufferSizeMB, float speculativeRatioPot, float speculativeRatioSil)
{
	IOctreeLoader* gpuLoader = nullptr;
	
	if (useCompress)
	{
		gpuLoader = new GpuOctreeLoaderCompress8();
	}
	else
	{
		gpuLoader = new GpuOctreeLoader();
	}

	dynamic_cast<IGpuOctreeLoader*>(gpuLoader)->setMaxBufferSize(bufferSizeMB);
	dynamic_cast<IGpuOctreeLoader*>(gpuLoader)->setSpeculativeRatios(speculativeRatioPot, speculativeRatioSil);

	if (!gpuLoader->init(_octree, gpuEdges, edges->getNofEdges()))
	{
		delete gpuLoader;
		std::cerr << "Failed to init GPU octree loader, switching to CPU (very slow)\n";
		_addEdgesCpu(edges);
		return;
	}

	//--
	/*
	dynamic_cast<IGpuOctreeLoader*>(gpuLoader)->profile(edges);
	//*/
	//--

	//HighResolutionTimer t;

	//t.reset();
	gpuLoader->addEdgesOnLowestLevel(edges);

	//auto dt = t.getElapsedTimeFromLastQuerySeconds();
	//std::cout << "Adding edges on GPU took " << dt << " sec\n";
	
	delete gpuLoader;

	//t.reset();
	const auto dl = _octree->getDeepestLevel();
	_sortLevel(dl);
	_sortLevel(dl-1);
	//dt = t.getElapsedTimeFromLastQuerySeconds();
	//std::cout << "Sorting lowest and second lowest level took " << dt << "sec\n";

	//--
	/*
	std::vector<float> mpA, mpP;
	const auto start = _octree->getLevelFirstNodeID(_octree->getDeepestLevel() - 2);
	const auto end = start + _octree->getNumNodesInLevel(_octree->getDeepestLevel());
	const float nofEdges = edges->getNofEdges();
	for (uint32_t i = start; i<end; ++i)
	{
		const auto node = _octree->getNode(i);

		mpA.push_back(float(node->edgesAlwaysCastMap[BitmaskAllSet].size()) / nofEdges);
		mpP.push_back(float(node->edgesMayCastMap[BitmaskAllSet].size()) / nofEdges);
	}
	std::sort(mpA.begin(), mpA.end(), std::greater<float>());
	std::sort(mpP.begin(), mpP.end(), std::greater<float>());
	std::cout << "Highest Sil: " << mpA[0] << " " << mpA[1] << " " << mpA[2] << " " << mpA[3] << " " << "\n";
	std::cout << "Highest Pot: " << mpP[0] << " " << mpP[1] << " " << mpP[2] << " " << mpP[3] << " " << "\n";
	//*/
	//--

	_propagateEdgesGpu();

	//std::cout << "Octree size: " << _octree->getOctreeSizeBytes() / 1024ul / 1024ul << "MB\n";
}

void OctreeVisitor::_addEdgesCpu(const AdjacencyType edges)
{
	CpuOctreeLoader loader;
	loader.init(_octree, nullptr, 0);
	loader.addEdgesOnLowestLevel(edges);

	//_propagateEdgesCpu();
	_propagateEdgesGpu();
}

void OctreeVisitor::_propagateEdgesCpu()
{
	CpuOctreeEdgePropagator propagator;
	propagator.propagateEdgesToUpperLevels(_octree);
}

void OctreeVisitor::_propagateEdgesToUpperLevelsGpu(std::shared_ptr<GpuOctreeEdgePropagator> propagator,uint32_t startingLevel, bool propagatePotential)
{
	for (int i = startingLevel; i > 0; --i)
		propagator->propagateEdgesToUpperLevel(i, propagatePotential ? BufferType::POTENTIAL : BufferType::SILHOUETTE);
}


int OctreeVisitor::getLowestNodeIndexFromPoint(const glm::vec3& point) const
{
	/*
	int currentParent = 0;
	const uint32_t deepestLevel = _octree->getDeepestLevel();

	for(uint32_t level = 0; level<deepestLevel && currentParent>=0; ++level)
		currentParent = _getChildNodeContainingPoint(currentParent, point);

	return currentParent;
	//*/

	if (!_isPointInsideNode(0, point))
		return -1;

	auto const& bb = _octree->getNode(0)->volume;
	auto singleUnitSize = bb.getExtents() / glm::vec3(ipow(2, _octree->getDeepestLevel()));

	glm::uvec3 pos = glm::uvec3(glm::floor((point - bb.getMinPoint()) / singleUnitSize));

	auto const deepstLevel = _octree->getDeepestLevel();
	int relPos = 0;
		
	for (uint32_t i = 0; i < deepstLevel; ++i)
		relPos+=((((pos.x >> i) & 1) << 0) + (((pos.y >> i) & 1) << 1) + (((pos.z >> i) & 1) << 2))*ipow(OCTREE_NUM_CHILDREN, i);

	relPos += _octree->getNumNodesInPreviousLevels(deepstLevel);
	return relPos;
}

bool OctreeVisitor::_isPointInsideNode(uint32_t nodeID, const glm::vec3& point) const
{
	const auto node = _octree->getNode(nodeID);

	assert(node != nullptr);

	return GeometryOps::testAabbPointIsInsideOrOn(node->volume, point);
}

int OctreeVisitor::_getChildNodeContainingPoint(uint32_t parent, const glm::vec3& point) const
{
	const int startingID = _octree->getChildrenStartingId(parent);

	for(uint32_t i=0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		if (_isPointInsideNode(startingID + i, point))
			return startingID + i;
	}

	return -1;
}

void OctreeVisitor::getSilhouttePotentialEdgesFromNodeUp(std::vector<uint32_t>& potential, std::vector<uint32_t>& silhouette, uint32_t nodeID) const
{
	int currentNodeID = nodeID;

	static bool printOnce = true;

	uint32_t comingFromChildId = 0;

	_getSilhouttePotentialEdgesFromNodeUpCompress2(potential, silhouette, nodeID);
}

void OctreeVisitor::_getSilhouttePotentialEdgesFromNodeUpCompress2(std::vector<uint32_t>& potential, std::vector<uint32_t>& silhouette, uint32_t nodeID) const
{
	int currentNodeID = nodeID;

	int currentLevel = _octree->getDeepestLevel();
	const uint32_t levelWithCompressedNodess = _octree->getDeepestLevel() - _octree->getCompressionLevel();
	uint32_t nofBuffersPot = 0;
	uint32_t nofBuffersSil = 0;

	const bool isCompressed = _octree->getCompressionLevel() != 0;

	while (currentLevel >= 0)
	{
		const auto node = _octree->getNode(currentNodeID);

		assert(node != nullptr);

		const auto& silBuffer = node->edgesAlwaysCastMap.find(BitmaskAllSet);
		if (silBuffer != node->edgesAlwaysCastMap.end())
		{
			silhouette.insert(silhouette.end(), silBuffer->second.begin(), silBuffer->second.end());
			nofBuffersSil++;
		}

		const auto& potBuffer = node->edgesMayCastMap.find(BitmaskAllSet);
		if (potBuffer != node->edgesMayCastMap.end())
		{
			potential.insert(potential.end(), potBuffer->second.begin(), potBuffer->second.end());
			nofBuffersPot++;
		}

		if (currentLevel == levelWithCompressedNodess && isCompressed)
		{
			const auto compressionId = _getCompressionIdWithinParent(nodeID);

			for (const auto& edgeBuffer : node->edgesAlwaysCastMap)
			{
				if (edgeBuffer.first != BitmaskAllSet && edgeBuffer.first & (BitmaskType(1) << compressionId))
				{
					silhouette.insert(silhouette.end(), edgeBuffer.second.begin(), edgeBuffer.second.end());
					nofBuffersSil++;
				}
			}

			for (const auto edgeBuffer : node->edgesMayCastMap)
			{ 
				if (edgeBuffer.first != BitmaskAllSet && edgeBuffer.first & (BitmaskType(1) << compressionId))
				{
					potential.insert(potential.end(), edgeBuffer.second.begin(), edgeBuffer.second.end());
					nofBuffersPot++;
				}
			}
		}

		const auto previousNodeId = currentNodeID;
		currentNodeID = _octree->getNodeParent(currentNodeID);
		--currentLevel;
	}
}

uint32_t OctreeVisitor::_getCompressionIdWithinParent(uint32_t nodeId) const
{
	const auto compressionLevel = _octree->getCompressionLevel();

	assert(compressionLevel <= 2);
	
	const auto relativeOneAbove = _getNodeIdWithinParent(nodeId);
	const auto parent = _octree->getNodeParent(nodeId);

	if (compressionLevel < 2)
		return relativeOneAbove;
	else //2
		return relativeOneAbove + OCTREE_NUM_CHILDREN * _getNodeIdWithinParent(parent);
}

uint32_t OctreeVisitor::_getNodeIdWithinParent(uint32_t nodeId) const
{
	auto parent = _octree->getNodeParent(nodeId);
	return nodeId - _octree->getChildrenStartingId(parent);
}

void OctreeVisitor::_sortLevel(uint32_t level)
{
	if (level > _octree->getDeepestLevel())
		return;

	const int startingID = _octree->getLevelFirstNodeID(level);
	const auto size = ipow(OCTREE_NUM_CHILDREN, level);

	#pragma omp parallel for 
	for(int i = startingID; i<(startingID+size); ++i)
	{
		auto n = _octree->getNode(i);

		auto& edgesSil = n->edgesAlwaysCastMap[BitmaskAllSet];
		std::sort(edgesSil.begin(), edgesSil.end());

		auto& edgesPot = n->edgesMayCastMap[BitmaskAllSet];
		std::sort(edgesPot.begin(), edgesPot.end());
	}
}

void OctreeVisitor::shrinkOctree()
{
	const int numNodes = int(_octree->getTotalNumNodes());

	#pragma omp parallel for 
	for(int i = 0; i<numNodes; ++i)
	{
		auto node = _octree->getNode(i);

		if(node)
		{
			for (auto edges = node->edgesAlwaysCastMap.begin(); edges != node->edgesAlwaysCastMap.end(); )
			{
				if (edges->second.size())
					(edges++)->second.shrink_to_fit();
				else
					node->edgesAlwaysCastMap.erase((edges++)->first);
			}

			for (auto edges = node->edgesMayCastMap.begin(); edges != node->edgesMayCastMap.end(); )
			{
				if (edges->second.size())
					(edges++)->second.shrink_to_fit();
				else
					node->edgesMayCastMap.erase((edges++)->first);
			}
		}
	}
}

uint32_t OctreeVisitor::getNofAllIndicesInNode(uint32_t nodeID) const
{
	assert(nodeID < _octree->getTotalNumNodes());

	const auto node = _octree->getNode(nodeID);

	uint32_t nofIndices = 0;

	for (const auto& buffer : node->edgesAlwaysCastMap)
		nofIndices += unsigned(buffer.second.size());

	for(const auto& buffer : node->edgesMayCastMap)
		nofIndices += unsigned(buffer.second.size());

	return nofIndices;
}

void OctreeVisitor::getNodeNofSubBuffersPotSil(uint32_t& pot, uint32_t& sil, uint32_t nodeID) const
{
	const auto node = _octree->getNode(nodeID);

	pot = 0;
	sil = 0;

	if(node)
	{
		pot = unsigned(node->edgesMayCastMap.size());
		sil = unsigned(node->edgesAlwaysCastMap.size());
	}
}

void OctreeVisitor::_getMaxNofSubBuffersInLevelPotSil(uint32_t& pot, uint32_t& sil, uint32_t level) const
{
	const auto startingIndex = _octree->getLevelFirstNodeID(level);
	const auto levelSize = unsigned(ipow(OCTREE_NUM_CHILDREN, level));

	pot = 0;
	sil = 0;

	for (uint32_t i = 0; i<levelSize; ++i)
	{
		uint32_t p = 0, s = 0;
		getNodeNofSubBuffersPotSil(p, s, startingIndex + i);
		pot = std::max(pot, p);
		sil = std::max(sil, s);
	}
}

void  OctreeVisitor::getMaxNofSubBuffersPotSil(uint32_t& pot, uint32_t& sil) const
{
	const auto deepestLevel = _octree->getDeepestLevel();
	uint32_t maxSubBuffers = 0;
	
	pot = sil = 0;

	for(uint32_t i = 0; i<=deepestLevel; ++i)
	{
		uint32_t p = 0, s = 0;
		_getMaxNofSubBuffersInLevelPotSil(p, s, i);
		pot += p;
		sil += s;
	}
}

#include <iostream>
#include <fstream>
void OctreeVisitor::dumpOctreeLevel(uint32_t level, const char* filename)
{
	std::ofstream file(filename);

	if (!file.is_open())
		return;

	//Get level start and size
	const auto firstNode = _octree->getLevelFirstNodeID(level);
	const auto lastNode = firstNode + _octree->getLevelSize(level);

	for (uint32_t currentNode = firstNode; currentNode < lastNode; ++currentNode)
	{
		const auto node = _octree->getNode(currentNode);

		file << "---Node " << std::to_string(currentNode) << std::endl;
		file << "POTENTIAL\n";
		for (const auto buffer : node->edgesMayCastMap)
		{
			if (!buffer.second.size())
				continue;
			
			file << std::to_string(buffer.first) << ":\n";

			for (const auto edge : buffer.second)
			{
				file << "\t" << std::to_string(edge) << std::endl;
			}
		}
		file << "SILHOUETTE\n";
		for (const auto buffer : node->edgesAlwaysCastMap)
		{
			if (!buffer.second.size())
				continue;

			file << std::to_string(buffer.first) << ":\n";

			for (const auto edge : buffer.second)
			{
				file << "\t" << std::to_string(decodeEdgeFromEncoded(edge)) << "(" << std::to_string(decodeEdgeMultiplicityFromId(edge)) << ")" << std::endl;
			}
		}
	}

	file.close();
}