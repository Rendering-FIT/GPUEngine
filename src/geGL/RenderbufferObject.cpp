#include<geGL/RenderbufferObject.h>

using namespace ge::gl;

RenderbufferObject::RenderbufferObject(
    GLenum  internalFormat,
    GLsizei width,
    GLsizei height){
#ifndef USE_DSA
  glGenRenderbuffers   (1,&this->_id);
  glBindRenderbuffer   (GL_RENDERBUFFER,this->_id);
  glRenderbufferStorage(GL_RENDERBUFFER,internalFormat,width,height);
#else //USE_DSA
  glCreateRenderbuffers(1,&this->_id);
  glNamedRenderbufferStorage(this->_id,internalFormat,width,height);
#endif//USE_DSA
}
RenderbufferObject::RenderbufferObject( 
    GLenum  internalFormat,
    GLsizei samples,
    GLsizei width,
    GLsizei height){
#ifndef USE_DSA
  glGenRenderbuffers   (1,&this->_id);
  glBindRenderbuffer   (GL_RENDERBUFFER,this->_id);
  glRenderbufferStorageMultisample(GL_RENDERBUFFER,internalFormat,samples,width,height);
#else //USE_DSA
  glCreateRenderbuffers(1,&this->_id);
  glNamedRenderbufferStorageMultisample(this->_id,internalFormat,samples,width,height);
#endif//USE_DSA
}
RenderbufferObject::~RenderbufferObject(){
  glDeleteRenderbuffers(1,&this->_id);
}
void   RenderbufferObject::bind(){
  glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
}

GLint RenderbufferObject::getWidth(){
  GLint width;
#ifndef USE_DSA
  glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
  glGetRenderbufferParameteriv(GL_RENDERBUFFER,GL_RENDERBUFFER_WIDTH,&width);
#else //USE_DSA
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_WIDTH,&width);
#endif//USE_DSA
  return width;
}
GLint RenderbufferObject::getHeight(){
  GLint height;
#ifndef USE_DSA
  glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
  glGetRenderbufferParameteriv(GL_RENDERBUFFER,GL_RENDERBUFFER_HEIGHT,&height);
#else //USE_DSA
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_HEIGHT,&height);
#endif//USE_DSA
  return height;
}
GLenum RenderbufferObject::getInternalFormat(){
  GLint internalFormat;
#ifndef USE_DSA
  glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
  glGetRenderbufferParameteriv(GL_RENDERBUFFER,GL_RENDERBUFFER_INTERNAL_FORMAT,&internalFormat);
#else //USE_DSA
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_INTERNAL_FORMAT,&internalFormat);
#endif//USE_DSA
  return internalFormat;
}
GLint RenderbufferObject::getSamples(){
  GLint samples;
#ifndef USE_DSA
  glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
  glGetRenderbufferParameteriv(GL_RENDERBUFFER,GL_RENDERBUFFER_SAMPLES,&samples);
#else //USE_DSA
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_SAMPLES,&samples);
#endif//USE_DSA
  return samples;
}

GLint RenderbufferObject::getRedSize(){
  GLint redSize;
#ifndef USE_DSA
  glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
  glGetRenderbufferParameteriv(GL_RENDERBUFFER,GL_RENDERBUFFER_RED_SIZE,&redSize);
#else //USE_DSA
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_RED_SIZE,&redSize);
#endif//USE_DSA
  return redSize;
}
GLint RenderbufferObject::getGreenSize(){
  GLint greenSize;
#ifndef USE_DSA
  glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
  glGetRenderbufferParameteriv(GL_RENDERBUFFER,GL_RENDERBUFFER_GREEN_SIZE,&greenSize);
#else //USE_DSA
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_GREEN_SIZE,&greenSize);
#endif//USE_DSA
  return greenSize;
}
GLint RenderbufferObject::getBlueSize(){
  GLint blueSize;
#ifndef USE_DSA
  glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
  glGetRenderbufferParameteriv(GL_RENDERBUFFER,GL_RENDERBUFFER_BLUE_SIZE,&blueSize);
#else //USE_DSA
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_BLUE_SIZE,&blueSize);
#endif//USE_DSA
  return blueSize;
}
GLint RenderbufferObject::getAlphaSize(){
  GLint alphaSize;
#ifndef USE_DSA
  glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
  glGetRenderbufferParameteriv(GL_RENDERBUFFER,GL_RENDERBUFFER_ALPHA_SIZE,&alphaSize);
#else //USE_DSA
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_ALPHA_SIZE,&alphaSize);
#endif//USE_DSA
  return alphaSize;
}
GLint RenderbufferObject::getDepthSize(){
  GLint depthSize;
#ifndef USE_DSA
  glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
  glGetRenderbufferParameteriv(GL_RENDERBUFFER,GL_RENDERBUFFER_DEPTH_SIZE,&depthSize);
#else //USE_DSA
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_DEPTH_SIZE,&depthSize);
#endif//USE_DSA
  return depthSize;
}
GLint RenderbufferObject::getStencilSize(){
  GLint stencilSize;
#ifndef USE_DSA
  glBindRenderbuffer(GL_RENDERBUFFER,this->_id);
  glGetRenderbufferParameteriv(GL_RENDERBUFFER,GL_RENDERBUFFER_STENCIL_SIZE,&stencilSize);
#else //USE_DSA
  glGetNamedRenderbufferParameteriv(this->_id,GL_RENDERBUFFER_STENCIL_SIZE,&stencilSize);
#endif//USE_DSA
  return stencilSize;
}

