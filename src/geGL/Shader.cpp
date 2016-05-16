#include<geGL/Shader.h>
#include<geGL/Program.h>

using namespace ge::gl;
using namespace ge::gl::opengl;

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
 * @param sources optional source code of shader
 */
Shader::Shader(GLenum type,Sources const&sources){
  this->create(type);
  this->compile(sources);
}

/**
 * @brief enpty consturctor
 *
 * @param table OpenGLFunctionTable
 */
Shader::Shader(FunctionTablePointer const&table):OpenGLObject(table){
  this->_id = 0;
}

/**
 * @brief constructor that creates shader of certain type
 *
 * @param table OpenGLFunctionTable
 * @param type type of shader
 * @param sources optional shader sources 
 */
Shader::Shader(
    FunctionTablePointer const&table  ,
    GLenum               const&type   ,
    Sources              const&sources):OpenGLObject(table){
  this->create(type);
  this->compile(sources);
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
 * @param sources optional source codes of shader
 */
void Shader::create(GLenum type){
  if(this->_id != 0)return;
  this->_id = glCreateShader(type);
}

/**
 * @brief this function sets shader source to shader
 * it does not compile shader
 *
 * @param source source codes of shader
 */
void Shader::setSource(Sources const& sources){
  std::vector<const GLchar*>ptr;
  for(auto const&x:sources)ptr.push_back(x.c_str());

  glShaderSource(this->getId(),(GLsizei)ptr.size(),ptr.data(),nullptr);
}

/**
 * @brief this function can set shader source code and compile shader
 * it also call link in programs that are using this shader
 *
 * @param source optional source codes
 */
void Shader::compile(Sources const& sources){
  if(sources.size()>0)this->setSource(sources);
  glCompileShader(this->getId());
  if(!this->getCompileStatus())return;
  for(auto const&x:this->_programs){
    x->link();
  }
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
  return (GLboolean)this->_getParam(GL_DELETE_STATUS);
}

/**
 * @brief gets compile status of shader
 *
 * @return compile status of shader
 */
GLboolean Shader::getCompileStatus()const{
  return (GLboolean)this->_getParam(GL_COMPILE_STATUS);
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
Shader::Source Shader::getSource()const{
  GLuint length=this->getSourceLength();
  if(!length)return"";
  std::string source(length,' ');
  glGetShaderSource(this->getId(),length,NULL,(GLchar*)source.c_str());
  return source;
}

