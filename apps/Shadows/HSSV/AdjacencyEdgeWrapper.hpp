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

inline void getEdgeVertices(AdjacencyType ad, size_t edgeId, glm::vec3& v1, glm::vec3& v2)
{
	v1 = glm::make_vec3(ad->getVertices() + ad->getEdgeVertexA(edgeId));
	v2 = glm::make_vec3(ad->getVertices() + ad->getEdgeVertexB(edgeId));
}

inline size_t getNofOppositeVertices(AdjacencyType ad, size_t edgeId)
{
	return ad->getNofOpposite(edgeId);
}

inline glm::vec3 getOppositeVertex(AdjacencyType ad, size_t edgeId, size_t oppositeVertexID)
{
	return glm::make_vec3(getVertex3v(ad, ad->getOpposite(edgeId, oppositeVertexID)));
}

inline void getEdgeOppositeVertices(AdjacencyType ad, size_t edgeId, std::vector<glm::vec3>& vertices)
{
	const auto nofOpposite = getNofOppositeVertices(ad, edgeId);
	vertices.reserve(nofOpposite);

	for(unsigned int i = 0; i<nofOpposite; ++i)
		vertices.push_back(glm::make_vec3(ad->getVertices() + ad->getOpposite(edgeId, i)));
}

