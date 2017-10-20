#pragma once

#include  <glm/glm.hpp>

namespace ge
{
   namespace util
   {
      struct Ray
      {
         //Ray(){}

         glm::vec3 origin;
         glm::vec3 direction;
      };
   }
}
