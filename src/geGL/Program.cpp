#include<geGL/Program.h>

using namespace ge::gl;
using namespace ge::gl::opengl;

Program::Program(ShaderPointers const&shaders){
  if(shaders.size()==0)return;
  this->link(shaders);
}

Program::Program(
    opengl::FunctionTablePointer const&table  ,
    ShaderPointers               const&shaders):OpenGLObject(table){
  if(shaders.size()==0)return;
  this->link(shaders);
}

void Program::create(){
  if(this->_id != 0)return;
  this->_id = glCreateProgram();
}

Program::~Program(){
  std::vector<ShaderPointer>forDeletion;
  for(auto const&x:this->_shaders)forDeletion.push_back(x);
  this->detachShaders(forDeletion);
  glDeleteProgram(this->_id);
}

GLboolean Program::isProgram()const{
  return glIsProgram(this->_id);
}

void Program::attachShaders(ShaderPointers const&shaders){
  this->create();
  for(auto const&x:shaders){
    glAttachShader(this->_id,x->getId());
    this->_shaders.insert(x);
    x->_programs.insert(this);
  }
}

void Program::detachShaders(ShaderPointers const&shaders){
  for(auto const&x:shaders){
    glDetachShader(this->_id,x->getId());
    this->_shaders.erase(x);
    x->_programs.erase(this);
  }
}

void Program::link(ShaderPointers const&shaders){
  this->attachShaders(shaders);
  glLinkProgram(this->_id);
}

void Program::use()const{
  glUseProgram(this->_id);
}

void Program::validate()const{
  glValidateProgram(this->_id);
}

GLint Program::getUniformLocation(std::string const&name)const{
  return glGetUniformLocation(this->_id,name.c_str());
}

GLint Program::getAttribLocation (std::string const&name)const{
  return glGetAttribLocation(this->_id,name.c_str());
}

