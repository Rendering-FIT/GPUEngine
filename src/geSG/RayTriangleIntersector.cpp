#include <geSG//RayTriangleIntersector.h>
#include <geSG//MeshPrimitiveIterator.h>
#include <glm/glm.hpp>

using namespace ge::util;
using namespace ge::sg;
using namespace glm;

/**
 * Not implemented yet. Use the static version.
 */
bool RayTriangleIntersector::intersects() const
{
   return false;
}

/**
 * Returns true if ray intersects the triangle, false otherwise. Implements
 * Muller-Trumbore algorithm.The algorithm has epsilon defined as 1e-6.
 * Bear in mind that this could be a source of future problems.
 */
bool RayTriangleIntersector::intersects(const Ray & ray, ge::sg::Triangle& triag)
{
   const float eps = 0.000001f;
   vec3& v0 = *reinterpret_cast<vec3*>(triag.v0);
   vec3& v1 = *reinterpret_cast<vec3*>(triag.v1);
   vec3& v2 = *reinterpret_cast<vec3*>(triag.v2);

   vec3 e0 = v1 - v0;
   vec3 e1 = v2 - v0;
   vec3 p = cross(ray.direction, e1);
   float det = dot(e0, p);

   if (det > -eps && det < eps)
   {
      return false;
   }

   float inv_det = 1.0f / det;
   vec3 r = ray.origin - v0;
   float u = dot(r, p)*inv_det;

   if (u<0.0f || u>1.0f)
   {
      return false;
   }

   vec3 q = cross(r, e0);
   float v = dot(ray.direction, q)*inv_det;

   if(v < 0.0f || u + v > 1.0f)
   {
      return false;
   }

   float t = dot(e1, q)*inv_det;
   if (t > eps)
   {
      return true;
   }

   return false;
}

/**
 * Returns parameter t  - distance along the ray (if ray direction is normalized)
 * in place of intersection. Returns FLT_MAX if the ray doesn't intersects the triangle.
 * Implements the Muller-Trumbore algorithm. The algorithm has epsilon defined as 1e-6.
 * Bear in mind that this could be a source of future problems.
 */
float RayTriangleIntersector::computeIntersection(const Ray & ray, Triangle& triag)
{
   const float eps = 0.000001f;
   vec3& v0 = *reinterpret_cast<vec3*>(triag.v0);
   vec3& v1 = *reinterpret_cast<vec3*>(triag.v1);
   vec3& v2 = *reinterpret_cast<vec3*>(triag.v2);

   vec3 e0 = v1 - v0;
   vec3 e1 = v2 - v0;
   vec3 p = cross(ray.direction, e1);
   float det = dot(e0, p);

   if(det > -eps && det < eps)
   {
      return FLT_MAX;
   }

   float inv_det = 1.0f / det;
   vec3 r = ray.origin - v0;
   float u = dot(r, p)*inv_det;

   if(u<0.0f || u>1.0f)
   {
      return FLT_MAX;
   }

   vec3 q = cross(r, e0);
   float v = dot(ray.direction, q)*inv_det;

   if(v < 0.0f || u + v > 1.0f)
   {
      return FLT_MAX;
   }

   float t = dot(e1, q)*inv_det;
   if(t > eps)
   {
      return t;
   }

   return FLT_MAX;
}

