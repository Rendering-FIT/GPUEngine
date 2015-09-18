#pragma once

#include <geSG/Export.h>

namespace ge{
   namespace sg
   {
      /**
       * Abstract class for basic spatial transformation.
       * Inner representation does not need to be a matrix but
       * it must be able to output/compute matrix for needs of
       * e.g. OpenGL API. The matrix ordering is defined by usage.
       */
      class GESG_EXPORT Transform
      {
      public:
         virtual float* getMatrixData() = 0;
         virtual const float* getMatrixData()const = 0;
      };
   }
}