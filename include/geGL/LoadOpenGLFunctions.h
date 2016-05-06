#pragma once

#include<memory>
#include<geGL/Export.h>
#include<geGL/OpenGLFunctionTable.h>

namespace ge{
  namespace gl{
    namespace opengl{
      typedef void(*FUNCTION_POINTER)();
      typedef FUNCTION_POINTER(*GET_PROC_ADDRESS)(char const*str);
      GEGL_EXPORT void loadFunctions(
          FunctionTablePointer const&,
          GET_PROC_ADDRESS);
    }
  }
}

