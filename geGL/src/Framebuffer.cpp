#include<GPUEngine/geGL/Framebuffer.h>
#include<GPUEngine/geGL/OpenGLUtil.h>
#include<GPUEngine/geGL/Texture.h>
#include<GPUEngine/geGL/Renderbuffer.h>
#include<iostream>
#include<sstream>
#include<cassert>

using namespace ge::gl;


GLint Framebuffer::getParam(GLenum pname){
  assert(this!=nullptr);
  GLint param;
  this->_gl.glGetNamedFramebufferParameteriv(this->_id,pname,&param);
  return param;
}

void Framebuffer::setParam(GLenum pname,GLint param){
  assert(this!=nullptr);
  this->_gl.glNamedFramebufferParameteri(this->_id,pname,param);
}

GLint Framebuffer::getAttachmentParam(GLenum attachment,GLenum pname){
  assert(this!=nullptr);
  GLint param;
  this->_gl.glGetNamedFramebufferAttachmentParameteriv(this->_id,attachment,pname,&param);
  return param;
}

Framebuffer::Framebuffer (
    FunctionTablePointer const&table,
    bool defaultFramebuffer):OpenGLObject(table){
  assert(this!=nullptr);
  if(defaultFramebuffer)this->_id=0;
  else this->_gl.glCreateFramebuffers(1,&this->_id);
}

Framebuffer::Framebuffer (bool defaultFramebuffer):Framebuffer(nullptr,defaultFramebuffer){
}

Framebuffer::~Framebuffer(){
  assert(this!=nullptr);
  for(auto const&x:this->_textureAttachments)
    x.second->_framebuffers.erase(this);
  for(auto const&x:this->_renderbufferAttachments)
    x.second->_framebuffers.erase(this);
  this->_gl.glDeleteFramebuffers(1,&this->_id);
}

void Framebuffer::attachRenderbuffer(
    GLenum                             attachment  ,
    std::shared_ptr<Renderbuffer>const&renderbuffer){
  assert(this!=nullptr);
  auto ii = this->_renderbufferAttachments.find(attachment);
  if(ii!=this->_renderbufferAttachments.end()){
    ii->second->_framebuffers.erase(this);
  }
  this->_renderbufferAttachments.erase(attachment);

  if(!renderbuffer){
    this->_gl.glNamedFramebufferRenderbuffer(this->_id,attachment,GL_RENDERBUFFER,0);
    return;
  }

  this->_renderbufferAttachments[attachment] = renderbuffer;
  renderbuffer->_framebuffers.insert(this);
  this->_gl.glNamedFramebufferRenderbuffer(this->_id,attachment,GL_RENDERBUFFER,renderbuffer->getId());
}

void Framebuffer::attachTexture(GLenum attachment,std::shared_ptr<Texture>const&texture,GLint level,GLint layer){
  assert(this!=nullptr);
  auto ii = this->_textureAttachments.find(attachment);
  if(ii!=this->_textureAttachments.end()){
    ii->second->_framebuffers.erase(this);
  }
  this->_textureAttachments.erase(attachment);

  if(!texture){
    if(layer==-1)
      this->_gl.glNamedFramebufferTexture(this->_id,attachment,0,level);
    else
      this->_gl.glNamedFramebufferTextureLayer(this->_id,attachment,0,level,layer);
    return;
  }

  this->_textureAttachments[attachment] = texture;
  if(layer==-1)
    this->_gl.glNamedFramebufferTexture(this->_id,attachment,texture->getId(),level);
  else
    this->_gl.glNamedFramebufferTextureLayer(this->_id,attachment,texture->getId(),level,layer);
}

void Framebuffer::bind  (GLenum target)const{
  assert(this!=nullptr);
  this->_gl.glBindFramebuffer(target,this->_id);
}
void Framebuffer::unbind(GLenum target)const{
  assert(this!=nullptr);
  this->_gl.glBindFramebuffer(target,0);
}

bool Framebuffer::check()const{
  assert(this!=nullptr);
  return this->_gl.glCheckNamedFramebufferStatus(this->_id,GL_DRAW_FRAMEBUFFER)==GL_FRAMEBUFFER_COMPLETE;
}

void Framebuffer::drawBuffer(GLenum buffer)const{
  assert(this!=nullptr);
  this->_gl.glNamedFramebufferDrawBuffer(this->_id,buffer);
}

void Framebuffer::drawBuffers(GLsizei n,const GLenum *buffers)const{
  assert(this!=nullptr);
  this->_gl.glNamedFramebufferDrawBuffers(this->_id,n,buffers);
}


void Framebuffer::drawBuffers(std::vector<GLenum>const buffers)const{
  assert(this!=nullptr);
  this->_gl.glNamedFramebufferDrawBuffers(this->_id,(GLsizei)buffers.size(),buffers.data());
}

void Framebuffer::drawBuffers(GLsizei n,...)const{
  assert(this!=nullptr);
  GLenum*drawBuffers=new GLenum[n];
  assert(drawBuffers!=nullptr);
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
  assert(this!=nullptr);
  this->_gl.glClearNamedFramebufferiv(this->_id,buffer,drawBuffer,value);
}

void Framebuffer::clearBuffer (GLenum buffer,GLint drawBuffer,const GLfloat*value)const{
  assert(this!=nullptr);
  this->_gl.glClearNamedFramebufferfv(this->_id,buffer,drawBuffer,value);
}

void Framebuffer::clearBuffer (GLenum buffer,GLint drawBuffer,const GLuint*value)const{
  assert(this!=nullptr);
  this->_gl.glClearNamedFramebufferuiv(this->_id,buffer,drawBuffer,value);
}

void Framebuffer::clearBuffer (GLenum buffer,GLint drawBuffer,GLfloat depth,GLint stencil)const{
  assert(this!=nullptr);
  this->_gl.glClearNamedFramebufferfi(this->_id,buffer,drawBuffer,depth,stencil);
}

void Framebuffer::invalidateFramebuffer(
    GLsizei       numAttachments,
    const GLenum* attachments   ,
    GLint         x             ,
    GLint         y             ,
    GLsizei       width         ,
    GLsizei       height        )const{
  assert(this!=nullptr);
  if(x==-1)
    this->_gl.glInvalidateNamedFramebufferData(this->_id,numAttachments,attachments);
  else
    this->_gl.glInvalidateNamedFramebufferSubData(this->_id,numAttachments,attachments,x,y,width,height);
}

GLboolean Framebuffer::isFramebuffer()const{
  assert(this!=nullptr);
  return this->_gl.glIsFramebuffer(this->_id);
}

void Framebuffer::setDefaultWidth(GLint width){
  assert(this!=nullptr);
  this->setParam(GL_FRAMEBUFFER_DEFAULT_WIDTH,width);
}
void Framebuffer::setDefaultHeight(GLint height){
  assert(this!=nullptr);
  this->setParam(GL_FRAMEBUFFER_DEFAULT_HEIGHT,height);
}
void Framebuffer::setDefaultFixedSampleLocations(GLint location){
  assert(this!=nullptr);
  this->setParam(GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS,location);
}
void Framebuffer::setDefaultSamples(GLint samples){
  assert(this!=nullptr);
  this->setParam(GL_FRAMEBUFFER_DEFAULT_SAMPLES,samples);
}
void Framebuffer::setDefaultLayers(GLint layers){
  assert(this!=nullptr);
  this->setParam(GL_FRAMEBUFFER_DEFAULT_LAYERS,layers);
}

GLint Framebuffer::getDefaultWidth(){
  assert(this!=nullptr);
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_WIDTH );
}
GLint Framebuffer::getDefaultHeight(){
  assert(this!=nullptr);
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_HEIGHT);
}
GLint Framebuffer::getDefaultLayers(){
  assert(this!=nullptr);
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_LAYERS);
}
GLint Framebuffer::getDefaultSamples(){
  assert(this!=nullptr);
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_SAMPLES);
}
GLint Framebuffer::getDefaultFixedSampleLocations(){
  assert(this!=nullptr);
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS);
}
GLint Framebuffer::getSamples(){
  assert(this!=nullptr);
  return this->getParam(GL_SAMPLES);
}
GLint Framebuffer::getSampleBuffers(){
  assert(this!=nullptr);
  return this->getParam(GL_SAMPLE_BUFFERS);
}

GLenum Framebuffer::getAttachmentObjectType   (GLenum attachment){
  assert(this!=nullptr);
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);
}
GLint  Framebuffer::getAttachmentRedSize      (GLenum attachment){
  assert(this!=nullptr);
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE);
}
GLint  Framebuffer::getAttachmentGreenSize    (GLenum attachment){
  assert(this!=nullptr);
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE);
}
GLint  Framebuffer::getAttachmentBlueSize     (GLenum attachment){
  assert(this!=nullptr);
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE);
}
GLint  Framebuffer::getAttachmentAlphaSize    (GLenum attachment){
  assert(this!=nullptr);
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE);
}
GLint  Framebuffer::getAttachmentDepthSize    (){
  assert(this!=nullptr);
  return this->getAttachmentParam(GL_DEPTH_ATTACHMENT,GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE);
}
GLint  Framebuffer::getAttachmentStencilSize  (){
  assert(this!=nullptr);
  return this->getAttachmentParam(GL_STENCIL_ATTACHMENT,GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE);
}
GLenum Framebuffer::getAttachmentComponentType(GLenum attachment){
  assert(this!=nullptr);
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE);
}
GLenum    Framebuffer::getAttachmentColorEncoding     (GLenum attachment){
  assert(this!=nullptr);
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING);
}
GLuint    Framebuffer::getAttachmentObjectName        (GLenum attachment){
  assert(this!=nullptr);
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME);
}
GLint     Framebuffer::getAttachmentTextureLevel      (GLenum attachment){
  assert(this!=nullptr);
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL);
}
GLenum    Framebuffer::getAttachmentTextureCubeMapFace(GLenum attachment){
  assert(this!=nullptr);
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE);
}
GLboolean Framebuffer::isAttachmentLayered            (GLenum attachment){
  assert(this!=nullptr);
  return (GLboolean)this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_LAYERED);
}
GLint     Framebuffer::getAttachmentTextureLayer      (GLenum attachment){
  assert(this!=nullptr);
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER);
}


GLint Framebuffer::getDoubleBuffer(){
  assert(this!=nullptr);
  return this->getParam(GL_DOUBLEBUFFER);
}
GLint Framebuffer::getImplementationColorReadFormat(){
  assert(this!=nullptr);
  return this->getParam(GL_IMPLEMENTATION_COLOR_READ_FORMAT);
}
GLint Framebuffer::getImplementationColorReadType  (){
  assert(this!=nullptr);
  return this->getParam(GL_IMPLEMENTATION_COLOR_READ_TYPE);
}
GLint Framebuffer::getStereo(){
  assert(this!=nullptr);
  return this->getParam(GL_STEREO);
}

std::string Framebuffer::getInfo(){
  assert(this!=nullptr);
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
  this->_gl.glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS,&maxColorAttachments);
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

