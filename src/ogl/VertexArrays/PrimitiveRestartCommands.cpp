#include"PrimitiveRestartCommands.h"

namespace ge
{
  namespace ogl
  {
    PrimitiveRestartIndex::PrimitiveRestartIndex(
        GLuint index){
      this->index = index;
    }
    void PrimitiveRestartIndex::apply(){
      glPrimitiveRestartIndex(
          this->index);
    }
  }//ogl
}//ge

