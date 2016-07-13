#include<geGL/Program.h>
#include<geGL/OpenGLUtil.h>
#include<iostream>
#include<string>

using namespace ge::gl;
using namespace ge::gl::opengl;

GLint Program::_getParam(GLenum pname)const{
  GLint params;
  glGetProgramiv(this->getId(),pname,&params);
  return params;
}

Program::Program(ShaderPointers const&shaders){
  this->_info = std::make_shared<ProgramInfo>();
  if(shaders.size()==0)return;
  this->link(shaders);
}

Program::Program(
    opengl::FunctionTablePointer const&table  ,
    ShaderPointers               const&shaders):OpenGLObject(table){
  this->_info = std::make_shared<ProgramInfo>();
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
  if(!this->getLinkStatus()){
    std::cerr<<this->getInfoLog()<<std::endl;
  }
  this->_fillInfo();
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

GLboolean Program::getDeleteStatus()const{
  return (GLboolean)this->_getParam(GL_DELETE_STATUS);
}

GLboolean Program::getLinkStatus()const{
  return (GLboolean)this->_getParam(GL_LINK_STATUS);
}

GLboolean Program::getValidateStatus()const{
  return (GLboolean)this->_getParam(GL_VALIDATE_STATUS);
}

GLuint    Program::getInfoLogLength()const{
  return this->_getParam(GL_INFO_LOG_LENGTH);
}

GLuint    Program::getNofShaders()const{
  return this->_getParam(GL_ATTACHED_SHADERS);
}

GLuint    Program::getNofActiveAtomicCounterBuffers()const{
  return this->_getParam(GL_ACTIVE_ATOMIC_COUNTER_BUFFERS);
}

GLuint    Program::getNofActiveAttributes()const{
  return this->_getParam(GL_ACTIVE_ATTRIBUTES);
}

GLuint    Program::getActiveAttributeMaxLength()const{
  return this->_getParam(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
}

GLuint    Program::getNofActiveUniforms()const{
  return this->_getParam(GL_ACTIVE_UNIFORMS);
}

GLuint    Program::getActiveUniformMaxLength()const{
  return this->_getParam(GL_ACTIVE_UNIFORM_MAX_LENGTH);
}

GLuint    Program::getBinaryLength()const{
  return this->_getParam(GL_PROGRAM_BINARY_LENGTH);
}

void      Program::getComputeWorkGroupSize(GLint*x){
  glGetProgramiv(this->getId(),GL_COMPUTE_WORK_GROUP_SIZE,x);
}

GLenum    Program::getTransformFeedbackBufferMode()const{
  return this->_getParam(GL_TRANSFORM_FEEDBACK_BUFFER_MODE);
}

GLuint    Program::getNofTransfromFeedbackVaryings()const{
  return this->_getParam(GL_TRANSFORM_FEEDBACK_VARYINGS);
}

GLuint    Program::getTransformFeedbackVaryingMaxLength()const{
  return this->_getParam(GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH);
}

GLuint    Program::getNofGeometryVerticesOut()const{
  return this->_getParam(GL_GEOMETRY_VERTICES_OUT);
}

GLenum    Program::getGeometryInputType()const{
  return this->_getParam(GL_GEOMETRY_INPUT_TYPE);
}

GLenum    Program::getGeometryOutputType()const{
  return this->_getParam(GL_GEOMETRY_OUTPUT_TYPE);
}

std::string Program::getInfoLog()const{
  GLuint length = this->getInfoLogLength();
  if(!length)return"";
  std::string info(length,' ');
  glGetProgramInfoLog(this->getId(),length,NULL,(GLchar*)info.c_str());
  return info;
}

GLint Program::_getUniform(std::string name){
  auto ii = this->_info->uniforms.find(name);
  if(ii==this->_info->uniforms.end())
    return -1;
  return std::get<ProgramInfo::LOCATION>(ii->second);
}

void Program::_fillUniformInfo(){
  GLint nofUniforms = this->getNofActiveUniforms();
  GLint longestUniform = this->getActiveUniformMaxLength();
  GLchar*buffer = new GLchar[longestUniform+1];
  for(GLint i=0;i<nofUniforms;++i){
    GLenum type;
    GLint size;
    std::string name;
    GLint location;
    GLsizei length;
    glGetActiveUniform(this->_id,i,longestUniform,&length,&size,&type,buffer);
    name = this->_chopIndexingInPropertyName(std::string(buffer));
    location = this->getUniformLocation(name);
    this->_info->uniforms[name] = ProgramInfo::Properties(location,type,name,size);
  }
  delete[]buffer;
}

void Program::_fillAttribInfo(){
  GLint nofAttribs = this->getNofActiveAttributes();
  GLint longestAttrib = this->getActiveAttributeMaxLength();
  GLchar*buffer = new GLchar[longestAttrib+1];
  for(GLint i=0;i<nofAttribs;++i){
    GLenum type;
    GLint size;
    std::string name;
    GLint location;
    GLsizei length;
    glGetActiveAttrib(this->_id,i,longestAttrib,&length,&size,&type,buffer);
    name = this->_chopIndexingInPropertyName(std::string(buffer));
    location = this->getAttribLocation(name);
    this->_info->attribs[name] = ProgramInfo::Properties(location,type,name,size);
  }
  delete[]buffer;
}

GLint Program::getInterfaceParam(GLenum interface,GLenum pname)const{
  GLint params;
  glGetProgramInterfaceiv(
      this->_id,
      interface,
      pname,
      &params);
  return params;
}

std::string Program::getResourceName(GLenum interface,GLuint index)const{
  GLuint maxLength = this->getInterfaceParam(interface,GL_MAX_NAME_LENGTH);
  char*buffer = new char[maxLength];
  glGetProgramResourceName(
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
  GLint param;
  glGetProgramResourceiv(
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
  this->_fillUniformInfo();
  this->_fillAttribInfo();
  this->_fillBufferInfo();
}

std::string Program::_chopIndexingInPropertyName(std::string name)const{
  std::size_t pos=name.find("[0]");
  if(pos!=std::string::npos)return name.substr(0,pos);
  return name;
}
