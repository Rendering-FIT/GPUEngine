#ifndef _DEPTHCOMMANDS_H_
#define _DEPTHCOMMANDS_H_

#include <geGL/OpenGL.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT DepthFunc: public Command{
      protected:
        GLenum _func;
      public:
        DepthFunc(GLenum func=GL_LESS);
        void apply();
        void set(GLenum func=GL_LESS);
        GLenum get();
    };

    class GEGL_EXPORT DepthMask: public Command{
      protected:
        GLboolean _mask;
      public:
        DepthMask(GLboolean mask=GL_TRUE);
        void apply();
        void set(GLboolean mask=GL_TRUE);
        GLboolean get();
    };

    class GEGL_EXPORT ClearDepth: public Command{
      protected:
        GLdouble _value;
      public:
        ClearDepth(GLdouble value=1.f);
        void apply();
        void set(GLdouble value=1.f);
        GLdouble get();
    };

    class GEGL_EXPORT ClearDepthf: public Command{
      protected:
        GLfloat _value;
      public:
        ClearDepthf(GLfloat value=1.);
        void apply();
        void set(GLfloat value=1.);
        GLfloat get();
    };

    class GEGL_EXPORT DepthFuncR: public Command{
      protected:
        GLenum*_func;
      public:
        DepthFuncR(GLenum*func=NULL);
        void apply();
        void set(GLenum*func=NULL);
        GLenum*get();
    };

    class GEGL_EXPORT DepthMaskR: public Command{
      protected:
        GLboolean*_mask;
      public:
        DepthMaskR(GLboolean*mask=NULL);
        void apply();
        void set(GLboolean*mask=NULL);
        GLboolean*get();
    };

    class GEGL_EXPORT ClearDepthR: public Command{
      protected:
        GLdouble*_value;
      public:
        ClearDepthR(GLdouble*value=NULL);
        void apply();
        void set(GLdouble*value=NULL);
        GLdouble*get();
    };

    class GEGL_EXPORT ClearDepthfR: public Command{
      protected:
        GLfloat*_value;
      public:
        ClearDepthfR(GLfloat*value=NULL);
        void apply();
        void set(GLfloat*value=NULL);
        GLfloat*get();
    };

  }//ogl
}//ge



#endif//_DEPTHCOMMANDS_H_
