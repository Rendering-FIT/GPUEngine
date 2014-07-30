#ifndef _MULTISAMPLEFRAGMENTOPERATIONSCOMMANDS_H_
#define _MULTISAMPLEFRAGMENTOPERATIONSCOMMANDS_H_

#include <geGL/Standard/OpenGL.h>

namespace ge
{
  namespace ogl
  {
    class GE_EXPORT SampleCoverage: public Command
    {
      public:
        GLfloat   value;
        GLboolean invert;
        SampleCoverage(GLfloat value,GLboolean invert);
        void apply();
    };

    class GE_EXPORT SampleMaski: public Command
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
