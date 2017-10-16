#pragma once
#include <GPUEngine/geCore/gecore_export.h>

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

