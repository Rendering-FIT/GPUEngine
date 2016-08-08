#pragma once

#include<geGL/OpenGL.h>
#include<geGL/OpenGLContext.h>

namespace ge{
  namespace gl{
    GEGL_EXPORT void setDefaultDebugMessage(
        opengl::ContextPointer const&gl = nullptr);
    GEGL_EXPORT void setLowAndGreaterDebugMessage(
        opengl::ContextPointer const&gl = nullptr);
    GEGL_EXPORT void setMediumAndGreaterDebugMessage(
        opengl::ContextPointer const&gl = nullptr);
    GEGL_EXPORT void setHighDebugMessage(
        opengl::ContextPointer const&gl = nullptr);
    GEGL_EXPORT void setDebugMessage(
        GLDEBUGPROC fce,
        void*data,
        opengl::ContextPointer const&gl = nullptr);
  }//gl
}//ge

