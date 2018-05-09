#include <geSG/RayAABBIntersector.h>
#include <geSG/AABB.h>
#include <algorithm>

using namespace ge::sg;
using namespace ge::util;

bool RayAABBIntersector::intersects(const Ray& ray, const AABB* aabb)
{
   if(!aabb) return false;

   float tmin = -INFINITY;
   float tmax = INFINITY;

   glm::vec3 dir_inv(1.f / ray.direction.x, 1.f / ray.direction.y, 1.f / ray.direction.z);

   for (int i = 0; i < 3; ++i)
   {
      float t1 = (aabb->min[i] - ray.origin[i]) * dir_inv[i];
      float t2 = (aabb->max[i] - ray.origin[i]) * dir_inv[i];

      tmin = std::max(tmin, std::min(t1, t2));
      tmax = std::min(tmax, std::max(t1, t2));
   }

   return tmax > std::max(tmin, 0.0f);
}

bool RayAABBIntersector::intersects() const
{
   return intersects(ray, aabb.get());
}
