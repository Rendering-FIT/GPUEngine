#include<geGL/FramebufferObject.h>
#include<iostream>

namespace ge{
  namespace gl{
    FramebufferObject::FramebufferObject(GLuint){
      this->_id=0;
    }
    FramebufferObject::FramebufferObject (){
#ifndef USE_DSA
      glGenFramebuffers(1,&this->_id);
      this->bind();
      this->unbind();
#else //USE_DSA
      glCreateFramebuffers(1,&this->_id);
#endif//USE_DSA
    }
    FramebufferObject::~FramebufferObject(){
      glDeleteFramebuffers(1,&this->_id);
    }
    void FramebufferObject::setWidth(GLint width){
#ifndef USE_DSA
      this->bind();
      glFramebufferParameteri(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_FRAMEBUFFER_DEFAULT_WIDTH,width);
      this->unbind();
#else //USE_DSA
      glNamedFramebufferParameteri(this->_id,GL_FRAMEBUFFER_DEFAULT_WIDTH,width);
#endif//USE_DSA
    }
    void FramebufferObject::setHeight(GLint height){
#ifndef USE_DSA
      this->bind();
      glFramebufferParameteri(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_FRAMEBUFFER_DEFAULT_HEIGHT,height);
      this->unbind();
#else //USE_DSA
      glNamedFramebufferParameteri(this->_id,GL_FRAMEBUFFER_DEFAULT_HEIGHT,height);
#endif//USE_DSA

    }
    void FramebufferObject::setFixedSampleLocations(GLint location){
#ifndef USE_DSA
      this->bind();
      glFramebufferParameteri(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS,location);
      this->unbind();
#else //USE_DSA
      glNamedFramebufferParameteri(this->_id,GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS,location);
#endif//USE_DSA
    }
    void FramebufferObject::setSamples(GLint samples){
#ifndef USE_DSA
      this->bind();
      glFramebufferParameteri(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_FRAMEBUFFER_DEFAULT_SAMPLES,samples);
      this->unbind();
#else //USE_DSA
      glNamedFramebufferParameteri(this->_id,GL_FRAMEBUFFER_DEFAULT_SAMPLES,samples);
#endif//USE_DSA
    }
    void FramebufferObject::setLayers(GLint layers){
#ifndef USE_DSA
      this->bind();
      glFramebufferParameteri(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_FRAMEBUFFER_DEFAULT_LAYERS,layers);
      this->unbind();
#else //USE_DSA
      glNamedFramebufferParameteri(this->_id,GL_FRAMEBUFFER_DEFAULT_LAYERS,layers);
#endif//USE_DSA
    }
    GLuint FramebufferObject::getId(){
      return this->_id;
    }

    GLint FramebufferObject::getWidth(){
      GLint width;
#ifndef USE_DSA
      this->bind();
      glGetFramebufferParameteriv(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_FRAMEBUFFER_DEFAULT_WIDTH,&width);
      this->unbind();
#else //USE_DSA
      glGetNamedFramebufferParameteriv(this->_id,GL_FRAMEBUFFER_DEFAULT_WIDTH,&width);
#endif//USE_DSA
      return width;
    }

    GLint FramebufferObject::getHeight              (){
      GLint height;
#ifndef USE_DSA
      this->bind();
      glGetFramebufferParameteriv(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_FRAMEBUFFER_DEFAULT_HEIGHT,&height);
      this->unbind();
#else //USE_DSA
      glGetNamedFramebufferParameteriv(this->_id,GL_FRAMEBUFFER_DEFAULT_HEIGHT,&height);
#endif//USE_DSA
      return height;
    }

    GLint FramebufferObject::getFixedSampleLocations(){
      GLint locations;
#ifndef USE_DSA
      this->bind();
      glGetFramebufferParameteriv(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS,&locations);
      this->unbind();
#else //USE_DSA
      glGetNamedFramebufferParameteriv(this->_id,GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS,&locations);
#endif//USE_DSA
      return locations;
    }

    GLint FramebufferObject::getSamples             (){
      GLint samples;
#ifndef USE_DSA
      this->bind();
      glGetFramebufferParameteriv(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_FRAMEBUFFER_DEFAULT_SAMPLES,&samples);
      this->unbind();
#else //USE_DSA
      glGetNamedFramebufferParameteriv(this->_id,GL_FRAMEBUFFER_DEFAULT_SAMPLES,&samples);
#endif//USE_DSA
      return samples;
    }

    GLint FramebufferObject::getLayers              (){
      GLint layers;
#ifndef USE_DSA
      this->bind();
      glGetFramebufferParameteriv(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_FRAMEBUFFER_DEFAULT_LAYERS,&layers);
      this->unbind();
#else //USE_DSA
      glGetNamedFramebufferParameteriv(this->_id,GL_FRAMEBUFFER_DEFAULT_LAYERS,&layers);
#endif//USE_DSA
      return layers;
    }

    GLint FramebufferObject::getDoubleBuffer        (){
      GLint doubleBuffer;
#ifndef USE_DSA
      this->bind();
      glGetFramebufferParameteriv(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_DOUBLEBUFFER,&doubleBuffer);
      this->unbind();
#else //USE_DSA
      glGetNamedFramebufferParameteriv(this->_id,GL_DOUBLEBUFFER,&doubleBuffer);
#endif//USE_DSA
      return doubleBuffer;
    }

    GLint FramebufferObject::getSampleBuffers       (){
      GLint sampleBuffers;
#ifndef USE_DSA
      this->bind();
      glGetFramebufferParameteriv(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_SAMPLE_BUFFERS,&sampleBuffers);
      this->unbind();
#else //USE_DSA
      glGetNamedFramebufferParameteriv(this->_id,GL_SAMPLE_BUFFERS,&sampleBuffers);
#endif//USE_DSA
      return sampleBuffers;
    }

    GLint FramebufferObject::getImplementationColorReadFormat(){
      GLint implementationColorReadFormat;
#ifndef USE_DSA
      this->bind();
      glGetFramebufferParameteriv(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_IMPLEMENTATION_COLOR_READ_FORMAT,&implementationColorReadFormat);
      this->unbind();
#else //USE_DSA
      glGetNamedFramebufferParameteriv(this->_id,GL_IMPLEMENTATION_COLOR_READ_FORMAT,&implementationColorReadFormat);
#endif//USE_DSA
      return implementationColorReadFormat;
    }

    GLint FramebufferObject::getImplementationColorReadType  (){
      GLint implementationColorReadType;
#ifndef USE_DSA
      this->bind();
      glGetFramebufferParameteriv(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_IMPLEMENTATION_COLOR_READ_TYPE,&implementationColorReadType);
      this->unbind();
#else //USE_DSA
      glGetNamedFramebufferParameteriv(this->_id,GL_IMPLEMENTATION_COLOR_READ_TYPE,&implementationColorReadType);
#endif//USE_DSA
      return implementationColorReadType;
    }

    GLint FramebufferObject::getStereo(){
      GLint stereo;
#ifndef USE_DSA
      this->bind();
      glGetFramebufferParameteriv(FRAMEBUFFEROBJECT_DEFAULT_TARGET,GL_STEREO,&stereo);
      this->unbind();
#else //USE_DSA
      glGetNamedFramebufferParameteriv(this->_id,GL_STEREO,&stereo);
#endif//USE_DSA
      return stereo;
    }
    void FramebufferObject::bind  (GLenum target){
      glBindFramebuffer(target,this->_id);
    }
    void FramebufferObject::unbind(GLenum target){
      glBindFramebuffer(target,0);
    }
    void FramebufferObject::attachDepthRenderbuffer(GLuint renderbuffer){
#ifndef USE_DSA
      this->bind();
      glFramebufferRenderbuffer(
          FRAMEBUFFEROBJECT_DEFAULT_TARGET,
          GL_DEPTH_ATTACHMENT,
          GL_RENDERBUFFER,
          renderbuffer);
      this->unbind();
#else //USE_DSA
      glNamedFramebufferRenderbuffer(
          this->_id,
          GL_DEPTH_ATTACHMENT,
          GL_RENDERBUFFER,
          renderbuffer);
#endif//USE_DSA
    }
    void FramebufferObject::attachDepthTexture(
        GLuint texture,
        GLint  level){ 
#ifndef USE_DSA
      this->bind();
      glFramebufferTexture(
          FRAMEBUFFEROBJECT_DEFAULT_TARGET,
          GL_DEPTH_ATTACHMENT,
          texture,
          level);
      this->unbind();
#else //USE_DSA
      glNamedFramebufferTexture(
          this->_id,
          GL_DEPTH_ATTACHMENT,
          texture,
          level);
#endif//USE_DSA
    }
    void FramebufferObject::attachStencilRenderbuffer(GLuint renderbuffer){
#ifndef USE_DSA
      this->bind();
      glFramebufferRenderbuffer(
          FRAMEBUFFEROBJECT_DEFAULT_TARGET,
          GL_STENCIL_ATTACHMENT,
          GL_RENDERBUFFER,
          renderbuffer);
      this->unbind();
#else //USE_DSA
      glNamedFramebufferRenderbuffer(
          this->_id,
          GL_STENCIL_ATTACHMENT,
          GL_RENDERBUFFER,
          renderbuffer);
#endif//USE_DSA
    }
    void FramebufferObject::attachStencilTexture(
        GLuint texture,
        GLint  level){ 
#ifndef USE_DSA
      this->bind();
      glFramebufferTexture(
          FRAMEBUFFEROBJECT_DEFAULT_TARGET,
          GL_STENCIL_ATTACHMENT,
          texture,
          level);
      this->unbind();
#else //USE_DSA
      glNamedFramebufferTexture(
          this->_id,
          GL_STENCIL_ATTACHMENT,
          texture,
          level);
#endif//USE_DSA
    }
    void FramebufferObject::attachColorRenderbuffer(
        GLenum   attachment,
        GLuint   renderbuffer){
#ifndef USE_DSA
      this->bind();
      glFramebufferRenderbuffer(
          FRAMEBUFFEROBJECT_DEFAULT_TARGET,
          attachment,
          GL_RENDERBUFFER,
          renderbuffer);
      this->unbind();
#else //USE_DSA
      glNamedFramebufferRenderbuffer(
          this->_id,
          attachment,
          GL_RENDERBUFFER,
          renderbuffer);
#endif//USE_DSA
    }

    void FramebufferObject::attachColorTexture(
        GLenum   attachment,
        GLuint   texture,
        GLint    level){
#ifndef USE_DSA
      this->bind();
      glFramebufferTexture(
          FRAMEBUFFEROBJECT_DEFAULT_TARGET,
          attachment,
          texture,
          level);
      this->unbind();
#else //USE_DSA
      glNamedFramebufferTexture(
          this->_id,
          attachment,
          texture,
          level);
#endif//USE_DSA

    }
    bool FramebufferObject::check(){
      this->bind();
      GLenum Status=glCheckFramebufferStatus(GL_FRAMEBUFFER);
      this->unbind();
      return Status==GL_FRAMEBUFFER_COMPLETE;
    }
    void FramebufferObject::drawBuffer(GLenum buffer){
      glDrawBuffer(buffer);
    }
    void FramebufferObject::drawBuffers(GLsizei n,GLenum *buffers){
      glDrawBuffers(n,buffers);
    }
    void FramebufferObject::drawBuffers(GLsizei n,...){
      GLenum*drawBuffers=new GLenum[n];
      va_list args;
      va_start(args,n);
      for(GLsizei i=0;i<n;++i){
        drawBuffers[i]=(GLenum)va_arg(args,GLenum);
      }
      va_end(args);
      this->bind();
      glDrawBuffers(n,drawBuffers);
      this->unbind();
      delete[]drawBuffers;
    }

    /*
       glFramebufferTexture
       glFramebufferTexture1D;
       glFramebufferTexture2D;
       glFramebufferTexture3D;
       glFramebufferTextureLayer;
       glNamedFramebufferTexture;
       glNamedFramebufferTextureLayer;
       */
  }
}

