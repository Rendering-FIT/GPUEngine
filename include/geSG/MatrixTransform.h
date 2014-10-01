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

         class MatricesDataAdapter;

         unsigned _numMatrices;
         std::unique_ptr<MatricesDataAdapter> _matricesDataAdapter;

      public:

         META_Node(ge::sg,MatrixTransform);

         virtual void setMatrix(std::shared_ptr<glm::mat4[]> matrices,unsigned numMatrices=1);
         virtual void setMatrix(glm::mat4 *matrices,unsigned numMatrices=1,bool deleteOnObjectDestruction=false);

         virtual void setMatrix(std::shared_ptr<float[][16]> matrices,unsigned numMatrices=1);
         virtual void setMatrix(float *matrices[16],unsigned numMatrices=1,bool deleteOnObjectDestruction=false);
         virtual void setMatrix(const float a1,const float a2,const float a3,const float a4,
                                const float a5,const float a6,const float a7,const float a8,
                                const float a9,const float a10,const float a11,const float a12,
                                const float a13,const float a14,const float a15,const float a16);

      protected:
         class MatricesDataAdapter {
         public:
            enum Type { GLM_MAT4_SHARED_PTR, GLM_MAT4_PTR, FLOAT_SHARED_PTR, FLOAT_PTR, SINGLE_MATRIX };
            virtual Type getType() const = 0;
            inline bool isOfType(Type t) const  { return getType()==t; }
            virtual ~MatricesDataAdapter() {}
         };
      };
   }
}

#endif // GE_SG_MATRIX_TRANSFORM_H
