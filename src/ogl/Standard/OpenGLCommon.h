#ifndef _COPENGLCOMMON_HPP_
#define _COPENGLCOMMON_HPP_

#include"OpenGL.h"

namespace ge
{
  namespace ogl
  {
    class EnableDisable: public Command
    {
      public:
        GLenum target;
        bool   value;
        EnableDisable(GLenum target,bool value);
        void apply();
    };
    class EnableDisablei: public Command
    {
      public:
        GLenum target;
        GLuint index;
        bool   value;
        EnableDisablei(GLenum target,GLuint index,bool value);
        void apply();
    };
    class Enable: public Command
    {
      public:
        GLenum target;
        Enable(GLenum target);
        void apply();
    };
    class Disable: public Command
    {
      public:
        GLenum target;
        Disable(GLenum target);
        void apply();
    };
    class Enablei: public Command
    {
      public:
        GLuint buffer;
        GLenum target;
        Enablei(GLuint buffer,GLenum target);
        void apply();
    };
    class Disablei: public Command
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
