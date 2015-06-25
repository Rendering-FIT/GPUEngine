#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT SampleCoverage: public ge::core::Command{
      public:
        GLfloat   value;
        GLboolean invert;
        SampleCoverage(GLfloat value,GLboolean invert);
        void operator()();
    };

    class GEGL_EXPORT SampleMaski: public ge::core::Command
    {
      public:
        GLuint     maskNumber;
        GLbitfield mask;
        SampleMaski(GLuint maskNumber,GLbitfield mask);
        void operator()();
    };
  }//ogl
}//ge

