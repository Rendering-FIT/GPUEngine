#pragma once

#include <glm/glm.hpp>

struct Material
{
	glm::vec4 ambientColor;
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	int32_t textureIndex;
	float shininess;
	float alignment1, alignment2;
};