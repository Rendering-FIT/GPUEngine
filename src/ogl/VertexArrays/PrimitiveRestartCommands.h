#ifndef _PRIMITIVERESTARTCOMMANDS_H_
#define _PRIMITIVERESTARTCOMMANDS_H_

#include"../../ogl/Standard/OpenGL.h"

namespace ge
{
  namespace ogl
  {
    class PrimitiveRestartIndex: public Command
    {
      public:
        GLuint index;
        PrimitiveRestartIndex(
            GLuint index);
        void apply();
    };
  }//ogl
}//ge

#endif//_PRIMITIVERESTARTCOMMANDS_H_
