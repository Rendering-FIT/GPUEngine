#include<geGL/ProgramObjectSubroutine.h>

using namespace ge::gl;

ShaderObjectSubroutine::~ShaderObjectSubroutine(){
  if(this->indices)
    delete[]this->indices;
}
ShaderObjectSubroutine::ShaderObjectSubroutine(){
  this->indices=nullptr;
}

