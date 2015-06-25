#pragma once
#include <geCore/Export.h>

namespace ge
{
   namespace core
   {
      class GECORE_EXPORT Functor
      {
      public:
         virtual void operator()() = 0;
      };
   }
}

