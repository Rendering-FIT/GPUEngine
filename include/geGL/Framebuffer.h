#pragma once

#include<geGL/OpenGLObject.h>
#include<stdarg.h>
#include<iostream>

namespace ge{
  namespace gl{
    /**
     * @brief 
     */
    class GEGL_EXPORT Framebuffer: public OpenGLObject{
      private:
        inline GLint getParam(GLenum pname);
        inline void  setParam(GLenum pname,GLint);
        inline GLint getAttachmentParam(GLenum attachment,GLenum pname);
      public:
        Framebuffer (bool defaultFramebuffer=false);
        Framebuffer (
            opengl::FunctionTablePointer const&table,
            bool defaultFramebuffer = false);
        ~Framebuffer();
        void   bind  (GLenum target = GL_DRAW_FRAMEBUFFER)const;
        void   unbind(GLenum target = GL_DRAW_FRAMEBUFFER)const;
        void attachTexture(
            GLenum attachment     ,
            GLuint texture        ,
            GLint  level      =  0,
            GLint  layer      = -1)const;
        void attachRenderbuffer(
            GLenum attachment  ,
            GLuint renderbuffer)const;
        bool check()const;
        void drawBuffer(GLenum buffer)const;
        void drawBuffers(GLsizei n,const GLenum *buffers)const;
        void drawBuffers(GLsizei n,...)const;
        void clearBuffer (GLenum buffer,GLint drawBuffer,const GLint*   value)const;
        void clearBuffer (GLenum buffer,GLint drawBuffer,const GLfloat* value)const;
        void clearBuffer (GLenum buffer,GLint drawBuffer,const GLuint*  value)const;
        void clearBuffer (GLenum buffer,GLint drawBuffer,GLfloat depth,GLint stencil)const;
        void invalidateFramebuffer(
            GLsizei       numAttachments     ,
            const GLenum* attachments        ,
            GLint         x              = -1,
            GLint         y              = -1,
            GLsizei       width          = -1,
            GLsizei       height         = -1)const;
        GLboolean isFramebuffer()const;

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
        void clear(GLbitfield buffers);
        void clearColor  (GLfloat r,GLfloat g,GLfloat b,GLfloat a);
        void clearDepth  (GLdouble d);
        void clearDepth  (GLfloat  d);
        void clearStencil(GLint    s);
        std::string getInfo();
    };
  }//gl
}//ge

