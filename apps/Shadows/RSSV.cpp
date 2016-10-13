#include"RSSV.h"

#include<geCore/Dtemplates.h>
#include"ProgramExtension.h"
#include"RSSVTiles.h"

const size_t HIERARCHICALDEPTHTEXTURE_BINDING_DEPTH     = 0;
const size_t HIERARCHICALDEPTHTEXTURE_BINDING_HDT       = 1;

const size_t HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT  = 0;
const size_t HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT = 1;

const size_t     WAVEFRONT_SIZE = 64;
const size_t     TILE_EDGE_SIZE = size_t(glm::sqrt(WAVEFRONT_SIZE));
const glm::uvec2 TILE_SIZE      = glm::uvec2(uint32_t(TILE_EDGE_SIZE),uint32_t(TILE_EDGE_SIZE));

RSSV::RSSV(
    glm::uvec2                      const&windowSize   ,
    std::shared_ptr<ge::gl::Texture>const&shadowMask   ,
    std::shared_ptr<ge::gl::Texture>const&depthTexture ,
    std::shared_ptr<Model>          const&model        
    ):_windowSize(windowSize),_shadowMask(shadowMask),_depthTexture(depthTexture){
  assert(this!=nullptr);
  assert(
      (windowSize.x==8    && windowSize.y==8   ) ||
      (windowSize.x==64   && windowSize.y==64  ) ||
      (windowSize.x==512  && windowSize.y==512 ) ||
      (windowSize.x==4096 && windowSize.y==4096) );
  (void)model;
  if(windowSize.x == 8   )this->_nofLevels = 1;
  if(windowSize.x == 64  )this->_nofLevels = 2;
  if(windowSize.x == 512 )this->_nofLevels = 3;
  if(windowSize.x == 4096)this->_nofLevels = 4;

#include"RSSVShaders.h"

  this->_generateHDT0Program = makeComputeProgram(
      defineComputeShaderHeader(TILE_SIZE,WAVEFRONT_SIZE),
      ge::gl::Shader::define("HIERARCHICALDEPTHTEXTURE_BINDING_DEPTH",(int)HIERARCHICALDEPTHTEXTURE_BINDING_DEPTH),
      ge::gl::Shader::define("HIERARCHICALDEPTHTEXTURE_BINDING_HDT"  ,(int)HIERARCHICALDEPTHTEXTURE_BINDING_HDT  ),
      _generateHDT0Src);
  this->_generateHDTProgram = makeComputeProgram(
      defineComputeShaderHeader(TILE_SIZE,WAVEFRONT_SIZE),
      ge::gl::Shader::define("HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT" ,(int)HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT ),
      ge::gl::Shader::define("HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT",(int)HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT),
      _generateHDTSrc);
  glm::uvec2 hdtSize = TILE_SIZE;
  for(size_t l=0;l<this->_nofLevels;++l){
    this->_HDT.push_back(std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D,GL_RG32F,1,hdtSize.x,hdtSize.y));
    this->_HDT.back()->texParameteri(GL_TEXTURE_MAG_FILTER,GL_NEAREST               );
    this->_HDT.back()->texParameteri(GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
    float data[2]={1,-1};
    this->_HDT.back()->clear(0,GL_RG,GL_FLOAT,data);
    hdtSize*=TILE_SIZE;
  }



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
  this->_depthTexture->bind(HIERARCHICALDEPTHTEXTURE_BINDING_DEPTH);
  this->_HDT[this->_nofLevels-1]->bindImage(HIERARCHICALDEPTHTEXTURE_BINDING_HDT);
  glm::uvec2 wgs = this->_windowSize/TILE_SIZE;

  std::cout<<wgs.x<<" x "<<wgs.y<<std::endl;
  glDispatchCompute(wgs.x,wgs.y,1);
  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

  this->_generateHDTProgram->use();
  this->_generateHDTProgram->set2uiv("windowSize",glm::value_ptr(this->_windowSize));

  for(int l=(int)this->_nofLevels-2;l>=0;--l){
    this->_HDT[l+1]->bindImage(HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT );
    this->_HDT[l  ]->bindImage(HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT);
    wgs/=TILE_SIZE;
    std::cout<<wgs.x<<" x "<<wgs.y<<std::endl;
    glDispatchCompute(wgs.x,wgs.y,1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
  }
}
