#include<geGL/VertexAttributeDivisorsCommands.h>

using namespace ge::gl;

VertexBindingDivisor::VertexBindingDivisor(
    GLuint bindingIndex,
    GLuint divisor){
  this->bindingIndex = bindingIndex;
  this->divisor      = divisor;
}
void VertexBindingDivisor::operator()(){
  glVertexBindingDivisor(
      this->bindingIndex,
      this->divisor     );
}

VertexAttribDivisor::VertexAttribDivisor(
    GLuint index,
    GLuint divisor){
  this->index   = index;
  this->divisor = divisor;
}
void VertexAttribDivisor::operator()(){
  glVertexAttribDivisor(
      this->index  ,
      this->divisor);
}

