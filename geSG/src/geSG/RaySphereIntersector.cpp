#include <geSG/RaySphereIntersector.h>

#include <geSG/BoundingSphere.h>

using namespace ge::sg;

/**
* Tests ray-sphere intersection. Note that the ray.direction
* needs to be normalized!
*
* @return True if ray intersects the sphere.
*/
bool RaySphereIntersector::intersects(const Ray & ray, const ge::sg::BoundingSphere & bs)
{
   float r2 = bs.radius * bs.radius;
   glm::vec3 oc = (ray.origin - bs.center);
   float b = glm::dot(ray.direction, oc);
   float c = glm::dot(oc, oc) - r2;

   b *= 2;
   float D = b * b - 4 * c;
   if(D < 0.0f) return false;
   D = (float)sqrt(D);
   if(-0.5 * (b + D) > 0) return true;
   if(-0.5 * (b - D) > 0) return true;
   return false;
}

float RaySphereIntersector::computeIntersection(const Ray& ray, ge::sg::BoundingSphere bs)
{
   float r2 = bs.radius * bs.radius;
   float a = glm::dot(ray.direction, ray.direction);
   float b = 2 * glm::dot(ray.direction, (ray.origin - bs.center));
   float c = glm::dot((ray.origin - bs.center), (ray.origin - bs.center)) - r2;
   float D = b * b - 4 * a * c;

   float t1, t2;
   if(D < 0.0f) return -1.0f;
   else if(D == 0.0f)
   {
      t1 = (-b - sqrtf(D)) / (2 * a);
   }
   else
   {
      t1 = (-b - sqrtf(D)) / (2 * a);
      t2 = (-b + sqrtf(D)) / (2 * a);
      t1 = t1 < t2 ? t1 : t2;
   }

   return t1;
}

bool RaySphereIntersector::intersects() const
{
   return intersects(ray, *bs);
}