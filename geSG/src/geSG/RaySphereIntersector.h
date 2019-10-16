#pragma once

#include <geSG/Export.h>
#include <geSG/Intersector.h>

#include <geSG/Ray.h>
#include <geSG/BoundingVolume.h>
#include <memory>

namespace ge
{
   namespace sg
   {
      class BoundingSphere;

      struct GESG_EXPORT RaySphereIntersector : public Intersector
      {
         static bool intersects(const Ray & ray, const BoundingSphere & bs);
         static float computeIntersection(const Ray& ray, BoundingSphere bs);

         virtual bool intersects() const override;

         Ray ray;
         std::shared_ptr<BoundingSphere> bs;
      };
   }
}
