#ifndef _CBLENDINGFUNCTIONS_HPP_
#define _CBLENDINGFUNCTIONS_HPP_

#include"../../ogl/Standard/OpenGL.h"

namespace ge
{
  namespace ogl
  {
    class BlendEnablei: public Command
    {
      public:
        GLuint buffer;
        bool   enable;
        BlendEnablei(GLuint buffer,bool enable);
        void apply();
    };

    class BlendEquation: public Command
    {
      public:
        GLenum mode;
        BlendEquation(GLenum mode);
        void apply();
    };

    class BlendEquationSeparate: public Command
    {
      public:
        GLenum modeRGB;
        GLenum modeAlpha;
        BlendEquationSeparate(
            GLenum modeRGB,
            GLenum modeAlpha);
        void apply();
    };

    class BlendEquationi: public Command
    {
      public:
        GLuint buffer;
        GLenum mode;
        BlendEquationi(
            GLuint buffer,
            GLenum mode);
        void apply();
    };

    class BlendEquationSeparatei: public Command
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

    class BlendFunc: public Command
    {
      public:
        GLenum src;
        GLenum dst;
        BlendFunc(
            GLenum src,
            GLenum dst);
        void apply();
    };

    class BlendFuncSeparate: public Command
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

    class BlendFunci: public Command
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

    class BlendFuncSeparatei: public Command
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

    class BlendColor: public Command
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
