#include <geSG/AABB.h>

using namespace ge::sg;

AABB::AABB()
{
}

AABB::AABB(const AABB& other): min(other.min)
                               , max(other.max)
{
}

void AABB::expand(const glm::vec3& p)
{
   min.x = min.x <= p.x ? min.x : p.x;
   min.y = min.y <= p.y ? min.y : p.y;
   min.z = min.z <= p.z ? min.z : p.z;

   max.x = max.x >= p.x ? max.x : p.x;
   max.y = max.y >= p.y ? max.y : p.y;
   max.z = max.z >= p.z ? max.z : p.z;
}

void AABB::expand(const AABB& aabb)
{
   min.x = min.x <= aabb.min.x ? min.x : aabb.min.x;
   min.y = min.y <= aabb.min.y ? min.y : aabb.min.y;
   min.z = min.z <= aabb.min.z ? min.z : aabb.min.z;

   max.x = max.x >= aabb.max.x ? max.x : aabb.max.x;
   max.y = max.y >= aabb.max.y ? max.y : aabb.max.y;
   max.z = max.z >= aabb.max.z ? max.z : aabb.max.z;
}
