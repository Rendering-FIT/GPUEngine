#include"ShadowVolumes.h"

ShadowVolumes::ShadowVolumes(
    std::shared_ptr<ge::gl::Texture>const&shadowMask,
    std::shared_ptr<ge::gl::Texture>const&depth     ,
    ShadowVolumesParams             const&params    ):
  _params(params)
{
  assert(this!=nullptr);
  this->_fbo = std::make_shared<ge::gl::Framebuffer>();
  this->_fbo->attachTexture(GL_DEPTH_ATTACHMENT,depth);
  this->_fbo->attachTexture(GL_STENCIL_ATTACHMENT,depth);
  assert(this->_fbo->check());

  this->_maskFbo = std::make_shared<ge::gl::Framebuffer>();
  this->_maskFbo->attachTexture(GL_STENCIL_ATTACHMENT,depth);
  this->_maskFbo->attachTexture(GL_COLOR_ATTACHMENT0,shadowMask);
  this->_maskFbo->drawBuffers(1,GL_COLOR_ATTACHMENT0);
  assert(this->_maskFbo->check());

  this->_emptyVao = std::make_shared<ge::gl::VertexArray>();

#include"ShadowVolumesShaders.h"
  this->_blitProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,blitVPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,blitFPSrc));
}

ShadowVolumes::~ShadowVolumes(){}

void ShadowVolumes::_blit(){
  assert(this!=nullptr);
  assert(this->_blitProgram!=nullptr);
  assert(this->_maskFbo!=nullptr);
  assert(this->_emptyVao!=nullptr);
  glDisable(GL_DEPTH_TEST);
  this->_maskFbo->bind();
  glClear(GL_COLOR_BUFFER_BIT);
  glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
  glStencilFunc(GL_EQUAL,0,0xff);
  glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
  glDepthFunc(GL_ALWAYS);
  glDepthMask(GL_FALSE);
  this->_blitProgram->use();
  this->_emptyVao->bind();
  glDrawArrays(GL_TRIANGLE_STRIP,0,4);
  this->_emptyVao->unbind();
  this->_maskFbo->unbind();
}


void ShadowVolumes::create(
    glm::vec4 const&lightPosition   ,
    glm::mat4 const&viewMatrix      ,
    glm::mat4 const&projectionMatrix){
  assert(this!=nullptr);
  assert(this->_fbo!=nullptr);

  if(this->timeStamp)this->timeStamp->stamp("");

  this->_fbo->bind();
  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_ALWAYS,0,0);

  if(this->_params.zfail){
    glStencilOpSeparate(GL_FRONT,GL_KEEP,GL_INCR_WRAP,GL_KEEP);
    glStencilOpSeparate(GL_BACK ,GL_KEEP,GL_DECR_WRAP,GL_KEEP);
  }else{
    glStencilOpSeparate(GL_FRONT,GL_KEEP,GL_KEEP,GL_INCR_WRAP);
    glStencilOpSeparate(GL_BACK ,GL_KEEP,GL_KEEP,GL_DECR_WRAP);
  }
  glDepthFunc(GL_LESS);
  glDepthMask(GL_FALSE);
  glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);

#define SIDES_RASTER_DISCARD

#ifdef SIDES_RASTER_DISCARD
  glEnable(GL_RASTERIZER_DISCARD);
#endif
  this->drawSides(lightPosition,viewMatrix,projectionMatrix);
  if(this->timeStamp)this->timeStamp->stamp("drawSides");
#ifdef SIDES_RASTER_DISCARD
  glDisable(GL_RASTERIZER_DISCARD);
#endif
  if(this->_params.zfail){
    this->drawCaps(lightPosition,viewMatrix,projectionMatrix);
    if(this->timeStamp)this->timeStamp->stamp("drawCaps");
  }
  this->_fbo->unbind();

  this->_blit();

  glDepthFunc(GL_LESS);
  glDisable(GL_STENCIL_TEST);
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);

  if(this->timeStamp)this->timeStamp->stamp("blit");
}

