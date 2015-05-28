#pragma once

#include<geGL/OpenGL.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT UseProgram: public Command{
      protected:
        GLuint _program;
      public:
        UseProgram(GLuint program=0);
        void apply();
        void set(GLuint program=0);
        GLuint get();
    };
    class GEGL_EXPORT UseProgramR: public Command{
      protected:
        GLuint*_program;
      public:
        UseProgramR(GLuint*program=NULL);
        void apply();
        void set(GLuint*program=NULL);
        GLuint*get();
    };
  }
}
