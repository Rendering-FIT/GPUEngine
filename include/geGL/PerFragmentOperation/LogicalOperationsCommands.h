#ifndef _LOGICALOPERATIONSCOMMANDS_H_
#define _LOGICALOPERATIONSCOMMANDS_H_

#include <geGL/Standard/OpenGL.h>

namespace ge
{
  namespace ogl
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
