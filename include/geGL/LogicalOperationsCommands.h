#ifndef _LOGICALOPERATIONSCOMMANDS_H_
#define _LOGICALOPERATIONSCOMMANDS_H_

#include <geGL/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GE_EXPORT LogicOp: public Command
    {
      public:
        GLenum op;
        LogicOp(GLenum op);
        void apply();
    };
  }//ogl
}//ge





#endif//_LOGICALOPERATIONSCOMMANDS_H_
