#include<geGL/Shader.h>

using namespace ge::gl;

/**
 * @brief gets shader parameter
 *
 * @param pname name of parameter
 *
 * @return value of parameter
 */
GLint Shader::_getParam(GLenum pname)const{
  GLint params;
  glGetShaderiv(this->getId(),pname,&params);
  return params;
}

/**
 * @brief empty constructor
 */
Shader::Shader(){
  this->_id = 0;
}

/**
 * @brief constructor that creates shader of certain type
 *
 * @param type type of shader
 * @param source optional source code of shader
 */
Shader::Shader(GLenum type,std::string source){
  this->create(type,source);
}

/**
 * @brief destructor that invalidates id
 */
Shader::~Shader(){
  glDeleteShader(this->_id);
}

/**
 * @brief constructing function that can be called on object 
 * created using empty constructor
 *
 * @param type type of shader
 * @param source optional source code of shader
 */
void Shader::create(GLenum type,std::string source){
  this->_id = glCreateShader(type);
  if(source!="")this->compile(source);
}

/**
 * @brief this function sets shader source to shader
 * it does not compile shader
 *
 * @param source source code of shader
 */
void Shader::setSource(std::string source){
  const char*string=source.c_str();
  glShaderSource(this->getId(),1,&string,NULL);
}

/**
 * @brief this function can set shader source code and compile shader
 *
 * @param source optional source code
 */
void Shader::compile(std::string source){
  if(source!="")this->setSource(source);
  glCompileShader(this->getId());
}

/**
 * @brief function returns true if object represents valid shader
 *
 * @return true if object represents valid shader
 */
GLboolean Shader::isShader()const{
  return glIsShader(this->getId());
}

/**
 * @brief gets type of shader
 *
 * @return type of shader
 */
GLenum Shader::getType()const{
  return this->_getParam(GL_SHADER_TYPE);
}

/**
 * @brief gets delete status of shader
 *
 * @return delete status of shader
 */
GLboolean Shader::getDeleteStatus()const{
  return this->_getParam(GL_DELETE_STATUS);
}

/**
 * @brief gets compile status of shader
 *
 * @return compile status of shader
 */
GLboolean Shader::getCompileStatus()const{
  return this->_getParam(GL_COMPILE_STATUS);
}

/**
 * @brief gets info log length
 *
 * @return info log length
 */
GLuint Shader::getInfoLogLength()const{
  return this->_getParam(GL_INFO_LOG_LENGTH);
}

/**
 * @brief gets source code length
 *
 * @return source code length
 */
GLuint Shader::getSourceLength()const{
  return this->_getParam(GL_SHADER_SOURCE_LENGTH);
}

/**
 * @brief gets info log after compilation
 *
 * @return info log or empty string if there is no info log
 */
std::string Shader::getInfoLog()const{
  GLuint length = this->getInfoLogLength();
  if(!length)return"";
  std::string info(length,' ');
  glGetShaderInfoLog(this->getId(),length,NULL,(GLchar*)info.c_str());
  return info;
}

/**
 * @brief gets shader source
 *
 * @return shader source or empty string if there is no source
 */
std::string Shader::getSource()const{
  GLuint length=this->getSourceLength();
  if(!length)return"";
  std::string source(length,' ');
  glGetShaderSource(this->getId(),length,NULL,(GLchar*)source.c_str());
  return source;
}

