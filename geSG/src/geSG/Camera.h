#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace ge
{
	namespace sg
	{
		struct Camera
		{
			glm::vec4 position;
			glm::vec3 direction;
			glm::vec3 up;

			float aspectRatio;
			float horizontalFOV; ///< in radians

			float nearPlane;
			float farPlane;
		};
	}
}