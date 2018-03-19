#include "OctreeVisitor.hpp"
#include "Plane.hpp"
#include "GeometryOperations.hpp"

#include <stack>
#include <iostream>

#include <omp.h>
#include "HighResolutionTimer.hpp"
#include "MultiplicityCoding.hpp"
#include "VoxelTestingShader.hpp"
#include "GpuOctreeLoader.hpp"

#include <geGL/Shader.h>


OctreeVisitor::OctreeVisitor(std::shared_ptr<Octree> octree)
{
	_octree = octree;
}

void OctreeVisitor::addEdges(const AdjacencyType edges)
{
	_expandWholeOctree();

	_getEdgesOneOpposite(edges, _octree->getNode(0)->edgesMayCast);

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
	_propagatePotentiallySilhouetteEdgesUpFromLevel(startingLevel);
	dt = t.getElapsedTimeFromLastQueryMilliseconds();

	std::cout << "Propagate Potential edges took " << dt / 1000.0f << " sec\n";
	t.reset();

	_propagateSilhouetteEdgesUpFromLevel(startingLevel);

	dt = t.getElapsedTimeFromLastQueryMilliseconds();

	std::cout << "Propagate Silhouette edges took " << dt / 1000.0f << " sec\n";
}

void OctreeVisitor::addEdgesGPU(const AdjacencyType edges)
{
	std::shared_ptr<GpuOctreeLoader> gpuLoader = std::make_shared<GpuOctreeLoader>();
	if (!gpuLoader->init(_octree))
	{
		std::cerr << "Failed to init GPU octree loader, switching to CPU (very slow)\n";
		addEdges(edges);
		return;
	}

	_expandWholeOctree();

	_getEdgesOneOpposite(edges, _octree->getNode(0)->edgesMayCast);

	HighResolutionTimer t;
	t.reset();

	gpuLoader->addEdgesOnLowestLevelGPU(edges);

	auto dt = t.getElapsedTimeFromLastQueryMilliseconds();

	std::cout << "Adding edges on GPU took " << dt / 1000.0f << " sec\n";
	t.reset();
	const auto startingLevel = _octree->getDeepestLevel() - 1;
	_propagatePotentiallySilhouetteEdgesUpFromLevel(startingLevel);
	dt = t.getElapsedTimeFromLastQueryMilliseconds();

	std::cout << "Propagate Potential edges took " << dt / 1000.0f << " sec\n";
	t.reset();

	_propagateSilhouetteEdgesUpFromLevel(startingLevel);

	dt = t.getElapsedTimeFromLastQueryMilliseconds();

	std::cout << "Propagate Silhouette edges took " << dt / 1000.0f << " sec\n";
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
		{
			//if (numOppositeVertices == 1 && parent >= 0)
			//	_storeEdgeIsPotentiallySilhouette(parent, edgeIndex);

			continue;
		}

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
			//node->sortEdgeVectors();
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

void OctreeVisitor::_storeEdgeIsAlwaysSilhouette(unsigned int nodeId, int augmentedEdgeIdWithResult)
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

	_propagatePotentiallySilhouetteEdgesUpFromLevel(maxLevel);
}

void OctreeVisitor::_propagatePotentiallySilhouetteEdgesUpFromLevel(unsigned int startingLevel)
{
	for(int i = startingLevel; i>0; --i)
		_processPotentialEdgesInLevel(i);
}

void OctreeVisitor::_propagateSilhouetteEdgesUpFromLevel(unsigned int startingLevel)
{
	for (int i = startingLevel; i > 0; --i)
		_processSilhouetteEdgesInLevel(i);
}

OctreeVisitor::TestResult OctreeVisitor::_haveAllSyblingsEdgeAsPotential(unsigned int startingNodeID, unsigned int edgeID) const
{	
	TestResult retval = TestResult::NON_EXISTING;
	
	for(unsigned int i=0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		const auto node = _octree->getNode(startingNodeID + i);
		
		if (!node)
			continue;

		if (std::find(node->edgesMayCast.begin(), node->edgesMayCast.end(), edgeID) == node->edgesMayCast.end())
			return TestResult::FALSE;
		
		retval = TestResult::TRUE;
	}

	return retval;
}

void OctreeVisitor::_processPotentialEdgesInLevel(unsigned int level)
{
	assert(level > 0);
	const int startingID = _octree->getLevelFirstNodeID(level);
	
	assert(startingID >= 0);

	const unsigned int stopId = ipow(OCTREE_NUM_CHILDREN, level) + startingID;

	int currentID = startingID;

	#pragma omp parallel for
	for (currentID = startingID; currentID<stopId; currentID += OCTREE_NUM_CHILDREN)
	{
		std::set<unsigned int> potentialEdgesSyblings;
		_getAllPotentialEdgesSyblings(currentID, potentialEdgesSyblings);

		for(auto edge : potentialEdgesSyblings)
		{
			auto result = _haveAllSyblingsEdgeAsPotential(currentID, edge);

			if (result == TestResult::TRUE)
			{
				_assignPotentialEdgeToNodeParent(currentID, edge);
				_removePotentialEdgeFromSyblings(currentID, edge);
			}
		}
	}
}

void OctreeVisitor::_processSilhouetteEdgesInLevel(unsigned int level)
{
	assert(level > 0);
	const int startingID = _octree->getLevelFirstNodeID(level);

	assert(startingID >= 0);

	const unsigned int stopId = ipow(OCTREE_NUM_CHILDREN, level) + startingID;

	int currentID = startingID;

	#pragma omp parallel for
	for (currentID = startingID; currentID<stopId; currentID += OCTREE_NUM_CHILDREN)
	{
		std::set<int> silhouetteEdgesSyblings;
		_getAllSilhouetteEdgesSyblings(currentID, silhouetteEdgesSyblings);

		for (auto edge : silhouetteEdgesSyblings)
		{
			auto result = _haveAllSyblingsEdgeAsPotential(currentID, edge);

			if (result == TestResult::TRUE)
			{
				_assignSilhouetteEdgeToNodeParent(currentID, edge);
				_removeSilhouetteEdgeFromSyblings(currentID, edge);
			}
		}
	}
}
/*
int	OctreeVisitor::_getFirstNodeIdInLevel(unsigned int level) const
{
	return _octree->getNumNodesInPreviousLevels(level);
}
*/
void OctreeVisitor::_getAllPotentialEdgesSyblings(unsigned int startingID, std::set<unsigned int>& edges) const
{
	for(unsigned int i=0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		const auto node = _octree->getNode(startingID + i);

		if(node!=nullptr)
			edges.insert(node->edgesMayCast.begin(), node->edgesMayCast.end());
	}
}

void OctreeVisitor::_getAllSilhouetteEdgesSyblings(unsigned int startingID, std::set<int>& edges) const
{
	for (unsigned int i = 0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		const auto node = _octree->getNode(startingID + i);

		if (node != nullptr)
			edges.insert(node->edgesAlwaysCast.begin(), node->edgesAlwaysCast.end());
	}
}

void OctreeVisitor::_removePotentialEdgeFromSyblings(unsigned int startingID, unsigned int edge)
{
	for(unsigned int i=0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		auto node = _octree->getNode(startingID + i);

		if(node)
			node->edgesMayCast.erase(std::find(node->edgesMayCast.begin(), node->edgesMayCast.end(), edge));
	}
}

void OctreeVisitor::_removeSilhouetteEdgeFromSyblings(unsigned int startingID, int edge)
{
	for (unsigned int i = 0; i<OCTREE_NUM_CHILDREN; ++i)
	{
		auto node = _octree->getNode(startingID + i);

		if (node)
			node->edgesAlwaysCast.erase(std::find(node->edgesAlwaysCast.begin(), node->edgesAlwaysCast.end(), edge));
	}
}

void OctreeVisitor::_assignPotentialEdgeToNodeParent(unsigned int node, unsigned int edge)
{
	const int parent = _octree->getNodeParent(node);

	assert(parent >= 0);

	auto n = _octree->getNode(parent);

	if (n)
		n->edgesMayCast.push_back(edge);
}

void OctreeVisitor::_assignSilhouetteEdgeToNodeParent(unsigned int node, int edge)
{
	const int parent = _octree->getNodeParent(node);

	assert(parent >= 0);

	auto n = _octree->getNode(parent);

	if (n)
		n->edgesAlwaysCast. push_back(edge);
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

void OctreeVisitor::getSilhouttePotentialEdgesFromNodeUp(std::vector<int>& potential, std::vector<int>& silhouette, unsigned int nodeID) const
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

void OctreeVisitor::_getEdgesOneOpposite(AdjacencyType edges, std::vector<unsigned int>& edgesWithSingleOV)
{
	const unsigned int nofEdges = edges->getNofEdges();

	for(unsigned int i=0; i<nofEdges; ++i)
	{
		const auto nofOpposite = edges->getNofOpposite(i);

		if (nofOpposite == 1)
			edgesWithSingleOV.push_back(i);
	}
}
