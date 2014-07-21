#ifndef _OCCLUSIONQUERIESCOMMANDS_H_
#define _OCCLUSIONQUERIESCOMMANDS_H_

#include"../../ogl/Standard/OpenGL.h"

namespace ge
{
  namespace ogl
  {
    class BeginQuery: public Command
    {
      public:
        GLenum target;
        GLuint id;
        BeginQuery(GLenum target,GLuint id);
        void apply();
    };
    class EndQuery: public Command
    {
      public:
        GLenum target;
        EndQuery(GLenum target);
        void apply();
    };
  }//ogl
}//ge



#endif//_OCCLUSIONQUERIESCOMMANDS_H_
