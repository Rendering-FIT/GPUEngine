#pragma once

#include"/usr/include/GL/gl.h"
#include"/usr/include/GL/glext.h"
//#include<GL/gl.h>
//#include<GL/glext.h>
#include<geGL/Export.h>
typedef unsigned short GLhalfNV;
typedef void* GLeglImageOES;
namespace ge{
  namespace gl{
    class GEGL_EXPORT OpenGLFunctionTable{
      public:
#include<geGL/GeneratedOpenGLPFN.h>
#include<geGL/GeneratedOpenGLFunctions.h>
    };
  }
}


