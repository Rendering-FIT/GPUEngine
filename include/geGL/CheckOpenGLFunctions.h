#pragma once

#include<memory>
#include<geGL/Export.h>

namespace ge{
  namespace gl{
    class OpenGLFunctionTable;
    GEGL_EXPORT void checkOpenGLFunctions(std::shared_ptr<OpenGLFunctionTable>const&);
  }
}
