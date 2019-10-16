#pragma once

#include <geSG/Export.h>
#include <geSG/Intersector.h>
#include <geSG/Ray.h>
#include <memory>


namespace ge
{
   namespace sg
   {
      class AABB;

      /**
      * Computes intersection for triangle mesh. Currently supports only
      * mesh represented by indexed/non-indexed structure of plain triangles.
      * No strips, fans etc.
      */
      struct GESG_EXPORT RayAABBIntersector : public Intersector
      {
         //static bool intersects(const Ray & ray, const glm::vec3 & v0, const glm::vec3 & v1, const glm::vec3 & v2);
         static bool intersects(const Ray & ray, const AABB* aabb);
         //static float computeIntersection(const util::Ray & ray, sg::AABB& mesh);

         virtual bool intersects() const override;

         Ray ray;
         std::shared_ptr<sg::AABB> aabb;
      };
   }
}