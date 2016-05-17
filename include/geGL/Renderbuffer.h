#pragma once

#include<geGL/OpenGLObject.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT Renderbuffer: public OpenGLObject{
      public:
        Renderbuffer(
            GLenum  internalFormat,
            GLsizei samples,
            GLsizei width,
            GLsizei height);
        Renderbuffer(
            GLenum  internalFormat,
            GLsizei width,
            GLsizei height);
        Renderbuffer(
            opengl::FunctionTablePointer const&table,
            GLenum  internalFormat,
            GLsizei samples,
            GLsizei width,
            GLsizei height);
        Renderbuffer(
            opengl::FunctionTablePointer const&table,
            GLenum  internalFormat,
            GLsizei width,
            GLsizei height);
        ~Renderbuffer();
        void   bind             ()const;
        void   unbind           ()const;
        GLint  getWidth         ()const;
        GLint  getHeight        ()const;
        GLenum getInternalFormat()const;
        GLint  getSamples       ()const;
        GLint  getRedSize       ()const;
        GLint  getGreenSize     ()const;
        GLint  getBlueSize      ()const;
        GLint  getAlphaSize     ()const;
        GLint  getDepthSize     ()const;
        GLint  getStencilSize   ()const;
    };
  }//gl
}//ge


