#include <geGL/PerFragmentOperation/LogicalOperationsCommands.h>

namespace ge
{
  namespace gl
  {
    LogicOp::LogicOp(GLenum op){
      this->op = op;
    }
    void LogicOp::apply(){
      glLogicOp(this->op);
    }
  }//ogl
}//ge
