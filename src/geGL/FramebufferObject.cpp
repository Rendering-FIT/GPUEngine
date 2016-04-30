#include<geGL/FramebufferObject.h>
#include<iostream>
#include<sstream>

using namespace ge::gl;

std::string ge::gl::translateFramebufferComponentType(GLenum type){
  switch(type){
    case GL_FLOAT              :return"GL_FLOAT"              ;
    case GL_INT                :return"GL_INT"                ;
    case GL_UNSIGNED_INT       :return"GL_UNSIGNED_INT"       ;
    case GL_SIGNED_NORMALIZED  :return"GL_SIGNED_NORMALIZED"  ;
    case GL_UNSIGNED_NORMALIZED:return"GL_UNSIGNED_NORMALIZED";
    default                    :return"unknown"               ;
  }
}

std::string ge::gl::translateFramebufferObjectType(GLenum type){
  switch(type){
    case GL_NONE               :return"GL_NONE"               ;
    case GL_FRAMEBUFFER_DEFAULT:return"GL_FRAMEBUFFER_DEFAULT";
    case GL_TEXTURE            :return"GL_TEXTURE"            ;
    case GL_RENDERBUFFER       :return"GL_RENDERBUFFER"       ;
    default                    :return"unknown"               ;
  }
}

std::string ge::gl::translateFramebufferAttachment(GLenum attachment){
  switch(attachment){
    case GL_DEPTH_ATTACHMENT  :return"GL_DEPTH_ATTACHMENT"  ;
    case GL_STENCIL_ATTACHMENT:return"GL_STENCIL_ATTACHMENT";
    case GL_COLOR_ATTACHMENT0 :return"GL_COLOR_ATTACHMENT0" ;
    case GL_COLOR_ATTACHMENT1 :return"GL_COLOR_ATTACHMENT1" ;
    case GL_COLOR_ATTACHMENT2 :return"GL_COLOR_ATTACHMENT2" ;
    case GL_COLOR_ATTACHMENT3 :return"GL_COLOR_ATTACHMENT3" ;
    case GL_COLOR_ATTACHMENT4 :return"GL_COLOR_ATTACHMENT4" ;
    case GL_COLOR_ATTACHMENT5 :return"GL_COLOR_ATTACHMENT5" ;
    case GL_COLOR_ATTACHMENT6 :return"GL_COLOR_ATTACHMENT6" ;
    case GL_COLOR_ATTACHMENT7 :return"GL_COLOR_ATTACHMENT7" ;
    case GL_COLOR_ATTACHMENT8 :return"GL_COLOR_ATTACHMENT8" ;
    case GL_COLOR_ATTACHMENT9 :return"GL_COLOR_ATTACHMENT8" ;
    case GL_COLOR_ATTACHMENT10:return"GL_COLOR_ATTACHMENT10";
    case GL_COLOR_ATTACHMENT11:return"GL_COLOR_ATTACHMENT11";
    case GL_COLOR_ATTACHMENT12:return"GL_COLOR_ATTACHMENT12";
    case GL_COLOR_ATTACHMENT13:return"GL_COLOR_ATTACHMENT13";
    case GL_COLOR_ATTACHMENT14:return"GL_COLOR_ATTACHMENT14";
    case GL_COLOR_ATTACHMENT15:return"GL_COLOR_ATTACHMENT15";
    default:                   return"unknown"              ;
  }
}

std::string ge::gl::translateFramebufferColorEncoding(GLenum type){
  switch(type){
    case GL_LINEAR:return"GL_LINEAR";
    case GL_SRGB  :return"GL_SRGB"  ;
    default       :return"unknown"  ;
  }
}

std::string ge::gl::translateCubeMapFace(GLenum face){
  switch(face){
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:return"GL_TEXTURE_CUBE_MAP_NEGATIVE_X";
    case GL_TEXTURE_CUBE_MAP_POSITIVE_X:return"GL_TEXTURE_CUBE_MAP_POSITIVE_X";
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:return"GL_TEXTURE_CUBE_MAP_NEGATIVE_Y";
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:return"GL_TEXTURE_CUBE_MAP_POSITIVE_Y";
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:return"GL_TEXTURE_CUBE_MAP_NEGATIVE_Z";
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:return"GL_TEXTURE_CUBE_MAP_POSITIVE_Z";
    default                            :return"unknown";
  }
}


GLint FramebufferObject::getParam(GLenum pname){
  GLint param;
  glGetNamedFramebufferParameteriv(this->_id,pname,&param);
  return param;
}

void FramebufferObject::setParam(GLenum pname,GLint param){
  glNamedFramebufferParameteri(this->_id,pname,param);
}

GLint FramebufferObject::getAttachmentParam(GLenum attachment,GLenum pname){
  GLint param;
  glGetNamedFramebufferAttachmentParameteriv(this->_id,attachment,pname,&param);
  return param;
}

FramebufferObject::FramebufferObject (bool defaultFramebuffer){
  if(defaultFramebuffer)this->_id=0;
  else glCreateFramebuffers(1,&this->_id);
}

FramebufferObject::~FramebufferObject(){
  glDeleteFramebuffers(1,&this->_id);
}

void FramebufferObject::attachRenderbuffer(GLenum attachment,GLuint renderbuffer)const{
  glNamedFramebufferRenderbuffer(this->_id,attachment,GL_RENDERBUFFER,renderbuffer);
}

void FramebufferObject::attachTexture(GLenum attachment,GLuint texture,GLint level,GLint layer)const{
  if(layer==-1)
    glNamedFramebufferTexture(this->_id,attachment,texture,level);
  else
    glNamedFramebufferTextureLayer(this->_id,attachment,texture,level,layer);
}

void FramebufferObject::bind  (GLenum target)const{
  glBindFramebuffer(target,this->_id);
}
void FramebufferObject::unbind(GLenum target)const{
  glBindFramebuffer(target,0);
}

bool FramebufferObject::check()const{
  return glCheckNamedFramebufferStatus(this->_id,GL_DRAW_FRAMEBUFFER)==GL_FRAMEBUFFER_COMPLETE;
}

void FramebufferObject::drawBuffer(GLenum buffer)const{
  glNamedFramebufferDrawBuffer(this->_id,buffer);
}

void FramebufferObject::drawBuffers(GLsizei n,const GLenum *buffers)const{
  glNamedFramebufferDrawBuffers(this->_id,n,buffers);
}

void FramebufferObject::drawBuffers(GLsizei n,...)const{
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

void FramebufferObject::clearBuffer (GLenum buffer,GLint drawBuffer,const GLint*value)const{
  glClearNamedFramebufferiv(this->_id,buffer,drawBuffer,value);
}

void FramebufferObject::clearBuffer (GLenum buffer,GLint drawBuffer,const GLfloat*value)const{
  glClearNamedFramebufferfv(this->_id,buffer,drawBuffer,value);
}

void FramebufferObject::clearBuffer (GLenum buffer,GLint drawBuffer,const GLuint*value)const{
  glClearNamedFramebufferuiv(this->_id,buffer,drawBuffer,value);
}

#if defined(REPLACE_GLEW)
void FramebufferObject::clearBuffer (GLenum buffer,GLint drawBuffer,GLfloat depth,GLint stencil)const{
  glClearNamedFramebufferfi(this->_id,buffer,drawBuffer,depth,stencil);
}
#else//REPLACE_GLEW
void FramebufferObject::clearBuffer (GLenum buffer,GLfloat depth,GLint stencil)const{
  glClearNamedFramebufferfi(this->_id,buffer,depth,stencil);
}
#endif//REPLACE_GLEW

void FramebufferObject::invalidateFramebuffer(
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

GLboolean FramebufferObject::isFramebuffer()const{
  return glIsFramebuffer(this->_id);
}

void FramebufferObject::setDefaultWidth(GLint width){
  this->setParam(GL_FRAMEBUFFER_DEFAULT_WIDTH,width);
}
void FramebufferObject::setDefaultHeight(GLint height){
  this->setParam(GL_FRAMEBUFFER_DEFAULT_HEIGHT,height);
}
void FramebufferObject::setDefaultFixedSampleLocations(GLint location){
  this->setParam(GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS,location);
}
void FramebufferObject::setDefaultSamples(GLint samples){
  this->setParam(GL_FRAMEBUFFER_DEFAULT_SAMPLES,samples);
}
void FramebufferObject::setDefaultLayers(GLint layers){
  this->setParam(GL_FRAMEBUFFER_DEFAULT_LAYERS,layers);
}

GLint FramebufferObject::getDefaultWidth(){
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_WIDTH );
}
GLint FramebufferObject::getDefaultHeight(){
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_HEIGHT);
}
GLint FramebufferObject::getDefaultLayers(){
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_LAYERS);
}
GLint FramebufferObject::getDefaultSamples(){
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_SAMPLES);
}
GLint FramebufferObject::getDefaultFixedSampleLocations(){
  return this->getParam(GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS);
}
GLint FramebufferObject::getSamples(){
  return this->getParam(GL_SAMPLES);
}
GLint FramebufferObject::getSampleBuffers(){
  return this->getParam(GL_SAMPLE_BUFFERS);
}

GLenum FramebufferObject::getAttachmentObjectType   (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);
}
GLint  FramebufferObject::getAttachmentRedSize      (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE);
}
GLint  FramebufferObject::getAttachmentGreenSize    (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE);
}
GLint  FramebufferObject::getAttachmentBlueSize     (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE);
}
GLint  FramebufferObject::getAttachmentAlphaSize    (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE);
}
GLint  FramebufferObject::getAttachmentDepthSize    (){
  return this->getAttachmentParam(GL_DEPTH_ATTACHMENT,GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE);
}
GLint  FramebufferObject::getAttachmentStencilSize  (){
  return this->getAttachmentParam(GL_STENCIL_ATTACHMENT,GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE);
}
GLenum FramebufferObject::getAttachmentComponentType(GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE);
}
GLenum    FramebufferObject::getAttachmentColorEncoding     (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING);
}
GLuint    FramebufferObject::getAttachmentObjectName        (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME);
}
GLint     FramebufferObject::getAttachmentTextureLevel      (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL);
}
GLenum    FramebufferObject::getAttachmentTextureCubeMapFace(GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE);
}
GLboolean FramebufferObject::isAttachmentLayered            (GLenum attachment){
  return (GLboolean)this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_LAYERED);
}
GLint     FramebufferObject::getAttachmentTextureLayer      (GLenum attachment){
  return this->getAttachmentParam(attachment,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER);
}


GLint FramebufferObject::getDoubleBuffer(){
  return this->getParam(GL_DOUBLEBUFFER);
}
GLint FramebufferObject::getImplementationColorReadFormat(){
  return this->getParam(GL_IMPLEMENTATION_COLOR_READ_FORMAT);
}
GLint FramebufferObject::getImplementationColorReadType  (){
  return this->getParam(GL_IMPLEMENTATION_COLOR_READ_TYPE);
}
GLint FramebufferObject::getStereo(){
  return this->getParam(GL_STEREO);
}

std::string FramebufferObject::getInfo(){
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
    ss<<"  object type:    "<<ge::gl::translateFramebufferObjectType(
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
    ss<<"  object type:    "<<ge::gl::translateFramebufferObjectType(
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
    ss<<"  object type:    "<<ge::gl::translateFramebufferObjectType(
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

