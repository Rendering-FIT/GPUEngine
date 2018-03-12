#include "AABB.hpp"

AABB::AABB()
{
	//Initialize to +/- infinity
	float maxFloat = std::numeric_limits<float>::infinity();
	float minFloat = -std::numeric_limits<float>::infinity();

	_minPoint = glm::vec3(maxFloat, maxFloat, maxFloat);
	_maxPoint = glm::vec3(minFloat, minFloat, minFloat);

	_extentX = _extentY = _extentZ = 0;
}

AABB::AABB(const glm::vec3& minPoint, const glm::vec3& maxPoint)
{
	setMinMaxPoints(minPoint, maxPoint);
}

AABB AABB::getInvalidAABB()
{
	return AABB();
}

bool AABB::isValid() const
{
	return !(_minPoint.x == std::numeric_limits<float>::infinity());
}

void AABB::setMinMaxPoints(const glm::vec3& minPoint, const glm::vec3& maxPoint)
{
	_minPoint = minPoint;
	_maxPoint = maxPoint;

	_updateExtents();
}

void AABB::updateWithTriangle(const glm::vec4* triangleVertices)
{
	_updateWithVertexInternal(triangleVertices[0]);
	_updateWithVertexInternal(triangleVertices[1]);
	_updateWithVertexInternal(triangleVertices[2]);

	_updateExtents();
}

void AABB::updateWithVertex(const glm::vec3& vertex)
{
	_updateWithVertexInternal(vertex);

	_updateExtents();
}

void AABB::updateWithVertex(const glm::vec4& vertex)
{
	_updateWithVertexInternal(vertex);

	_updateExtents();
}

void AABB::updateWithAABB(const AABB& bbox)
{
	_updateWithVertexInternal(bbox._minPoint);
	_updateWithVertexInternal(bbox._maxPoint);

	_updateExtents();
}

void AABB::getTransformedAABB(const glm::mat4 matrix, AABB& newBB) const
{
	glm::vec3 points[8];
	getAllVertices(points);

	points[0] = glm::vec3(matrix * glm::vec4(points[0], 1.0f));
	points[1] = glm::vec3(matrix * glm::vec4(points[1], 1.0f));
	points[2] = glm::vec3(matrix * glm::vec4(points[2], 1.0f));
	points[3] = glm::vec3(matrix * glm::vec4(points[3], 1.0f));
	points[4] = glm::vec3(matrix * glm::vec4(points[4], 1.0f));
	points[5] = glm::vec3(matrix * glm::vec4(points[5], 1.0f));
	points[6] = glm::vec3(matrix * glm::vec4(points[6], 1.0f));
	points[7] = glm::vec3(matrix * glm::vec4(points[7], 1.0f));

	newBB = AABB();
	newBB._updateWithVertexInternal(points[0]);
	newBB._updateWithVertexInternal(points[1]);
	newBB._updateWithVertexInternal(points[2]);
	newBB._updateWithVertexInternal(points[3]);
	newBB._updateWithVertexInternal(points[4]);
	newBB._updateWithVertexInternal(points[5]);
	newBB._updateWithVertexInternal(points[6]);
	newBB._updateWithVertexInternal(points[7]);

	newBB._updateExtents();
}

void AABB::getAllVertices(glm::vec3(&points)[8]) const
{
	points[0] = _minPoint;
	points[1] = glm::vec3(_minPoint.x + _extentX, _minPoint.y, _minPoint.z);
	points[2] = glm::vec3(_minPoint.x, _minPoint.y, _minPoint.z + _extentZ);
	points[3] = glm::vec3(_minPoint.x + _extentX, _minPoint.y, _minPoint.z + _extentZ);

	points[4] = glm::vec3(_minPoint.x, _minPoint.y + _extentY, _minPoint.z);
	points[5] = glm::vec3(_minPoint.x + _extentX, _minPoint.y + _extentY, _minPoint.z);
	points[6] = glm::vec3(_minPoint.x, _minPoint.y + _extentY, _minPoint.z + _extentZ);
	points[7] = _maxPoint;
}

void AABB::getExtents(float& x, float& y, float& z) const
{
	x = _extentX;
	y = _extentY;
	z = _extentZ;
}

glm::vec3 AABB::getMinPoint() const
{
	return _minPoint;
}

glm::vec3 AABB::getMaxPoint() const
{
	return _maxPoint;
}

glm::vec3 AABB::getCenterPoint() const
{
	return glm::vec3(_minPoint + glm::vec3(_extentX / 2, _extentY / 2, _extentZ / 2));
}

void AABB::applyTransform(const glm::mat4& matrix)
{
	AABB b;
	getTransformedAABB(matrix, b);

	_minPoint = b._minPoint;
	_maxPoint = b._maxPoint;

	_extentX = b._extentX;
	_extentY = b._extentY;
	_extentZ = b._extentZ;
}

void AABB::_updateExtents()
{
	_extentX = _maxPoint.x - _minPoint.x;
	_extentY = _maxPoint.y - _minPoint.y;
	_extentZ = _maxPoint.z - _minPoint.z;
}

void AABB::_updateWithVertexInternal(const glm::vec4& vertex)
{
	_updateWithVertexInternal(glm::vec3(vertex));
}

void AABB::_updateWithVertexInternal(const glm::vec3& vertex)
{
	if (vertex.x < _minPoint.x)
		_minPoint.x = vertex.x;

	if (vertex.y < _minPoint.y)
		_minPoint.y = vertex.y;

	if (vertex.z < _minPoint.z)
		_minPoint.z = vertex.z;

	if (vertex.x > _maxPoint.x)
		_maxPoint.x = vertex.x;

	if (vertex.y > _maxPoint.y)
		_maxPoint.y = vertex.y;

	if (vertex.z > _maxPoint.z)
		_maxPoint.z = vertex.z;
}
