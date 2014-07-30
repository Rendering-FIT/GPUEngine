#ifndef _VERTEXATTRIBUTEDIVISORS_H_
#define _VERTEXATTRIBUTEDIVISORS_H_

#include<geGL/Standard/OpenGL.h>

namespace ge
{
  namespace ogl
  {
    class GE_EXPORT VertexBindingDivisor: public Command
    {
      public:
        GLuint bindingIndex;
        GLuint divisor;
        VertexBindingDivisor(
            GLuint bindingIndex,
            GLuint divisor);
        void apply();
    };
    class GE_EXPORT VertexAttribDivisor: public Command
    {
      public:
        GLuint index;
        GLuint divisor;
        VertexAttribDivisor(
            GLuint index,
            GLuint divisor);
        void apply();
    };
  }//ogl
}//ge

#endif//_VERTEXATTRIBUTEDIVISORS_H_
