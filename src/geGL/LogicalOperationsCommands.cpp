#include <geGL/LogicalOperationsCommands.h>

namespace ge{
  namespace gl{
    LogicOp::LogicOp(GLenum op){
      this->op = op;
    }
    void LogicOp::operator()(){
      glLogicOp(this->op);
    }
  }//ogl
}//ge
