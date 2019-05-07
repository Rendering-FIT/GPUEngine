#pragma once

#include <geSG/Export.h>
#include <geSG/Intersector.h>
#include <geSG/Ray.h>

namespace ge{
   namespace sg
   {
      struct Triangle;
   

      /**
       * Computes ray triangle intersection with Muller-Trumbore algorithm. The epsilon
       * is set to 1e-6.
       */
      struct GESG_EXPORT RayTriangleIntersector : public Intersector
      {
         //static bool intersects(const Ray & ray, const glm::vec3 & v0, const glm::vec3 & v1, const glm::vec3 & v2);
         static bool intersects(const Ray & ray, const ge::sg::Triangle& triag);
         static float computeIntersection(const Ray & ray, const Triangle& triag);

         virtual bool intersects() const override;

         Ray ray;
         glm::vec3 v0, v1, v2;
      };
   }
}
