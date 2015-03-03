#include<geGL/ShaderObjectSubroutine.h>

using namespace ge::gl;

ShaderObjectSubroutine::~ShaderObjectSubroutine(){
  if(this->Indices)
    delete[]this->Indices;
}
ShaderObjectSubroutine::ShaderObjectSubroutine(){
  this->Indices=NULL;
}

