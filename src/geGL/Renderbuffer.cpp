#include<geGL/Renderbuffer.h>

using namespace ge::gl;
using namespace ge::gl::opengl;

Renderbuffer::Renderbuffer(
    GLenum  internalFormat,
    GLsizei width,
    GLsizei height){
  glCreateRenderbuffers(1,&this->_id);
  glNamedRenderbufferStorage(this->_id,internalFormat,width,height);
}

Renderbuffer::Renderbuffer( 
    GLenum  internalFormat,
    GLsizei samples,
    GLsizei width,
    GLsizei height){
  glCreateRenderbuffers(1,&this->_id);
  glNamedRenderbufferStorageMultisample(this->_id,internalFormat,samples,width,height);
}

Renderbuffer::Renderbuffer(
    FunctionTablePointer const&table,
    GLenum  internalFormat,
    GLsizei samples,
    GLsizei width,
    GLsizei height):OpenGLObject(table){
  glCreateRenderbuffers(1,&this->_id);
  glNamedRenderbufferStorageMultisample(this->_id,internalFormat,samples,width,height);
}
Renderbuffer::Renderbuffer(
    FunctionTablePointer const&table,
    GLenum  internalFormat,
    GLsizei width,
    GLsizei height):OpenGLObject(table){
  glCreateRenderbuffers(1,&this->_id);
  glNamedRenderbufferStorage(this->_id,internalFormat,width,height);
}

Renderbuffer::~Renderbuffer(){
  glDeleteRenderbuffers(1,&this->_id);
}

void   Renderbuffer::bind()const{
  glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
}

GLint Renderbuffer::getWidth()const{
  GLint width;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_WIDTH,&width);
  return width;
}

GLint Renderbuffer::getHeight()const{
  GLint height;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_HEIGHT,&height);
  return height;
}

GLenum Renderbuffer::getInternalFormat()const{
  GLint internalFormat;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_INTERNAL_FORMAT,&internalFormat);
  return internalFormat;
}

GLint Renderbuffer::getSamples()const{
  GLint samples;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_SAMPLES,&samples);
  return samples;
}

GLint Renderbuffer::getRedSize()const{
  GLint redSize;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_RED_SIZE,&redSize);
  return redSize;
}

GLint Renderbuffer::getGreenSize()const{
  GLint greenSize;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_GREEN_SIZE,&greenSize);
  return greenSize;
}

GLint Renderbuffer::getBlueSize()const{
  GLint blueSize;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_BLUE_SIZE,&blueSize);
  return blueSize;
}

GLint Renderbuffer::getAlphaSize()const{
  GLint alphaSize;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_ALPHA_SIZE,&alphaSize);
  return alphaSize;
}

GLint Renderbuffer::getDepthSize()const{
  GLint depthSize;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_DEPTH_SIZE,&depthSize);
  return depthSize;
}

GLint Renderbuffer::getStencilSize()const{
  GLint stencilSize;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_STENCIL_SIZE,&stencilSize);
  return stencilSize;
}

