#pragma once

#include<geGL/OpenGL.h>
#include<geGL/OpenGLContext.h>

namespace ge{
  namespace gl{
    GEGL_EXPORT void setDefaultDebugMessage(
        ContextPointer const&gl = nullptr);
    GEGL_EXPORT void setLowAndGreaterDebugMessage(
        ContextPointer const&gl = nullptr);
    GEGL_EXPORT void setMediumAndGreaterDebugMessage(
        ContextPointer const&gl = nullptr);
    GEGL_EXPORT void setHighDebugMessage(
        ContextPointer const&gl = nullptr);
    GEGL_EXPORT void setDebugMessage(
        GLDEBUGPROC fce,
        void*data,
        ContextPointer const&gl = nullptr);
  }//gl
}//ge

