#pragma once

#include<memory>
#include<geGL/Export.h>

namespace ge{
  namespace gl{
    class OpenGLFunctionTable;
    typedef void(*FUNCTION_POINTER)();
    typedef FUNCTION_POINTER(*GET_PROC_ADDRESS)(char const*str);
    GEGL_EXPORT void loadOpenGLFunctions(
        std::shared_ptr<OpenGLFunctionTable>const&,
        GET_PROC_ADDRESS);
  }
}

