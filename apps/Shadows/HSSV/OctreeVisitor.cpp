#include "OctreeVisitor.hpp"
#include "Plane.hpp"
#include "GeometryOperations.hpp"

#include <stack>
#include <iostream>

#include <omp.h>
#include "HighResolutionTimer.hpp"
#include "MultiplicityCoding.hpp"
#include "GpuOctreeLoader.hpp"
#include "GpuOctreeEdgePropagator.hpp"

OctreeVisitor::OctreeVisitor(std::shared_ptr<Octree> octree)
{
	_octree = octree;
}

void OctreeVisitor::addEdges(const AdjacencyType edges)
{
	_expandWholeOctree();

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
	_propagateEdgesUpFromLevel(startingLevel, true);
	dt = t.getElapsedTimeFromLastQueryMilliseconds();

	std::cout << "Propagate Potential edges took " << dt / 1000.0f << " sec\n";
	t.reset();

	_propagateEdgesUpFromLevel(startingLevel, false);

	dt = t.getElapsedTimeFromLastQueryMilliseconds();

	std::cout << "Propagate Silhouette edges took " << dt / 1000.0f << " sec\n";
}

void OctreeVisitor::addEdgesGPU(const AdjacencyType edges, unsigned int subgroupSize)
{
	std::shared_ptr<GpuOctreeLoader> gpuLoader = std::make_shared<GpuOctreeLoader>();

	if (!gpuLoader->init(_octree, subgroupSize))
	{
		std::cerr << "Failed to init GPU octree loader, switching to CPU (very slow)\n";
		addEdges(edges);
		return;
	}

	_expandWholeOctree();
	
	//--
	//gpuLoader->profile(edges, subgroupSize);
	//--

	HighResolutionTimer t;

	t.reset();
	gpuLoader->addEdgesOnLowestLevelGPU(edges);
	auto dt = t.getElapsedTimeFromLastQuerySeconds();
	std::cout << "Adding edges on GPU took " << dt << " sec\n";
	
	t.reset();
	const auto dl = _octree->getDeepestLevel();
	_sortLevel(dl);
	_sortLevel(dl-1);
	dt = t.getElapsedTimeFromLastQuerySeconds();
	std::cout << "Sorting lowest and second lowest level took " << dt << "sec\n";

	const auto startingLevel = _octree->getDeepestLevel() - 1;
	_propagateEdgesUpFromLevel(startingLevel, true);
	dt = t.getElapsedTimeFromLastQuerySeconds();
	std::cout << "Propagate Potential edges took " << dt << " sec\n";
	
	t.reset();
	_propagateEdgesUpFromLevel(startingLevel, false);
	dt = t.getElapsedTimeFromLastQuerySeconds();
	std::cout << "Propagate Silhouette edges took " << dt << " sec\n";

	t.reset();
	_shrinkOctree();
	dt = t.getElapsedTimeFromLastQuerySeconds();
	std::cout << "Shrinking octree took " << dt << " sec\n";

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
		_addEdgesSyblingsParent(edgePlanes, edges, i);
		//static int a = 0;
		//std::cout << "Iter " << a++ << " Added edges to node " << i << " current tree size " << float(_octree->getOctreeSizeBytes()) / 1024.0 / 1024.0 << "MB" << std::endl;
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
		unsigned int silhouetteMask = 0;

		int potentialIndices[OCTREE_NUM_CHILDREN];
		int silhouetteIndices[OCTREE_NUM_CHILDREN];

		const auto numOppositeVertices = edges->getNofOpposite(edgeIndex);

		if(numOppositeVertices!=2)
			continue;

		for (unsigned int index = startingID; index<(startingID + OCTREE_NUM_CHILDREN); index++)
		{
			const bool isPotentiallySilhouette = GeometryOps::isEdgeSpaceAaabbIntersecting(edgePlanes[edgeIndex][0], edgePlanes[edgeIndex][1], _octree->getNodeVolume(index));

			if(isPotentiallySilhouette)
				potentialIndices[numPotential++] = index;
			else
			{
				const int multiplicity = GeometryOps::calcEdgeMultiplicity(edges, edgeIndex, _octree->getNodeVolume(index).getMinPoint());
				if (multiplicity != 0)
				{
					silhouetteIndices[index-startingID] = encodeEdgeMultiplicityToId(edgeIndex, multiplicity);
					silhouetteMask |= 1 << (index - startingID);
				}
			}
		}

		if (parent >= 0)
		{
			if (numPotential == OCTREE_NUM_CHILDREN)
			{
				_storeEdgeIsPotentiallySilhouette(parent, edgeIndex);
				numPotential = 0;
			}

			if (silhouetteMask == (ipow(2, OCTREE_NUM_CHILDREN)-1))
			{
				bool areAllSame = _doAllSilhouetteFaceTheSame(silhouetteIndices);

				if (areAllSame)
				{
					_storeEdgeIsAlwaysSilhouette(parent, silhouetteIndices[0]);
					silhouetteMask = 0;
				}

				numPotential = 0;
			}
		}

		for(unsigned int i = 0; i<numPotential; ++i)
			_storeEdgeIsPotentiallySilhouette(potentialIndices[i], edgeIndex);

		if(silhouetteMask)
			for (unsigned int i = 0; i < OCTREE_NUM_CHILDREN; ++i)
			{
				if(silhouetteMask & (1 << i))
					_storeEdgeIsAlwaysSilhouette(startingID + i, silhouetteIndices[i]);
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

void OctreeVisitor::_storeEdgeIsAlwaysSilhouette(unsigned int nodeId, unsigned int augmentedEdgeIdWithResult)
{
	auto node = _octree->getNode(nodeId);

	assert(node != nullptr);

	node->edgesAlwaysCast.push_back(augmentedEdgeIdWithResult);
}

void OctreeVisitor::_storeEdgeIsPotentiallySilhouette(unsigned int nodeID, unsigned int edgeID)
{
	auto node = _octree->getNode(nodeID);

	assert(node != nullptr);

	node->edgesMayCast.push_back(edgeID);
}

void OctreeVisitor::processPotentialEdges()
{
	const unsigned int maxLevel = _octree->getDeepestLevel();

	_propagateEdgesUpFromLevel(maxLevel, true);
}

void OctreeVisitor::_propagateEdgesUpFromLevel(unsigned int startingLevel, bool propagatePotential)
{
	if (propagatePotential)
	{
		for (int i = startingLevel; i > 0; --i)
			_processEdgesInLevel(i, propagatePotential);
	}
	
	else
	{
		std::shared_ptr<GpuOctreeEdgePropagator> propagator = std::make_shared<GpuOctreeEdgePropagator>();

		propagator->init(_octree, 32);

		for (int i = startingLevel; i > 0; --i)
			propagator->propagateEdgesToUpperLevel(i, propagatePotential ? BufferType::POTENTIAL : BufferType::SILHOUETTE);

	}
	//*/
}

OctreeVisitor::TestResult OctreeVisitor::_haveAllSyblingsEdgeInCommon(unsigned int startingNodeID, unsigned int edgeID, bool propagatePotential) const
{	
	TestResult retval = TestResult::NON_EXISTING;
	
	for(unsigned int i=0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		const auto node = _octree->getNode(startingNodeID + i);
		
		if (!node)
			continue;

		if (propagatePotential)
		{
			if (!std::binary_search(node->edgesMayCast.begin(), node->edgesMayCast.end(), edgeID))
				return TestResult::FALSE;
		}
		else
			if (!std::binary_search(node->edgesAlwaysCast.begin(), node->edgesAlwaysCast.end(), edgeID))
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

	const unsigned int stopId = ipow(OCTREE_NUM_CHILDREN, level) + startingID;

	int currentID = startingID;

	#pragma omp parallel for
	for (currentID = startingID; currentID<stopId; currentID += OCTREE_NUM_CHILDREN)
	{
		auto firstNode = _octree->getNode(currentID);
		const auto edges = propagatePotential ? firstNode->edgesMayCast : firstNode->edgesAlwaysCast;

		if (!edges.empty())
		{
			for (const auto edge : edges)
			{
				auto result = _haveAllSyblingsEdgeInCommon(currentID, edge, propagatePotential);

				if (result == TestResult::TRUE)
				{
					_assignEdgeToNodeParent(currentID, edge, propagatePotential);
					_removeEdgeFromSyblings(currentID, edge, propagatePotential);
				}
			}
		}
	}
}

void OctreeVisitor::_removeEdgeFromSyblings(unsigned int startingID, unsigned int edge, bool propagatePotential)
{
	for(unsigned int i=0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		auto node = _octree->getNode(startingID + i);

		if (node)
		{
			if(propagatePotential)
				node->edgesMayCast.erase(std::lower_bound(node->edgesMayCast.begin(), node->edgesMayCast.end(), edge));
			else
				node->edgesAlwaysCast.erase(std::lower_bound(node->edgesAlwaysCast.begin(), node->edgesAlwaysCast.end(), edge));
		}
	}
}

void OctreeVisitor::_assignEdgeToNodeParent(unsigned int node, unsigned int edge, bool propagatePotential)
{
	const int parent = _octree->getNodeParent(node);

	assert(parent >= 0);

	auto n = _octree->getNode(parent);

	if (n)
	{
		if(propagatePotential)
			n->edgesMayCast.push_back(edge);
		else
			n->edgesAlwaysCast.push_back(edge);
	}
}

//NEVOLAT!
void OctreeVisitor::cleanEmptyNodes()
{
	/*const int startingID = _getFirstNodeIdInLevel(_octree->getDeepestLevel());
	const int bottomLevelSize = ipow(OCTREE_NUM_CHILDREN, _octree->getDeepestLevel());

	for(int i = startingID; i<(startingID + bottomLevelSize); ++i)
	{
		auto node = _octree->getNode(i);

		if (node && !node->edgesAlwaysCast.size() && !node->edgesMayCast.size())
			_octree->deleteNodeSubtree(i);
	}*/

	for(unsigned int level = _octree->getDeepestLevel(); level>0; --level)
	{
		_processEmptyNodesInLevel(level);
	}
}

void OctreeVisitor::_processEmptyNodesInLevel(unsigned int level)
{
	assert(level > 0);
	const int startingID = _octree->getLevelFirstNodeID(level);

	assert(startingID >= 0);

	const unsigned int stopId = ipow(OCTREE_NUM_CHILDREN, level) + startingID;

	unsigned int currentID = startingID;

	const unsigned int deepestLevel = _octree->getDeepestLevel();

	while (currentID < stopId)
	{
		_processEmptyNodesSyblingsParent(currentID);

		currentID += OCTREE_NUM_CHILDREN;
	}
}

void OctreeVisitor::_processEmptyNodesSyblingsParent(unsigned int first)
{
	unsigned int numRemoved = 0;
	
	for(unsigned int i=0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		auto node = _octree->getNode(first + i);

		if(node && !node->edgesMayCast.size() && !node->edgesAlwaysCast.size())
		{
			_octree->deleteNode(first + i);
			++numRemoved;
		}
		else
			++numRemoved;
	}

	if(numRemoved==OCTREE_NUM_CHILDREN)
	{
		const int parentID = _octree->getNodeParent(first);
		auto parent = _octree->getNode(parentID);

		if (parent && !parent->edgesMayCast.size() && !parent->edgesAlwaysCast.size())
			_octree->deleteNode(parentID);
	}
}

void OctreeVisitor::_expandWholeOctree()
{
	std::stack<unsigned int> nodeStack;
	
	nodeStack.push(0);

	const int deepestLevel = _octree->getDeepestLevel();

	while(!nodeStack.empty())
	{
		const auto node = nodeStack.top();
		nodeStack.pop();

		_octree->splitNode(node);

		const auto level = _octree->getNodeRecursionLevel(node);

		if (level < (deepestLevel-1))
		{
			const auto startingChild = _octree->getChildrenStartingId(node);
			for (int i = 0; i < OCTREE_NUM_CHILDREN; ++i)
				nodeStack.push(startingChild + i);
		}
	}

	_octree->makeNodesFit();
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

void OctreeVisitor::getSilhouttePotentialEdgesFromNodeUp(std::vector<unsigned int>& potential, std::vector<unsigned int>& silhouette, unsigned int nodeID) const
{
	int currentNodeID = nodeID;

	static bool printOnce = false;

	while(currentNodeID>=0)
	{
		const auto node = _octree->getNode(currentNodeID);

		assert(node != nullptr);

		silhouette.insert(silhouette.end(), node->edgesAlwaysCast.begin(), node->edgesAlwaysCast.end());
		potential.insert(potential.end(), node->edgesMayCast.begin(), node->edgesMayCast.end());

		if(!printOnce)
			std::cout << "Getting " << node->edgesAlwaysCast.size() << " silhouette and " << node->edgesMayCast.size() << " potential from node " << currentNodeID << std::endl;

		currentNodeID = _octree->getNodeParent(currentNodeID);
	}

	printOnce = true;
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

		std::sort(n->edgesAlwaysCast.begin(), n->edgesAlwaysCast.end());
		std::sort(n->edgesMayCast.begin(), n->edgesMayCast.end());
	}
}

void OctreeVisitor::_shrinkOctree()
{
	const auto numNodes = _octree->getTotalNumNodes();

	#pragma omp parallel for
	for(int i = 0; i<numNodes; ++i)
	{
		auto node = _octree->getNode(i);

		if(node)
		{
			node->edgesAlwaysCast.shrink_to_fit();
			node->edgesMayCast.shrink_to_fit();
		}
	}
}