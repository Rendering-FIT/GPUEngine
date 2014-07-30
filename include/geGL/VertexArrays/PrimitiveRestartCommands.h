#ifndef _PRIMITIVERESTARTCOMMANDS_H_
#define _PRIMITIVERESTARTCOMMANDS_H_

#include<geGL/Standard/OpenGL.h>

namespace ge
{
  namespace ogl
  {
    class GE_EXPORT PrimitiveRestartIndex: public Command
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
