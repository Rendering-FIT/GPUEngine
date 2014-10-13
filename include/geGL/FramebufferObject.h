#ifndef _FRAMEBUFFEROBJECT_H_
#define _FRAMEBUFFEROBJECT_H_

#include<geGL/Standard/OpenGL.h>
#include<stdarg.h>

#define FRAMEBUFFEROBJECT_DEFAULT_TARGET        GL_FRAMEBUFFER
#define FRAMEBUFFEROBJECT_DEFAULT_TEXTURE_LAYER 0
#define FRAMEBUFFEROBJECT_DEFAULT_TEXTURE_LEVEL 0

namespace ge{
  namespace gl{
    /**
     * @brief 
     */
    class FramebufferObject
    {
      protected:
        GLuint _id;
      public:
        FramebufferObject (GLuint framebuffer);
        FramebufferObject ();
        ~FramebufferObject();
        void   setWidth               (GLint width   );
        void   setHeight              (GLint height  );
        void   setFixedSampleLocations(GLint location);
        void   setSamples             (GLint samples );
        void   setLayers              (GLint layers  );
        GLuint getId                  ();
        GLint  getWidth               ();
        GLint  getHeight              ();
        GLint  getFixedSampleLocations();
        GLint  getSamples             ();
        GLint  getLayers              ();
        GLint  getDoubleBuffer        ();
        GLint  getSampleBuffers       ();
        GLint  getImplementationColorReadFormat();
        GLint  getImplementationColorReadType  ();
        GLint  getStereo();
        void   bind  (GLenum target = FRAMEBUFFEROBJECT_DEFAULT_TARGET);
        void   unbind(GLenum target = FRAMEBUFFEROBJECT_DEFAULT_TARGET);
        void attachDepthRenderbuffer(
            GLuint renderbuffer);
        void attachDepthTexture(
            GLuint texture,
            GLint  level = FRAMEBUFFEROBJECT_DEFAULT_TEXTURE_LEVEL);
        void attachStencilRenderbuffer(
            GLuint renderbuffer);
        void attachStencilTexture(
            GLuint texture,
            GLint  level = FRAMEBUFFEROBJECT_DEFAULT_TEXTURE_LEVEL);
        void attachColorRenderbuffer(
            GLenum   attachment,
            GLuint   renderbuffer);
        void attachColorTexture(
            GLenum   attachment,
            GLuint   texture,
            GLint    level = FRAMEBUFFEROBJECT_DEFAULT_TEXTURE_LEVEL);
        bool check();
        void drawBuffer(GLenum buffer);
        void drawBuffers(GLsizei n,GLenum *buffers);
        void drawBuffers(GLsizei n,...);
        void clear(GLbitfield buffers);
        void clearColor  (GLfloat r,GLfloat g,GLfloat b,GLfloat a);
        void clearDepth  (GLdouble d);
        void clearDepth  (GLfloat  d);
        void clearStencil(GLint    s);
        void clearBuffer (GLenum buffer,GLint drawBuffer,GLint   *value);
        void clearBuffer (GLenum buffer,GLint drawBuffer,GLfloat *value);
        void clearBuffer (GLenum buffer,GLint drawBuffer,GLuint  *value);
        void clearBuffer (GLenum buffer,GLint drawbuffer,GLfloat depth,GLint stencil);
        void invalidateFramebuffer(
            GLenum   target,
            GLsizei  numAttachments,
            GLenum  *attachments,
            GLint    x,
            GLint    y,
            GLsizei  width,
            GLsizei  height);
        void invalidateFramebuffer(
            GLenum   target,
            GLsizei  numAttachments,
            GLenum  *attachments);
    };
  }//gl
}//ge

#endif//_FRAMEBUFFEROBJECT_H_
