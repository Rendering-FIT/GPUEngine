#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT BeginConditionalRender{
      public:
        GLuint id;
        GLenum mode;
        BeginConditionalRender(GLuint id,GLenum mode);
        void operator()();
    };
    class GEGL_EXPORT EndConditionalRender
    {
      public:
        EndConditionalRender();
        void operator()();
    };
  }//ogl
}//ge

