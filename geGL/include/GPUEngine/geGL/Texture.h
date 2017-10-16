#pragma once

#include<GPUEngine/geGL/OpenGLObject.h>
#include<iostream>
#include<set>

class GEGL_EXPORT ge::gl::Texture: public OpenGLObject{
  friend class Framebuffer;
  public:
  Texture();
  void create(
      GLenum  target            ,
      GLenum  internalFormat    ,
      GLsizei levels            ,
      GLsizei width             ,
      GLsizei height         = 0,
      GLsizei depth          = 0);
  Texture(
      GLenum  target        ,
      GLenum  internalFormat,
      GLsizei levels        ,
      GLsizei width         );
  Texture(
      GLenum  target        ,
      GLenum  internalFormat,
      GLsizei levels        ,
      GLsizei width         ,
      GLsizei height        );
  Texture(
      GLenum  target        ,
      GLenum  internalFormat,
      GLsizei levels        ,
      GLsizei width         ,
      GLsizei height        ,
      GLsizei depth         );
  Texture(
      FunctionTablePointer const&table,
      GLenum  target        ,
      GLenum  internalFormat,
      GLsizei levels        ,
      GLsizei width         );
  Texture(
      FunctionTablePointer const&table,
      GLenum  target        ,
      GLenum  internalFormat,
      GLsizei levels        ,
      GLsizei width         ,
      GLsizei height        );
  Texture(
      FunctionTablePointer const&table,
      GLenum  target        ,
      GLenum  internalFormat,
      GLsizei levels        ,
      GLsizei width         ,
      GLsizei height        ,
      GLsizei depth         );
  ~Texture();
  void bind     (GLuint unit)const;
  void unbind   (GLuint unit)const;
  void bindImage(
      GLuint    unit                   ,
      GLint     level   = 0            ,
      GLenum    format  = 0            ,
      GLenum    access  = GL_READ_WRITE,
      GLboolean layered = GL_FALSE     ,
      GLint     layer   = 0            )const;
  void setData1D(
      const GLvoid*data                      ,
      GLenum       format  = GL_RGBA         ,
      GLenum       type    = GL_UNSIGNED_BYTE,
      GLint        level   = 0               ,
      GLint        xoffset = 0               ,
      GLsizei      width   = 0               )const;
  void setData2D(
      const GLvoid*data                        ,
      GLenum       format    = GL_RGBA         ,
      GLenum       type      = GL_UNSIGNED_BYTE,
      GLint        level     = 0               ,
      GLenum       target    = 0               ,
      GLint        xoffset   = 0               ,
      GLint        yoffset   = 0               ,
      GLsizei      width     = 0               ,
      GLsizei      height    = 0               ,
      GLint        rowLength = 0               )const;
  void setData3D(
      const GLvoid*data                        ,
      GLenum       format    = GL_RGBA         ,
      GLenum       type      = GL_UNSIGNED_BYTE,
      GLint        level     = 0               ,
      GLenum       target    = 0               ,
      GLint        xoffset   = 0               ,
      GLint        yoffset   = 0               ,
      GLint        zoffset   = 0               ,
      GLsizei      width     = 0               ,
      GLsizei      height    = 0               ,
      GLsizei      depth     = 0               ,
      GLint        rowLength = 0               ,
      GLint        imgHeight = 0               )const;


  void    generateMipmap()const;
  void    clear(
      GLint        level           ,
      GLenum       format          ,
      GLenum       type            ,
      GLvoid const*data   = nullptr);
  void    texParameteri (GLenum pname,GLint    params)const;
  void    texParameterfv(GLenum pname,GLfloat *params)const;
  GLenum  getFormat()const;
  bool      hasHeight()const;
  bool      hasDepth ()const;
  GLuint    getWidth                 (GLint level)const;
  GLuint    getHeight                (GLint level)const;
  GLuint    getDepth                 (GLint level)const;
  GLuint    getSamples               (GLint level)const;
  GLboolean getFixedSampleLocation   (GLint level)const;
  GLenum    getInternalFormat        (GLint level)const;
  GLuint    getRedSize               (GLint level)const;
  GLuint    getGreenSize             (GLint level)const;
  GLuint    getBlueSize              (GLint level)const;
  GLuint    getAlphaSize             (GLint level)const;
  GLuint    getDepthSize             (GLint level)const;
  GLuint    getStencilSize           (GLint level)const;
  GLuint    getSharedSize            (GLint level)const;
  GLenum    getRedType               (GLint level)const;
  GLenum    getGreenType             (GLint level)const;
  GLenum    getBlueType              (GLint level)const;
  GLenum    getAlphaType             (GLint level)const;
  GLenum    getDepthType             (GLint level)const;
  GLboolean getCompressed            (GLint level)const;
  GLuint    getCompressedImageSize   (GLint level)const;
  GLuint    getBufferDataStoreBinding(GLint level)const;
  GLint     getBufferOffset          (GLint level)const;
  GLint     getBufferSize            (GLint level)const;
  GLenum    getSwizzleR                    (             )const;
  GLenum    getSwizzleG                    (             )const;
  GLenum    getSwizzleB                    (             )const;
  GLenum    getSwizzleA                    (             )const;
  void      getBorderColor                 (GLfloat*color)const;
  GLenum    getMinFilter                   (             )const;
  GLenum    getMagFilter                   (             )const;
  GLenum    getWrapS                       (             )const;
  GLenum    getWrapT                       (             )const;
  GLenum    getWrapR                       (             )const;
  GLenum    getTarget                      (             )const;
  GLfloat   getMinLod                      (             )const;
  GLfloat   getMaxLod                      (             )const;
  GLuint    getBaseLevel                   (             )const;
  GLuint    getMaxLevel                    (             )const;
  GLfloat   getLodBias                     (             )const;
  GLenum    getDepthStencilTextureMode     (             )const;
  GLenum    getCompareMode                 (             )const;
  GLenum    getCompareFunc                 (             )const;
  GLenum    getImageFormatCompatibilityType(             )const;
  GLboolean getImmutableFormat             (             )const;
  GLuint    getImmutableLevels             (             )const;
  GLuint    getViewMinLevel                (             )const;
  GLuint    getViewNumLevels               (             )const;
  GLuint    getViewMinLayer                (             )const;
  GLuint    getViewNumLayers               (             )const;
  std::string getInfo()const;
  unsigned long long getSize()const;
  unsigned long long getLevelSize(GLint level)const;
  private:
  inline GLint _getTexLevelParameter(GLint level,GLenum pname)const;
  inline GLint _getTexParameter (GLenum pname)const;
  inline void  _getTexParameterf(GLfloat*data,GLenum pname)const;
  inline GLuint _bindSafe()const;
  GLenum  _target;
  GLenum  _format;
  std::set<Framebuffer*>_framebuffers;

};

