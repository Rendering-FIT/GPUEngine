#include<geGL/ShaderObjectParameter.h>
#include<sstream>

using namespace ge::gl;

ShaderObjectParameter::ShaderObjectParameter(
    GLint       location,
    GLenum      type,
    std::string name,
    GLint       size){
  this->location = location;//parameter id
  this->type     = type;//parameter type
  this->name     = name;//parameter name
  this->size     = size;//parameter size
}

std::string ge::gl::translateUniformType(GLenum type){
  switch(type){
    case GL_FLOAT                                    :return"GL_FLOAT"                                    ;
    case GL_FLOAT_VEC2                               :return"GL_FLOAT_VEC2"                               ;
    case GL_FLOAT_VEC3                               :return"GL_FLOAT_VEC3"                               ;
    case GL_FLOAT_VEC4                               :return"GL_FLOAT_VEC4"                               ;
    case GL_DOUBLE                                   :return"GL_DOUBLE"                                   ;
    case GL_DOUBLE_VEC2                              :return"GL_DOUBLE_VEC2"                              ;
    case GL_DOUBLE_VEC3                              :return"GL_DOUBLE_VEC3"                              ;
    case GL_DOUBLE_VEC4                              :return"GL_DOUBLE_VEC4"                              ;
    case GL_INT                                      :return"GL_INT"                                      ;
    case GL_INT_VEC2                                 :return"GL_INT_VEC2"                                 ;
    case GL_INT_VEC3                                 :return"GL_INT_VEC3"                                 ;
    case GL_INT_VEC4                                 :return"GL_INT_VEC4"                                 ;
    case GL_UNSIGNED_INT                             :return"GL_UNSIGNED_INT"                             ;
    case GL_UNSIGNED_INT_VEC2                        :return"GL_UNSIGNED_INT_VEC2"                        ;
    case GL_UNSIGNED_INT_VEC3                        :return"GL_UNSIGNED_INT_VEC3"                        ;
    case GL_UNSIGNED_INT_VEC4                        :return"GL_UNSIGNED_INT_VEC4"                        ;
    case GL_BOOL                                     :return"GL_BOOL"                                     ;
    case GL_BOOL_VEC2                                :return"GL_BOOL_VEC2"                                ;
    case GL_BOOL_VEC3                                :return"GL_BOOL_VEC3"                                ;
    case GL_BOOL_VEC4                                :return"GL_BOOL_VEC4"                                ;
    case GL_FLOAT_MAT2                               :return"GL_FLOAT_MAT2"                               ;
    case GL_FLOAT_MAT3                               :return"GL_FLOAT_MAT3"                               ;
    case GL_FLOAT_MAT4                               :return"GL_FLOAT_MAT4"                               ;
    case GL_FLOAT_MAT2x3                             :return"GL_FLOAT_MAT2x3"                             ;
    case GL_FLOAT_MAT2x4                             :return"GL_FLOAT_MAT2x4"                             ;
    case GL_FLOAT_MAT3x2                             :return"GL_FLOAT_MAT3x2"                             ;
    case GL_FLOAT_MAT3x4                             :return"GL_FLOAT_MAT3x4"                             ;
    case GL_FLOAT_MAT4x2                             :return"GL_FLOAT_MAT4x2"                             ;
    case GL_FLOAT_MAT4x3                             :return"GL_FLOAT_MAT4x3"                             ;
    case GL_DOUBLE_MAT2                              :return"GL_DOUBLE_MAT2"                              ;
    case GL_DOUBLE_MAT3                              :return"GL_DOUBLE_MAT3"                              ;
    case GL_DOUBLE_MAT4                              :return"GL_DOUBLE_MAT4"                              ;
    case GL_DOUBLE_MAT2x3                            :return"GL_DOUBLE_MAT2x3"                            ;
    case GL_DOUBLE_MAT2x4                            :return"GL_DOUBLE_MAT2x4"                            ;
    case GL_DOUBLE_MAT3x2                            :return"GL_DOUBLE_MAT3x2"                            ;
    case GL_DOUBLE_MAT3x4                            :return"GL_DOUBLE_MAT3x4"                            ;
    case GL_DOUBLE_MAT4x2                            :return"GL_DOUBLE_MAT4x2"                            ;
    case GL_DOUBLE_MAT4x3                            :return"GL_DOUBLE_MAT4x3"                            ;
    case GL_SAMPLER_1D                               :return"GL_SAMPLER_1D"                               ;
    case GL_SAMPLER_2D                               :return"GL_SAMPLER_2D"                               ;
    case GL_SAMPLER_3D                               :return"GL_SAMPLER_3D"                               ;
    case GL_SAMPLER_CUBE                             :return"GL_SAMPLER_CUBE"                             ;
    case GL_SAMPLER_1D_SHADOW                        :return"GL_SAMPLER_1D_SHADOW"                        ;
    case GL_SAMPLER_2D_SHADOW                        :return"GL_SAMPLER_2D_SHADOW"                        ;
    case GL_SAMPLER_1D_ARRAY                         :return"GL_SAMPLER_1D_ARRAY"                         ;
    case GL_SAMPLER_2D_ARRAY                         :return"GL_SAMPLER_2D_ARRAY"                         ;
    case GL_SAMPLER_1D_ARRAY_SHADOW                  :return"GL_SAMPLER_1D_ARRAY_SHADOW"                  ;
    case GL_SAMPLER_2D_ARRAY_SHADOW                  :return"GL_SAMPLER_2D_ARRAY_SHADOW"                  ;
    case GL_SAMPLER_2D_MULTISAMPLE                   :return"GL_SAMPLER_2D_MULTISAMPLE"                   ;
    case GL_SAMPLER_2D_MULTISAMPLE_ARRAY             :return"GL_SAMPLER_2D_MULTISAMPLE_ARRAY"             ;
    case GL_SAMPLER_CUBE_SHADOW                      :return"GL_SAMPLER_CUBE_SHADOW"                      ;
    case GL_SAMPLER_BUFFER                           :return"GL_SAMPLER_BUFFER"                           ;
    case GL_SAMPLER_2D_RECT                          :return"GL_SAMPLER_2D_RECT"                          ;
    case GL_SAMPLER_2D_RECT_SHADOW                   :return"GL_SAMPLER_2D_RECT_SHADOW"                   ;
    case GL_INT_SAMPLER_1D                           :return"GL_INT_SAMPLER_1D"                           ;
    case GL_INT_SAMPLER_2D                           :return"GL_INT_SAMPLER_2D"                           ;
    case GL_INT_SAMPLER_3D                           :return"GL_INT_SAMPLER_3D"                           ;
    case GL_INT_SAMPLER_CUBE                         :return"GL_INT_SAMPLER_CUBE"                         ;
    case GL_INT_SAMPLER_1D_ARRAY                     :return"GL_INT_SAMPLER_1D_ARRAY"                     ;
    case GL_INT_SAMPLER_2D_ARRAY                     :return"GL_INT_SAMPLER_2D_ARRAY"                     ;
    case GL_INT_SAMPLER_2D_MULTISAMPLE               :return"GL_INT_SAMPLER_2D_MULTISAMPLE"               ;
    case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY         :return"GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY"         ;
    case GL_INT_SAMPLER_BUFFER                       :return"GL_INT_SAMPLER_BUFFER"                       ;
    case GL_INT_SAMPLER_2D_RECT                      :return"GL_INT_SAMPLER_2D_RECT"                      ;
    case GL_UNSIGNED_INT_SAMPLER_1D                  :return"GL_UNSIGNED_INT_SAMPLER_1D"                  ;
    case GL_UNSIGNED_INT_SAMPLER_2D                  :return"GL_UNSIGNED_INT_SAMPLER_2D"                  ;
    case GL_UNSIGNED_INT_SAMPLER_3D                  :return"GL_UNSIGNED_INT_SAMPLER_3D"                  ;
    case GL_UNSIGNED_INT_SAMPLER_CUBE                :return"GL_UNSIGNED_INT_SAMPLER_CUBE"                ;
    case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY            :return"GL_UNSIGNED_INT_SAMPLER_1D_ARRAY"            ;
    case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY            :return"GL_UNSIGNED_INT_SAMPLER_2D_ARRAY"            ;
    case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE      :return"GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE"      ;
    case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:return"GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY";
    case GL_UNSIGNED_INT_SAMPLER_BUFFER              :return"GL_UNSIGNED_INT_SAMPLER_BUFFER"              ;
    case GL_UNSIGNED_INT_SAMPLER_2D_RECT             :return"GL_UNSIGNED_INT_SAMPLER_2D_RECT"             ;
    default                                          :return"unknown"                                     ;
  }
}
std::string ge::gl::translateBufferProperty(GLenum property){
  switch(property){
    case GL_TYPE                                :return"GL_TYPE"                                ;
    case GL_ARRAY_SIZE                          :return"GL_ARRAY_SIZE"                          ;
    case GL_OFFSET                              :return"GL_OFFSET"                              ;
    case GL_BLOCK_INDEX                         :return"GL_BLOCK_INDEX"                         ;
    case GL_ARRAY_STRIDE                        :return"GL_ARRAY_STRIDE"                        ;
    case GL_MATRIX_STRIDE                       :return"GL_MATRIX_STRIDE"                       ;
    case GL_IS_ROW_MAJOR                        :return"GL_IS_ROW_MAJOR"                        ;
    case GL_REFERENCED_BY_VERTEX_SHADER         :return"GL_REFERENCED_BY_VERTEX_SHADER"         ;
    case GL_REFERENCED_BY_TESS_CONTROL_SHADER   :return"GL_REFERENCED_BY_TESS_CONTROL_SHADER"   ;
    case GL_REFERENCED_BY_TESS_EVALUATION_SHADER:return"GL_REFERENCED_BY_TESS_EVALUATION_SHADER";
    case GL_REFERENCED_BY_GEOMETRY_SHADER       :return"GL_REFERENCED_BY_GEOMETRY_SHADER"       ;
    case GL_REFERENCED_BY_FRAGMENT_SHADER       :return"GL_REFERENCED_BY_FRAGMENT_SHADER"       ;
    case GL_REFERENCED_BY_COMPUTE_SHADER        :return"GL_REFERENCED_BY_COMPUTE_SHADER"        ;
    case GL_TOP_LEVEL_ARRAY_SIZE                :return"GL_TOP_LEVEL_ARRAY_SIZE"                ;
    case GL_TOP_LEVEL_ARRAY_STRIDE              :return"GL_TOP_LEVEL_ARRAY_STRIDE"              ;
    default                                     :return"unknown"                                ;
  }
}

const GLenum bufferProperties[]={
  GL_TYPE                                ,
  GL_ARRAY_SIZE                          ,
  GL_OFFSET                              ,
  GL_BLOCK_INDEX                         ,
  GL_ARRAY_STRIDE                        ,
  GL_MATRIX_STRIDE                       ,
  GL_IS_ROW_MAJOR                        ,
  GL_REFERENCED_BY_VERTEX_SHADER         ,
  GL_REFERENCED_BY_TESS_CONTROL_SHADER   ,
  GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
  GL_REFERENCED_BY_GEOMETRY_SHADER       ,
  GL_REFERENCED_BY_FRAGMENT_SHADER       ,
  GL_REFERENCED_BY_COMPUTE_SHADER        ,
  GL_TOP_LEVEL_ARRAY_SIZE                ,
  GL_TOP_LEVEL_ARRAY_STRIDE              ,
};
const unsigned nofBufferProperties = sizeof(bufferProperties)/sizeof(GLenum);

std::string ge::gl::chopIndexingInPropertyName(std::string name){
  std::size_t pos=name.find("[0]");
  if(pos!=std::string::npos)return name.substr(0,pos);
  return name;
}

BufferParams::BufferParams(GLuint program,GLuint index){
  //std::cerr<<"BufferParams\n";
  GLint lenght;
  glGetProgramResourceiv(
      program,
      GL_BUFFER_VARIABLE,
      index,
      nofBufferProperties,
      bufferProperties,
      sizeof(this->_params)/sizeof(GLint),
      &lenght,
      this->_params);
  GLint bufLen=0;
  glGetProgramInterfaceiv(
      program,
      GL_BUFFER_VARIABLE,
      GL_MAX_NAME_LENGTH,
      &bufLen);
  char*buffer = new char[bufLen];
  glGetProgramResourceName(
      program,
      GL_BUFFER_VARIABLE,
      index,
      bufLen,
      &lenght,
      buffer);
  //this->_name = std::string(buffer);
  this->_name = chopIndexingInPropertyName(std::string(buffer));
  //std::cerr<<"BINDING\n";
  GLenum bindingProperty=GL_BUFFER_BINDING;
  glGetProgramResourceiv(program,GL_SHADER_STORAGE_BLOCK,index,1,&bindingProperty,1,&lenght,&this->_binding);
  delete[]buffer;
  //std::cerr<<this->toStr()<<std::endl;
  //std::cerr<<"name: "<<this->_name<<std::endl;
  //std::cerr<<"binding: "<<this->_binding<<std::endl;
}
GLint BufferParams::getProperty(enum Properties property){
  return this->_params[(int)property];
}
std::string BufferParams::getName(){
  return this->_name;
}
std::string BufferParams::toStr(){
  std::stringstream ss;
  for(unsigned i=0;i<nofBufferProperties;++i){
    ss<<translateBufferProperty(bufferProperties[i])<<" : ";
    if(bufferProperties[i]==GL_TYPE)ss<<translateUniformType(this->_params[i]);
    else ss<<this->_params[i];
    ss<<std::endl;
  }
  return ss.str();
}

GLint BufferParams::getBinding(){
  return this->_binding;
}


bool SamplerParam::isSampler(GLenum type){
  switch(type){
    case GL_SAMPLER_1D                               :
    case GL_SAMPLER_2D                               :
    case GL_SAMPLER_3D                               :
    case GL_SAMPLER_CUBE                             :
    case GL_SAMPLER_1D_SHADOW                        :
    case GL_SAMPLER_2D_SHADOW                        :
    case GL_SAMPLER_1D_ARRAY                         :
    case GL_SAMPLER_2D_ARRAY                         :
    case GL_SAMPLER_1D_ARRAY_SHADOW                  :
    case GL_SAMPLER_2D_ARRAY_SHADOW                  :
    case GL_SAMPLER_2D_MULTISAMPLE                   :
    case GL_SAMPLER_2D_MULTISAMPLE_ARRAY             :
    case GL_SAMPLER_CUBE_SHADOW                      :
    case GL_SAMPLER_BUFFER                           :
    case GL_SAMPLER_2D_RECT                          :
    case GL_SAMPLER_2D_RECT_SHADOW                   :
    case GL_INT_SAMPLER_1D                           :
    case GL_INT_SAMPLER_2D                           :
    case GL_INT_SAMPLER_3D                           :
    case GL_INT_SAMPLER_CUBE                         :
    case GL_INT_SAMPLER_1D_ARRAY                     :
    case GL_INT_SAMPLER_2D_ARRAY                     :
    case GL_INT_SAMPLER_2D_MULTISAMPLE               :
    case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY         :
    case GL_INT_SAMPLER_BUFFER                       :
    case GL_INT_SAMPLER_2D_RECT                      :
    case GL_UNSIGNED_INT_SAMPLER_1D                  :
    case GL_UNSIGNED_INT_SAMPLER_2D                  :
    case GL_UNSIGNED_INT_SAMPLER_3D                  :
    case GL_UNSIGNED_INT_SAMPLER_CUBE                :
    case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY            :
    case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY            :
    case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE      :
    case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
    case GL_UNSIGNED_INT_SAMPLER_BUFFER              :
    case GL_UNSIGNED_INT_SAMPLER_2D_RECT             :
                                                      return true;
    default:
                                                      return false;
  }
}

SamplerParam::SamplerParam(){}

SamplerParam::SamplerParam(std::string name,GLint location,GLenum type,GLint binding){
  this->_name     = name    ;
  this->_location = location;
  this->_type     = type    ;
  this->_binding  = binding ;
}

std::string SamplerParam::getName(){
  return this->_name;
}

void SamplerParam::setBinding(GLint binding){
  this->_binding = binding;
  glUniform1i(this->_location,binding);
}

GLint SamplerParam::getBinding(){
  return this->_binding;
}

GLint SamplerParam::getLocation(){
  return this->_location;
}


