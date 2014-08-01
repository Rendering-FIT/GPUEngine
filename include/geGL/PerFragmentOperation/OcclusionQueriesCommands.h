#ifndef _OCCLUSIONQUERIESCOMMANDS_H_
#define _OCCLUSIONQUERIESCOMMANDS_H_

#include <geGL/Standard/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GE_EXPORT BeginQuery: public Command
    {
      public:
        GLenum target;
        GLuint id;
        BeginQuery(GLenum target,GLuint id);
        void apply();
    };
    class GE_EXPORT EndQuery: public Command
    {
      public:
        GLenum target;
        EndQuery(GLenum target);
        void apply();
    };
  }//ogl
}//ge



#endif//_OCCLUSIONQUERIESCOMMANDS_H_
