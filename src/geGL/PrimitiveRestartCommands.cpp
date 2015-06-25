#include<geGL/PrimitiveRestartCommands.h>

using namespace ge::gl;

PrimitiveRestartIndex::PrimitiveRestartIndex(
    GLuint index){
  this->index = index;
}
void PrimitiveRestartIndex::operator()(){
  glPrimitiveRestartIndex(
      this->index);
}

