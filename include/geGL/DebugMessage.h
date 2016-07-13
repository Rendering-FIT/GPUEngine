#pragma once

#include<geGL/OpenGL.h>
#include<geGL/OpenGLFunctionProvider.h>

namespace ge{
  namespace gl{
    GEGL_EXPORT void setDefaultDebugMessage(
        opengl::FunctionProviderPointer const&gl = nullptr);
    GEGL_EXPORT void setLowAndGreaterDebugMessage(
        opengl::FunctionProviderPointer const&gl = nullptr);
    GEGL_EXPORT void setMediumAndGreaterDebugMessage(
        opengl::FunctionProviderPointer const&gl = nullptr);
    GEGL_EXPORT void setHighDebugMessage(
        opengl::FunctionProviderPointer const&gl = nullptr);
    GEGL_EXPORT void setDebugMessage(
        GLDEBUGPROC fce,
        void*data,
        opengl::FunctionProviderPointer const&gl = nullptr);
  }//gl
}//ge

