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
      /**
       * Base class for general bounding volume.
       * Class is currently empty.
       */   

      class BoundingVolume
      {
      public:
         virtual void expand(const BoundingVolume* BV) = 0;
      };

      /**
       * Class representing Bounding Sphere.
       */
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

         /**
          * Transforms the BS with transform matrix.
          * 
          */
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
                this->radius = newRadius >= rad ? newRadius : rad;
             }
          }


          glm::vec3 center;
          float radius;
      };

      /**
       * Template Extension of BS.
       * 
       * @param Insides The type of the object this BS is bounding e.g. MatrixTransform or Mesh.
       */
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

      class AABB : public BoundingVolume
      {
      public:
         AABB(){}

         AABB(const AABB& other)
            : min(other.min)
            , max(other.max)
         {}

         void expand(const glm::vec3& p)
         {
            min.x = min.x <= p.x ? min.x : p.x;
            min.y = min.y <= p.y ? min.y : p.y;
            min.z = min.z <= p.z ? min.z : p.z;

            max.x = max.x >= p.x ? max.x : p.x;
            max.y = max.y >= p.y ? max.y : p.y;
            max.z = max.z >= p.z ? max.z : p.z;
         }

         void expand(const AABB& aabb)
         {
            min.x = min.x <= aabb.min.x ? min.x : aabb.min.x;
            min.y = min.y <= aabb.min.y ? min.y : aabb.min.y;
            min.z = min.z <= aabb.min.z ? min.z : aabb.min.z;

            max.x = max.x >= aabb.max.x ? max.x : aabb.max.x;
            max.y = max.y >= aabb.max.y ? max.y : aabb.max.y;
            max.z = max.z >= aabb.max.z ? max.z : aabb.max.z;
         }

      protected:
         glm::vec3 min;
         glm::vec3 max;
      };

      template<typename Inside>
      class AABBTemplate: public AABB
      {
      public:
         AABBTemplate()
            :AABB()
         {}

         AABBTemplate(const AABBTemplate& other)
            : AABB(other)
            , insideThing(other.insideThing)
         {}

         std::shared_ptr<Insides> insideThing;         
      };
   }//namesace sg
}//namespace ge
