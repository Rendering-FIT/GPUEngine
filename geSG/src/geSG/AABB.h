#pragma once

#include <geSG/BoundingVolume.h>
#include <geSG/Export.h>
#include <glm/glm.hpp>

namespace std
{
   template<class _Ty, size_t _Size> class array;
}

namespace ge
{
   namespace sg
   {
      class GESG_EXPORT AABB : public BoundingVolume
      {
      public:
         AABB();

         AABB(const AABB& other);

         void expand(const glm::vec3& p);
         void expand(const std::array<float,3>& p);

         void expand(const AABB& aabb);

         glm::vec3 min;
         glm::vec3 max;
      };

      template<typename Insides>
      class AABBTemplate : public AABB
      {
      public:
         AABBTemplate()
            :AABB()
         {}

         AABBTemplate(const AABBTemplate& other)
            : AABB(other)
            , insideThing(other.insideThing)
         {}

         Insides insideThing;
      };
   }
}