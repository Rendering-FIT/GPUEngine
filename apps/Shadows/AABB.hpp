#pragma once

#include <glm/glm.hpp>


//Axis-aligned bounding box
struct AABB
{
	AABB();
	AABB(const glm::vec3& minPoint, const glm::vec3& maxPoint);

	void setMinMaxPoints(const glm::vec3& minPoint, const glm::vec3& maxPoint);
	
	glm::vec3 getMinPoint() const;
	glm::vec3 getMaxPoint() const;
	glm::vec3 getCenterPoint() const;

	static AABB getInvalidAABB();

	void updateWithTriangle(const glm::vec4* triangleVertices);

	void updateWithVertex(const glm::vec3& vertex);

	void updateWithVertex(const glm::vec4& vertex);

	void updateWithAABB(const AABB& bbox);

	void getTransformedAABB(const glm::mat4 matrix, AABB& newBB) const;

	void getAllVertices(glm::vec3(&points)[8]) const;

	void getExtents(float& x, float& y, float& z) const;

	void applyTransform(const glm::mat4& matrix);

	bool isValid() const;

private:

	void _updateExtents();

	void _updateWithVertexInternal(const glm::vec4& vertex);

	void _updateWithVertexInternal(const glm::vec3& vertex);

	float _extentX;
	float _extentY;
	float _extentZ;

	glm::vec3 _minPoint;
	glm::vec3 _maxPoint;
};