#include <geSG/BoundingVolume.h>

namespace ge
{
   namespace sg
   {
      class AABB : public BoundingVolume
      {
      public:
         AABB();

         AABB(const AABB& other);

         void expand(const glm::vec3& p);

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