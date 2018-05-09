#pragma once

#include <glm/glm.hpp>
#include <geUtil/IntersectPrimitive.h>

namespace ge
{
   namespace util
   {
      struct Ray: public IntersectPrimitive
      {
         //Ray(){}

         glm::vec3 origin;
         glm::vec3 direction;
      };
   }
}
