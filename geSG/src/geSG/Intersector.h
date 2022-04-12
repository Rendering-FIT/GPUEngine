#pragma once

namespace ge
{
   namespace sg
   {
      struct  Intersector
      {
         virtual bool intersects() const = 0;
      };
   }
}
