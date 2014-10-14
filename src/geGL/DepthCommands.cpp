#include <geGL/DepthCommands.h>

namespace ge
{
  namespace gl
  {
    DepthFunc::DepthFunc(GLenum func){
      this->func = func;
    }
    void DepthFunc::apply(){
      glDepthFunc(this->func);
    }
  }//ogl
}//ge
