#include<geGL/Renderbuffer.h>

using namespace ge::gl;

Renderbuffer::Renderbuffer(
    FunctionTablePointer const&table,
    GLenum  internalFormat,
    GLsizei width,
    GLsizei height,
    GLsizei samples):OpenGLObject(table){
  assert(this!=nullptr);
  this->_gl.glCreateRenderbuffers(1,&this->_id);
  this->setStorage(internalFormat,width,height,samples);
}

Renderbuffer::Renderbuffer( 
    GLenum  internalFormat,
    GLsizei width,
    GLsizei height,
    GLsizei samples):Renderbuffer(nullptr,internalFormat,width,height,samples){
}

void Renderbuffer::setStorage(
    GLenum  internalFormat,
    GLsizei width,
    GLsizei height,
    GLsizei samples)const{
  assert(this!=nullptr);
  this->_gl.glNamedRenderbufferStorageMultisample(this->_id,internalFormat,samples,width,height);
}


Renderbuffer::~Renderbuffer(){
  assert(this!=nullptr);
  this->_gl.glDeleteRenderbuffers(1,&this->_id);
}

void   Renderbuffer::bind()const{
  assert(this!=nullptr);
  this->_gl.glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
}

void Renderbuffer::unbind()const{
  assert(this!=nullptr);
  this->_gl.glBindRenderbuffer(GL_RENDERBUFFER,0);
}

GLint Renderbuffer::getWidth()const{
  assert(this!=nullptr);
  return this->_getParamateri(GL_RENDERBUFFER_WIDTH);
}

GLint Renderbuffer::getHeight()const{
  assert(this!=nullptr);
  return this->_getParamateri(GL_RENDERBUFFER_HEIGHT);
}

GLenum Renderbuffer::getInternalFormat()const{
  assert(this!=nullptr);
  return this->_getParamateri(GL_RENDERBUFFER_INTERNAL_FORMAT);
}

GLint Renderbuffer::getSamples()const{
  assert(this!=nullptr);
  return this->_getParamateri(GL_RENDERBUFFER_SAMPLES);
}

GLint Renderbuffer::getRedSize()const{
  assert(this!=nullptr);
  return this->_getParamateri(GL_RENDERBUFFER_RED_SIZE);
}

GLint Renderbuffer::getGreenSize()const{
  assert(this!=nullptr);
  return this->_getParamateri(GL_RENDERBUFFER_GREEN_SIZE);
}

GLint Renderbuffer::getBlueSize()const{
  assert(this!=nullptr);
  return this->_getParamateri(GL_RENDERBUFFER_BLUE_SIZE);
}

GLint Renderbuffer::getAlphaSize()const{
  assert(this!=nullptr);
  return this->_getParamateri(GL_RENDERBUFFER_ALPHA_SIZE);
}

GLint Renderbuffer::getDepthSize()const{
  assert(this!=nullptr);
  return this->_getParamateri(GL_RENDERBUFFER_DEPTH_SIZE);
}

GLint Renderbuffer::getStencilSize()const{
  assert(this!=nullptr);
  return this->_getParamateri(GL_RENDERBUFFER_STENCIL_SIZE);
}

GLint Renderbuffer::_getParamateri(GLenum pname)const{
  assert(this!=nullptr);
  GLint param;
  this->_gl.glGetNamedRenderbufferParameteriv(this->_id,pname,&param);
  return param;
}


