#ifndef GE_RG_MATRIX_GPU_DATA_H
#define GE_RG_MATRIX_GPU_DATA_H

#include <glm/mat4x4.hpp>

namespace ge
{
   namespace rg
   {

      /** MatrixGpuData structure is used to access
       *  4x4 matrices usually stored in GPU memory.
       *  It is composed of 16 tightly packed floats.
       */
      struct MatrixGpuData {
         float matrix[16];  ///< 4x4 matrix data.
         inline float* asFloats()  { return matrix; }
         inline glm::mat4& asGlmMatrix()  { return *reinterpret_cast<glm::mat4*>(&matrix[0]); }
      };

   }
}

#endif // GE_RG_MATRIX_GPU_DATA_H
