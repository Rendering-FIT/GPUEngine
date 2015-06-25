#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT EnableDisable: public ge::core::Command
    {
      public:
        GLenum target;
        bool   value;
        EnableDisable(GLenum target,bool value);
        void apply();
    };
    class GEGL_EXPORT EnableDisablei: public ge::core::Command
    {
      public:
        GLenum target;
        GLuint index;
        bool   value;
        EnableDisablei(GLenum target,GLuint index,bool value);
        void apply();
    };
    class GEGL_EXPORT Enable: public ge::core::Command
    {
      public:
        GLenum target;
        Enable(GLenum target);
        void apply();
    };
    class GEGL_EXPORT Disable: public ge::core::Command
    {
      public:
        GLenum target;
        Disable(GLenum target);
        void apply();
    };
    class GEGL_EXPORT Enablei: public ge::core::Command
    {
      public:
        GLuint buffer;
        GLenum target;
        Enablei(GLuint buffer,GLenum target);
        void apply();
    };
    class GEGL_EXPORT Disablei: public ge::core::Command
    {
      public:
        GLuint buffer;
        GLenum target;
        Disablei(GLuint buffer,GLenum target);
        void apply();
    };
  }//ogl
}//ge

