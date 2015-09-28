#include<geGL/ProgramObjectSubroutine.h>

using namespace ge::gl;

ShaderObjectSubroutine::~ShaderObjectSubroutine(){
  if(this->_indices)
    delete[]this->_indices;
}

ShaderObjectSubroutine::ShaderObjectSubroutine(){
  this->_indices=nullptr;
}

void ShaderObjectSubroutine::addUniform(std::string name,ShaderObjectSubroutineUniform const&uniform){
  this->_subroutineUniformList[name]=uniform;
}

void ShaderObjectSubroutine::addSubroutine(std::string name,GLuint location){
  this->_subroutineList[name]=location;
}

void ShaderObjectSubroutine::allocInidices(unsigned num){
  this->_numIndices = num;
  this->_indices = new GLuint[this->_numIndices];
  for(GLsizei i=0;i<this->_numIndices;++i)
    this->_indices[i]=0;
}

void ShaderObjectSubroutine::set(GLenum type,std::string uniform,unsigned offset,std::string subroutine){
  this->_indices[this->_subroutineUniformList[uniform].index+offset]=
    this->_subroutineList[subroutine];
  glUniformSubroutinesuiv(type,this->_numIndices,this->_indices);
}
