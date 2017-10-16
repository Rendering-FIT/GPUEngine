#include<GPUEngine/geGL/Program.h>
#include<GPUEngine/geGL/OpenGLUtil.h>
#include<GPUEngine/geGL/Buffer.h>
#include<iostream>
#include<string>
#include<limits>
#include<GPUEngine/geCore/ErrorPrinter/ErrorPrinter.h>

using namespace ge::gl;

static bool printUniformWarnings = true;

/**
 * @brief sets warning for setting non existing uniform 
 *
 * @param enableWarning true for enabling warning
 */
void Program::setNonexistingUniformWarning(bool enableWarning){
  printUniformWarnings = enableWarning;
}

/**
 * @brief is non existing uniform warning enabled
 *
 * @return true if warning is enabled
 */
bool Program::isNonexistingUniformWarningEnabled(){
  return printUniformWarnings;
}

GLint Program::_getParam(GLenum pname)const{
  assert(this!=nullptr);
  GLint params;
  this->_gl.glGetProgramiv(this->getId(),pname,&params);
  return params;
}

/**
 * @brief creates new program from shaders
 *
 * @param shaders vector of compiled shaders
 */
Program::Program(ShaderPointers const&shaders){
  assert(this!=nullptr);
  this->_info = std::make_shared<ProgramInfo>();
  if(shaders.size()==0)return;
  this->link(shaders);
}

/**
 * @brief creates new program from shaders
 *
 * @param table opengl function table 
 * @param vector of compiled shaders
 */
Program::Program(
    FunctionTablePointer const&table  ,
    ShaderPointers       const&shaders):OpenGLObject(table){
  assert(this!=nullptr);
  this->_info = std::make_shared<ProgramInfo>();
  if(shaders.size()==0)return;
  this->link(shaders);
}

/**
 * @brief create empty shader program
 */
void Program::create(){
  assert(this!=nullptr);
  if(this->_id != 0)return;
  this->_id = this->_gl.glCreateProgram();
}

/**
 * @brief destroys program
 */
Program::~Program(){
  assert(this!=nullptr);
  std::vector<ShaderPointer>forDeletion;
  for(auto const&x:this->_shaders)forDeletion.push_back(x);
  this->detachShaders(forDeletion);
  this->_gl.glDeleteProgram(this->_id);
}

/**
 * @brief check if this program is existing
 *
 * @return true if this program is existing
 */
GLboolean Program::isProgram()const{
  assert(this!=nullptr);
  return this->_gl.glIsProgram(this->_id);
}

/**
 * @brief attach vector of compiled shaders into this program
 *
 * @param shaders vector of compiled shaders
 */
void Program::attachShaders(ShaderPointers const&shaders){
  assert(this!=nullptr);
  this->create();
  for(auto const&x:shaders){
    this->_gl.glAttachShader(this->_id,x->getId());
    this->_shaders.insert(x);
    x->_programs.insert(this);
  }
}

/**
 * @brief detach vector of compiled shaders from this program
 *
 * @param shaders vector of compiled shaders
 */
void Program::detachShaders(ShaderPointers const&shaders){
  assert(this!=nullptr);
  for(auto const&x:shaders){
    this->_gl.glDetachShader(this->_id,x->getId());
    this->_shaders.erase(x);
    x->_programs.erase(this);
  }
}

/**
 * @brief link program with optional additional vector of compiled shaders
 *
 * @param shaders optional vector fo compiled shaders
 */
void Program::link(ShaderPointers const&shaders){
  assert(this!=nullptr);
  this->attachShaders(shaders);
  this->_gl.glLinkProgram(this->_id);
  if(!this->getLinkStatus()){
    std::cerr<<this->getInfoLog()<<std::endl;
  }
  this->_fillInfo();
}

/**
 * @brief use this program
 */
void Program::use()const{
  assert(this!=nullptr);
  this->_gl.glUseProgram(this->_id);
}

/**
 * @brief validate this program
 */
void Program::validate()const{
  assert(this!=nullptr);
  this->_gl.glValidateProgram(this->_id);
}

/**
 * @brief gets location of particular uniform variable
 *
 * @param name name of uniform variable
 *
 * @return location of uniform variable
 */
GLint Program::getUniformLocation(std::string const&name)const{
  assert(this!=nullptr);
  return this->_gl.glGetUniformLocation(this->_id,name.c_str());
}

/**
 * @brief gets location of particular vertex attrib
 *
 * @param name name of vertex attrib
 *
 * @return location of vertex attrib
 */
GLint Program::getAttribLocation (std::string const&name)const{
  assert(this!=nullptr);
  return this->_gl.glGetAttribLocation(this->_id,name.c_str());
}

/**
 * @brief gets delete status of shader program
 *
 * @return delete status
 */
GLboolean Program::getDeleteStatus()const{
  assert(this!=nullptr);
  return (GLboolean)this->_getParam(GL_DELETE_STATUS);
}

/**
 * @brief is program correctly linked
 *
 * @return link status
 */
GLboolean Program::getLinkStatus()const{
  assert(this!=nullptr);
  return (GLboolean)this->_getParam(GL_LINK_STATUS);
}

/**
 * @brief is program validated
 *
 * @return validate status
 */
GLboolean Program::getValidateStatus()const{
  assert(this!=nullptr);
  return (GLboolean)this->_getParam(GL_VALIDATE_STATUS);
}

/**
 * @brief gets length of info log, log after linking, ...
 *
 * @return lenght of info log
 */
GLuint    Program::getInfoLogLength()const{
  assert(this!=nullptr);
  return this->_getParam(GL_INFO_LOG_LENGTH);
}

/**
 * @brief gets number of shaders in this program
 *
 * @return number of shaders in this program
 */
GLuint    Program::getNofShaders()const{
  assert(this!=nullptr);
  return this->_getParam(GL_ATTACHED_SHADERS);
}

/**
 * @brief gets number of active atomic counter buffers in this program
 *
 * @return number of active atomic counter buffers
 */
GLuint    Program::getNofActiveAtomicCounterBuffers()const{
  assert(this!=nullptr);
  return this->_getParam(GL_ACTIVE_ATOMIC_COUNTER_BUFFERS);
}

/**
 * @brief gets number of active vertex attributes
 *
 * @return number of active vertex attributes
 */
GLuint    Program::getNofActiveAttributes()const{
  assert(this!=nullptr);
  return this->_getParam(GL_ACTIVE_ATTRIBUTES);
}

/**
 * @brief gets maximal length of active attribute name
 *
 * @return maximal length of active attribute
 */
GLuint    Program::getActiveAttributeMaxLength()const{
  assert(this!=nullptr);
  return this->_getParam(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
}

/**
 * @brief gets number of active uniforms
 *
 * @return number of active uniforms
 */
GLuint    Program::getNofActiveUniforms()const{
  assert(this!=nullptr);
  return this->_getParam(GL_ACTIVE_UNIFORMS);
}

/**
 * @brief gets maximal length of name of active uniform
 *
 * @return maximal length of active uniform name
 */
GLuint    Program::getActiveUniformMaxLength()const{
  assert(this!=nullptr);
  return this->_getParam(GL_ACTIVE_UNIFORM_MAX_LENGTH);
}

/**
 * @brief gets byte length of program binary
 *
 * @return binary length
 */
GLuint    Program::getBinaryLength()const{
  assert(this!=nullptr);
  return this->_getParam(GL_PROGRAM_BINARY_LENGTH);
}

/**
 * @brief gets compute shaders work group size
 *
 * @param x returned work group size (x,y,z)
 */
void      Program::getComputeWorkGroupSize(GLint*x)const{
  assert(this!=nullptr);
  this->_gl.glGetProgramiv(this->getId(),GL_COMPUTE_WORK_GROUP_SIZE,x);
}

/**
 * @brief gets transform feedback buffer mode
 *
 * @return transform feedback buffer mode
 */
GLenum    Program::getTransformFeedbackBufferMode()const{
  assert(this!=nullptr);
  return this->_getParam(GL_TRANSFORM_FEEDBACK_BUFFER_MODE);
}

/**
 * @brief gets number of transform feedback varyings
 *
 * @return number of transform feedback varyings
 */
GLuint    Program::getNofTransfromFeedbackVaryings()const{
  assert(this!=nullptr);
  return this->_getParam(GL_TRANSFORM_FEEDBACK_VARYINGS);
}

/**
 * @brief gets maximal length of transform feedback varying name
 *
 * @return maximal length of name of transform feedback varying
 */
GLuint    Program::getTransformFeedbackVaryingMaxLength()const{
  assert(this!=nullptr);
  return this->_getParam(GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH);
}

/**
 * @brief gets number of output geometry shader vertices
 *
 * @return number of output geometry shader vertices
 */
GLuint    Program::getNofGeometryVerticesOut()const{
  assert(this!=nullptr);
  return this->_getParam(GL_GEOMETRY_VERTICES_OUT);
}

/**
 * @brief gets geometry shader input primitive type
 *
 * @return geometry shader input primitive type
 */
GLenum    Program::getGeometryInputType()const{
  assert(this!=nullptr);
  return this->_getParam(GL_GEOMETRY_INPUT_TYPE);
}

/**
 * @brief gets geometry shader output primitive type
 *
 * @return geometry shader output primitive type
 */
GLenum    Program::getGeometryOutputType()const{
  assert(this!=nullptr);
  return this->_getParam(GL_GEOMETRY_OUTPUT_TYPE);
}

/**
 * @brief gets info log
 *
 * @return info log
 */
std::string Program::getInfoLog()const{
  assert(this!=nullptr);
  GLuint length = this->getInfoLogLength();
  if(!length)return"";
  std::string info(length,' ');
  this->_gl.glGetProgramInfoLog(this->getId(),length,NULL,(GLchar*)info.c_str());
  return info;
}

GLint Program::getInterfaceParam(GLenum interf,GLenum pname)const{
  assert(this!=nullptr);
  GLint params;
  this->_gl.glGetProgramInterfaceiv(
      this->_id,
      interf,
      pname,
      &params);
  return params;
}

std::string Program::getResourceName(GLenum interf,GLuint index)const{
  assert(this!=nullptr);
  GLuint maxLength = this->getInterfaceParam(interf,GL_MAX_NAME_LENGTH);
  char*buffer = new char[maxLength];
  assert(buffer!=nullptr);
  this->_gl.glGetProgramResourceName(
      this->_id,
      interf,
      index,
      maxLength,
      nullptr,
      buffer);
  std::string name(buffer);
  delete[]buffer;
  return name;
}

GLint Program::getResourceParam(GLenum interf,GLenum pname,GLuint index)const{
  assert(this!=nullptr);
  GLint param;
  this->_gl.glGetProgramResourceiv(
      this->_id,
      interf,
      index,
      1,
      &pname,
      1,
      nullptr,
      &param);
  return param;
}

#define GE_GL_PROGRAM_SET(fce,type,...)\
  assert(this!=nullptr);\
  auto ii = this->_info->uniforms.find(name);\
  if(ii==this->_info->uniforms.end()){\
    if(printUniformWarnings)\
      ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);\
    return this;\
  }\
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == type);\
  std::get<ProgramInfo::LOCATION>(ii->second);\
  this->_gl.fce(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),__VA_ARGS__);\
  return this

#define GE_GL_PROGRAM_SETI(fce,type0,type1,...)\
  assert(this!=nullptr);\
  auto ii = this->_info->uniforms.find(name);\
  if(ii==this->_info->uniforms.end()){\
    if(printUniformWarnings)\
      ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);\
    return this;\
  }\
  assert(\
      std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == type0 ||\
      std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == type1);\
  std::get<ProgramInfo::LOCATION>(ii->second);\
  this->_gl.fce(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),__VA_ARGS__);\
  return this

#define GE_GL_PROGRAM_SETV(fce,type)\
  assert(this!=nullptr);\
  auto ii = this->_info->uniforms.find(name);\
  if(ii==this->_info->uniforms.end()){\
    if(printUniformWarnings)\
      ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);\
    return this;\
  }\
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == type);\
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));\
  this->_gl.fce(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,v0);\
  return this

#define GE_GL_PROGRAM_SETIV(fce,type0,type1)\
  assert(this!=nullptr);\
  auto ii = this->_info->uniforms.find(name);\
  if(ii==this->_info->uniforms.end()){\
    if(printUniformWarnings)\
      ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);\
    return this;\
  }\
  assert(\
      std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == type0 ||\
      std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == type1);\
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));\
  this->_gl.fce(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,v0);\
  return this


#define GE_GL_PROGRAM_SETMATRIX(fce,type)\
  assert(this!=nullptr);\
  auto ii = this->_info->uniforms.find(name);\
  if(ii==this->_info->uniforms.end()){\
    if(printUniformWarnings)\
      ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);\
    return this;\
  }\
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == type);\
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));\
  this->_gl.fce(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);\
  return this



Program const* Program::set1f(std::string const&name,float v0)const{
  GE_GL_PROGRAM_SET(glProgramUniform1f,GL_FLOAT,v0);
}

Program const* Program::set2f(std::string const&name,float v0,float v1)const{
  GE_GL_PROGRAM_SET(glProgramUniform2f,GL_FLOAT_VEC2,v0,v1);
}

Program const* Program::set3f(std::string const&name,float v0,float v1,float v2)const{
  GE_GL_PROGRAM_SET(glProgramUniform3f,GL_FLOAT_VEC3,v0,v1,v2);
}

Program const* Program::set4f(std::string const&name,float v0,float v1,float v2,float v3)const{
  GE_GL_PROGRAM_SET(glProgramUniform4f,GL_FLOAT_VEC4,v0,v1,v2,v3);
}

Program const* Program::set1i(std::string const&name,int32_t v0)const{
  GE_GL_PROGRAM_SETI(glProgramUniform1i,GL_INT,GL_BOOL,v0);
}

Program const* Program::set2i(std::string const&name,int32_t v0,int32_t v1)const{
  GE_GL_PROGRAM_SETI(glProgramUniform2i,GL_INT_VEC2,GL_BOOL_VEC2,v0,v1);
}

Program const* Program::set3i(std::string const&name,int32_t v0,int32_t v1,int32_t v2)const{
  GE_GL_PROGRAM_SETI(glProgramUniform3i,GL_INT_VEC3,GL_BOOL_VEC3,v0,v1,v2);
}

Program const* Program::set4i(std::string const&name,int32_t v0,int32_t v1,int32_t v2,int32_t v3)const{
  GE_GL_PROGRAM_SETI(glProgramUniform4i,GL_INT_VEC4,GL_BOOL_VEC4,v0,v1,v2,v3);
}

Program const* Program::set1ui(std::string const&name,uint32_t v0)const{
  GE_GL_PROGRAM_SET(glProgramUniform1ui,GL_UNSIGNED_INT,v0);
}

Program const* Program::set2ui(std::string const&name,uint32_t v0,uint32_t v1)const{
  GE_GL_PROGRAM_SET(glProgramUniform2ui,GL_UNSIGNED_INT_VEC2,v0,v1);
}

Program const* Program::set3ui(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2)const{
  GE_GL_PROGRAM_SET(glProgramUniform3ui,GL_UNSIGNED_INT_VEC3,v0,v1,v2);
}

Program const* Program::set4ui(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2,uint32_t v3)const{
  GE_GL_PROGRAM_SET(glProgramUniform4ui,GL_UNSIGNED_INT_VEC4,v0,v1,v2,v3);
}


Program const* Program::set1fv(std::string const&name,float const*v0,GLsizei count)const{
  GE_GL_PROGRAM_SETV(glProgramUniform1fv,GL_FLOAT);
}

Program const* Program::set2fv(std::string const&name,float const*v0,GLsizei count)const{
  GE_GL_PROGRAM_SETV(glProgramUniform2fv,GL_FLOAT_VEC2);
}

Program const* Program::set3fv(std::string const&name,float const*v0,GLsizei count)const{
  GE_GL_PROGRAM_SETV(glProgramUniform3fv,GL_FLOAT_VEC3);
}

Program const* Program::set4fv(std::string const&name,float const*v0,GLsizei count)const{
  GE_GL_PROGRAM_SETV(glProgramUniform4fv,GL_FLOAT_VEC4);
}

Program const* Program::set1iv(std::string const&name,int32_t const*v0,GLsizei count)const{
  GE_GL_PROGRAM_SETIV(glProgramUniform1iv,GL_INT,GL_BOOL);
}

Program const* Program::set2iv(std::string const&name,int32_t const*v0,GLsizei count)const{
  GE_GL_PROGRAM_SETIV(glProgramUniform2iv,GL_INT_VEC2,GL_BOOL_VEC2);
}

Program const* Program::set3iv(std::string const&name,int32_t const*v0,GLsizei count)const{
  GE_GL_PROGRAM_SETIV(glProgramUniform3iv,GL_INT_VEC3,GL_BOOL_VEC3);
}

Program const* Program::set4iv(std::string const&name,int32_t const*v0,GLsizei count)const{
  GE_GL_PROGRAM_SETIV(glProgramUniform4iv,GL_INT_VEC4,GL_BOOL_VEC4);
}

Program const* Program::set1uiv(std::string const&name,uint32_t const*v0,GLsizei count)const{
  GE_GL_PROGRAM_SETV(glProgramUniform1uiv,GL_UNSIGNED_INT);
}

Program const* Program::set2uiv(std::string const&name,uint32_t const*v0,GLsizei count)const{
  GE_GL_PROGRAM_SETV(glProgramUniform2uiv,GL_UNSIGNED_INT_VEC2);
}

Program const* Program::set3uiv(std::string const&name,uint32_t const*v0,GLsizei count)const{
  GE_GL_PROGRAM_SETV(glProgramUniform3uiv,GL_UNSIGNED_INT_VEC3);
}

Program const* Program::set4uiv(std::string const&name,uint32_t const*v0,GLsizei count)const{
  GE_GL_PROGRAM_SETV(glProgramUniform4uiv,GL_UNSIGNED_INT_VEC4);
}

Program const* Program::setMatrix4fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix4fv,GL_FLOAT_MAT4);
}

Program const* Program::setMatrix3fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix3fv,GL_FLOAT_MAT3);
}

Program const* Program::setMatrix2fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix2fv,GL_FLOAT_MAT2);
}

Program const* Program::setMatrix4x3fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix4x3fv,GL_FLOAT_MAT4x3);
}

Program const* Program::setMatrix4x2fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix4x2fv,GL_FLOAT_MAT4x2);
}

Program const* Program::setMatrix3x4fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix3x4fv,GL_FLOAT_MAT3x4);
}

Program const* Program::setMatrix3x2fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix3x2fv,GL_FLOAT_MAT3x2);
}

Program const* Program::setMatrix2x4fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix2x4fv,GL_FLOAT_MAT2x4);
}

Program const* Program::setMatrix2x3fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix2x3fv,GL_FLOAT_MAT2x3);
}

Program const* Program::setMatrix4dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix4dv,GL_DOUBLE_MAT4);
}

Program const* Program::setMatrix3dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix3dv,GL_DOUBLE_MAT3);
}

Program const* Program::setMatrix2dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix2dv,GL_DOUBLE_MAT2);
}

Program const* Program::setMatrix4x3dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix4x3dv,GL_DOUBLE_MAT4x3);
}

Program const* Program::setMatrix4x2dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix4x2dv,GL_DOUBLE_MAT4x2);
}

Program const* Program::setMatrix3x4dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix3x4dv,GL_DOUBLE_MAT3x4);
}

Program const* Program::setMatrix3x2dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix3x2dv,GL_DOUBLE_MAT3x2);
}

Program const* Program::setMatrix2x4dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix2x4dv,GL_DOUBLE_MAT2x4);
}

Program const* Program::setMatrix2x3dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose)const{
  GE_GL_PROGRAM_SETMATRIX(glProgramUniformMatrix2x3dv,GL_DOUBLE_MAT2x3);
}

GLint Program::_getUniform(std::string name){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);
  if(ii==this->_info->uniforms.end())
    return -1;
  return std::get<ProgramInfo::LOCATION>(ii->second);
}

void Program::_fillUniformInfo(){
  assert(this!=nullptr);
  GLint nofUniforms = this->getNofActiveUniforms();
  GLint longestUniform = this->getActiveUniformMaxLength();
  GLchar*buffer = new GLchar[longestUniform+1];
  assert(buffer!=nullptr);
  for(GLint i=0;i<nofUniforms;++i){
    GLenum type;
    GLint size;
    std::string name;
    GLint location;
    GLsizei length;
    this->_gl.glGetActiveUniform(this->_id,i,longestUniform,&length,&size,&type,buffer);
    name = this->_chopIndexingInPropertyName(std::string(buffer));
    location = this->getUniformLocation(name);
    this->_info->uniforms[name] = ProgramInfo::Properties(location,type,name,size);
    //add all variants name[0], name[1], ...
    for(GLint s=0;s<size;++s){
      std::string uniformNameWithIndexing = name+"["+ge::core::value2str(s)+"]";
      this->_info->uniforms[uniformNameWithIndexing] = ProgramInfo::Properties(
          this->getUniformLocation(uniformNameWithIndexing),
          type,
          uniformNameWithIndexing,
          1);
    }
  }
  delete[]buffer;
}

void Program::_fillAttribInfo(){
  assert(this!=nullptr);
  GLint nofAttribs = this->getNofActiveAttributes();
  GLint longestAttrib = this->getActiveAttributeMaxLength();
  GLchar*buffer = new GLchar[longestAttrib+1];
  assert(buffer!=nullptr);
  for(GLint i=0;i<nofAttribs;++i){
    GLenum type;
    GLint size;
    std::string name;
    GLint location;
    GLsizei length;
    this->_gl.glGetActiveAttrib(this->_id,i,longestAttrib,&length,&size,&type,buffer);
    name = this->_chopIndexingInPropertyName(std::string(buffer));
    location = this->getAttribLocation(name);
    this->_info->attribs[name] = ProgramInfo::Properties(location,type,name,size);
  }
  delete[]buffer;
}

void Program::_fillBufferInfo(){
  assert(this!=nullptr);
  GLuint nofBuffers = this->getInterfaceParam(GL_SHADER_STORAGE_BLOCK,GL_ACTIVE_RESOURCES);
  for(GLuint i=0;i<nofBuffers;++i){
    std::string name = this->_chopIndexingInPropertyName(this->getResourceName(GL_BUFFER_VARIABLE,i));
    GLint binding            = this->getResourceParam(GL_SHADER_STORAGE_BLOCK,GL_BUFFER_BINDING                      ,i);
    GLint dataSize           = this->getResourceParam(GL_SHADER_STORAGE_BLOCK,GL_BUFFER_DATA_SIZE                    ,i);
    GLint nofActiveVariables = this->getResourceParam(GL_SHADER_STORAGE_BLOCK,GL_NUM_ACTIVE_VARIABLES                ,i);
    GLint vertex             = this->getResourceParam(GL_SHADER_STORAGE_BLOCK,GL_REFERENCED_BY_VERTEX_SHADER         ,i);
    GLint control            = this->getResourceParam(GL_SHADER_STORAGE_BLOCK,GL_REFERENCED_BY_TESS_CONTROL_SHADER   ,i);
    GLint evaluation         = this->getResourceParam(GL_SHADER_STORAGE_BLOCK,GL_REFERENCED_BY_TESS_EVALUATION_SHADER,i);
    GLint geometry           = this->getResourceParam(GL_SHADER_STORAGE_BLOCK,GL_REFERENCED_BY_GEOMETRY_SHADER       ,i);
    GLint fragment           = this->getResourceParam(GL_SHADER_STORAGE_BLOCK,GL_REFERENCED_BY_FRAGMENT_SHADER       ,i);
    GLint compute            = this->getResourceParam(GL_SHADER_STORAGE_BLOCK,GL_REFERENCED_BY_COMPUTE_SHADER        ,i);
    this->_info->buffers[name] = ProgramInfo::BufferProperties(
        name,
        binding,
        dataSize,
        nofActiveVariables,
        vertex,
        control,
        evaluation,
        geometry,
        fragment,
        compute);
  }
}

void Program::_fillInfo(){
  assert(this!=nullptr);
  this->_fillUniformInfo();
  this->_fillAttribInfo();
  this->_fillBufferInfo();
}

std::string Program::_chopIndexingInPropertyName(std::string name)const{
  assert(this != nullptr);
  std::size_t pos = name.find("[0]");
  if(pos != std::string::npos)return name.substr(0,pos);
  return name;
}

GLuint const Program::nonExistingBufferBinding = std::numeric_limits<GLuint>::max();

GLuint Program::getBufferBinding(std::string const&name)const{
  assert(this != nullptr);
  auto ii = this->_info->buffers.find(name);
  if(ii == this->_info->buffers.end()){
    ge::core::printError(GE_CORE_FCENAME,"there is no such buffer",name);
    return Program::nonExistingBufferBinding;;
  }
  return std::get<ProgramInfo::BUFFER_BINDING>(ii->second);
}

Program const*Program::bindBuffer(
    std::string            const&name  ,
    std::shared_ptr<Buffer>const&buffer)const{
  assert(this   != nullptr);
  assert(buffer != nullptr);
  auto const& binding = this->getBufferBinding(name);
  if(binding != Program::nonExistingBufferBinding)
    buffer->bindBase(GL_SHADER_STORAGE_BUFFER,binding);
  return this;
}

Program const*Program::dispatch(GLuint nofWorkGroupsX,GLuint nofWorkGroupsY,GLuint nofWorkGroupsZ)const{
  assert(this!=nullptr);
  this->use();
  this->_gl.glDispatchCompute(nofWorkGroupsX,nofWorkGroupsY,nofWorkGroupsZ);
  return this;
}
