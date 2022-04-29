#include<geGL/Shader.h>
#include<geGL/private/ShaderImpl.h>
#include<geGL/Program.h>
#include<sstream>

using namespace ge::gl;

/**
 * @brief gets shader parameter
 *
 * @param pname name of parameter
 *
 * @return value of parameter
 */
GLint Shader::_getParam(GLenum pname)const{
  assert(this!=nullptr);
  GLint params;
  this->getContext().glGetShaderiv(this->getId(),pname,&params);
  return params;
}

/**
 * @brief empty constructor
 */
Shader::Shader():Shader(nullptr){}

/**
 * @brief constructor that creates shader of certain type
 *
 * @param type type of shader
 * @param sources optional source code of shader
 */
Shader::Shader(GLenum type,Sources const&sources):Shader(){
  assert(this!=nullptr);
  this->create(type);
  this->compile(sources);
}

/**
 * @brief empty consturctor
 *
 * @param table OpenGLFunctionTable
 */
Shader::Shader(FunctionTablePointer const&table):OpenGLObject(table){
  impl = new ShaderImpl();
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
    Sources              const&sources):Shader(table){
  assert(this!=nullptr);
  this->create(type);
  this->compile(sources);
}

/**
 * @brief destructor that invalidates id
 */
Shader::~Shader(){
  assert(this!=nullptr);
  this->getContext().glDeleteShader(this->getId());
  delete impl;
}

/**
 * @brief constructing function that can be called on object 
 * created using empty constructor
 *
 * @param type type of shader
 * @param sources optional source codes of shader
 */
void Shader::create(GLenum type){
  assert(this!=nullptr);
  if(this->getId() != 0)return;
  this->getId() = this->getContext().glCreateShader(type);
}

/**
 * @brief this function sets shader source to shader.
 * It does not compile shader.
 *
 * @param source source codes of shader
 */
void Shader::setSource(Sources const& sources){
  assert(this!=nullptr);
  std::vector<const GLchar*>ptr;
  for(auto const&x:sources)ptr.push_back(x.c_str());

  this->getContext().glShaderSource(this->getId(),(GLsizei)ptr.size(),ptr.data(),nullptr);
}

/**
 * @brief this function can set shader source code and compile shader.
 * It also call link in programs that are using this shader.
 *
 * @param source optional source codes
 */
void Shader::compile(Sources const& sources){
  assert(this!=nullptr);
  if(sources.size()>0)this->setSource(sources);
  this->getContext().glCompileShader(this->getId());
  if(!this->getCompileStatus()){
    std::cerr<<this->getInfoLog()<<std::endl;
    return;
  }
  for(auto const&x:this->impl->programs){
    x->link();
  }
}

/**
 * @brief function returns true if object represents valid shader
 *
 * @return true if object represents valid shader
 */
GLboolean Shader::isShader()const{
  assert(this!=nullptr);
  return this->getContext().glIsShader(this->getId());
}

/**
 * @brief gets type of shader
 *
 * @return type of shader
 */
GLenum Shader::getType()const{
  assert(this!=nullptr);
  return this->_getParam(GL_SHADER_TYPE);
}

/**
 * @brief gets delete status of shader
 *
 * @return delete status of shader
 */
GLboolean Shader::getDeleteStatus()const{
  assert(this!=nullptr);
  return (GLboolean)this->_getParam(GL_DELETE_STATUS);
}

/**
 * @brief gets compile status of shader
 *
 * @return compile status of shader
 */
GLboolean Shader::getCompileStatus()const{
  assert(this!=nullptr);
  return (GLboolean)this->_getParam(GL_COMPILE_STATUS);
}

/**
 * @brief gets info log length
 *
 * @return info log length
 */
GLuint Shader::getInfoLogLength()const{
  assert(this!=nullptr);
  return this->_getParam(GL_INFO_LOG_LENGTH);
}

/**
 * @brief gets source code length
 *
 * @return source code length
 */
GLuint Shader::getSourceLength()const{
  assert(this!=nullptr);
  return this->_getParam(GL_SHADER_SOURCE_LENGTH);
}

/**
 * @brief gets info log after compilation
 *
 * @return info log or empty string if there is no info log
 */
std::string Shader::getInfoLog()const{
  assert(this!=nullptr);
  GLuint length = this->getInfoLogLength();
  if(!length)return"";
  std::string info(length,' ');
  this->getContext().glGetShaderInfoLog(this->getId(),length,NULL,(GLchar*)info.c_str());
  return info;
}

/**
 * @brief gets shader source
 *
 * @return shader source or empty string if there is no source
 */
Shader::Source Shader::getSource()const{
  assert(this!=nullptr);
  GLuint length=this->getSourceLength();
  if(!length)return"";
  std::string source(length,' ');
  this->getContext().glGetShaderSource(this->getId(),length,NULL,(GLchar*)source.c_str());
  return source;
}

std::string Shader::define(std::string const&name){
  return"#define "+name+"\n";
}

std::string Shader::define(std::string const&name,uint32_t value){
  std::stringstream result;
  result<<"#define "<<name<<" "<<value<<"u\n";
  return result.str();
}

std::string Shader::define(std::string const&name,uint32_t value0,uint32_t value1){
  std::stringstream result;
  result<<"#define "<<name<<" uvec2("<<value0<<"u,"<<value1<<"u)\n";
  return result.str();
}

std::string Shader::define(std::string const&name,uint32_t value0,uint32_t value1,uint32_t value2){
  std::stringstream result;
  result<<"#define "<<name<<" uvec3("<<value0<<"u,"<<value1<<"u,"<<value2<<"u)\n";
  return result.str();
}

std::string Shader::define(std::string const&name,uint32_t value0,uint32_t value1,uint32_t value2,uint32_t value3){
  std::stringstream result;
  result<<"#define "<<name<<" uvec3("<<value0<<"u,"<<value1<<"u,"<<value2<<"u,"<<value3<<"u)\n";
  return result.str();
}

std::string Shader::define(std::string const&Name,uint32_t vectorSize,uint32_t const*values){
  assert(vectorSize<4);
  if(vectorSize==1)return define(Name,values[0]);
  std::stringstream result;
  result<<"#define "<<Name<<" uvec"<<vectorSize<<"(";
  for(uint32_t i=0;i<vectorSize;++i){
    result<<values[i]<<"u";
    if(i==vectorSize-1)result<<")\n";
    else result<<",";
  }
  return result.str();
}

std::string Shader::define(std::string const&Name,int32_t Value){
  std::stringstream result;
  result<<"#define "<<Name<<" "<<Value<<"\n";
  return result.str();
}

std::string Shader::define(std::string const&Name,int32_t value0,int32_t value1){
  std::stringstream result;
  result<<"#define "<<Name<<" ivec2("<<value0<<","<<value1<<")\n";
  return result.str();
}

std::string Shader::define(std::string const&Name,int32_t value0,int32_t value1,int32_t value2){
  std::stringstream result;
  result<<"#define "<<Name<<" ivec3("<<value0<<","<<value1<<","<<value2<<")\n";
  return result.str();
}

std::string Shader::define(std::string const&Name,int32_t value0,int32_t value1,int32_t value2,int32_t value3){
  std::stringstream result;
  result<<"#define "<<Name<<" ivec3("<<value0<<","<<value1<<","<<value2<<","<<value3<<")\n";
  return result.str();
}

std::string Shader::define(std::string const&Name,uint32_t vectorSize,int32_t const*values){
  assert(vectorSize<4);
  if(vectorSize==1)return define(Name,values[0]);
  std::stringstream result;
  result<<"#define "<<Name<<" ivec"<<vectorSize<<"(";
  for(uint32_t i=0;i<vectorSize;++i){
    result<<values[i];
    if(i==vectorSize-1)result<<")\n";
    else result<<",";
  }
  return result.str();
}

std::string Shader::define(std::string const&Name,float Value){
  std::stringstream result;
  result<<"#define "<<Name<<" float("<<Value<<")\n";
  return result.str();
}

std::string Shader::define(std::string const&Name,float value0,float value1){
  std::stringstream result;
  result<<"#define "<<Name<<" vec2("<<value0<<","<<value1<<")\n";
  return result.str();
}

std::string Shader::define(std::string const&Name,float value0,float value1,float value2){
  std::stringstream result;
  result<<"#define "<<Name<<" vec3("<<value0<<","<<value1<<","<<value2<<")\n";
  return result.str();
}

std::string Shader::define(std::string const&Name,float value0,float value1,float value2,float value3){
  std::stringstream result;
  result<<"#define "<<Name<<" vec3("<<value0<<","<<value1<<","<<value2<<","<<value3<<")\n";
  return result.str();
}

std::string Shader::define(std::string const&Name,uint32_t vectorSize,float const*values){
  assert(vectorSize<4);
  if(vectorSize==1)return define(Name,values[0]);
  std::stringstream result;
  result<<"#define "<<Name<<" vec"<<vectorSize<<"(";
  for(uint32_t i=0;i<vectorSize;++i){
    result<<values[i];
    if(i==vectorSize-1)result<<")\n";
    else result<<",";
  }
  return result.str();
}

std::string Shader::define(std::string const&Name,std::string const&Value){
  return"#define "+Name+" "+Value+"\n";
}


