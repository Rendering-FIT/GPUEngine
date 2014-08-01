#ifndef _COPENGLCOMMON_HPP_
#define _COPENGLCOMMON_HPP_

#include"OpenGL.h"

namespace ge
{
  namespace gl
  {
    class GE_EXPORT EnableDisable: public Command
    {
      public:
        GLenum target;
        bool   value;
        EnableDisable(GLenum target,bool value);
        void apply();
    };
    class GE_EXPORT EnableDisablei: public Command
    {
      public:
        GLenum target;
        GLuint index;
        bool   value;
        EnableDisablei(GLenum target,GLuint index,bool value);
        void apply();
    };
    class GE_EXPORT Enable: public Command
    {
      public:
        GLenum target;
        Enable(GLenum target);
        void apply();
    };
    class GE_EXPORT Disable: public Command
    {
      public:
        GLenum target;
        Disable(GLenum target);
        void apply();
    };
    class GE_EXPORT Enablei: public Command
    {
      public:
        GLuint buffer;
        GLenum target;
        Enablei(GLuint buffer,GLenum target);
        void apply();
    };
    class GE_EXPORT Disablei: public Command
    {
      public:
        GLuint buffer;
        GLenum target;
        Disablei(GLuint buffer,GLenum target);
        void apply();
    };
  }//ogl
}//ge

#endif//_COPENGLCOMMON_HPP_
