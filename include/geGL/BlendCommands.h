#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT BlendEnablei: public ge::core::Command
    {
      public:
        GLuint buffer;
        bool   enable;
        BlendEnablei(GLuint buffer,bool enable);
        void operator()();
    };

    class GEGL_EXPORT BlendEquation: public ge::core::Command
    {
      public:
        GLenum mode;
        BlendEquation(GLenum mode);
        void operator()();
    };

    class GEGL_EXPORT BlendEquationSeparate: public ge::core::Command
    {
      public:
        GLenum modeRGB;
        GLenum modeAlpha;
        BlendEquationSeparate(
            GLenum modeRGB,
            GLenum modeAlpha);
        void operator()();
    };

    class GEGL_EXPORT BlendEquationi: public ge::core::Command
    {
      public:
        GLuint buffer;
        GLenum mode;
        BlendEquationi(
            GLuint buffer,
            GLenum mode);
        void operator()();
    };

    class GEGL_EXPORT BlendEquationSeparatei: public ge::core::Command
    {
      public:
        GLuint buffer;
        GLenum modeRGB;
        GLenum modeAlpha;
        BlendEquationSeparatei(
            GLuint buffer,
            GLenum modeRGB,
            GLenum modeAlpha);
        void operator()();
    };

    class GEGL_EXPORT BlendFunc: public ge::core::Command
    {
      public:
        GLenum src;
        GLenum dst;
        BlendFunc(
            GLenum src,
            GLenum dst);
        void operator()();
    };

    class GEGL_EXPORT BlendFuncSeparate: public ge::core::Command
    {
      public:
        GLenum srcRGB;
        GLenum dstRGB;
        GLenum srcAlpha;
        GLenum dstAlpha;
        BlendFuncSeparate(
            GLenum srcRGB,
            GLenum dstRGB,
            GLenum srcAlpha,
            GLenum dstAlpha);
        void operator()();
    };

    class GEGL_EXPORT BlendFunci: public ge::core::Command
    {
      public:
        GLuint buffer;
        GLenum src;
        GLenum dst;
        BlendFunci(
            GLuint buffer,
            GLenum src,
            GLenum dst);
        void operator()();
    };

    class GEGL_EXPORT BlendFuncSeparatei: public ge::core::Command
    {
      public:
        GLuint buffer;
        GLenum srcRGB;
        GLenum dstRGB;
        GLenum srcAlpha;
        GLenum dstAlpha;
        BlendFuncSeparatei(
            GLuint buffer,
            GLenum srcRGB,
            GLenum dstRGB,
            GLenum srcAlpha,
            GLenum dstAlpha);
        void operator()();
    };

    class GEGL_EXPORT BlendColor: public ge::core::Command
    {
      public:
        GLfloat red;
        GLfloat green;
        GLfloat blue;
        GLfloat alpha;
        BlendColor(
            GLfloat red,
            GLfloat green,
            GLfloat blue,
            GLfloat alpha);
        void operator()();
    };
  }
}

