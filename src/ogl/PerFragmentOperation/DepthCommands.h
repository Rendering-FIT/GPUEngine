#ifndef _DEPTHCOMMANDS_H_
#define _DEPTHCOMMANDS_H_

#include"../../ogl/Standard/OpenGL.h"

namespace ge
{
  namespace ogl
  {
    class DepthFunc: public Command
    {
      public:
        GLenum func;
        DepthFunc(GLenum func);
        void apply();
    };
  }//ogl
}//ge



#endif//_DEPTHCOMMANDS_H_
