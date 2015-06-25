#include<geGL/ShaderObjectsCommands.h>

using namespace ge::gl;

SharedShader::SharedShader(std::shared_ptr<GLuint>shader){
  this->_shader = shader;
}

std::shared_ptr<GLuint>SharedShader::getShader(){
  return this->_shader;
}

CreateShader::CreateShader(
    std::shared_ptr<GLuint>shader,
    std::shared_ptr<GLenum>type):SharedShader(shader){
  this->_type   = type;
}

void CreateShader::operator()(){
  *this->_shader = glCreateShader(*this->_type);
}

std::shared_ptr<GLenum>CreateShader::getType(){
  return this->_type;
}



ShaderSourceData::ShaderSourceData(
    GLsizei             count ,
    const GLchar*const* string,
    const GLint*        length){
  this->set(count,string,length);
}

void ShaderSourceData::set(
    GLsizei             count ,
    const GLchar*const* string,
    const GLint*        length){
  this->_count  = count;
  this->_string = string;
  this->_length = length;
}

GLsizei ShaderSourceData::getCount(){
  return this->_count;
}

const GLchar*const*ShaderSourceData::getString(){
  return this->_string;
}

const GLint*ShaderSourceData::getLength(){
  return this->_length;
}



ShaderSource::ShaderSource(
    std::shared_ptr<GLuint>shader        ,
    std::shared_ptr<ShaderSourceData>data):SharedShader(shader){
  this->_data   = data  ;
}

void ShaderSource::operator()(){
  glShaderSource(
      *this->_shader,
      this->_data->getCount(),
      this->_data->getString(),
      this->_data->getLength());
}

std::shared_ptr<ShaderSourceData>ShaderSource::getData(){
  return this->_data;
}



CompileShader::CompileShader(std::shared_ptr<GLuint>shader):SharedShader(shader){}

void CompileShader::operator()(){
  glCompileShader(*this->_shader);
}



ReleaseShaderCompiler::ReleaseShaderCompiler(){}

void ReleaseShaderCompiler::operator()(){
  glReleaseShaderCompiler();
}



DeleteShader::DeleteShader(std::shared_ptr<GLuint>shader):SharedShader(shader){}

void DeleteShader::operator()(){
  glDeleteShader(*this->_shader);
}



IsShader::IsShader(std::shared_ptr<GLboolean>is,std::shared_ptr<GLuint>shader):SharedShader(shader){
  this->_is = is;
}

void IsShader::operator()(){
  *this->_is = glIsShader(*this->_shader);
}



ShaderBinaryData::ShaderBinaryData(
    GLenum        format,
    const GLvoid* binary,
    GLsizei       length){
  this->set(format,binary,length);
}

void ShaderBinaryData::set(
    GLenum        format,
    const GLvoid* binary,
    GLsizei       length){
  this->_format = format;
  this->_binary = binary;
  this->_length = length;
}

GLenum ShaderBinaryData::getFormat(){
  return this->_format;
}

const GLvoid*ShaderBinaryData::getBinary(){
  return this->_binary;
}

GLsizei ShaderBinaryData::getLength(){
  return this->_length;
}



ShaderBinary::ShaderBinary(
    std::shared_ptr<GLsizei>         count  ,
    std::shared_ptr<GLuint>          shaders,
    std::shared_ptr<ShaderBinaryData>binary ){
  this->_count   = count  ;
  this->_shaders = shaders;
  this->_binary  = binary ;
}

void ShaderBinary::operator()(){
  glShaderBinary(
      *this->_count,
      &(*this->_shaders),
      this->_binary->getFormat(),
      this->_binary->getBinary(),
      this->_binary->getLength());
}

std::shared_ptr<GLsizei>ShaderBinary::getCount(){
  return this->_count;
}

std::shared_ptr<GLuint>ShaderBinary::getShaders(){
  return this->_shaders;
}

std::shared_ptr<ShaderBinaryData>ShaderBinary::getBinary(){
  return this->_binary;
}

