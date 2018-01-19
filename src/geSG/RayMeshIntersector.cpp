#include <geSG/RayMeshIntersector.h>
#include <geSG/RayTriangleIntersector.h>
#include <geSG/MeshPrimitiveIterator.h>

#include <functional>
#include <algorithm>
#include <numeric>
#include <cfloat>

#if defined(_DEBUG)
   #include <iostream>
   using namespace std;
#endif

using namespace ge::util;
using namespace ge::sg;
using namespace std;
using namespace std::placeholders;

/**
 * Not implemented, returns always false. Use the static methods.
 */
bool RayMeshIntersector::intersects() const
{
   return false;
}

/**
 * Returns true if the ray intersects any of the triangle of the mesh, false otherwise. 
 */
bool RayMeshIntersector::intersects(const Ray & ray, Mesh& mesh)
{
   if(mesh.primitive != Mesh::PrimitiveType::TRIANGLES)
   {
#if defined(_DEBUG)
      cout << "RayMeshIntersector supports Triangles ONLY!" << endl;
#endif
      return false;
   }

   return std::any_of(MeshPositionIteratorBegin(&mesh), MeshPositionIteratorEnd(&mesh), std::bind((bool(*)(const Ray &, ge::sg::Triangle&))RayTriangleIntersector::intersects, ray, _1));

   /**
    * the above line should implement the algorithm below
    */
   /*MeshIndexedTriangleIterator beg = MeshPositionIteratorBegin(&mesh);
   MeshIndexedTriangleIterator end = MeshPositionIteratorEnd(&mesh);
   MeshIndexedTriangleIterator it(beg);

   for(; it != end; ++it)
   {
      if(RayTriangleIntersector::intersects(ray, (*it)))
         return true;
   }

   return false;*/
}


/**
 * Returns minimal t found by testing ray with every triangle from mesh. If the
 * direction of the ray is normalized, then t is distance of the hit from the ray origin. It
 * is the multiplier of direction vector length. NOTE that the direction should ALWAYS be normalized.
 */
float RayMeshIntersector::computeIntersection(const Ray & ray, Mesh& mesh)
{
   if(mesh.primitive != Mesh::PrimitiveType::TRIANGLES)
   {
#if defined(_DEBUG)
      cout << "RayMeshIntersector supports Triangles ONLY!" << endl;
#endif
      return false;
   }

   MeshIndexedTriangleIterator beg = MeshPositionIteratorBegin(&mesh);
   MeshIndexedTriangleIterator end = MeshPositionIteratorEnd(&mesh);
   MeshIndexedTriangleIterator it(beg);

   /**
    * When c++17 is defined this is what it does -> whole function could be
    * done in a single transform reduce call. Provided that the above constructed
    * iterators and bind functor are constructed in the call.
    */
   /*
   auto intersectorOp = std::bind(RayTriangleIntersector::computeIntersection, ray, _1);
   std::transform_reduce(beg, end, intersectorOp, FLT_MAX, std::min);
   */


   float t_min = FLT_MAX;
   float hit;
   for(; it != end; ++it)
   {
      hit = RayTriangleIntersector::computeIntersection(ray, (*it));
      t_min = min(t_min, hit);
   }

   return t_min;
}
