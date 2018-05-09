#pragma once

#include <geSG/BoundingVolume.h>
#include <geSG/Export.h>

#include <glm/glm.hpp>
#include <memory>

namespace ge
{
   namespace sg
   {
      /**
      * Class representing Bounding Sphere.
      */
      class GESG_EXPORT BoundingSphere : public BoundingVolume
      {
      public:
         BoundingSphere();

         BoundingSphere(const BoundingSphere& other);

         /**
         * Transforms the BS with transform matrix.
         *
         */
         void transform(const glm::mat4& mat);

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

            newCenter /= container.size() + 1;
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
      * @param Insides The type of the object this BS is bounding e.g. shared_ptr<MatrixTransform> or Mesh.
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

         Insides insideThing;
      };

   }
}