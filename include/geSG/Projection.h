#ifndef GE_SG_PROJECTION_H
#define GE_SG_PROJECTION_H

#include <geSG/MatrixTransform.h>

namespace ge
{
   namespace sg
   {

      class Projection : public MatrixTransform
      {
      protected:
         glm::mat4 _projectionMatrix;

      public:

         virtual void setProjectionMatrix(const glm::mat4 &matrix);
         virtual void setProjectionMatrix(const float *matrix);
         virtual void setProjectionMatrix(const float a1,const float a2,const float a3,const float a4,
                                          const float a5,const float a6,const float a7,const float a8,
                                          const float a9,const float a10,const float a11,const float a12,
                                          const float a13,const float a14,const float a15,const float a16);

      };
   }
}

#endif // GE_SG_PROJECTION_H
