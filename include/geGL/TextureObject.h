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
    GLenum textureTarget2Binding(GLenum target );
    GLenum textureBinding2Target(GLenum binding);
    std::string translateTextureTarget     (GLenum target );
    std::string translateTextureBinding    (GLenum binding);
    std::string translateTextureCompareMode(GLint mode    );
    std::string translateTextureCompareFunc(GLint func    );
    std::string translateTextureFilter     (GLint filter  );
    std::string translateTextureWrap       (GLint wrap    );
    std::string translateTextureSwizzle    (GLint swizzle );

    class GEGL_EXPORT TextureObject: public OpenGLObject
    {
      private:
        inline GLint _getTexLevelParameter(GLint level,GLenum pname);
        inline GLint _getTexParameter(GLenum pname);
        GLenum  _target;
        GLenum  _format;
      public:
        /**
         * @brief Creates 1D texture
         *
         * @param target target of texture
         * @param internalFormat internal format of data of texture
         * @param levels number of mipmap levels
         * @param width x size of texture
         */
        TextureObject(
            GLenum  target,
            GLenum  internalFormat,
            GLsizei levels,
            GLsizei width);
        /**
         * @brief Creates 2D texture
         *
         * @param target target of texture
         * @param internalFormat internal format of data of texture
         * @param levels number of mipmap levels
         * @param width x size of texture
         * @param height y size of texture
         */
        TextureObject(
            GLenum  target,
            GLenum  internalFormat,
            GLsizei levels,
            GLsizei width,
            GLsizei height);
        /**
         * @brief Creates 3D texture
         *
         * @param target target of texture
         * @param internalFormat internal format of data of texture
         * @param levels number of mipmap levels
         * @param width x size of texture
         * @param height y size of texture
         * @param depth z size of texture
         */
        TextureObject(
            GLenum  target,
            GLenum  internalFormat,
            GLsizei levels,
            GLsizei width,
            GLsizei height,
            GLsizei depth);
        /**
         * @brief destroys texture
         */
        ~TextureObject();
        /**
         * @brief binds texture to texture unit
         *
         * @param unit texture unit
         */
        void bind     (GLuint unit);
        /**
         * @brief unbinds texture unit
         *
         * @param unit texture unit
         */
        void unbind   (GLuint unit);
        /**
         * @brief binds image of texture
         *
         * @param unit texture unit
         * @param level level of mipmap
         * @param format format of data
         * @param access read/write
         * @param layered use layered 
         * @param layer index of layer
         */
        void bindImage(
            GLuint    unit,
            GLint     level,
            GLenum    format  = TEXTUREOBJECT_DEFAULT_FORMAT,
            GLenum    access  = TEXTUREOBJECT_DEFAULT_ACCESS,
            GLboolean layered = TEXTUREOBJECT_DEFAULT_LAYERED,
            GLint     layer   = TEXTUREOBJECT_DEFAULT_LAYER);
        /**
         * @brief sets parameters of texture
         *
         * @param pname name of parameter
         * @param params value of parameter
         */
        void    texParameteri (GLenum pname,GLint    params);
        /**
         * @brief sets parameters of texture
         *
         * @param pname name of parameter
         * @param params values of parameter
         */
        void    texParameterfv(GLenum pname,GLfloat *params);
        /**
         * @brief gets target of texture
         *
         * @return target
         */
        GLenum  getTarget();
        /**
         * @brief gets internal format of texture
         *
         * @return format
         */
        GLenum  getFormat();
        /**
         * @brief gets width of texture at specific level
         *
         * @param level level of mipmap
         *
         * @return width of mipmap
         */
        GLsizei getWidth (GLint level);
        /**
         * @brief gets height of texture at specific level
         *
         * @param level level of mipmap
         *
         * @return height of mipmap
         */
        GLsizei getHeight(GLint level);
        /**
         * @brief gets depth of texture at specific level
         *
         * @param level level of mipmap
         *
         * @return depth of mipmap
         */
        GLsizei getDepth (GLint level);
        /**
         * @brief gets fixed sample location
         *
         * @param level level of mipmap
         *
         * @return fixed sample location
         */
        GLint   getFixedSampleLocation(GLint level);
        /**
         * @brief gets compressed flag
         *
         * @param level level of mipmap
         *
         * @return compressed flag
         */
        GLint   getCompressed(GLint level);
        /**
         * @brief gets compressed image size
         *
         * @param level level of mipmap
         *
         * @return compressed image size
         */
        GLint   getCompressedImageSize(GLint level);
        /**
         * @brief gets number of samples
         *
         * @param level level of mipmap
         *
         * @return number of samples
         */
        GLint   getSamples(GLint level);
        GLint   getImmutableFormat();
        GLint   getSwizzleR();
        GLint   getSwizzleG();
        GLint   getSwizzleB();
        GLint   getSwizzleA();
        GLint   getMaxLevel();
        GLint   getBaseLevel();

    };
  }//gl
}//ge


#endif//_TEXTUREOBJECT_H_
