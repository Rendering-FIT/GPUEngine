#include<geGL/BufferCommands.h>

using namespace ge::gl;

BindBufferBase::BindBufferBase(GLenum target,GLuint index,GLuint buffer){
  this->_target = target;
  this->_index  = index ;
  this->_buffer = buffer;
}
BindBufferBase::BindBufferBase(
    ge::gl::ProgramObject*program,
    std::string           name   ,
    ge::gl::BufferObject* buffer ){
  this->_target = GL_SHADER_STORAGE_BUFFER;
  this->_index  = program->getBuffer(name);
  this->_buffer = buffer->getId();
}
void BindBufferBase::operator()(){
  glBindBufferBase(this->_target,this->_index,this->_buffer);
}
GLenum BindBufferBase::getTarget(){
  return this->_target;
}
GLuint BindBufferBase::getIndex (){
  return this->_index;
}
GLuint BindBufferBase::getBuffer(){
  return this->_buffer;
}

