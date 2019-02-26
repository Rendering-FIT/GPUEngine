#pragma once

#include "../FastAdjacency.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

using AdjacencyType = std::shared_ptr<const Adjacency>;

inline const float* getVertex3v(AdjacencyType ad, size_t vertexID)
{
	return ad->getVertices() + vertexID;
}

inline const glm::vec3& getEdgeVertexLow(AdjacencyType ad, size_t edgeId)
{
	return *(reinterpret_cast<const glm::vec3*>(ad->getVertices() + ad->getEdgeVertexA(edgeId)));
}

inline const glm::vec3& getEdgeVertexHigh(AdjacencyType ad, size_t edgeId)
{
	return *(reinterpret_cast<const glm::vec3*>(ad->getVertices() + ad->getEdgeVertexB(edgeId)));
}

inline size_t getNofOppositeVertices(AdjacencyType ad, size_t edgeId)
{
	return ad->getNofOpposite(edgeId);
}

inline const glm::vec3& getOppositeVertex(AdjacencyType ad, size_t edgeId, size_t oppositeVertexID)
{
	return *(reinterpret_cast<const glm::vec3*>(getVertex3v(ad, ad->getOpposite(edgeId, oppositeVertexID))));
}

inline void getEdgeOppositeVertices(AdjacencyType ad, size_t edgeId, std::vector<glm::vec3>& vertices)
{
	const auto nofOpposite = getNofOppositeVertices(ad, edgeId);
	vertices.reserve(nofOpposite);

	for(uint32_t i = 0; i<nofOpposite; ++i)
		vertices.push_back(*(reinterpret_cast<const glm::vec3*>(ad->getVertices() + ad->getOpposite(edgeId, i))));
}

