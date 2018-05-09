#pragma once

#include <geSG/Export.h>
#include <geUtil/Intersector.h>
#include <geUtil/Ray.h>
#include <memory>


namespace ge
{
   namespace sg
   {
      class Mesh;
   
      /**
       * Computes intersection for triangle mesh. Currently supports only
       * mesh represented by indexed/non-indexed structure of plain triangles.
       * No strips, fans etc.
       */
      struct GESG_EXPORT RayMeshIntersector : public util::Intersector
      {
         //static bool intersects(const Ray & ray, const glm::vec3 & v0, const glm::vec3 & v1, const glm::vec3 & v2);
         static bool intersects(const util::Ray & ray, sg::Mesh& mesh);
         static float computeIntersection(const util::Ray & ray, sg::Mesh& mesh);

         virtual bool intersects() const override;

         util::Ray ray;
         std::shared_ptr<sg::Mesh> mesh;
      };
   }
}