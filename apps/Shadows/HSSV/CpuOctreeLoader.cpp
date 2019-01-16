#include "CpuOctreeLoader.hpp"
#include "HighResolutionTimer.hpp"
#include <omp.h>
#include <bitset>
#include "MultiplicityCoding.hpp"
#include "GeometryOperations.hpp"


bool CpuOctreeLoader::init(std::shared_ptr<Octree> octree, std::shared_ptr<GpuEdges> gpuEdges, unsigned int nofEdges)
{
	_octree = octree;

	return true;
}

void CpuOctreeLoader::addEdgesOnLowestLevel(AdjacencyType edges)
{
	std::cout << "NoF edges: " << edges->getNofEdges() << "\n";

	std::vector< std::vector<Plane> > edgePlanes;
	_generateEdgePlanes(edges, edgePlanes);

	HighResolutionTimer t;
	t.reset();
	_addEdgesOnLowestLevel(edgePlanes, edges);
	auto dt = t.getElapsedTimeFromLastQueryMilliseconds();

	std::cout << "Adding edges took " << dt / 1000.0f << " sec\n";
}

void CpuOctreeLoader::_generateEdgePlanes(const AdjacencyType edges, std::vector< std::vector<Plane> >& planes) const
{
	const auto numEdges = edges->getNofEdges();

	planes.resize(numEdges);

	unsigned int index = 0;

	for (size_t i = 0; i<numEdges; ++i)
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

void CpuOctreeLoader::_addEdgesOnLowestLevel(std::vector< std::vector<Plane> >& edgePlanes, const AdjacencyType edges)
{
	const int deepestLevel = _octree->getDeepestLevel();
	const int levelSize = ipow(OCTREE_NUM_CHILDREN, deepestLevel);

	const int startingIndex = _octree->getNumNodesInPreviousLevels(deepestLevel);
	const int stopIndex = _octree->getTotalNumNodes();

	std::cout << "Total iterations: " << (stopIndex - startingIndex) / OCTREE_NUM_CHILDREN << "\n";

#pragma omp parallel for
	for (int i = startingIndex; i < stopIndex; i += OCTREE_NUM_CHILDREN)
	{
		_addEdgesSyblingsParentCompress8(edgePlanes, edges, i);
	}
}

void CpuOctreeLoader::_addEdgesSyblingsParentCompress8(const std::vector< std::vector<Plane> >& edgePlanes, AdjacencyType edges, unsigned int startingID)
{
	unsigned int edgeIndex = 0;

	const int parent = _octree->getNodeParent(startingID);

	const size_t nofEdges = edges->getNofEdges();
	for (size_t edgeIndex = 0; edgeIndex < nofEdges; ++edgeIndex)
	{
		unsigned int numPotential = 0;

		std::bitset<8> potentialBitmask(0);
		std::unordered_map<int, std::bitset<8>> silhouetteBitmasks;

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
				if ((*sil).second.count()>3)
				{
					_storeEdgeIsAlwaysSilhouette(parent, (*sil).first, (*sil).second.to_ullong());
					silhouetteBitmasks.erase(sil++);
				}
				else
					++sil;
			}
		}

		for (unsigned int i = 0; i<numPotential; ++i)
			_storeEdgeIsPotentiallySilhouette(potentialIndices[i], unsigned int(edgeIndex), BitmaskAllSet);

		//Store each silhouette edge variant in leaves
		for (auto sil = silhouetteBitmasks.cbegin(); sil != silhouetteBitmasks.cend(); ++sil)
		{
			const auto count = sil->second.count();
			unsigned int currentPosition = 0;

			for (unsigned int i = 0; i<count; ++i)
			{
				while (!sil->second[currentPosition]) ++currentPosition;

				_storeEdgeIsAlwaysSilhouette(startingID + currentPosition, sil->first, BitmaskAllSet);
			}
		}
	}

	for (auto i = startingID; i<(startingID + OCTREE_NUM_CHILDREN); ++i)
	{
		auto node = _octree->getNode(i);

		if (node)
		{
			node->shrinkEdgeVectors();
			node->sortEdgeVectors();
		}
	}
}

bool CpuOctreeLoader::_doAllSilhouetteFaceTheSame(const int(&indices)[OCTREE_NUM_CHILDREN]) const
{
	const int first = indices[0];

	for (unsigned int i = 1; i<OCTREE_NUM_CHILDREN; ++i)
	{
		if (indices[i] != first)
			return false;
	}

	return true;
}

void CpuOctreeLoader::_storeEdgeIsAlwaysSilhouette(unsigned int nodeId, unsigned int augmentedEdgeIdWithResult, const BitmaskType subarrayIndex)
{
	auto node = _octree->getNode(nodeId);

	assert(node != nullptr);

	node->edgesAlwaysCastMap[subarrayIndex].push_back(augmentedEdgeIdWithResult);
}

void CpuOctreeLoader::_storeEdgeIsPotentiallySilhouette(unsigned int nodeID, unsigned int edgeID, const BitmaskType subarrayIndex)
{
	auto node = _octree->getNode(nodeID);

	assert(node != nullptr);

	node->edgesMayCastMap[subarrayIndex].push_back(edgeID);
}
