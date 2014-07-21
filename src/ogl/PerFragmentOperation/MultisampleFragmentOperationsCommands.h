#ifndef _MULTISAMPLEFRAGMENTOPERATIONSCOMMANDS_H_
#define _MULTISAMPLEFRAGMENTOPERATIONSCOMMANDS_H_

#include"../../ogl/Standard/OpenGL.h"

namespace ge
{
  namespace ogl
  {
    class SampleCoverage: public Command
    {
      public:
        GLfloat   value;
        GLboolean invert;
        SampleCoverage(GLfloat value,GLboolean invert);
        void apply();
    };

    class SampleMaski: public Command
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
