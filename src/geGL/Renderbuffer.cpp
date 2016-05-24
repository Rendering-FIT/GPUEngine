#include<geGL/Renderbuffer.h>

using namespace ge::gl;
using namespace ge::gl::opengl;

Renderbuffer::Renderbuffer(
    FunctionTablePointer const&table,
    GLenum  internalFormat,
    GLsizei width,
    GLsizei height,
    GLsizei samples):OpenGLObject(table){
  glCreateRenderbuffers(1,&this->_id);
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
  glNamedRenderbufferStorageMultisample(this->_id,internalFormat,samples,width,height);
}


Renderbuffer::~Renderbuffer(){
  glDeleteRenderbuffers(1,&this->_id);
}

void   Renderbuffer::bind()const{
  glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
}

void Renderbuffer::unbind()const{
  glBindRenderbuffer(GL_RENDERBUFFER,0);
}

GLint Renderbuffer::getWidth()const{
  return this->_getParamateri(GL_RENDERBUFFER_WIDTH);
}

GLint Renderbuffer::getHeight()const{
  return this->_getParamateri(GL_RENDERBUFFER_HEIGHT);
}

GLenum Renderbuffer::getInternalFormat()const{
  return this->_getParamateri(GL_RENDERBUFFER_INTERNAL_FORMAT);
}

GLint Renderbuffer::getSamples()const{
  return this->_getParamateri(GL_RENDERBUFFER_SAMPLES);
}

GLint Renderbuffer::getRedSize()const{
  return this->_getParamateri(GL_RENDERBUFFER_RED_SIZE);
}

GLint Renderbuffer::getGreenSize()const{
  return this->_getParamateri(GL_RENDERBUFFER_GREEN_SIZE);
}

GLint Renderbuffer::getBlueSize()const{
  return this->_getParamateri(GL_RENDERBUFFER_BLUE_SIZE);
}

GLint Renderbuffer::getAlphaSize()const{
  return this->_getParamateri(GL_RENDERBUFFER_ALPHA_SIZE);
}

GLint Renderbuffer::getDepthSize()const{
  return this->_getParamateri(GL_RENDERBUFFER_DEPTH_SIZE);
}

GLint Renderbuffer::getStencilSize()const{
  return this->_getParamateri(GL_RENDERBUFFER_STENCIL_SIZE);
}

GLint Renderbuffer::_getParamateri(GLenum pname)const{
  GLint param;
  glGetNamedRenderbufferParameteriv(this->_id,pname,&param);
  return param;
}


