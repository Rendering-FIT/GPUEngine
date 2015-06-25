#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT StencilFunc: public ge::core::Command
    {
      public:
        GLenum func;
        GLint  ref ;
        GLuint mask;
        StencilFunc(GLenum func,GLint ref,GLuint mask);
        void operator()();
    };

    class GEGL_EXPORT StencilFuncSeparate: public ge::core::Command
    {
      public:
        GLenum face;
        GLenum func;
        GLint  ref ;
        GLuint mask;
        StencilFuncSeparate(GLenum face,GLenum func,GLint ref,GLuint mask);
        void operator()();
    };

    class GEGL_EXPORT StencilOp: public ge::core::Command
    {
      public:
        GLenum sfail ;
        GLenum dpfail;
        GLenum dppass;
        StencilOp(GLenum sfail,GLenum dpfail,GLenum dppass);
        void operator()();
    };

    class GEGL_EXPORT StencilOpSeparate: public ge::core::Command
    {
      public:
        GLenum face  ;
        GLenum sfail ;
        GLenum dpfail;
        GLenum dppass;
        StencilOpSeparate(GLenum face,GLenum sfail,GLenum dpfail,GLenum dppass);
        void operator()();
    };
  }//ogl
}//ge

