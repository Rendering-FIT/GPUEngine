#ifndef _MULTISAMPLEFRAGMENTOPERATIONSCOMMANDS_H_
#define _MULTISAMPLEFRAGMENTOPERATIONSCOMMANDS_H_

#include <geGL/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GEGL_EXPORT SampleCoverage: public Command
    {
      public:
        GLfloat   value;
        GLboolean invert;
        SampleCoverage(GLfloat value,GLboolean invert);
        void apply();
    };

    class GEGL_EXPORT SampleMaski: public Command
    {
      public:
        GLuint     maskNumber;
        GLbitfield mask;
        SampleMaski(GLuint maskNumber,GLbitfield mask);
        void apply();
    };
  }//ogl
}//ge




#endif//_MULTISAMPLEFRAGMENTOPERATIONSCOMMANDS_H_
