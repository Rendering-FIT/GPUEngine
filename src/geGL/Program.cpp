#include<geGL/Program.h>

using namespace ge::gl;
using namespace ge::gl::opengl;

Program::Program(){
  this->_id = glCreateProgram();
}

#if defined(REPLACE_GLEW)
Program::Program(FunctionTablePointer const&table):OpenGLObject(table){
  this->_id = glCreateProgram();
}
#endif


Program::~Program(){
  glDeleteProgram(this->_id);
}

GLboolean Program::isProgram()const{
  return glIsProgram(this->_id);
}

void Program::attachShader(std::shared_ptr<Shader>const&shader){
  this->_shaders.insert(shader);
  glAttachShader(this->_id,shader->getId());
}

void Program::detachShader(std::shared_ptr<Shader>const&shader){
  this->_shaders.erase(shader);
  glDetachShader(this->_id,shader->getId());
}

void Program::link()const{
  glLinkProgram(this->_id);
}

void Program::use()const{
  glUseProgram(this->_id);
}

void Program::validate()const{
  glValidateProgram(this->_id);
}

GLint Program::getUniformLocation(const char*name)const{
  return glGetUniformLocation(this->_id,name);
}

GLint Program::getAttribLocation (const char*name)const{
  return glGetAttribLocation(this->_id,name);
}

