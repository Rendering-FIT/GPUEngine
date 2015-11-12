#pragma once
#include <glm/detail/type_vec4.hpp>
#include <glm/detail/type_vec3.hpp>

namespace ge
{
   namespace sg
   {
      /**
       * Holds information about the point or directional light. The usage is up to the user.
       * You can put it into a scene graph and make a visualisation technique that will lit only
       * the scene beyond the light node. You can make VT that takes light and uses it as gloabal
       * sun light or headlight.
       */
      struct Light
      {
         glm::vec4 position; ///< Position in homogenous coords. Set w to 0 to have directional light. The semantic is position so (1,0,0,0) means light shines at direction (-1,0,0,0).
         glm::vec4 color; ///< light intensity in RGBA (the A could be used as user sees fit)
      };

      struct SpotLight : public Light
      {
         glm::vec3 direction; ///< direction of the center of the spot light
         float angle; ///< angle in radians
      };
   }
}