#pragma once

#include<geGL/Export.h>
#include<geCore/Command.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class ActiveTexture: public ge::core::Command{
      protected:
        GLenum _unit;
      public:
        ActiveTexture(GLenum unit);
        virtual void operator()();
        GLenum getUnit();
        void   setUnit(GLenum unit);
    };

    class BindTexture: public ge::core::Command{
      protected:
        GLenum _target ;
        GLuint _texture;
      public:
        BindTexture(GLenum target,GLuint texture);
        virtual void operator()();
        GLenum getTarget();
        void   setTarget(GLenum target);
        GLuint getTexture();
        void   setTexture(GLuint texture);
    };

    class BindTextureUnit: public ge::core::Command{
      protected:
        GLuint _unit   ;
        GLuint _texture;
      public:
        BindTextureUnit(GLuint unit,GLuint texture);
        virtual void operator()();
        GLuint getUnit();
        void   setUnit(GLuint unit);
        GLuint getTexture();
        void   setTexture(GLuint texture);
    };

  }
}

