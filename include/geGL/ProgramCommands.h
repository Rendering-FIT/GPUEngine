#pragma once

#include<geGL/OpenGL.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT UseProgram: public Command{
      public:
        GLuint program;
        UseProgram(GLuint program);
        void apply();
    };
  }
}
