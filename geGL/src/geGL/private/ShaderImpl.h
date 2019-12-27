#pragma once

#include<set>
#include<geGL/Fwd.h>

class ge::gl::ShaderImpl {
public:
  std::set<Program*>programs;
};
