#ifndef _FRAMEBUFFEROBJECT_H_
#define _FRAMEBUFFEROBJECT_H_

#include<geGL/OpenGL.h>
#include<geGL/OpenGLObject.h>
#include<stdarg.h>
#include<iostream>

#define FRAMEBUFFEROBJECT_DEFAULT_TARGET        GL_FRAMEBUFFER
#define FRAMEBUFFEROBJECT_DEFAULT_TEXTURE_LAYER 0
#define FRAMEBUFFEROBJECT_DEFAULT_TEXTURE_LEVEL 0

namespace ge{
  namespace gl{
    std::string translateFramebufferComponentType(GLenum type);
    std::string translateFramebufferObjectType   (GLenum type);
    std::string translateFramebufferAttachment   (GLenum attachment);
    std::string translateFramebufferColorEncoding(GLenum type);
    std::string translateCubeMapFace(GLenum face);
    /**
     * @brief 
     */
    class GEGL_EXPORT FramebufferObject: public OpenGLObject
    {
      private:
        inline GLint getParam(GLenum pname);
        inline void  setParam(GLenum pname,GLint);
        inline GLint getAttachmentParam(GLenum attachment,GLenum pname);
        inline void  attachRenderbuffer(GLenum attachment,GLuint renderbuffer);
        inline void  attachTexture     (GLenum attachment,GLuint texture,GLint level);
      public:
        FramebufferObject (GLuint framebuffer);
        FramebufferObject ();
        ~FramebufferObject();
        void   setDefaultWidth               (GLint width   );
        void   setDefaultHeight              (GLint height  );
        void   setDefaultFixedSampleLocations(GLint location);
        void   setDefaultSamples             (GLint samples );
        void   setDefaultLayers              (GLint layers  );
        GLint  getDefaultWidth               ();
        GLint  getDefaultHeight              ();
        GLint  getDefaultLayers              ();
        GLint  getDefaultSamples             ();
        GLint  getDefaultFixedSampleLocations();
        GLint  getSamples                    ();
        GLint  getSampleBuffers              ();
        GLenum    getAttachmentObjectType        (GLenum attachment);
        GLint     getAttachmentRedSize           (GLenum attachment);
        GLint     getAttachmentGreenSize         (GLenum attachment);
        GLint     getAttachmentBlueSize          (GLenum attachment);
        GLint     getAttachmentAlphaSize         (GLenum attachment);
        GLint     getAttachmentDepthSize         ();
        GLint     getAttachmentStencilSize       ();
        GLenum    getAttachmentComponentType     (GLenum attachment);
        GLenum    getAttachmentColorEncoding     (GLenum attachment);
        GLuint    getAttachmentObjectName        (GLenum attachment);
        GLint     getAttachmentTextureLevel      (GLenum attachment);
        GLenum    getAttachmentTextureCubeMapFace(GLenum attachment);
        GLboolean isAttachmentLayered            (GLenum attachment);
        GLint     getAttachmentTextureLayer      (GLenum attachment);

        GLint  getDoubleBuffer        ();
        GLint  getImplementationColorReadFormat();
        GLint  getImplementationColorReadType  ();
        GLint  getStereo();
        void   bind  (GLenum target = FRAMEBUFFEROBJECT_DEFAULT_TARGET);
        void   unbind(GLenum target = FRAMEBUFFEROBJECT_DEFAULT_TARGET);
        void attachDepthTexture(
            GLuint texture,
            GLint  level = FRAMEBUFFEROBJECT_DEFAULT_TEXTURE_LEVEL);
        void attachDepthTexture(
            GLuint texture,
            GLenum target,
            GLint  level = FRAMEBUFFEROBJECT_DEFAULT_TEXTURE_LEVEL);
        void attachStencilTexture(
            GLuint texture,
            GLint  level = FRAMEBUFFEROBJECT_DEFAULT_TEXTURE_LEVEL);
        void attachStencilTexture(
            GLuint texture,
            GLenum target,
            GLint  level = FRAMEBUFFEROBJECT_DEFAULT_TEXTURE_LEVEL);
        void attachColorTexture(
            GLenum   attachment,
            GLuint   texture,
            GLint    level = FRAMEBUFFEROBJECT_DEFAULT_TEXTURE_LEVEL);
        void attachColorTexture(
            GLenum   attachment,
            GLuint   texture,
            GLenum   target,
            GLint    level = FRAMEBUFFEROBJECT_DEFAULT_TEXTURE_LEVEL);
        void attachColorRenderbuffer(
            GLenum   attachment,
            GLuint   renderbuffer);
        void attachStencilRenderbuffer(
            GLuint renderbuffer);
        void attachDepthRenderbuffer(
            GLuint renderbuffer);

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
        std::string getInfo();
    };
  }//gl
}//ge

#endif//_FRAMEBUFFEROBJECT_H_
