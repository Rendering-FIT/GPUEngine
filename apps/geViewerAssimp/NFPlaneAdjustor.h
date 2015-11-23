#pragma once

#include <glm/glm.hpp>
#include <geSG/BoundingVolumes.h>

namespace fsg
{
   class NFPlaneAdjustor
   {
   public:
      NFPlaneAdjustor();

      std::pair<float, float> computeNearFar();

      std::shared_ptr<glm::mat4> viewMatrix;
      std::shared_ptr<ge::sg::BoundingSphere> bs;
      float minimumNear;
   };
}