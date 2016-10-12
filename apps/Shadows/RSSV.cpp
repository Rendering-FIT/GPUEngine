#include"RSSV.h"

#include<geCore/Dtemplates.h>
#include"ProgramExtension.h"

RSSV::RSSV(
    glm::uvec2                      const&windowSize   ,
    std::shared_ptr<ge::gl::Texture>const&shadowMask   ,
    std::shared_ptr<ge::gl::Texture>const&depthTexture ,
    std::shared_ptr<Model>          const&model        ,
    size_t                          const&wavefrontSize
    ):_windowSize(windowSize),_shadowMask(shadowMask),_depthTexture(depthTexture),_wavefrontSize(wavefrontSize){
  assert(this!=nullptr);
  (void)model;
#include"RSSVShaders.h"
  this->_generateHDT0Program = makeComputeProgram(
      defineComputeShaderHeader(this->_generateHDT0WGS,this->_wavefrontSize),
      _generateHDT0Src);
}

RSSV::~RSSV(){}

void RSSV::create(
    glm::vec4 const&lightPosition,
    glm::mat4 const&view         ,
    glm::mat4 const&projection   ){
  assert(this!=nullptr);
  (void)lightPosition;
  (void)view;
  (void)projection;
  this->_generateHDT();
}

void RSSV::_generateHDT(){
  assert(this!=nullptr);
  this->_generateHDT0Program->use();
  this->_generateHDT0Program->set2uiv("windowSize",glm::value_ptr(this->_windowSize));
  this->_depthTexture->bind(0);
  this->_HDT[this->_nofLevels-1]->bindImage(1);
  glDispatchCompute(
      (GLuint)ge::core::getDispatchSize(this->_windowSize.x,this->_generateHDT0WGS.x),
      (GLuint)ge::core::getDispatchSize(this->_windowSize.y,this->_generateHDT0WGS.y),
      1);
}
