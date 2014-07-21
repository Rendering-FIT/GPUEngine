#ifndef _SCISSORCOMMANDS_H_
#define _SCISSORCOMMANDS_H_

#include"../../ogl/Standard/OpenGL.h"

namespace ge
{
  namespace ogl
  {
    class ScissorArrayv: public Command
    {
      public:
        GLuint        first;
        GLsizei       count;
        GLint * v;
        ScissorArrayv(GLuint first,GLsizei count,GLint*v);
        void apply();
    };
    class ScissorIndexed: public Command
    {
      public:
        GLuint  index;
        GLint   left;
        GLint   bottom;
        GLsizei width;
        GLsizei height;
        ScissorIndexed(GLuint index,GLint left,GLint bottom,GLsizei width,GLsizei height);
        void apply();
    };
    class ScissorIndexedv: public Command
    {
      public:
        GLuint   index;
        GLint  * v;
        ScissorIndexedv(GLuint index,GLint*v);
        void apply();
    };
    class Scissor: public Command
    {
      public:
        GLint   left;
        GLint   bottom;
        GLsizei width;
        GLsizei height;
        Scissor(GLint left,GLint bottom,GLsizei width,GLsizei height);
        void apply();
    };
  }//ogl
}//ge


#endif//_SCISSORCOMMANDS_H_
