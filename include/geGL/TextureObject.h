#ifndef _TEXTUREOBJECT_H_
#define _TEXTUREOBJECT_H_

#include<geGL/OpenGL.h>
#include<geGL/OpenGLObject.h>
#include<iostream>

//#define USE_DSA

#define TEXTUREOBJECT_DEFAULT_LAYERED GL_FALSE
#define TEXTUREOBJECT_DEFAULT_LAYER   0
#define TEXTUREOBJECT_DEFAULT_ACCESS  GL_READ_WRITE
#define TEXTUREOBJECT_DEFAULT_FORMAT  0

namespace ge{
  namespace gl{
    GEGL_EXPORT GLenum textureTarget2Binding(GLenum target );
    GEGL_EXPORT GLenum textureBinding2Target(GLenum binding);
    GEGL_EXPORT std::string translateTextureTarget     (GLenum target );
    GEGL_EXPORT std::string translateTextureBinding    (GLenum binding);
    GEGL_EXPORT std::string translateTextureCompareMode(GLint mode    );
    GEGL_EXPORT std::string translateTextureCompareFunc(GLint func    );
    GEGL_EXPORT std::string translateTextureFilter     (GLint filter  );
    GEGL_EXPORT std::string translateTextureWrap       (GLint wrap    );
    GEGL_EXPORT std::string translateTextureSwizzle    (GLint swizzle );
    GEGL_EXPORT std::string translateTextureChannelType(GLenum type   );
    GEGL_EXPORT unsigned internalFormatSize(GLenum internalFormat);

    class GEGL_EXPORT TextureObject: public OpenGLObject
    {
      private:
        inline GLint _getTexLevelParameter(GLint level,GLenum pname);
        inline GLint _getTexParameter (GLenum pname);
        inline void  _getTexParameterf(GLfloat*data,GLenum pname);
        inline GLuint _bindSafe();
#ifndef USE_DSA
        GLenum  _target;
#endif//USE_DSA
        GLenum  _format;
      public:
        TextureObject(
            GLenum  target,
            GLenum  internalFormat,
            GLsizei levels,
            GLsizei width);
        TextureObject(
            GLenum  target,
            GLenum  internalFormat,
            GLsizei levels,
            GLsizei width,
            GLsizei height);
        TextureObject(
            GLenum  target,
            GLenum  internalFormat,
            GLsizei levels,
            GLsizei width,
            GLsizei height,
            GLsizei depth);
        ~TextureObject();
        void bind     (GLuint unit);
        void unbind   (GLuint unit);
        void bindImage(
            GLuint    unit,
            GLint     level,
            GLenum    format  = TEXTUREOBJECT_DEFAULT_FORMAT,
            GLenum    access  = TEXTUREOBJECT_DEFAULT_ACCESS,
            GLboolean layered = TEXTUREOBJECT_DEFAULT_LAYERED,
            GLint     layer   = TEXTUREOBJECT_DEFAULT_LAYER);
        void    texParameteri (GLenum pname,GLint    params);
        void    texParameterfv(GLenum pname,GLfloat *params);
        GLenum  getFormat();
        GLuint    getWidth                 (GLint level);
        GLuint    getHeight                (GLint level);
        GLuint    getDepth                 (GLint level);
        GLuint    getSamples               (GLint level);
        GLboolean getFixedSampleLocation   (GLint level);
        GLenum    getInternalFormat        (GLint level);
        GLuint    getRedSize               (GLint level);
        GLuint    getGreenSize             (GLint level);
        GLuint    getBlueSize              (GLint level);
        GLuint    getAlphaSize             (GLint level);
        GLuint    getDepthSize             (GLint level);
        GLuint    getStencilSize           (GLint level);
        GLuint    getSharedSize            (GLint level);
        GLenum    getRedType               (GLint level);
        GLenum    getGreenType             (GLint level);
        GLenum    getBlueType              (GLint level);
        GLenum    getAlphaType             (GLint level);
        GLenum    getDepthType             (GLint level);
        GLboolean getCompressed            (GLint level);
        GLuint    getCompressedImageSize   (GLint level);
        GLuint    getBufferDataStoreBinding(GLint level);
        GLint     getBufferOffset          (GLint level);
        GLint     getBufferSize            (GLint level);
        GLenum    getSwizzleR                    (             );
        GLenum    getSwizzleG                    (             );
        GLenum    getSwizzleB                    (             );
        GLenum    getSwizzleA                    (             );
        void      getBorderColor                 (GLfloat*color);
        GLenum    getMinFilter                   (             );
        GLenum    getMagFilter                   (             );
        GLenum    getWrapS                       (             );
        GLenum    getWrapT                       (             );
        GLenum    getWrapR                       (             );
        GLenum    getTarget                      (             );
        GLfloat   getMinLod                      (             );
        GLfloat   getMaxLod                      (             );
        GLuint    getBaseLevel                   (             );
        GLuint    getMaxLevel                    (             );
        GLfloat   getLodBias                     (             );
        GLenum    getDepthStencilTextureMode     (             );
        GLenum    getCompareMode                 (             );
        GLenum    getCompareFunc                 (             );
        GLenum    getImageFormatCompatibilityType(             );
        GLboolean getImmutableFormat             (             );
        GLuint    getImmutableLevels             (             );
        GLuint    getViewMinLevel                (             );
        GLuint    getViewNumLevels               (             );
        GLuint    getViewMinLayer                (             );
        GLuint    getViewNumLayers               (             );
        std::string getInfo();
        unsigned long long getSize();
    };
  }//gl
}//ge


#endif//_TEXTUREOBJECT_H_
