#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT DepthFunc: public ge::core::Command{
      protected:
        GLenum _func;
      public:
        DepthFunc(GLenum func=GL_LESS);
        void operator()();
        void set(GLenum func=GL_LESS);
        GLenum get();
    };

    class GEGL_EXPORT DepthMask: public ge::core::Command{
      protected:
        GLboolean _mask;
      public:
        DepthMask(GLboolean mask=GL_TRUE);
        void operator()();
        void set(GLboolean mask=GL_TRUE);
        GLboolean get();
    };

    class GEGL_EXPORT ClearDepth: public ge::core::Command{
      protected:
        GLdouble _value;
      public:
        ClearDepth(GLdouble value=1.f);
        void operator()();
        void set(GLdouble value=1.f);
        GLdouble get();
    };

    class GEGL_EXPORT ClearDepthf: public ge::core::Command{
      protected:
        GLfloat _value;
      public:
        ClearDepthf(GLfloat value=1.);
        void operator()();
        void set(GLfloat value=1.);
        GLfloat get();
    };

    class GEGL_EXPORT DepthFuncR: public ge::core::Command{
      protected:
        GLenum*_func;
      public:
        DepthFuncR(GLenum*func=NULL);
        void operator()();
        void set(GLenum*func=NULL);
        GLenum*get();
    };

    class GEGL_EXPORT DepthMaskR: public ge::core::Command{
      protected:
        GLboolean*_mask;
      public:
        DepthMaskR(GLboolean*mask=NULL);
        void operator()();
        void set(GLboolean*mask=NULL);
        GLboolean*get();
    };

    class GEGL_EXPORT ClearDepthR: public ge::core::Command{
      protected:
        GLdouble*_value;
      public:
        ClearDepthR(GLdouble*value=NULL);
        void operator()();
        void set(GLdouble*value=NULL);
        GLdouble*get();
    };

    class GEGL_EXPORT ClearDepthfR: public ge::core::Command{
      protected:
        GLfloat*_value;
      public:
        ClearDepthfR(GLfloat*value=NULL);
        void operator()();
        void set(GLfloat*value=NULL);
        GLfloat*get();
    };

  }//ogl
}//ge

