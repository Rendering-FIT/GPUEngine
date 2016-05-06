#pragma once

#include<geGL/OpenGL.h>
#if defined(REPLACE_GLEW)
#include<geGL/OpenGLFunctionProvider.h>
#endif

#include<iostream>

namespace ge{
  namespace gl{
    GEGL_EXPORT std::string translateDebugSource  (GLenum source  );
    GEGL_EXPORT std::string translateDebugType    (GLenum type    );
    GEGL_EXPORT std::string translateDebugSeverity(GLenum severity);
    GEGL_EXPORT void setDefaultDebugMessage(
#if defined(REPLACE_GLEW)
        opengl::FunctionProvider const&gl
#endif
        );
    GEGL_EXPORT void setLowAndGreaterDebugMessage(
#if defined(REPLACE_GLEW)
        opengl::FunctionProvider const&gl
#endif       
        );
    GEGL_EXPORT void setMediumAndGreaterDebugMessage(
#if defined(REPLACE_GLEW)
        opengl::FunctionProvider const&gl
#endif       
        );
    GEGL_EXPORT void setHighDebugMessage(
#if defined(REPLACE_GLEW)
        opengl::FunctionProvider const&gl
#endif       
        );
    GEGL_EXPORT void setDebugMessage(
#if defined(REPLACE_GLEW)
        opengl::FunctionProvider const&gl,
#endif       
        GLDEBUGPROC fce,
        void*data);
  }//gl
}//ge

