#ifndef _OCCLUSIONQUERIESCOMMANDS_H_
#define _OCCLUSIONQUERIESCOMMANDS_H_

#include <geGL/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GEGL_EXPORT BeginQuery: public Command
    {
      public:
        GLenum target;
        GLuint id;
        BeginQuery(GLenum target,GLuint id);
        void apply();
    };
    class GEGL_EXPORT EndQuery: public Command
    {
      public:
        GLenum target;
        EndQuery(GLenum target);
        void apply();
    };
  }//ogl
}//ge



#endif//_OCCLUSIONQUERIESCOMMANDS_H_
