#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT ScissorArrayv: public ge::core::Command
    {
      public:
        GLuint        first;
        GLsizei       count;
        GLint * v;
        ScissorArrayv(GLuint first,GLsizei count,GLint*v);
        void operator()();
    };
    class GEGL_EXPORT ScissorIndexed: public ge::core::Command
    {
      public:
        GLuint  index;
        GLint   left;
        GLint   bottom;
        GLsizei width;
        GLsizei height;
        ScissorIndexed(GLuint index,GLint left,GLint bottom,GLsizei width,GLsizei height);
        void operator()();
    };
    class GEGL_EXPORT ScissorIndexedv: public ge::core::Command
    {
      public:
        GLuint   index;
        GLint  * v;
        ScissorIndexedv(GLuint index,GLint*v);
        void operator()();
    };
    class GEGL_EXPORT Scissor: public ge::core::Command
    {
      public:
        GLint   left;
        GLint   bottom;
        GLsizei width;
        GLsizei height;
        Scissor(GLint left,GLint bottom,GLsizei width,GLsizei height);
        void operator()();
    };
  }//ogl
}//ge

