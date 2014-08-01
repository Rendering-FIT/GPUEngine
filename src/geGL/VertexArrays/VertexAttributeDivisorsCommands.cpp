#include<geGL/VertexArrays/VertexAttributeDivisorsCommands.h>

namespace ge
{
  namespace gl
  {
    VertexBindingDivisor::VertexBindingDivisor(
            GLuint bindingIndex,
            GLuint divisor){
          this->bindingIndex = bindingIndex;
          this->divisor      = divisor;
        }
        void VertexBindingDivisor::apply(){
          glVertexBindingDivisor(
              this->bindingIndex,
              this->divisor);
        }
        VertexAttribDivisor::VertexAttribDivisor(
            GLuint index,
            GLuint divisor){
          this->index   = index;
          this->divisor = divisor;
        }
        void VertexAttribDivisor::apply(){
          glVertexAttribDivisor(
              this->index,
              this->divisor);
        }
  }//ogl
}//ge

