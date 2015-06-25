#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT UseProgram: public ge::core::Command{
      protected:
        GLuint _program;
      public:
        UseProgram(GLuint program=0);
        void operator()();
        void set(GLuint program=0);
        GLuint get();
    };
    class GEGL_EXPORT UseProgramR: public ge::core::Command{
      protected:
        GLuint*_program;
      public:
        UseProgramR(GLuint*program=NULL);
        void operator()();
        void set(GLuint*program=NULL);
        GLuint*get();
    };
  }
}
