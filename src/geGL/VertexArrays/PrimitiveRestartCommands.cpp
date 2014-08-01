#include<geGL/VertexArrays/PrimitiveRestartCommands.h>

namespace ge
{
  namespace gl
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

