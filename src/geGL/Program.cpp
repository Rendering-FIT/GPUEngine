#include<geGL/Program.h>
#include<geGL/OpenGLUtil.h>
#include<iostream>
#include<string>
#include<geCore/ErrorPrinter.h>

using namespace ge::gl;

static bool printUniformWarnings = true;

void Program::setNonexistingUniformWarning(bool enableWarning){
  printUniformWarnings = enableWarning;
}

bool Program::isNonexistingUniformWarningEnabled(){
  return printUniformWarnings;
}

GLint Program::_getParam(GLenum pname)const{
  assert(this!=nullptr);
  GLint params;
  this->_gl.glGetProgramiv(this->getId(),pname,&params);
  return params;
}

Program::Program(ShaderPointers const&shaders){
  assert(this!=nullptr);
  this->_info = std::make_shared<ProgramInfo>();
  if(shaders.size()==0)return;
  this->link(shaders);
}

Program::Program(
    FunctionTablePointer const&table  ,
    ShaderPointers               const&shaders):OpenGLObject(table){
  assert(this!=nullptr);
  this->_info = std::make_shared<ProgramInfo>();
  if(shaders.size()==0)return;
  this->link(shaders);
}

void Program::create(){
  assert(this!=nullptr);
  if(this->_id != 0)return;
  this->_id = this->_gl.glCreateProgram();
}

Program::~Program(){
  assert(this!=nullptr);
  std::vector<ShaderPointer>forDeletion;
  for(auto const&x:this->_shaders)forDeletion.push_back(x);
  this->detachShaders(forDeletion);
  this->_gl.glDeleteProgram(this->_id);
}

GLboolean Program::isProgram()const{
  assert(this!=nullptr);
  return this->_gl.glIsProgram(this->_id);
}

void Program::attachShaders(ShaderPointers const&shaders){
  assert(this!=nullptr);
  this->create();
  for(auto const&x:shaders){
    this->_gl.glAttachShader(this->_id,x->getId());
    this->_shaders.insert(x);
    x->_programs.insert(this);
  }
}

void Program::detachShaders(ShaderPointers const&shaders){
  assert(this!=nullptr);
  for(auto const&x:shaders){
    this->_gl.glDetachShader(this->_id,x->getId());
    this->_shaders.erase(x);
    x->_programs.erase(this);
  }
}

void Program::link(ShaderPointers const&shaders){
  assert(this!=nullptr);
  this->attachShaders(shaders);
  this->_gl.glLinkProgram(this->_id);
  if(!this->getLinkStatus()){
    std::cerr<<this->getInfoLog()<<std::endl;
  }
  this->_fillInfo();
}

void Program::use()const{
  assert(this!=nullptr);
  this->_gl.glUseProgram(this->_id);
}

void Program::validate()const{
  assert(this!=nullptr);
  this->_gl.glValidateProgram(this->_id);
}

GLint Program::getUniformLocation(std::string const&name)const{
  assert(this!=nullptr);
  return this->_gl.glGetUniformLocation(this->_id,name.c_str());
}

GLint Program::getAttribLocation (std::string const&name)const{
  assert(this!=nullptr);
  return this->_gl.glGetAttribLocation(this->_id,name.c_str());
}

GLboolean Program::getDeleteStatus()const{
  assert(this!=nullptr);
  return (GLboolean)this->_getParam(GL_DELETE_STATUS);
}

GLboolean Program::getLinkStatus()const{
  assert(this!=nullptr);
  return (GLboolean)this->_getParam(GL_LINK_STATUS);
}

GLboolean Program::getValidateStatus()const{
  assert(this!=nullptr);
  return (GLboolean)this->_getParam(GL_VALIDATE_STATUS);
}

GLuint    Program::getInfoLogLength()const{
  assert(this!=nullptr);
  return this->_getParam(GL_INFO_LOG_LENGTH);
}

GLuint    Program::getNofShaders()const{
  assert(this!=nullptr);
  return this->_getParam(GL_ATTACHED_SHADERS);
}

GLuint    Program::getNofActiveAtomicCounterBuffers()const{
  assert(this!=nullptr);
  return this->_getParam(GL_ACTIVE_ATOMIC_COUNTER_BUFFERS);
}

GLuint    Program::getNofActiveAttributes()const{
  assert(this!=nullptr);
  return this->_getParam(GL_ACTIVE_ATTRIBUTES);
}

GLuint    Program::getActiveAttributeMaxLength()const{
  assert(this!=nullptr);
  return this->_getParam(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
}

GLuint    Program::getNofActiveUniforms()const{
  assert(this!=nullptr);
  return this->_getParam(GL_ACTIVE_UNIFORMS);
}

GLuint    Program::getActiveUniformMaxLength()const{
  assert(this!=nullptr);
  return this->_getParam(GL_ACTIVE_UNIFORM_MAX_LENGTH);
}

GLuint    Program::getBinaryLength()const{
  assert(this!=nullptr);
  return this->_getParam(GL_PROGRAM_BINARY_LENGTH);
}

void      Program::getComputeWorkGroupSize(GLint*x){
  assert(this!=nullptr);
  this->_gl.glGetProgramiv(this->getId(),GL_COMPUTE_WORK_GROUP_SIZE,x);
}

GLenum    Program::getTransformFeedbackBufferMode()const{
  assert(this!=nullptr);
  return this->_getParam(GL_TRANSFORM_FEEDBACK_BUFFER_MODE);
}

GLuint    Program::getNofTransfromFeedbackVaryings()const{
  assert(this!=nullptr);
  return this->_getParam(GL_TRANSFORM_FEEDBACK_VARYINGS);
}

GLuint    Program::getTransformFeedbackVaryingMaxLength()const{
  assert(this!=nullptr);
  return this->_getParam(GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH);
}

GLuint    Program::getNofGeometryVerticesOut()const{
  assert(this!=nullptr);
  return this->_getParam(GL_GEOMETRY_VERTICES_OUT);
}

GLenum    Program::getGeometryInputType()const{
  assert(this!=nullptr);
  return this->_getParam(GL_GEOMETRY_INPUT_TYPE);
}

GLenum    Program::getGeometryOutputType()const{
  assert(this!=nullptr);
  return this->_getParam(GL_GEOMETRY_OUTPUT_TYPE);
}

std::string Program::getInfoLog()const{
  assert(this!=nullptr);
  GLuint length = this->getInfoLogLength();
  if(!length)return"";
  std::string info(length,' ');
  this->_gl.glGetProgramInfoLog(this->getId(),length,NULL,(GLchar*)info.c_str());
  return info;
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

GLint Program::getInterfaceParam(GLenum interface,GLenum pname)const{
  assert(this!=nullptr);
  GLint params;
  this->_gl.glGetProgramInterfaceiv(
      this->_id,
      interface,
      pname,
      &params);
  return params;
}

std::string Program::getResourceName(GLenum interface,GLuint index)const{
  assert(this!=nullptr);
  GLuint maxLength = this->getInterfaceParam(interface,GL_MAX_NAME_LENGTH);
  char*buffer = new char[maxLength];
  assert(buffer!=nullptr);
  this->_gl.glGetProgramResourceName(
      this->_id,
      interface,
      index,
      maxLength,
      nullptr,
      buffer);
  std::string name(buffer);
  delete[]buffer;
  return name;
}

GLint Program::getResourceParam(GLenum interface,GLenum pname,GLuint index)const{
  assert(this!=nullptr);
  GLint param;
  this->_gl.glGetProgramResourceiv(
      this->_id,
      interface,
      index,
      1,
      &pname,
      1,
      nullptr,
      &param);
  return param;
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
  assert(this!=nullptr);
  std::size_t pos=name.find("[0]");
  if(pos!=std::string::npos)return name.substr(0,pos);
  return name;
}

void Program::set1f(std::string const&name,float v0){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT);
  std::get<ProgramInfo::LOCATION>(ii->second);
  this->_gl.glProgramUniform1f(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),v0);
}

void Program::set2f(std::string const&name,float v0,float v1){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_VEC2);
  this->_gl.glProgramUniform2f(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),v0,v1);
}

void Program::set3f(std::string const&name,float v0,float v1,float v2){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_VEC3);
  this->_gl.glProgramUniform3f(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),v0,v1,v2);
}

void Program::set4f(std::string const&name,float v0,float v1,float v2,float v3){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_VEC4);
  this->_gl.glProgramUniform4f(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),v0,v1,v2,v3);
}

void Program::set1i(std::string const&name,int32_t v0){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(
      std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_INT          || 
      ge::gl::isSamplerType(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name])));
  this->_gl.glProgramUniform1i(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),v0);
}

void Program::set2i(std::string const&name,int32_t v0,int32_t v1){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_INT_VEC2);
  this->_gl.glProgramUniform2i(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),v0,v1);
}

void Program::set3i(std::string const&name,int32_t v0,int32_t v1,int32_t v2){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_INT_VEC3);
  this->_gl.glProgramUniform3i(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),v0,v1,v2);
}

void Program::set4i(std::string const&name,int32_t v0,int32_t v1,int32_t v2,int32_t v3){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_INT_VEC4);
  this->_gl.glProgramUniform4i(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),v0,v1,v2,v3);
}

void Program::set1ui(std::string const&name,uint32_t v0){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_UNSIGNED_INT ||
      ge::gl::isSamplerType(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name])));
  this->_gl.glProgramUniform1ui(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),v0);
}

void Program::set2ui(std::string const&name,uint32_t v0,uint32_t v1){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_UNSIGNED_INT_VEC2);
  this->_gl.glProgramUniform2ui(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),v0,v1);
}

void Program::set3ui(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_UNSIGNED_INT_VEC3);
  this->_gl.glProgramUniform3ui(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),v0,v1,v2);
}

void Program::set4ui(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2,uint32_t v3){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_UNSIGNED_INT_VEC4);
  this->_gl.glProgramUniform4ui(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),v0,v1,v2,v3);
}


void Program::set1fv(std::string const&name,float const*v0,GLsizei count){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniform1fv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,v0);
}

void Program::set2fv(std::string const&name,float const*v0,GLsizei count){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_VEC2);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniform2fv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,v0);
}

void Program::set3fv(std::string const&name,float const*v0,GLsizei count){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_VEC3);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniform3fv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,v0);
}

void Program::set4fv(std::string const&name,float const*v0,GLsizei count){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_VEC4);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniform4fv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,v0);
}

void Program::set1iv(std::string const&name,int32_t const*v0,GLsizei count){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_INT);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniform1iv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,v0);
}

void Program::set2iv(std::string const&name,int32_t const*v0,GLsizei count){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_INT_VEC2);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniform2iv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,v0);
}

void Program::set3iv(std::string const&name,int32_t const*v0,GLsizei count){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_INT_VEC3);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniform3iv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,v0);
}

void Program::set4iv(std::string const&name,int32_t const*v0,GLsizei count){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_INT_VEC4);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniform4iv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,v0);
}

void Program::set1uiv(std::string const&name,uint32_t const*v0,GLsizei count){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_UNSIGNED_INT);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniform1uiv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,v0);
}

void Program::set2uiv(std::string const&name,uint32_t const*v0,GLsizei count){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_UNSIGNED_INT_VEC2);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniform2uiv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,v0);
}

void Program::set3uiv(std::string const&name,uint32_t const*v0,GLsizei count){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_UNSIGNED_INT_VEC3);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniform3uiv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,v0);
}

void Program::set4uiv(std::string const&name,uint32_t const*v0,GLsizei count){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_UNSIGNED_INT_VEC4);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniform4uiv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,v0);
}

void Program::setMatrix4fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_MAT4);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix4fv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix3fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_MAT3);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix3fv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix2fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_MAT2);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix2fv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix4x3fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_MAT4x3);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix4x3fv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix4x2fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_MAT4x2);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix4x2fv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix3x4fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_MAT3x4);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix3x4fv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix3x2fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_MAT3x2);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix3x2fv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix2x4fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_MAT2x4);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix2x4fv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix2x3fv(std::string const&name,float const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_FLOAT_MAT2x3);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix2x3fv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix4dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_DOUBLE_MAT4);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix4dv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix3dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_DOUBLE_MAT3);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix3dv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix2dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_DOUBLE_MAT2);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix2dv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix4x3dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_DOUBLE_MAT4x3);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix4x3dv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix4x2dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_DOUBLE_MAT4x2);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix4x2dv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix3x4dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_DOUBLE_MAT3x4);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix3x4dv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix3x2dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_DOUBLE_MAT3x2);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix3x2dv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix2x4dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_DOUBLE_MAT2x4);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix2x4dv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

void Program::setMatrix2x3dv(std::string const&name,double const*v0,GLsizei count,GLboolean transpose){
  assert(this!=nullptr);
  auto ii = this->_info->uniforms.find(name);if(ii==this->_info->uniforms.end()){if(printUniformWarnings)ge::core::printError(GE_CORE_FCENAME,"there is no such uniform",name);return;}
  assert(std::get<ProgramInfo::TYPE>(this->_info->uniforms[name]) == GL_DOUBLE_MAT2x3);
  assert(count<=std::get<ProgramInfo::SIZE>(this->_info->uniforms[name]));
  this->_gl.glProgramUniformMatrix2x3dv(this->_id,std::get<ProgramInfo::LOCATION>(ii->second),count,transpose,v0);
}

