#pragma once

#include <geSG/Export.h>

namespace ge{
   namespace sg
   {
      /**
       * Abstract class for basic spatial transformation.
       */
      class GESG_EXPORT Transform
      {
      public:
         virtual float* getMatrixData() = 0;
         virtual const float* getMatrixData()const = 0;
      };
   }
}