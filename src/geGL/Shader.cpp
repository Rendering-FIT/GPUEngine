#include<geGL/Shader.h>

using namespace ge::gl;

GLint Shader::_getParam(GLenum pname)const{
  GLint params;
  glGetShaderiv(this->getId(),pname,&params);
  return params;
}

Shader::Shader(){
  this->_id = 0;
}

Shader::Shader(GLenum type,std::string source){
  this->create(type,source);
}

Shader::~Shader(){
  glDeleteShader(this->_id);
}

void Shader::create(GLenum type,std::string source){
  this->_id = glCreateShader(type);
  if(source!="")this->compile(source);
}

void Shader::setSource(std::string source){
  const char*string=source.c_str();
  glShaderSource(this->getId(),1,&string,NULL);
}

void Shader::compile(std::string source){
  if(source!="")this->setSource(source);
  glCompileShader(this->getId());
}

GLboolean Shader::isShader()const{
  return glIsShader(this->getId());
}

GLenum Shader::getType()const{
  return this->_getParam(GL_SHADER_TYPE);
}

GLboolean Shader::getDeleteStatus()const{
  return this->_getParam(GL_DELETE_STATUS);
}

GLboolean Shader::getCompileStatus()const{
  return this->_getParam(GL_COMPILE_STATUS);
}

GLuint Shader::getInfoLogLength()const{
  return this->_getParam(GL_INFO_LOG_LENGTH);
}

GLuint Shader::getSourceLength()const{
  return this->_getParam(GL_SHADER_SOURCE_LENGTH);
}

std::string Shader::getInfoLog()const{
  GLuint length = this->getInfoLogLength();
  if(!length)return"";
  std::string info(length,' ');
  glGetShaderInfoLog(this->getId(),length,NULL,(GLchar*)info.c_str());
  return info;
}

std::string Shader::getSource()const{
  GLuint length=this->getSourceLength();
  if(!length)return"";
  std::string source(length,' ');
  glGetShaderSource(this->getId(),length,NULL,(GLchar*)source.c_str());
  return source;
}

