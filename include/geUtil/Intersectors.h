#pragma once

#include <geUtil/Export.h>

#include <geUtil/Ray.h>
#include <geSG/BoundingVolumes.h>

namespace ge
{
   namespace util
   {
      struct Intersector
      {
         virtual bool intersects() = 0;

         virtual ~Intersector()
         {}
      };

      struct GEUTIL_EXPORT RaySphereIntersector : public Intersector
      {
         static bool intersects(const Ray & ray, const ge::sg::BoundingSphere & bs);
         static float computeIntersection(Ray ray, ge::sg::BoundingSphere bs);

         virtual bool intersects() override;

         Ray ray;
         std::shared_ptr<ge::sg::BoundingSphere> bs;
      };
   }
}