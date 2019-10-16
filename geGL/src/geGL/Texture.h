#pragma once

#include<geGL/OpenGLObject.h>
#include<iostream>
#include<set>
#include<vector>

class ge::gl::Texture: public OpenGLObject{
  friend class Framebuffer;
  public:
  GEGL_EXPORT Texture();
  GEGL_EXPORT void create(
      GLenum  target            ,
      GLenum  internalFormat    ,
      GLsizei levels            ,
      GLsizei width             ,
      GLsizei height         = 0,
      GLsizei depth          = 0);
  GEGL_EXPORT Texture(
      GLenum  target        ,
      GLenum  internalFormat,
      GLsizei levels        ,
      GLsizei width         );
  GEGL_EXPORT Texture(
      GLenum  target        ,
      GLenum  internalFormat,
      GLsizei levels        ,
      GLsizei width         ,
      GLsizei height        );
  GEGL_EXPORT Texture(
      GLenum  target        ,
      GLenum  internalFormat,
      GLsizei levels        ,
      GLsizei width         ,
      GLsizei height        ,
      GLsizei depth         );
  GEGL_EXPORT Texture(
      FunctionTablePointer const&table,
      GLenum  target        ,
      GLenum  internalFormat,
      GLsizei levels        ,
      GLsizei width         );
  GEGL_EXPORT Texture(
      FunctionTablePointer const&table,
      GLenum  target        ,
      GLenum  internalFormat,
      GLsizei levels        ,
      GLsizei width         ,
      GLsizei height        );
  GEGL_EXPORT Texture(
      FunctionTablePointer const&table,
      GLenum  target        ,
      GLenum  internalFormat,
      GLsizei levels        ,
      GLsizei width         ,
      GLsizei height        ,
      GLsizei depth         );
  GEGL_EXPORT ~Texture();
  GEGL_EXPORT void bind     (GLuint unit)const;
  GEGL_EXPORT void unbind   (GLuint unit)const;
  GEGL_EXPORT void bindImage(
      GLuint    unit                   ,
      GLint     level   = 0            ,
      GLenum    format  = 0            ,
      GLenum    access  = GL_READ_WRITE,
      GLboolean layered = GL_FALSE     ,
      GLint     layer   = 0            )const;
  GEGL_EXPORT void setData1D(
      const GLvoid*data                      ,
      GLenum       format  = GL_RGBA         ,
      GLenum       type    = GL_UNSIGNED_BYTE,
      GLint        level   = 0               ,
      GLint        xoffset = 0               ,
      GLsizei      width   = 0               )const;
  GEGL_EXPORT void setData2D(
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
  GEGL_EXPORT void setData3D(
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
  GEGL_EXPORT void getCompressedData(void*data,GLsizei bufSize,GLint level);
  GEGL_EXPORT void getCompressedData(std::vector<uint8_t>&data,GLint level);


  GEGL_EXPORT void    generateMipmap()const;
  GEGL_EXPORT void    clear(
      GLint        level           ,
      GLenum       format          ,
      GLenum       type            ,
      GLvoid const*data   = nullptr);
  GEGL_EXPORT void    texParameteri (GLenum pname,GLint    params)const;
  GEGL_EXPORT void    texParameterfv(GLenum pname,GLfloat *params)const;
  GEGL_EXPORT GLenum  getFormat()const;
  GEGL_EXPORT bool      hasHeight()const;
  GEGL_EXPORT bool      hasDepth ()const;
  GEGL_EXPORT GLuint    getWidth                 (GLint level)const;
  GEGL_EXPORT GLuint    getHeight                (GLint level)const;
  GEGL_EXPORT GLuint    getDepth                 (GLint level)const;
  GEGL_EXPORT GLuint    getSamples               (GLint level)const;
  GEGL_EXPORT GLboolean getFixedSampleLocation   (GLint level)const;
  GEGL_EXPORT GLenum    getInternalFormat        (GLint level)const;
  GEGL_EXPORT GLuint    getRedSize               (GLint level)const;
  GEGL_EXPORT GLuint    getGreenSize             (GLint level)const;
  GEGL_EXPORT GLuint    getBlueSize              (GLint level)const;
  GEGL_EXPORT GLuint    getAlphaSize             (GLint level)const;
  GEGL_EXPORT GLuint    getDepthSize             (GLint level)const;
  GEGL_EXPORT GLuint    getStencilSize           (GLint level)const;
  GEGL_EXPORT GLuint    getSharedSize            (GLint level)const;
  GEGL_EXPORT GLenum    getRedType               (GLint level)const;
  GEGL_EXPORT GLenum    getGreenType             (GLint level)const;
  GEGL_EXPORT GLenum    getBlueType              (GLint level)const;
  GEGL_EXPORT GLenum    getAlphaType             (GLint level)const;
  GEGL_EXPORT GLenum    getDepthType             (GLint level)const;
  GEGL_EXPORT GLboolean getCompressed            (GLint level)const;
  GEGL_EXPORT GLuint    getCompressedImageSize   (GLint level)const;
  GEGL_EXPORT GLuint    getBufferDataStoreBinding(GLint level)const;
  GEGL_EXPORT GLint     getBufferOffset          (GLint level)const;
  GEGL_EXPORT GLint     getBufferSize            (GLint level)const;
  GEGL_EXPORT GLenum    getSwizzleR                    (             )const;
  GEGL_EXPORT GLenum    getSwizzleG                    (             )const;
  GEGL_EXPORT GLenum    getSwizzleB                    (             )const;
  GEGL_EXPORT GLenum    getSwizzleA                    (             )const;
  GEGL_EXPORT void      getBorderColor                 (GLfloat*color)const;
  GEGL_EXPORT GLenum    getMinFilter                   (             )const;
  GEGL_EXPORT GLenum    getMagFilter                   (             )const;
  GEGL_EXPORT GLenum    getWrapS                       (             )const;
  GEGL_EXPORT GLenum    getWrapT                       (             )const;
  GEGL_EXPORT GLenum    getWrapR                       (             )const;
  GEGL_EXPORT GLenum    getTarget                      (             )const;
  GEGL_EXPORT GLfloat   getMinLod                      (             )const;
  GEGL_EXPORT GLfloat   getMaxLod                      (             )const;
  GEGL_EXPORT GLuint    getBaseLevel                   (             )const;
  GEGL_EXPORT GLuint    getMaxLevel                    (             )const;
  GEGL_EXPORT GLfloat   getLodBias                     (             )const;
  GEGL_EXPORT GLenum    getDepthStencilTextureMode     (             )const;
  GEGL_EXPORT GLenum    getCompareMode                 (             )const;
  GEGL_EXPORT GLenum    getCompareFunc                 (             )const;
  GEGL_EXPORT GLenum    getImageFormatCompatibilityType(             )const;
  GEGL_EXPORT GLboolean getImmutableFormat             (             )const;
  GEGL_EXPORT GLuint    getImmutableLevels             (             )const;
  GEGL_EXPORT GLuint    getViewMinLevel                (             )const;
  GEGL_EXPORT GLuint    getViewNumLevels               (             )const;
  GEGL_EXPORT GLuint    getViewMinLayer                (             )const;
  GEGL_EXPORT GLuint    getViewNumLayers               (             )const;
  GEGL_EXPORT std::string getInfo()const;
  GEGL_EXPORT unsigned long long getSize()const;
  GEGL_EXPORT unsigned long long getLevelSize(GLint level)const;
  private:
  inline GLint _getTexLevelParameter(GLint level,GLenum pname)const;
  inline GLint _getTexParameter (GLenum pname)const;
  inline void  _getTexParameterf(GLfloat*data,GLenum pname)const;
  inline GLuint _bindSafe()const;
  GLenum  _target;
  GLenum  _format;
  std::set<Framebuffer*>_framebuffers;
  friend class Framebuffer;
};

