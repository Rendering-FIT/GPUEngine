#pragma once

#include<geGL/OpenGLObject.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT RenderbufferObject: public OpenGLObject{
      public:
        RenderbufferObject(
            GLenum  internalFormat,
            GLsizei samples,
            GLsizei width,
            GLsizei height);
        RenderbufferObject(
            GLenum  internalFormat,
            GLsizei width,
            GLsizei height);
#if defined(REPLACE_GLEW)
        RenderbufferObject(
            opengl::FunctionTablePointer const&table,
            GLenum  internalFormat,
            GLsizei samples,
            GLsizei width,
            GLsizei height);
        RenderbufferObject(
            opengl::FunctionTablePointer const&table,
            GLenum  internalFormat,
            GLsizei width,
            GLsizei height);
#endif
        ~RenderbufferObject();
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


