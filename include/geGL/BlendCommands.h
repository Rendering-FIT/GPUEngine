#ifndef _CBLENDINGFUNCTIONS_HPP_
#define _CBLENDINGFUNCTIONS_HPP_

#include <geGL/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GEGL_EXPORT BlendEnablei: public Command
    {
      public:
        GLuint buffer;
        bool   enable;
        BlendEnablei(GLuint buffer,bool enable);
        void apply();
    };

    class GEGL_EXPORT BlendEquation: public Command
    {
      public:
        GLenum mode;
        BlendEquation(GLenum mode);
        void apply();
    };

    class GEGL_EXPORT BlendEquationSeparate: public Command
    {
      public:
        GLenum modeRGB;
        GLenum modeAlpha;
        BlendEquationSeparate(
            GLenum modeRGB,
            GLenum modeAlpha);
        void apply();
    };

    class GEGL_EXPORT BlendEquationi: public Command
    {
      public:
        GLuint buffer;
        GLenum mode;
        BlendEquationi(
            GLuint buffer,
            GLenum mode);
        void apply();
    };

    class GEGL_EXPORT BlendEquationSeparatei: public Command
    {
      public:
        GLuint buffer;
        GLenum modeRGB;
        GLenum modeAlpha;
        BlendEquationSeparatei(
            GLuint buffer,
            GLenum modeRGB,
            GLenum modeAlpha);
        void apply();
    };

    class GEGL_EXPORT BlendFunc: public Command
    {
      public:
        GLenum src;
        GLenum dst;
        BlendFunc(
            GLenum src,
            GLenum dst);
        void apply();
    };

    class GEGL_EXPORT BlendFuncSeparate: public Command
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
        void apply();
    };

    class GEGL_EXPORT BlendFunci: public Command
    {
      public:
        GLuint buffer;
        GLenum src;
        GLenum dst;
        BlendFunci(
            GLuint buffer,
            GLenum src,
            GLenum dst);
        void apply();
    };

    class GEGL_EXPORT BlendFuncSeparatei: public Command
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
        void apply();
    };

    class GEGL_EXPORT BlendColor: public Command
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
        void apply();
    };
  }
}

#endif//_CBLENDINGFUNCTIONS_HPP_
