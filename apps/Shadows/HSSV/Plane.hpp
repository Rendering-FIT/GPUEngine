#pragma once

#include <glm/glm.hpp>

struct Plane
{
	glm::vec4 equation;

	void createFromPointsCCW(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3);
	void createFromPointNormalCCW(const glm::vec3& point, const glm::vec3& normal);
	void toHessianNormalForm();
};