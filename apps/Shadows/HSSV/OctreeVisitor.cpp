#include "OctreeVisitor.hpp"
#include "Plane.hpp"
#include "GeometryOperations.hpp"

#include <iostream>
#include <bitset>
#include <set>

#include <omp.h>
#include "HighResolutionTimer.hpp"
#include "MultiplicityCoding.hpp"
#include "GpuOctreeLoader.hpp"
#include "GpuOctreeEdgePropagator.hpp"
#include <iterator>
#include <functional>

OctreeVisitor::OctreeVisitor(std::shared_ptr<Octree> octree)
{
	_octree = octree;
}

void OctreeVisitor::_propagateEdgesGpu()
{
	std::shared_ptr<GpuOctreeEdgePropagator> edgePropagator = std::make_shared<GpuOctreeEdgePropagator>();

	edgePropagator->init(_octree, 1024);
	const auto startingLevel = _octree->getDeepestLevel() - 1;

	HighResolutionTimer t;
	t.reset();

	_propagateEdgesToUpperLevelsGpu(edgePropagator, startingLevel, true);
	
	float dt = t.getElapsedTimeFromLastQuerySeconds();
	std::cout << "Propagate Potential edges took " << dt << " sec\n";

	_propagateEdgesToUpperLevelsGpu(edgePropagator, startingLevel, false);
	dt = t.getElapsedTimeFromLastQuerySeconds();

	std::cout << "Propagate Silhouette edges took " << dt << " sec\n";
}

void OctreeVisitor::addEdges(const AdjacencyType edges)
{
	std::cout << "NoF edges: " << edges->getNofEdges() << "\n";

	std::vector< std::vector<Plane> > edgePlanes;
	_generateEdgePlanes(edges, edgePlanes);
	
	HighResolutionTimer t;
	t.reset();
	_addEdgesOnLowestLevel(edgePlanes, edges);
	auto dt = t.getElapsedTimeFromLastQueryMilliseconds();

	std::cout << "Adding edges took " << dt / 1000.0f << " sec\n";

	t.reset();
	const auto startingLevel = _octree->getDeepestLevel() - 1;
	_propagateEdgesToUpperLevelsCpu(startingLevel, true);
	dt = t.getElapsedTimeFromLastQueryMilliseconds();

	std::cout << "Propagate Potential edges took " << dt / 1000.0f << " sec\n";
	t.reset();

	_propagateEdgesToUpperLevelsCpu(startingLevel, false);

	dt = t.getElapsedTimeFromLastQueryMilliseconds();

	std::cout << "Propagate Silhouette edges took " << dt / 1000.0f << " sec\n";
}

void OctreeVisitor::addEdgesGPU(const AdjacencyType edges, std::shared_ptr<GpuEdges> gpuEdges, unsigned int subgroupSize)
{
	GpuOctreeLoader* gpuLoader = new GpuOctreeLoader();

	if (!gpuLoader->init(_octree, gpuEdges, subgroupSize, edges->getNofEdges()))
	{
		std::cerr << "Failed to init GPU octree loader, switching to CPU (very slow)\n";
		addEdges(edges);
		return;
	}

	//--
	/*
	gpuLoader->profile1(edges);
	//*/
	//--

	HighResolutionTimer t;

	t.reset();
	gpuLoader->addEdgesOnLowestLevelGPU(edges);

	auto dt = t.getElapsedTimeFromLastQuerySeconds();
	std::cout << "Adding edges on GPU took " << dt << " sec\n";
	
	delete gpuLoader;

	t.reset();
	const auto dl = _octree->getDeepestLevel();
	_sortLevel(dl);
	_sortLevel(dl-1);
	dt = t.getElapsedTimeFromLastQuerySeconds();
	std::cout << "Sorting lowest and second lowest level took " << dt << "sec\n";

	//--
	/*
	std::vector<float> mpA, mpP;
	const auto start = _octree->getLevelFirstNodeID(_octree->getDeepestLevel() - 2);
	const auto end = start + _octree->getNumNodesInLevel(_octree->getDeepestLevel());
	const float nofEdges = edges->getNofEdges();
	for (unsigned int i = start; i<end; ++i)
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

	std::cout << "Octree size: " << _octree->getOctreeSizeBytes() / 1024ul / 1024ul << "MB\n";
}


void OctreeVisitor::_generateEdgePlanes(const AdjacencyType edges, std::vector< std::vector<Plane> >& planes) const
{
	const auto numEdges = edges->getNofEdges();

	planes.resize(numEdges);

	unsigned int index = 0;

	for(size_t i = 0; i<numEdges; ++i)
	{
		const auto nofOpposites = getNofOppositeVertices(edges, i);
		planes[index].reserve(nofOpposites);

		const glm::vec3& v1 = getEdgeVertexLow(edges, i);
		const glm::vec3& v2 = getEdgeVertexHigh(edges, i);

		for (unsigned int j = 0; j<nofOpposites; ++j)
		{
			Plane p;
			p.createFromPointsCCW(v1, getOppositeVertex(edges, i, j), v2);

			planes[index].push_back(p);
		}

		++index;
	}
}

void OctreeVisitor::_addEdgesOnLowestLevel(std::vector< std::vector<Plane> >& edgePlanes, const AdjacencyType edges)
{
	const int deepestLevel = _octree->getDeepestLevel();
	const int levelSize = ipow(OCTREE_NUM_CHILDREN, deepestLevel);

	const int startingIndex = _octree->getNumNodesInPreviousLevels(deepestLevel);
	const int stopIndex = _octree->getTotalNumNodes();
	
	std::cout << "Total iterations: " << (stopIndex - startingIndex) / OCTREE_NUM_CHILDREN << "\n";
	
	#pragma omp parallel for
	for (int i = startingIndex; i < stopIndex; i += OCTREE_NUM_CHILDREN)
	{
		static int a = 0;
		_addEdgesSyblingsParent(edgePlanes, edges, i);
		std::cout << a++ << std::endl;
	}
}

void OctreeVisitor::_addEdgesSyblingsParent(const std::vector< std::vector<Plane> >& edgePlanes, AdjacencyType edges, unsigned int startingID)
{
	unsigned int edgeIndex = 0;

	const int parent = _octree->getNodeParent(startingID);

	const size_t nofEdges = edges->getNofEdges();
	for (size_t edgeIndex = 0; edgeIndex < nofEdges; ++edgeIndex)
	{
		unsigned int numPotential = 0;

		std::bitset<8> potentialBitmask(0);
		std::map<int, std::bitset<8>> silhouetteBitmasks;

		int potentialIndices[OCTREE_NUM_CHILDREN];

		const auto numOppositeVertices = edges->getNofOpposite(edgeIndex);

		for (unsigned int index = startingID; index<(startingID + OCTREE_NUM_CHILDREN); index++)
		{
			const bool isPotentiallySilhouette = numOppositeVertices>1 && GeometryOps::isEdgeSpaceAaabbIntersecting(edgePlanes[edgeIndex][0], edgePlanes[edgeIndex][1], _octree->getNodeVolume(index));

			if (isPotentiallySilhouette)
			{
				potentialIndices[numPotential++] = index;
				potentialBitmask[index - startingID] = true;
			}
			else
			{
				const int multiplicity = GeometryOps::calcEdgeMultiplicity(edges, edgeIndex, _octree->getNodeVolume(index).getMinPoint());
				if (multiplicity != 0)
				{
					const auto encodedEdge = encodeEdgeMultiplicityToId(unsigned int(edgeIndex), multiplicity);
					silhouetteBitmasks[encodedEdge][index - startingID] = true;
				}
			}
		}

		if (parent >= 0)
		{
			if (potentialBitmask.count() > 3)
			{
				_storeEdgeIsPotentiallySilhouette(parent, unsigned int(edgeIndex), potentialBitmask.to_ullong());
				numPotential = 0;
			}

			for (auto sil = silhouetteBitmasks.cbegin(); sil != silhouetteBitmasks.cend(); )
			{
				if((*sil).second.count()>3)
				{
					_storeEdgeIsAlwaysSilhouette(parent, (*sil).first, (*sil).second.to_ullong());
					silhouetteBitmasks.erase(sil++);
				}
				else
					++sil;
			}
		}

		for(unsigned int i = 0; i<numPotential; ++i)
			_storeEdgeIsPotentiallySilhouette(potentialIndices[i], unsigned int(edgeIndex), BitmaskAllSet);

		//Store each silhouette edge variant in leaves
		for(auto sil = silhouetteBitmasks.cbegin(); sil != silhouetteBitmasks.cend(); ++sil)
		{
			const auto count = sil->second.count();
			unsigned int currentPosition = 0;

			for(unsigned int i=0; i<count; ++i)
			{
				while (!sil->second[currentPosition]) ++currentPosition;

				_storeEdgeIsAlwaysSilhouette(startingID + currentPosition, sil->first, BitmaskAllSet);
			}
		}
	}
	
	for(auto i = startingID; i<(startingID+OCTREE_NUM_CHILDREN); ++i)
	{
		auto node = _octree->getNode(i);

		if (node)
		{
			node->shrinkEdgeVectors();
			node->sortEdgeVectors();
		}
	}
	//*/
}

bool OctreeVisitor::_doAllSilhouetteFaceTheSame(const int(&indices)[OCTREE_NUM_CHILDREN]) const
{
	const int first = indices[0];

	for(unsigned int i = 1; i<OCTREE_NUM_CHILDREN; ++i)
	{
		if (indices[i] != first)
			return false;
	}

	return true;
}

void OctreeVisitor::_storeEdgeIsAlwaysSilhouette(unsigned int nodeId, unsigned int augmentedEdgeIdWithResult, const BitmaskType subarrayIndex)
{
	auto node = _octree->getNode(nodeId);

	assert(node != nullptr);

	node->edgesAlwaysCastMap[subarrayIndex].push_back(augmentedEdgeIdWithResult);
}

void OctreeVisitor::_storeEdgeIsPotentiallySilhouette(unsigned int nodeID, unsigned int edgeID, const BitmaskType subarrayIndex)
{
	auto node = _octree->getNode(nodeID);

	assert(node != nullptr);

	node->edgesMayCastMap[subarrayIndex].push_back(edgeID);
}

void OctreeVisitor::_propagateEdgesToUpperLevelsGpu(std::shared_ptr<GpuOctreeEdgePropagator> propagator,unsigned int startingLevel, bool propagatePotential)
{
	for (int i = startingLevel; i > 0; --i)
		propagator->propagateEdgesToUpperLevel(i, propagatePotential ? BufferType::POTENTIAL : BufferType::SILHOUETTE);
}

void OctreeVisitor::_propagateEdgesToUpperLevelsCpu(unsigned int startingLevel, bool propagatePotential)
{
	for (int i = startingLevel; i > 0; --i)
		_processEdgesInLevel(i, propagatePotential);
}

OctreeVisitor::TestResult OctreeVisitor::_haveAllSyblingsEdgeInCommon(unsigned int startingNodeID, unsigned int edgeID, bool propagatePotential, BitmaskType subBufferId) const
{	
	TestResult retval = TestResult::NON_EXISTING;
	
	for(unsigned int i=0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		const auto node = _octree->getNode(startingNodeID + i);
		
		if (!node)
			continue;

		if (propagatePotential)
		{
			if (node->edgesMayCastMap.find(subBufferId) == node->edgesMayCastMap.end() || !std::binary_search(node->edgesMayCastMap[subBufferId].begin(), node->edgesMayCastMap[subBufferId].end(), edgeID))
				return TestResult::FALSE;
		}
		else
			if (node->edgesAlwaysCastMap.find(subBufferId) == node->edgesAlwaysCastMap.end() || !std::binary_search(node->edgesAlwaysCastMap[subBufferId].begin(), node->edgesAlwaysCastMap[subBufferId].end(), edgeID))
				return TestResult::FALSE;
		
		retval = TestResult::TRUE;
	}

	return retval;
}

void OctreeVisitor::_processEdgesInLevel(unsigned int level, bool propagatePotential)
{
	assert(level > 0);
	const int startingID = _octree->getLevelFirstNodeID(level);
	
	assert(startingID >= 0);

	const int stopId = ipow(OCTREE_NUM_CHILDREN, level) + startingID;

	int currentID = startingID;

	#pragma omp parallel for
	for (currentID = startingID; currentID<stopId; currentID += OCTREE_NUM_CHILDREN)
	{
		auto firstNode = _octree->getNode(currentID);
		const auto edgesMap = propagatePotential ? firstNode->edgesMayCastMap : firstNode->edgesAlwaysCastMap;

		if (!edgesMap.empty())
		{
			auto it = edgesMap.find(BitmaskAllSet);
			if (it != edgesMap.end())
			{
				auto edgeSubBuffer = *it;
				for (const auto edge : edgeSubBuffer.second)
				{
					auto result = _haveAllSyblingsEdgeInCommon(currentID, edge, propagatePotential, edgeSubBuffer.first);

					if (result == TestResult::TRUE)
					{
						assignEdgeToNodeParent(currentID, edge, propagatePotential, edgeSubBuffer.first);
						_removeEdgeFromSyblings(currentID, edge, propagatePotential, edgeSubBuffer.first);
					}
				}
			}
		}
	}
}

void OctreeVisitor::_removeEdgeFromSyblings(unsigned int startingID, unsigned int edge, bool propagatePotential, BitmaskType subBufferId)
{
	for(unsigned int i=0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		auto node = _octree->getNode(startingID + i);

		if (node)
		{
			if (propagatePotential)
				node->edgesMayCastMap[subBufferId].erase(std::lower_bound(node->edgesMayCastMap[subBufferId].begin(), node->edgesMayCastMap[subBufferId].end(), edge));
			else
				node->edgesAlwaysCastMap[subBufferId].erase(std::lower_bound(node->edgesAlwaysCastMap[subBufferId].begin(), node->edgesAlwaysCastMap[subBufferId].end(), edge));
		}
	}
}

void OctreeVisitor::assignEdgeToNodeParent(unsigned int node, unsigned int edge, bool propagatePotential, BitmaskType subBufferId)
{
	const int parent = _octree->getNodeParent(node);

	assert(parent >= 0);

	assignEdgeToNode(parent, edge, propagatePotential, subBufferId);
}

void OctreeVisitor::assignEdgeToNode(unsigned int node, unsigned int edge, bool propagatePotential, BitmaskType subBufferId)
{
	auto n = _octree->getNode(node);

	if (n)
	{
		if (propagatePotential)
			n->edgesMayCastMap[subBufferId].push_back(edge);
		else
			n->edgesAlwaysCastMap[subBufferId].push_back(edge);
	}
}

int OctreeVisitor::getLowestNodeIndexFromPoint(const glm::vec3& point) const
{
	int currentParent = 0;
	const unsigned int deepestLevel = _octree->getDeepestLevel();

	for(unsigned int level = 0; level<deepestLevel && currentParent>=0; ++level)
		currentParent = _getChildNodeContainingPoint(currentParent, point);

	return currentParent;
}

bool OctreeVisitor::_isPointInsideNode(unsigned int nodeID, const glm::vec3& point) const
{
	const auto node = _octree->getNode(nodeID);

	assert(node != nullptr);

	return GeometryOps::testAabbPointIsInsideOrOn(node->volume, point);
}

int OctreeVisitor::_getChildNodeContainingPoint(unsigned int parent, const glm::vec3& point) const
{
	const int startingID = _octree->getChildrenStartingId(parent);

	for(unsigned int i=0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		if (_isPointInsideNode(startingID + i, point))
			return startingID + i;
	}

	return -1;
}

#include <sstream>
#include <iostream>
#include <fstream>
void OctreeVisitor::getSilhouttePotentialEdgesFromNodeUp(std::vector<unsigned int>& potential, std::vector<unsigned int>& silhouette, unsigned int nodeID) const
{
	int currentNodeID = nodeID;

	static bool printOnce = true;

	unsigned int comingFromChildId = 0;

	_getSilhouttePotentialEdgesFromNodeUpCompress2(potential, silhouette, nodeID);
}

void OctreeVisitor::_getSilhouttePotentialEdgesFromNodeUpCompress2(std::vector<unsigned int>& potential, std::vector<unsigned int>& silhouette, unsigned int nodeID) const
{
	int currentNodeID = nodeID;

	int currentLevel = _octree->getDeepestLevel();
	const unsigned int levelWithCompressedNodess = _octree->getDeepestLevel() - _octree->getCompressionLevel();
	unsigned int nofBuffersPot = 0;
	unsigned int nofBuffersSil = 0;
	while (currentLevel >= 0)
	{
		const auto node = _octree->getNode(currentNodeID);

		assert(node != nullptr);

		const auto silBuffer = node->edgesAlwaysCastMap.find(BitmaskAllSet);
		if (silBuffer != node->edgesAlwaysCastMap.end())
		{
			silhouette.insert(silhouette.end(), silBuffer->second.begin(), silBuffer->second.end());
			nofBuffersSil++;
		}

		const auto potBuffer = node->edgesMayCastMap.find(BitmaskAllSet);
		if (potBuffer != node->edgesMayCastMap.end())
		{
			potential.insert(potential.end(), potBuffer->second.begin(), potBuffer->second.end());
			nofBuffersPot++;
		}

		if (currentLevel == levelWithCompressedNodess)
		{
			const auto compressionId = _getCompressionIdWithinParent(nodeID);

			for (const auto edgeBuffer : node->edgesAlwaysCastMap)
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

unsigned int OctreeVisitor::_getCompressionIdWithinParent(unsigned int nodeId) const
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

unsigned int OctreeVisitor::_getNodeIdWithinParent(unsigned int nodeId) const
{
	auto parent = _octree->getNodeParent(nodeId);
	return nodeId - _octree->getChildrenStartingId(parent);
}

void OctreeVisitor::_sortLevel(unsigned int level)
{
	if (level > _octree->getDeepestLevel())
		return;

	const int startingID = _octree->getLevelFirstNodeID(level);
	const auto size = ipow(OCTREE_NUM_CHILDREN, level);

	#pragma omp parallel for
	for(int i = startingID; i<(startingID+size); ++i)
	{
		auto n = _octree->getNode(i);

		auto edgesSil = n->edgesAlwaysCastMap[BitmaskAllSet];
		std::sort(edgesSil.begin(), edgesSil.end());

		auto edgesPot = n->edgesMayCastMap[BitmaskAllSet];
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

unsigned int OctreeVisitor::getNofAllIndicesInNode(unsigned int nodeID) const
{
	assert(nodeID < _octree->getTotalNumNodes());

	const auto node = _octree->getNode(nodeID);

	unsigned int nofIndices = 0;

	for (const auto& buffer : node->edgesAlwaysCastMap)
		nofIndices += unsigned(buffer.second.size());

	for(const auto& buffer : node->edgesMayCastMap)
		nofIndices += unsigned(buffer.second.size());

	return nofIndices;
}

void OctreeVisitor::getNodeNofSubBuffersPotSil(unsigned int& pot, unsigned int& sil, unsigned int nodeID) const
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

void OctreeVisitor::_getMaxNofSubBuffersInLevelPotSil(unsigned int& pot, unsigned int& sil, unsigned int level) const
{
	const auto startingIndex = _octree->getLevelFirstNodeID(level);
	const auto levelSize = unsigned(ipow(OCTREE_NUM_CHILDREN, level));

	pot = 0;
	sil = 0;

	for (unsigned int i = 0; i<levelSize; ++i)
	{
		unsigned int p = 0, s = 0;
		getNodeNofSubBuffersPotSil(p, s, startingIndex + i);
		pot = std::max(pot, p);
		sil = std::max(sil, s);
	}
}

void  OctreeVisitor::getMaxNofSubBuffersPotSil(unsigned int& pot, unsigned int& sil) const
{
	const auto deepestLevel = _octree->getDeepestLevel();
	unsigned int maxSubBuffers = 0;
	
	pot = sil = 0;

	for(unsigned int i = 0; i<=deepestLevel; ++i)
	{
		unsigned int p = 0, s = 0;
		_getMaxNofSubBuffersInLevelPotSil(p, s, i);
		pot = std::max(pot, p);
		sil = std::max(sil, s);
	}
}

#include <iostream>
#include <fstream>
void OctreeVisitor::dumpOctreeLevel(unsigned int level, const char* filename)
{
	std::ofstream file(filename);

	if (!file.is_open())
		return;

	//Get level start and size
	const auto firstNode = _octree->getLevelFirstNodeID(level);
	const auto lastNode = firstNode + _octree->getLevelSize(level);

	for (unsigned int currentNode = firstNode; currentNode < lastNode; ++currentNode)
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