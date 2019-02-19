#include<geGL/Framebuffer.h>
#include<geGL/OpenGLUtil.h>
#include<geGL/Texture.h>
#include<geGL/Renderbuffer.h>
#include<iostream>
#include<sstream>
#include<cassert>

using namespace ge::gl;


GLint Framebuffer::getParam(GLenum pname){
  assert(this!=nullptr);
  GLint param;
  this->getContext().glGetNamedFramebufferParameteriv(this->getId(),pname,&param);
  return param;
}

void Framebuffer::setParam(GLenum pname,GLint param){
  assert(this!=nullptr);
  this->getContext().glNamedFramebufferParameteri(this->getId(),pname,param);
}

GLint Framebuffer::getAttachmentParam(GLenum attachment,GLenum pname){
  assert(this!=nullptr);
  GLint param;
  this->getContext().glGetNamedFramebufferAttachmentParameteriv(this->getId(),attachment,pname,&param);
  return param;
}

Framebuffer::Framebuffer (
    FunctionTablePointer const&table,
    bool defaultFramebuffer):OpenGLObject(table){
  assert(this!=nullptr);
  if(defaultFramebuffer)this->getId()=0;
  else this->getContext().glCreateFramebuffers(1,&this->getId());
}

Framebuffer::Framebuffer (bool defaultFramebuffer):Framebuffer(nullptr,defaultFramebuffer){
}

Framebuffer::~Framebuffer(){
  assert(this!=nullptr);
  for(auto const&x:this->_textureAttachments)
    x.second->_framebuffers.erase(this);
  for(auto const&x:this->_renderbufferAttachments)
    x.second->_framebuffers.erase(this);
  this->getContext().glDeleteFramebuffers(1,&this->getId());
}

void Framebuffer::removeLinktoAttachedRenderbuffer(GLenum attachment){
  if(_renderbufferAttachments.count(attachment)>0){
    auto buf = _renderbufferAttachments.at(attachment);
    size_t counter = 0;
    for(auto const&x:_renderbufferAttachments)
      if(x.second == buf)
        counter++;
    if(counter == 1)
      buf->_framebuffers.erase(this);
  }
  this->_renderbufferAttachments.erase(attachment);
}

void Framebuffer::attachRenderbuffer(
    GLenum       attachment  ,
    Renderbuffer*renderbuffer){
  assert(this!=nullptr);
  removeLinktoAttachedRenderbuffer(attachment);

  if(!renderbuffer){
    this->getContext().glNamedFramebufferRenderbuffer(this->getId(),attachment,GL_RENDERBUFFER,0);
    return;
  }

  this->_renderbufferAttachments[attachment] = renderbuffer;
  renderbuffer->_framebuffers.insert(this);

  this->getContext().glNamedFramebufferRenderbuffer(this->getId(),attachment,GL_RENDERBUFFER,renderbuffer->getId());
}

void Framebuffer::attachRenderbuffer(
    GLenum                             attachment  ,
    std::shared_ptr<Renderbuffer>const&renderbuffer){
  attachRenderbuffer(attachment,&*renderbuffer);
}

void Framebuffer::removeLinkToAttachedTexture(GLenum attachment){
  if(_textureAttachments.count(attachment)>0){
    auto tex = _textureAttachments.at(attachment);
    size_t counter = 0;
    for(auto const&x:_textureAttachments)
      if(x.second == tex)
        counter++;
    if(counter == 1)
      tex->_framebuffers.erase(this);
  }
  this->_textureAttachments.erase(attachment);
}

void Framebuffer::attachTexture(GLenum attachment,Texture*texture,GLint level,GLint layer){
  assert(this!=nullptr);

  removeLinkToAttachedTexture(attachment);

  if(!texture){
    if(layer==-1)
      this->getContext().glNamedFramebufferTexture(this->getId(),attachment,0,level);
    else
      this->getContext().glNamedFramebufferTextureLayer(this->getId(),attachment,0,level,layer);
    return;
  }

  this->_textureAttachments[attachment] = texture;
  texture->_framebuffers.insert(this);

  if(layer==-1)
    this->getContext().glNamedFramebufferTexture(this->getId(),attachment,texture->getId(),level);
  else
    this->getContext().glNamedFramebufferTextureLayer(this->getId(),attachment,texture->getId(),level,layer);
}

void Framebuffer::attachTexture(GLenum attachment,std::shared_ptr<Texture>const&texture,GLint level,GLint layer){
  attachTexture(attachment,&*texture,level,layer);
}

void Framebuffer::bind  (GLenum target)const{
  assert(this!=nullptr);
  this->getContext().glBindFramebuffer(target,this->getId());
}
void Framebuffer::unbind(GLenum target)const{
  assert(this!=nullptr);
  this->getContext().glBindFramebuffer(target,0);
}

bool Framebuffer::check()const{
  assert(this!=nullptr);
  return this->getContext().glCheckNamedFramebufferStatus(this->getId(),GL_DRAW_FRAMEBUFFER)==GL_FRAMEBUFFER_COMPLETE;
}

void Framebuffer::drawBuffer(GLenum buffer)const{
  assert(this!=nullptr);
  this->getContext().glNamedFramebufferDrawBuffer(this->getId(),buffer);
}

void Framebuffer::drawBuffers(GLsizei n,const GLenum *buffers)const{
  assert(this!=nullptr);
  this->getContext().glNamedFramebufferDrawBuffers(this->getId(),n,buffers);
}


void Framebuffer::drawBuffers(std::vector<GLenum>const buffers)const{
  assert(this!=nullptr);
  this->getContext().glNamedFramebufferDrawBuffers(this->getId(),(GLsizei)buffers.size(),buffers.data());
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
  this->getContext().glClearNamedFramebufferiv(this->getId(),buffer,drawBuffer,value);
}

void Framebuffer::clearBuffer (GLenum buffer,GLint drawBuffer,const GLfloat*value)const{
  assert(this!=nullptr);
  this->getContext().glClearNamedFramebufferfv(this->getId(),buffer,drawBuffer,value);
}

void Framebuffer::clearBuffer (GLenum buffer,GLint drawBuffer,const GLuint*value)const{
  assert(this!=nullptr);
  this->getContext().glClearNamedFramebufferuiv(this->getId(),buffer,drawBuffer,value);
}

void Framebuffer::clearBuffer (GLenum buffer,GLint drawBuffer,GLfloat depth,GLint stencil)const{
  assert(this!=nullptr);
  this->getContext().glClearNamedFramebufferfi(this->getId(),buffer,drawBuffer,depth,stencil);
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
    this->getContext().glInvalidateNamedFramebufferData(this->getId(),numAttachments,attachments);
  else
    this->getContext().glInvalidateNamedFramebufferSubData(this->getId(),numAttachments,attachments,x,y,width,height);
}

GLboolean Framebuffer::isFramebuffer()const{
  assert(this!=nullptr);
  return this->getContext().glIsFramebuffer(this->getId());
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
  this->getContext().glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS,&maxColorAttachments);
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

