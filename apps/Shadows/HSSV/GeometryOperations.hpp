#pragma once

#include "AABB.hpp"
#include "Plane.hpp"
#include "AdjacencyEdgeWrapper.hpp"

#include <vector>


enum class EdgeSilhouetness : int
{
	EDGE_NOT_SILHOUETTE = 0,
	EDGE_POTENTIALLY_SILHOUETTE = 1,
	EDGE_IS_SILHOUETTE_PLUS = 2,
	EDGE_IS_SILHOUETTE_MINUS = 3
};

#define EDGE_IS_SILHOUETTE(sihlouettness) (int(sihlouettness) >= 2)

enum class TestResult : int
{
	ABOVE_OUTSIDE = 1,
	BELOW_INSIDE = -1,
	INTERSECTS_ON = 0
};

namespace GeometryOps
{
	inline bool isInRange(float value, float min, float max)
	{
		return value >= min && value <= max;
	}
	
	inline float testPlanePoint(const Plane& plane, const glm::vec3& point)
	{
		return plane.equation.x*point.x + plane.equation.y*point.y + plane.equation.z*point.z + plane.equation.w;
	}

	inline bool testAabbPointIsInsideOrOn(const AABB& bbox, const glm::vec3& point)
	{
		const auto minPoint = bbox.getMinPoint();
		const auto maxPoint = bbox.getMaxPoint();

		return isInRange(point.x, minPoint.x, maxPoint.x) & isInRange(point.y, minPoint.y, maxPoint.y) & isInRange(point.z, minPoint.z, maxPoint.z);
	}

	inline TestResult interpretResult(float result)
	{
		TestResult r = TestResult::INTERSECTS_ON;

		if (result > 0)
			r = TestResult::ABOVE_OUTSIDE;
		else if (result < 0)
			r = TestResult::BELOW_INSIDE;

		return r;
	}

	inline TestResult testAabbPlane(const AABB& bbox, const Plane& plane)
	{
		glm::vec3 points[8];
		bbox.getAllVertices(points);

		const TestResult result = interpretResult(testPlanePoint(plane, points[0]));

		for (unsigned int i = 1; i < 8; ++i)
		{
			TestResult r = interpretResult(testPlanePoint(plane, points[i]));

			if (r != result)
				return TestResult::INTERSECTS_ON;
		}

		return result;
	}

	inline int greaterVec(const glm::vec3& a, const glm::vec3& b)
	{
		return int(glm::dot(glm::vec3(glm::sign(a - b)), glm::vec3(4, 2, 1)));
	}

	inline int computeMult(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec4& L) 
	{
		glm::vec3 n = glm::cross(C - A, glm::vec3(L) - A*L.w);
		return int(glm::sign(dot(n, B - A)));
	}

	inline int currentMultiplicity(const glm::vec3& A, const glm::vec3& B, const glm::vec3& O, const glm::vec4& L) 
	{
		if (greaterVec(A, O)>0)
			return computeMult(O, A, B, L);
		else if (greaterVec(B, O)>0)
			return -computeMult(A, O, B, L);
		else
			return computeMult(A, B, O, L);
	}

	inline int calcEdgeMultiplicity(AdjacencyType edges, size_t edgeIndex, const glm::vec3& lightPos)
	{
		glm::vec3 lowerPoint, higherPoint;
		getEdgeVertices(edges, edgeIndex, lowerPoint, higherPoint);

		const size_t nofOpposites = getNofOppositeVertices(edges, edgeIndex);
		int multiplicity = 0;
		const glm::vec4 L = glm::vec4(lightPos, 1);

		for (size_t i = 0; i<nofOpposites; ++i)
			multiplicity += currentMultiplicity(lowerPoint, higherPoint, getOppositeVertex(edges, edgeIndex, i), L);

		return multiplicity;
	}

	inline EdgeSilhouetness testEdgeSpaceAabb(const Plane& p1, const Plane& p2, AdjacencyType edges, size_t edgeIndex, const AABB& voxel)
	{
		auto result1 = testAabbPlane(voxel, p1);
		auto result2 = testAabbPlane(voxel, p2);

		EdgeSilhouetness result = EdgeSilhouetness::EDGE_NOT_SILHOUETTE;

		if (result1 == TestResult::INTERSECTS_ON || result2 == TestResult::INTERSECTS_ON)
			result = EdgeSilhouetness::EDGE_POTENTIALLY_SILHOUETTE;
		else
		{
			int multiplicity = calcEdgeMultiplicity(edges, edgeIndex, voxel.getMinPoint());

			if (multiplicity > 0)
				result = EdgeSilhouetness::EDGE_IS_SILHOUETTE_PLUS;
			else if (multiplicity < 0)
				result = EdgeSilhouetness::EDGE_IS_SILHOUETTE_MINUS;
		}

		return result;
	}
};