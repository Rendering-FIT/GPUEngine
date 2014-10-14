#ifndef _COMDITIONALRENDERINGCOMMANDS_H_
#define _COMDITIONALRENDERINGCOMMANDS_H_

#include <geGL/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GE_EXPORT BeginConditionalRender
    {
      public:
        GLuint id;
        GLenum mode;
        BeginConditionalRender(GLuint id,GLenum mode);
        void apply();
    };
    class GE_EXPORT EndConditionalRender
    {
      public:
        EndConditionalRender();
        void apply();
    };
  }//ogl
}//ge

#endif//_COMDITIONALRENDERINGCOMMANDS_H_
