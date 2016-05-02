#include<geGL/RenderbufferObject.h>

using namespace ge::gl;

RenderbufferObject::RenderbufferObject(
    GLenum  internalFormat,
    GLsizei width,
    GLsizei height){
  glCreateRenderbuffers(1,&this->_id);
  glNamedRenderbufferStorage(this->_id,internalFormat,width,height);
}

RenderbufferObject::RenderbufferObject( 
    GLenum  internalFormat,
    GLsizei samples,
    GLsizei width,
    GLsizei height){
  glCreateRenderbuffers(1,&this->_id);
  glNamedRenderbufferStorageMultisample(this->_id,internalFormat,samples,width,height);
}

#if defined(REPLACE_GLEW)
RenderbufferObject::RenderbufferObject(
    std::shared_ptr<OpenGLFunctionTable>const&table,
    GLenum  internalFormat,
    GLsizei samples,
    GLsizei width,
    GLsizei height):OpenGLObject(table){
  glCreateRenderbuffers(1,&this->_id);
  glNamedRenderbufferStorageMultisample(this->_id,internalFormat,samples,width,height);
}
RenderbufferObject::RenderbufferObject(
    std::shared_ptr<OpenGLFunctionTable>const&table,
    GLenum  internalFormat,
    GLsizei width,
    GLsizei height):OpenGLObject(table){
  glCreateRenderbuffers(1,&this->_id);
  glNamedRenderbufferStorage(this->_id,internalFormat,width,height);
}
#endif


RenderbufferObject::~RenderbufferObject(){
  glDeleteRenderbuffers(1,&this->_id);
}

void   RenderbufferObject::bind()const{
  glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
}

GLint RenderbufferObject::getWidth()const{
  GLint width;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_WIDTH,&width);
  return width;
}

GLint RenderbufferObject::getHeight()const{
  GLint height;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_HEIGHT,&height);
  return height;
}

GLenum RenderbufferObject::getInternalFormat()const{
  GLint internalFormat;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_INTERNAL_FORMAT,&internalFormat);
  return internalFormat;
}

GLint RenderbufferObject::getSamples()const{
  GLint samples;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_SAMPLES,&samples);
  return samples;
}

GLint RenderbufferObject::getRedSize()const{
  GLint redSize;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_RED_SIZE,&redSize);
  return redSize;
}

GLint RenderbufferObject::getGreenSize()const{
  GLint greenSize;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_GREEN_SIZE,&greenSize);
  return greenSize;
}

GLint RenderbufferObject::getBlueSize()const{
  GLint blueSize;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_BLUE_SIZE,&blueSize);
  return blueSize;
}

GLint RenderbufferObject::getAlphaSize()const{
  GLint alphaSize;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_ALPHA_SIZE,&alphaSize);
  return alphaSize;
}

GLint RenderbufferObject::getDepthSize()const{
  GLint depthSize;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_DEPTH_SIZE,&depthSize);
  return depthSize;
}

GLint RenderbufferObject::getStencilSize()const{
  GLint stencilSize;
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_STENCIL_SIZE,&stencilSize);
  return stencilSize;
}

