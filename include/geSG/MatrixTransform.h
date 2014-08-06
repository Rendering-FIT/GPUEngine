#ifndef GE_SG_MATRIX_TRANSFORM_H
#define GE_SG_MATRIX_TRANSFORM_H

#include <glm/glm.hpp>
#include <geSG/Group.h>

namespace ge
{
   namespace sg
   {

      class MatrixTransform : public Group
      {
      protected:
         unsigned _numMatrices;
         
      public:

         virtual void set(std::shared_ptr<glm::mat4[]> matrices,unsigned numMatrices=1);
         virtual void set(glm::mat4 *matrices,unsigned numMatrices=1,bool deleteOnObjectDestruction=false);

         virtual void set(std::shared_ptr<float[][16]> matrices,unsigned numMatrices=1);
         virtual void set(float *matrices[16],unsigned numMatrices=1,bool deleteOnObjectDestruction=false);
         virtual void set(const float a1,const float a2,const float a3,const float a4,
                          const float a5,const float a6,const float a7,const float a8,
                          const float a9,const float a10,const float a11,const float a12,
                          const float a13,const float a14,const float a15,const float a16);

      };
   }
}

#endif // GE_SG_MATRIX_TRANSFORM_H
