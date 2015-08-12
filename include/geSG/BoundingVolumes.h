#pragma once
//#include <geSG/Export.h>

#include <geUtil/Ray.h>

#include <glm/glm.hpp>
#include <memory>
#include <algorithm>

namespace ge
{
   namespace sg
   {
      class BoundingVolume
      {
      public:
      };

      class BoundingSphere : public BoundingVolume
      {
      public:
          BoundingSphere()
             : center(glm::vec3())
             , radius(0.0f)
          {}

          BoundingSphere( const BoundingSphere& other)
             : center(other.center)
             , radius(other.radius)
          {}

          /*virtual bool RayIntersect(ge::util::Ray ray)
          {
             float r2 = this->radius * this->radius;
             float a = glm::dot(ray.direction, ray.direction);
             float  b = 2 * glm::dot(ray.direction, (ray.origin - this->center));
             float  c = glm::dot((ray.origin - this->center), (ray.origin - this->center)) - r2;
             float  D = b * b - 4 * a * c;
             float t1 = 0.0f;
             float t2;
             if(D < 0.0f) return false;
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
          }*/

          void transform(const glm::mat4& mat)
          {
             glm::vec4 pos(this->center, 1.0f);
             pos = mat * pos;
             glm::vec4 x(1, 0, 0, 0), y(0, 1, 0, 0), z(0, 0, 1, 0);
             x = mat * x;
             y = mat * y;
             z = mat * z;
             float maxScale = 0.0f;
             float lx = glm::length(x);
             float ly = glm::length(y);
             float lz = glm::length(z);
             maxScale = std::max(lx, ly);
             maxScale = std::max(maxScale, lz);
             this->center = glm::vec3(pos);
             this->radius *= maxScale;
          }

          /*void expand(const BoundingSphere& bs)
          {
             glm::vec3 newCenter = (bs.center + this->center) / 2.0f;
             float rad1 = glm::distance(newCenter, this->center) + this->radius;
             float rad2 = glm::distance(newCenter, bs.center) + bs.radius;

             this->center = newCenter;
             this->radius = rad1 > rad2 ? rad1 : rad2;
          }*/

          /**
           * Probably doesn't work yet.
           */
          template<template <typename...> class BSContainer >
          void expand(const BSContainer<std::shared_ptr<BoundingSphere>>& container)
          {
             glm::vec3 newCenter = this->center;
             float newRadius = 0.0f;

             //compute new center
             for(auto BS : container)
             {
                newCenter += (*BS).center;
             }

             newCenter /= container.size()+1;
             newRadius = glm::distance(newCenter, this->center) + this->radius;

             for(auto BS : container)
             {
                float rad = glm::distance(newCenter, BS->center) + BS->radius;
                this->radius = newRadius >= rad ? newCenter : rad;
             }
          }


          glm::vec3 center;
          float radius;
      };

      template<typename Insides>
      class BoundingSphereTemplate : public BoundingSphere
      {
      public:
         BoundingSphereTemplate()
            : BoundingSphere()
         {}

         BoundingSphereTemplate(std::shared_ptr<Insides> & insides)
            : BoundingSphere()
            , insideThing(insides)
         {}

         BoundingSphereTemplate(const BoundingSphereTemplate& other)
            : BoundingSphere(other)
            , insideThing(other.insideThing)
         {}

         std::shared_ptr<Insides> insideThing;
      };
   }
}