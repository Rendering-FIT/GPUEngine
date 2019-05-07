#pragma once

#include <geSG/Export.h>

namespace ge
{
   namespace sg
   {
      struct /*GEUTIL_EXPORT*/ Intersector
      {
         virtual bool intersects() const = 0;

         virtual ~Intersector()
         {}
      };
   }
}
