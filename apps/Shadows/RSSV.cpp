#include"RSSV.h"

template<typename...ARGS>
std::shared_ptr<ge::gl::Program>createComputeProgram(ARGS...args){
  return std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,args...));
}

std::string defineWorkgroupSize(size_t const&wgs){
  return
    ge::gl::Shader::define("WORKGROUP_SIZE_X",(int)wgs);
}

std::string defineWorkgroupSize(glm::uvec2 const&wgs){
  return
    ge::gl::Shader::define("WORKGROUP_SIZE_X",(int)wgs.x)+
    ge::gl::Shader::define("WORKGROUP_SIZE_Y",(int)wgs.y);
}

std::string defineWorkgroupSize(glm::uvec3 const&wgs){
  return
    ge::gl::Shader::define("WORKGROUP_SIZE_X",(int)wgs.x)+
    ge::gl::Shader::define("WORKGROUP_SIZE_Y",(int)wgs.y)+
    ge::gl::Shader::define("WORKGROUP_SIZE_Z",(int)wgs.z);
}

std::string defineVersion(size_t version,std::string const&profile = "core"){
  std::stringstream ss;
  ss<<"#version "<<version<<" "<<profile<<" \n";
  return ss.str();
}

std::string defineWavefrontSize(size_t wavefrontSize){
  return ge::gl::Shader::define("WAVEFRONT_SIZE",(int)wavefrontSize);
}

std::string defineComputeShaderHeader(
    size_t const&wgs,
    size_t wavefrontSize,
    size_t glslVersion = 450,std::string const&profile = "core"){
  return 
    defineVersion(glslVersion,profile)+
    defineWorkgroupSize(wgs)+
    defineWavefrontSize(wavefrontSize);
}

std::string defineComputeShaderHeader(
    glm::uvec2 const&wgs,
    size_t wavefrontSize,
    size_t glslVersion = 450,std::string const&profile = "core"){
  return 
    defineVersion(glslVersion,profile)+
    defineWorkgroupSize(wgs)+
    defineWavefrontSize(wavefrontSize);
}

std::string defineComputeShaderHeader(
    glm::uvec3 const&wgs,
    size_t wavefrontSize,
    size_t glslVersion = 450,std::string const&profile = "core"){
  return 
    defineVersion(glslVersion,profile)+
    defineWorkgroupSize(wgs)+
    defineWavefrontSize(wavefrontSize);
}



RSSV::RSSV(
    glm::uvec2                      const&windowSize   ,
    std::shared_ptr<ge::gl::Texture>const&shadowMask   ,
    std::shared_ptr<ge::gl::Texture>const&depthTexture ,
    std::shared_ptr<Model>          const&model        ,
    size_t                          const&wavefrontSize
    ):_windowSize(windowSize),_shadowMask(shadowMask),_depthTexture(depthTexture),_wavefrontSize(wavefrontSize){
  (void)model;
#include"RSSVShaders.h"
  this->_generateHDT0 = createComputeProgram(
      defineComputeShaderHeader(this->_generateHDT0WGS,this->_wavefrontSize),
      _generateHDT0Src
      );
}

RSSV::~RSSV(){}

void RSSV::create(
    glm::vec4 const&lightPosition,
    glm::mat4 const&view         ,
    glm::mat4 const&projection   ){
  (void)lightPosition;
  (void)view;
  (void)projection;
}

