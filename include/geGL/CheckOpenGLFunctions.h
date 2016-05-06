#pragma once

#include<memory>
#include<geGL/Export.h>
#include<geGL/OpenGLFunctionTable.h>

namespace ge{
  namespace gl{
    namespace opengl{
      GEGL_EXPORT void checkFunctions(FunctionTablePointer const&);
    }
  }
}
