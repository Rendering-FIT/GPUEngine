#include<geGL/ProgramObjectSubroutineUniform.h>

using namespace ge::gl;

ShaderObjectSubroutineUniform::ShaderObjectSubroutineUniform(
    GLint       location     ,
    GLint       size         ,
    GLint       numCompatible,
    std::string name         ,
    unsigned    index        ){
  this->location      = location;//parameter id
  this->size          = size;
  this->numCompatible = numCompatible;
  this->name          = name;
  this->index         = index;
}

