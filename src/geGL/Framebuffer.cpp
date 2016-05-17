#include<geGL/Framebuffer.h>
#include<geGL/OpenGLUtil.h>
#include<iostream>
#include<sstream>

using namespace ge::gl;
using namespace ge::gl::opengl;


GLint Framebuffer::getParam(GLenum pname){
  GLint param;
  glGetNamedFramebufferParameteriv(this->_id,pname,&param);
  return param;
}

void Framebuffer::setParam(GLenum pname,GLint param){
  glNamedFramebufferParameteri(this->_id,pname,param);
}

GLint Framebuffer::getAttachmentParam(GLenum attachment,GLenum pname){
  GLint param;
  glGetNamedFramebufferAttachmentParameteriv(this->_id,attachment,pname,&param);
  return param;
}

Framebuffer::Framebuffer (bool defaultFramebuffer){
  if(defaultFramebuffer)this->_id=0;
  else glCreateFramebuffers(1,&this->_id);
}

Framebuffer::Framebuffer (
    FunctionTablePointer const&table,
    bool defaultFramebuffer):OpenGLObject(table){
  if(defaultFramebuffer)this->_id=0;
  else glCreateFramebuffers(1,&this->_id);
}

Framebuffer::~Framebuffer(){
  glDeleteFramebuffers(1,&this->_id);
}

void Framebuffer::attachRenderbuffer(GLenum attachment,GLuint renderbuffer)const{
  glNamedFramebufferRenderbuffer(this->_id,attachment,GL_RENDERBUFFER,renderbuffer);
}

void Framebuffer::attachTexture(GLenum attachment,GLuint texture,GLint level,GLint layer)const{
  if(layer==-1)
    glNamedFramebufferTexture(this->_id,attachment,texture,level);
  else
    glNamedFramebufferTextureLayer(this->_id,attachment,texture,level,layer);
}

void Framebuffer::bind  (GLenum target)const{
  glBindFramebuffer(target,this->_id);
}
void Framebuffer::unbind(GLenum target)const{
  glBindFramebuffer(target,0);
}

bool Framebuffer::check()const{
  return glCheckNamedFramebufferStatus(this->_id,GL_DRAW_FRAMEBUFFER)==GL_FRAMEBUFFER_COMPLETE;
}

void Framebuffer::drawBuffer(GLenum buffer)const{
  glNamedFramebufferDrawBuffer(this->_id,buffer);
}

void Framebuffer::drawBuffers(GLsizei n,const GLenum *buffers)const{
  glNamedFramebufferDrawBuffers(this->_id,n,buffers);
}

void Framebuffer::drawBuffers(GLsizei n,...)const{
  GLenum*drawBuffers=new GLenum[n];
  va_list args;
  va_start(args,n);
  for(GLsizei i=0;i<n;++i){
    drawBuffers[i]=(GLenum)va_arg(args,GLenum);
  }
  va_end(args);
  this->drawBuffers(n,drawBuffers);
  delete[]drawBuffers;
}

void Framebuffer::clearBuffer (GLenum buffer,GLint drawBuffer,const GLint*value)const{
  glClearNamedFramebufferiv(this->_id,buffer,drawBuffer,value);
}

void Framebuffer::clearBuffer (GLenum buffer,GLint drawBuffer,const GLfloat*value)const{
  glClearNamedFramebufferfv(this->_id,buffer,drawBuffer,value);
}

void Framebuffer::clearBuffer (GLenum buffer,GLint drawBuffer,const GLuint*value)const{
  glClearNamedFramebufferuiv(this->_id,buffer,drawBuffer,value);
}

void Framebuffer::clearBuffer (GLenum buffer,GLint drawBuffer,GLfloat depth,GLint stencil)const{
  glClearNamedFramebufferfi(this->_id,buffer,drawBuffer,depth,stencil);
}

void Framebuffer::invalidateFramebuffer(
    GLsizei       numAttachments,
    const GLenum* attachments   ,
    GLint         x             ,
    GLint         y             ,
    GLsizei       width         ,
    GLsizei       height        )const{
  if(x==-1)
    glInvalidateNamedFramebufferData(this->_id,numAttachments,attachments);
  else
    glInvalidateNamedFramebufferSubData(this->_id,numAttachments,attachments,x,y,width,height);
}

GLboolean Framebuffer::isFramebuffer()const{
  return glIsFramebuffer(this->_id);
}

void Framebuffer::setDefaultWidth(GLint width){
  this->setParam(GL_FRAMEBUFFER_DEFAULT_WIDTH,width);
}
void Framebuffer::setDefaultHeight(GLint height){
  this->setParam(GL_FRAMEBUFFER_DEFAULT_HEIGHT,height);
}
void Framebuffer::setDefaultFixedSampleLocations(GLint location){
  this->setParam(GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS,location);
}
void Framebuffer::setDefaultSamples(GLint samples){
  this->setParam(GL_FRAMEBUFFER_DEFAULT_SAMPLES,samples);
}
void Framebuffer::setDefaultLayers(GLint layers){
  this->setParam(GL_FRAMEBUFFER_DEFAULT_LAYERS,layers);
}

GLint Framebuffer::getDefaultWidth(){
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_WIDTH );
}
GLint Framebuffer::getDefaultHeight(){
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_HEIGHT);
}
GLint Framebuffer::getDefaultLayers(){
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_LAYERS);
}
GLint Framebuffer::getDefaultSamples(){
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_SAMPLES);
}
GLint Framebuffer::getDefaultFixedSampleLocations(){
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS);
}
GLint Framebuffer::getSamples(){
  return this->getParam(GL_SAMPLES);
}
GLint Framebuffer::getSampleBuffers(){
  return this->getParam(GL_SAMPLE_BUFFERS);
}

GLenum Framebuffer::getAttachmentObjectType   (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);
}
GLint  Framebuffer::getAttachmentRedSize      (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE);
}
GLint  Framebuffer::getAttachmentGreenSize    (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE);
}
GLint  Framebuffer::getAttachmentBlueSize     (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE);
}
GLint  Framebuffer::getAttachmentAlphaSize    (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE);
}
GLint  Framebuffer::getAttachmentDepthSize    (){
  return this->getAttachmentParam(GL_DEPTH_ATTACHMENT,GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE);
}
GLint  Framebuffer::getAttachmentStencilSize  (){
  return this->getAttachmentParam(GL_STENCIL_ATTACHMENT,GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE);
}
GLenum Framebuffer::getAttachmentComponentType(GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE);
}
GLenum    Framebuffer::getAttachmentColorEncoding     (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING);
}
GLuint    Framebuffer::getAttachmentObjectName        (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME);
}
GLint     Framebuffer::getAttachmentTextureLevel      (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL);
}
GLenum    Framebuffer::getAttachmentTextureCubeMapFace(GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE);
}
GLboolean Framebuffer::isAttachmentLayered            (GLenum attachment){
  return (GLboolean)this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_LAYERED);
}
GLint     Framebuffer::getAttachmentTextureLayer      (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER);
}


GLint Framebuffer::getDoubleBuffer(){
  return this->getParam(GL_DOUBLEBUFFER);
}
GLint Framebuffer::getImplementationColorReadFormat(){
  return this->getParam(GL_IMPLEMENTATION_COLOR_READ_FORMAT);
}
GLint Framebuffer::getImplementationColorReadType  (){
  return this->getParam(GL_IMPLEMENTATION_COLOR_READ_TYPE);
}
GLint Framebuffer::getStereo(){
  return this->getParam(GL_STEREO);
}

std::string Framebuffer::getInfo(){
  std::stringstream ss;
  ss<<"Default Width:               "<<this->getDefaultWidth               ()<<std::endl;
  ss<<"Default Height:              "<<this->getDefaultHeight              ()<<std::endl;
  ss<<"Default Layers:              "<<this->getDefaultLayers              ()<<std::endl;
  ss<<"Default Samples:             "<<this->getDefaultSamples             ()<<std::endl;
  ss<<"Default FixedSampleLocation: "<<this->getDefaultFixedSampleLocations()<<std::endl;
  //ss<<"samples:                     "<<this->getSamples                    ()<<std::endl;
  //ss<<"sample buffer:               "<<this->getSampleBuffers              ()<<std::endl;

  ss<<ge::gl::translateFramebufferAttachment(GL_DEPTH_ATTACHMENT)<<":"<<std::endl;
  if(this->getAttachmentObjectType(GL_DEPTH_ATTACHMENT)!=GL_NONE){
    ss<<"  object type:    "<<ge::gl::translateFramebufferType(
        /*                  */this->getAttachmentObjectType         (GL_DEPTH_ATTACHMENT))<<std::endl;
    ss<<"  depth size:     "<<this->getAttachmentDepthSize()                              <<std::endl;
    ss<<"  component type: "<<ge::gl::translateFramebufferComponentType(
        /*                  */this->getAttachmentComponentType      (GL_DEPTH_ATTACHMENT))<<std::endl;
    ss<<"  object name:    "<<this->getAttachmentObjectName         (GL_DEPTH_ATTACHMENT) <<std::endl;
    ss<<"  texture level:  "<<this->getAttachmentTextureLevel       (GL_DEPTH_ATTACHMENT) <<std::endl;
    ss<<"  cubemap face:   "<<ge::gl::translateCubeMapFace(
        /*                  */this->getAttachmentTextureCubeMapFace (GL_DEPTH_ATTACHMENT))<<std::endl;
    ss<<"  texture layer:  "<<this->getAttachmentTextureLayer       (GL_DEPTH_ATTACHMENT) <<std::endl;
  }

  ss<<ge::gl::translateFramebufferAttachment(GL_STENCIL_ATTACHMENT)<<":"<<std::endl;
  if(this->getAttachmentObjectType(GL_STENCIL_ATTACHMENT)!=GL_NONE){
    ss<<"  object type:    "<<ge::gl::translateFramebufferType(
        /*                  */this->getAttachmentObjectType         (GL_STENCIL_ATTACHMENT))<<std::endl;
    ss<<"  stencil size:   "<<this->getAttachmentStencilSize()                              <<std::endl;
    ss<<"  component type: "<<ge::gl::translateFramebufferComponentType(
        /*                  */this->getAttachmentComponentType      (GL_STENCIL_ATTACHMENT))<<std::endl;
    ss<<"  object name:    "<<this->getAttachmentObjectName         (GL_STENCIL_ATTACHMENT) <<std::endl;
    ss<<"  texture level:  "<<this->getAttachmentTextureLevel       (GL_STENCIL_ATTACHMENT) <<std::endl;
    ss<<"  cubemap face:   "<<ge::gl::translateCubeMapFace(
        /*                  */this->getAttachmentTextureCubeMapFace (GL_STENCIL_ATTACHMENT))<<std::endl;
    ss<<"  texture layer:  "<<this->getAttachmentTextureLayer       (GL_STENCIL_ATTACHMENT) <<std::endl;
  }

  GLint maxColorAttachments;
  glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS,&maxColorAttachments);
  ss<<"GL_MAX_COLOR_ATTACHMENTS: "<<maxColorAttachments<<std::endl;
  for(GLint a=0;a<maxColorAttachments;++a){
    ss<<ge::gl::translateFramebufferAttachment(GL_COLOR_ATTACHMENT0+a)<<":"<<std::endl;
    if(this->getAttachmentObjectType(GL_COLOR_ATTACHMENT0+a)==GL_NONE)continue;
    ss<<"  object type:    "<<ge::gl::translateFramebufferType(
        /*                  */this->getAttachmentObjectType        (GL_COLOR_ATTACHMENT0+a))<<std::endl;
    ss<<"  red size:       "<<this->getAttachmentRedSize           (GL_COLOR_ATTACHMENT0+a) <<std::endl;
    ss<<"  green size:     "<<this->getAttachmentGreenSize         (GL_COLOR_ATTACHMENT0+a) <<std::endl;
    ss<<"  blue size:      "<<this->getAttachmentBlueSize          (GL_COLOR_ATTACHMENT0+a) <<std::endl;
    ss<<"  alpha size:     "<<this->getAttachmentAlphaSize         (GL_COLOR_ATTACHMENT0+a) <<std::endl;
    ss<<"  component type: "<<ge::gl::translateFramebufferComponentType(
        /*                  */this->getAttachmentComponentType     (GL_COLOR_ATTACHMENT0+a))<<std::endl;
    ss<<"  color encoding: "<<ge::gl::translateFramebufferColorEncoding(
        /*                  */this->getAttachmentColorEncoding     (GL_COLOR_ATTACHMENT0+a))<<std::endl;
    ss<<"  object name:    "<<this->getAttachmentObjectName        (GL_COLOR_ATTACHMENT0+a) <<std::endl;
    ss<<"  texture level:  "<<this->getAttachmentTextureLevel      (GL_COLOR_ATTACHMENT0+a) <<std::endl;
    ss<<"  cubemap face:   "<<ge::gl::translateCubeMapFace(
        /*                  */this->getAttachmentTextureCubeMapFace(GL_COLOR_ATTACHMENT0+a))<<std::endl;
    ss<<"  texture layer:  "<<this->getAttachmentTextureLayer      (GL_COLOR_ATTACHMENT0+a) <<std::endl;
  }
  return ss.str();
}

