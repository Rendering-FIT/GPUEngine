#pragma once

#include<geGL/gegl_export.h>
#include<geGL/OpenGLFunctionTable.h>

namespace ge{
  namespace gl{
    class Global;
    extern thread_local ge::gl::Global global;
  }
}

class ge::gl::Global{
  public:
    FunctionTablePointer table   = nullptr;
    ContextPointer       context = nullptr;
};
