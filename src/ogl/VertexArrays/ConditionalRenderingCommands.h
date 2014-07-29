#ifndef _COMDITIONALRENDERINGCOMMANDS_H_
#define _COMDITIONALRENDERINGCOMMANDS_H_

#include"../../ogl/Standard/OpenGL.h"

namespace ge
{
  namespace ogl
  {
    class BeginConditionalRender
    {
      public:
        GLuint id;
        GLenum mode;
        BeginConditionalRender(GLuint id,GLenum mode);
        void apply();
    };
    class EndConditionalRender
    {
      public:
        EndConditionalRender();
        void apply();
    };
  }//ogl
}//ge

#endif//_COMDITIONALRENDERINGCOMMANDS_H_
