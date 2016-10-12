#pragma once

#include<sstream>
#include<glm/glm.hpp>
#include<geGL/geGL.h>

template<typename...ARGS>
std::shared_ptr<ge::gl::Program>makeComputeProgram(ARGS...args){
  return std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,args...));
}

inline std::string defineWorkgroupSize(size_t const&wgs){
  return
    ge::gl::Shader::define("WORKGROUP_SIZE_X",(int)wgs);
}

inline std::string defineWorkgroupSize(glm::uvec2 const&wgs){
  return
    ge::gl::Shader::define("WORKGROUP_SIZE_X",(int)wgs.x)+
    ge::gl::Shader::define("WORKGROUP_SIZE_Y",(int)wgs.y);
}

inline std::string defineWorkgroupSize(glm::uvec3 const&wgs){
  return
    ge::gl::Shader::define("WORKGROUP_SIZE_X",(int)wgs.x)+
    ge::gl::Shader::define("WORKGROUP_SIZE_Y",(int)wgs.y)+
    ge::gl::Shader::define("WORKGROUP_SIZE_Z",(int)wgs.z);
}

inline std::string defineVersion(size_t version,std::string const&profile = "core"){
  std::stringstream ss;
  ss<<"#version "<<version<<" "<<profile<<" \n";
  return ss.str();
}

inline std::string defineWavefrontSize(size_t wavefrontSize){
  return ge::gl::Shader::define("WAVEFRONT_SIZE",(int)wavefrontSize);
}

inline std::string defineComputeShaderHeader(
    size_t const&wgs,
    size_t wavefrontSize,
    size_t glslVersion = 450,std::string const&profile = "core"){
  return 
    defineVersion(glslVersion,profile)+
    defineWorkgroupSize(wgs)+
    defineWavefrontSize(wavefrontSize);
}

inline std::string defineComputeShaderHeader(
    glm::uvec2 const&wgs,
    size_t wavefrontSize,
    size_t glslVersion = 450,std::string const&profile = "core"){
  return 
    defineVersion(glslVersion,profile)+
    defineWorkgroupSize(wgs)+
    defineWavefrontSize(wavefrontSize);
}

inline std::string defineComputeShaderHeader(
    glm::uvec3 const&wgs,
    size_t wavefrontSize,
    size_t glslVersion = 450,std::string const&profile = "core"){
  return 
    defineVersion(glslVersion,profile)+
    defineWorkgroupSize(wgs)+
    defineWavefrontSize(wavefrontSize);
}


