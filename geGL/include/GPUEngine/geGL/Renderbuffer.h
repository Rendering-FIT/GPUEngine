#pragma once

#include<GPUEngine/geGL/OpenGLObject.h>
#include<set>

class GEGL_EXPORT ge::gl::Renderbuffer: public OpenGLObject{
  public:
    Renderbuffer();
    Renderbuffer(
        GLenum  const&internalFormat    ,
        GLsizei const&width             ,
        GLsizei const&height            ,
        GLsizei const&samples        = 0);
    Renderbuffer(
        FunctionTablePointer const&table             ,
        GLenum               const&internalFormat    ,
        GLsizei              const&width             ,
        GLsizei              const&height            ,
        GLsizei              const&samples        = 0);
    ~Renderbuffer();
    void setStorage(
        GLenum  const&internalFormat    ,
        GLsizei const&width             ,
        GLsizei const&height            ,
        GLsizei const&samples        = 0)const;
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
    enum InternalFormat{
      RED                = GL_RED               ,
      RG                 = GL_RG                ,
      RGB                = GL_RGB               ,
      RGBA               = GL_RGBA              ,
      RGBA32F            = GL_RGBA32F           ,
      RGBA32UI           = GL_RGBA32UI          ,
      DEPTH_COMPONENT16  = GL_DEPTH_COMPONENT16 ,
      DEPTH_COMPONENT24  = GL_DEPTH_COMPONENT24 ,
      DEPTH_COMPONENT32  = GL_DEPTH_COMPONENT32 ,
      DEPTH_COMPONENT32F = GL_DEPTH_COMPONENT32F,
      DEPTH24_STENCIL8   = GL_DEPTH24_STENCIL8  ,
      DEPTH32F_STENCIL8  = GL_DEPTH32F_STENCIL8 ,
      STENCIL_INDEX1     = GL_STENCIL_INDEX1    ,
      STENCIL_INDEX4     = GL_STENCIL_INDEX4    ,
      STENCIL_INDEX8     = GL_STENCIL_INDEX8    ,
      STENCIL_INDEX16    = GL_STENCIL_INDEX16   ,
    };
  protected:
    GLint _getParamateri(GLenum pname)const;
    std::set<Framebuffer*>_framebuffers;
    friend class Framebuffer;
};

