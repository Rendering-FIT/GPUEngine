#pragma once

#include<geGL/Export.h>

#include<geGL/OpenGL.h>
#include<geGL/OpenGLCapabilities.h>

typedef unsigned short GLhalfNV;
typedef void* GLeglImageOES;

namespace ge{
  namespace gl{
    class GEGL_EXPORT OpenGLFunctionTable{
      public:
        OpenGLCapabilities capabilities;
#include<geGL/GeneratedOpenGLPFN.h>
#include<geGL/GeneratedOpenGLFunctions.h>
    };
  }
}


