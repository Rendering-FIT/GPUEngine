#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT BeginQuery: public ge::core::Command
    {
      public:
        GLenum target;
        GLuint id;
        BeginQuery(GLenum target,GLuint id);
        void operator()();
    };
    class GEGL_EXPORT EndQuery: public ge::core::Command
    {
      public:
        GLenum target;
        EndQuery(GLenum target);
        void operator()();
    };
  }//ogl
}//ge

