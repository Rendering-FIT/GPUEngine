#pragma once

#include <geSG/Export.h>
#include <geUtil/Intersector.h>

#include <geUtil/Ray.h>
#include <geSG/BoundingVolume.h>
#include <memory>

namespace ge
{
   namespace sg
   {
      class BoundingSphere;

      struct GESG_EXPORT RaySphereIntersector : public ge::util::Intersector
      {
         static bool intersects(const ge::util::Ray & ray, const ge::sg::BoundingSphere & bs);
         static float computeIntersection(const ge::util::Ray& ray, ge::sg::BoundingSphere bs);

         virtual bool intersects() const override;

         ge::util::Ray ray;
         std::shared_ptr<ge::sg::BoundingSphere> bs;
      };
   }
}
