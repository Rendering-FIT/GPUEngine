#pragma once

#include <geSG/Export.h>
#include <geSG/Intersector.h>
#include <geSG/Ray.h>
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
      struct GESG_EXPORT RayMeshIntersector : public Intersector
      {
         //static bool intersects(const Ray & ray, const glm::vec3 & v0, const glm::vec3 & v1, const glm::vec3 & v2);
         static bool intersects(const Ray & ray, sg::Mesh& mesh);
         static float computeIntersection(const Ray & ray, sg::Mesh& mesh);

         virtual bool intersects() const override;

         Ray ray;
         std::shared_ptr<sg::Mesh> mesh;
      };
   }
}