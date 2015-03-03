#ifndef _RENDERBUFFEROBJECT_H_
#define _RENDERBUFFEROBJECT_H_

#include<geGL/OpenGL.h>
#include<geGL/OpenGLObject.h>

namespace ge{
  namespace gl{
    class RenderbufferObject: public OpenGLObject
    {
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
        ~RenderbufferObject();
        void   bind             ();
        void   unbind           ();
        GLint  getWidth         ();
        GLint  getHeight        ();
        GLenum getInternalFormat();
        GLint  getSamples       ();
        GLint  getRedSize       ();
        GLint  getGreenSize     ();
        GLint  getBlueSize      ();
        GLint  getAlphaSize     ();
        GLint  getDepthSize     ();
        GLint  getStencilSize   ();
    };
  }//gl
}//ge

#endif//_RENDERBUFFEROBJECT_H_

