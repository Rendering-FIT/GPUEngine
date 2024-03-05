#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace ge
{
   namespace sg
   {
      /**
       * Holds information about point lights and directional lights, serves as a base class for spotlights.
       */
      struct Light
      {
          glm::vec4 position; ///< position in homogenous coords, if w == 0, it is a directional light and the first three components contain its direction
          glm::vec4 color; ///< light intensity in RGBA (the A could be used as user sees fit)
      };

      struct SpotLight : public Light
      {
          glm::vec3 direction; ///< vector containing the direction of the center of the spotlight cone 
          float innerAngle; ///< inner angle (hot spot) in radians
          float outerAngle; ///< outer angle (falloff) in radians
      };
   }
}