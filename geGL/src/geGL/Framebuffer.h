#pragma once

#include<geGL/OpenGLObject.h>
#include<stdarg.h>
#include<iostream>
#include<map>
#include<vector>

class ge::gl::Framebuffer: public OpenGLObject{
  friend class Texture;
  friend class Renderbuffer;
  public:
  GEGL_EXPORT Framebuffer (bool defaultFramebuffer=false);
  GEGL_EXPORT Framebuffer (
      FunctionTablePointer const&table,
      bool defaultFramebuffer = false);
  GEGL_EXPORT ~Framebuffer();
  GEGL_EXPORT void   bind  (GLenum target = GL_DRAW_FRAMEBUFFER)const;
  GEGL_EXPORT void   unbind(GLenum target = GL_DRAW_FRAMEBUFFER)const;
  GEGL_EXPORT void attachTexture(
      GLenum                        attachment          ,
      std::shared_ptr<Texture>const&texture    = nullptr,
      GLint                         level      = 0      ,
      GLint                         layer      = -1     );
  GEGL_EXPORT void attachTexture(
      GLenum  attachment          ,
      Texture*texture    = nullptr,
      GLint   level      = 0      ,
      GLint   layer      = -1     );
  GEGL_EXPORT void attachRenderbuffer(
      GLenum                             attachment            ,
      std::shared_ptr<Renderbuffer>const&renderbuffer = nullptr);
  GEGL_EXPORT void attachRenderbuffer(
      GLenum       attachment            ,
      Renderbuffer*renderbuffer = nullptr);
  GEGL_EXPORT bool check()const;
  GEGL_EXPORT void drawBuffer(GLenum buffer)const;
  GEGL_EXPORT void drawBuffers(GLsizei n,const GLenum *buffers)const;
  GEGL_EXPORT void drawBuffers(GLsizei n,...)const;
  GEGL_EXPORT void drawBuffers(std::vector<GLenum>const buffers)const;
  GEGL_EXPORT void clearBuffer(GLenum buffer,GLint drawBuffer,const GLint*   value)const;
  GEGL_EXPORT void clearBuffer(GLenum buffer,GLint drawBuffer,const GLfloat* value)const;
  GEGL_EXPORT void clearBuffer(GLenum buffer,GLint drawBuffer,const GLuint*  value)const;
  GEGL_EXPORT void clearBuffer(GLenum buffer,GLint drawBuffer,GLfloat depth,GLint stencil)const;
  GEGL_EXPORT void invalidateFramebuffer(
      GLsizei       numAttachments     ,
      const GLenum* attachments        ,
      GLint         x              = -1,
      GLint         y              = -1,
      GLsizei       width          = -1,
      GLsizei       height         = -1)const;
  GEGL_EXPORT GLboolean isFramebuffer()const;

  GEGL_EXPORT void   setDefaultWidth               (GLint width   );
  GEGL_EXPORT void   setDefaultHeight              (GLint height  );
  GEGL_EXPORT void   setDefaultFixedSampleLocations(GLint location);
  GEGL_EXPORT void   setDefaultSamples             (GLint samples );
  GEGL_EXPORT void   setDefaultLayers              (GLint layers  );
  GEGL_EXPORT GLint  getDefaultWidth               ();
  GEGL_EXPORT GLint  getDefaultHeight              ();
  GEGL_EXPORT GLint  getDefaultLayers              ();
  GEGL_EXPORT GLint  getDefaultSamples             ();
  GEGL_EXPORT GLint  getDefaultFixedSampleLocations();
  GEGL_EXPORT GLint  getSamples                    ();
  GEGL_EXPORT GLint  getSampleBuffers              ();
  GEGL_EXPORT GLenum    getAttachmentObjectType        (GLenum attachment);
  GEGL_EXPORT GLint     getAttachmentRedSize           (GLenum attachment);
  GEGL_EXPORT GLint     getAttachmentGreenSize         (GLenum attachment);
  GEGL_EXPORT GLint     getAttachmentBlueSize          (GLenum attachment);
  GEGL_EXPORT GLint     getAttachmentAlphaSize         (GLenum attachment);
  GEGL_EXPORT GLint     getAttachmentDepthSize         ();
  GEGL_EXPORT GLint     getAttachmentStencilSize       ();
  GEGL_EXPORT GLenum    getAttachmentComponentType     (GLenum attachment);
  GEGL_EXPORT GLenum    getAttachmentColorEncoding     (GLenum attachment);
  GEGL_EXPORT GLuint    getAttachmentObjectName        (GLenum attachment);
  GEGL_EXPORT GLint     getAttachmentTextureLevel      (GLenum attachment);
  GEGL_EXPORT GLenum    getAttachmentTextureCubeMapFace(GLenum attachment);
  GEGL_EXPORT GLboolean isAttachmentLayered            (GLenum attachment);
  GEGL_EXPORT GLint     getAttachmentTextureLayer      (GLenum attachment);

  GEGL_EXPORT GLint  getDoubleBuffer        ();
  GEGL_EXPORT GLint  getImplementationColorReadFormat();
  GEGL_EXPORT GLint  getImplementationColorReadType  ();
  GEGL_EXPORT GLint  getStereo();
  GEGL_EXPORT void clear(GLbitfield buffers);
  GEGL_EXPORT void clearColor  (GLfloat r,GLfloat g,GLfloat b,GLfloat a);
  GEGL_EXPORT void clearDepth  (GLdouble d);
  GEGL_EXPORT void clearDepth  (GLfloat  d);
  GEGL_EXPORT void clearStencil(GLint    s);
  std::string getInfo();
  private:
  inline GLint getParam(GLenum pname);
  inline void  setParam(GLenum pname,GLint);
  inline GLint getAttachmentParam(GLenum attachment,GLenum pname);
  std::map<GLenum,Texture*>_textureAttachments;
  std::map<GLenum,Renderbuffer*>_renderbufferAttachments;
  void removeLinkToAttachedTexture(GLenum attachment);
  void removeLinktoAttachedRenderbuffer(GLenum attachment);
  friend class Texture;
  friend class Renderbuffer;
};

