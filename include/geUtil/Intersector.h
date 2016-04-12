#pragma once

#include <geUtil/Export.h>

namespace ge
{
   namespace util
   {
      struct /*GEUTIL_EXPORT*/ Intersector
      {
         virtual bool intersects() = 0;

         virtual ~Intersector()
         {}
      };
   }
}
