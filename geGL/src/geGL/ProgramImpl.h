#pragma once

#include<memory>
#include<set>
#include<map>
#include<geGL/ProgramInfo.h>

class ge::gl::ProgramImpl {
public:
  using ShaderPointer = std::shared_ptr<Shader>;
  std::set<ShaderPointer>shaders;
  std::map<std::string, GLint>name2Uniform;
  std::shared_ptr<ProgramInfo>info;
};