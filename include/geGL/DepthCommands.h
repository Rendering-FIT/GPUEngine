#ifndef _DEPTHCOMMANDS_H_
#define _DEPTHCOMMANDS_H_

#include <geGL/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GEGL_EXPORT DepthFunc: public Command
    {
      public:
        GLenum func;
        DepthFunc(GLenum func);
        void apply();
    };
  }//ogl
}//ge



#endif//_DEPTHCOMMANDS_H_
