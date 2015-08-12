#include <geUtil/Intersectors.h>

bool ge::util::RaySphereIntersector::intersects(const Ray & ray, const ge::sg::BoundingSphere & bs)
{
   float r2 = bs.radius * bs.radius;
   float a = glm::dot(ray.direction, ray.direction);
   float  b = 2 * glm::dot(ray.direction, (ray.origin - bs.center));
   float  c = glm::dot((ray.origin - bs.center), (ray.origin - bs.center)) - r2;
   float  D = b * b - 4 * a * c;
   float t1 = 0.0f;
   float t2;
   if(D < 0.0f) return false;
   return true;
}

float ge::util::RaySphereIntersector::computeIntersection(Ray ray, ge::sg::BoundingSphere bs)
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
      t1 = (-b - sqrt(D)) / (2 * a);
   }
   else
   {
      t1 = (-b - sqrt(D)) / (2 * a);
      t2 = (-b + sqrt(D)) / (2 * a);
      t1 = t1 < t2 ? t1 : t2;
   }

   return t1;
}

bool ge::util::RaySphereIntersector::intersects()
{
   return intersects(ray, *bs);
}