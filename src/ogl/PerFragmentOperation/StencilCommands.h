#ifndef _CSTENCILFUNCTIONS_HPP_
#define _CSTENCILFUNCTIONS_HPP_

#include"../../ogl/Standard/OpenGL.h"

namespace ge
{
  namespace ogl
  {
    class StencilFunc: public Command
    {
      public:
        GLenum func;
        GLint  ref;
        GLuint mask;
        StencilFunc(GLenum func,GLint ref,GLuint mask);
        void apply();
    };

    class StencilFuncSeparate: public Command
    {
      public:
        GLenum face;
        GLenum func;
        GLint  ref;
        GLuint mask;
        StencilFuncSeparate(GLenum face,GLenum func,GLint ref,GLuint mask);
        void apply();
    };

    class StencilOp: public Command
    {
      public:
        GLenum sfail;
        GLenum dpfail;
        GLenum dppass;
        StencilOp(GLenum sfail,GLenum dpfail,GLenum dppass);
        void apply();
    };

    class StencilOpSeparate: public Command
    {
      public:
        GLenum face;
        GLenum sfail;
        GLenum dpfail;
        GLenum dppass;
        StencilOpSeparate(GLenum face,GLenum sfail,GLenum dpfail,GLenum dppass);
        void apply();
    };
  }//ogl
}//ge

#endif//_CSTENCILFUNCTIONS_HPP_
