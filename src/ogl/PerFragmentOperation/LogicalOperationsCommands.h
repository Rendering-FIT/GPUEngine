#ifndef _LOGICALOPERATIONSCOMMANDS_H_
#define _LOGICALOPERATIONSCOMMANDS_H_

#include"../../ogl/Standard/OpenGL.h"

namespace ge
{
  namespace ogl
  {
    class LogicOp: public Command
    {
      public:
        GLenum op;
        LogicOp(GLenum op);
        void apply();
    };
  }//ogl
}//ge





#endif//_LOGICALOPERATIONSCOMMANDS_H_
