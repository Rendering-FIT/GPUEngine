#ifndef _SCISSORCOMMANDS_H_
#define _SCISSORCOMMANDS_H_

#include <geGL/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GEGL_EXPORT ScissorArrayv: public Command
    {
      public:
        GLuint        first;
        GLsizei       count;
        GLint * v;
        ScissorArrayv(GLuint first,GLsizei count,GLint*v);
        void apply();
    };
    class GEGL_EXPORT ScissorIndexed: public Command
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
    class GEGL_EXPORT ScissorIndexedv: public Command
    {
      public:
        GLuint   index;
        GLint  * v;
        ScissorIndexedv(GLuint index,GLint*v);
        void apply();
    };
    class GEGL_EXPORT Scissor: public Command
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
