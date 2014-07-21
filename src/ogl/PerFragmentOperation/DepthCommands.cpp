#include"DepthCommands.h"

namespace ge
{
  namespace ogl
  {
    DepthFunc::DepthFunc(GLenum func){
      this->func = func;
    }
    void DepthFunc::apply(){
      glDepthFunc(this->func);
    }
  }//ogl
}//ge
