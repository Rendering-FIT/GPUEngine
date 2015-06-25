#pragma once

#include <geGL/OpenGL.h>
#include <geGL/OpenGLObject.h>

#include <iostream>

namespace ge{
  namespace gl{
    GEGL_EXPORT std::string translateBufferTarget (GLenum target );
    GEGL_EXPORT std::string translateBufferBinding(GLenum binding);
    GEGL_EXPORT GLenum      bufferTarget2Binding  (GLenum target );
    GEGL_EXPORT GLenum      bufferBinding2Target  (GLenum binding);

    /**
     * Abstraction of the OpenGL Buffer Object.
     */
    class GEGL_EXPORT BufferObject:public OpenGLObject
    {
      private:
        GLint   _getBufferParameter(GLenum pname);
        GLvoid* _getBufferPointer  (GLenum pname);
      public:
        BufferObject(
            GLsizeiptr    size                  ,
            const GLvoid* data  = NULL          ,
            GLbitfield    flags = GL_STATIC_DRAW);
        ~BufferObject();
        GLvoid*map(
            GLbitfield access = GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);
        GLvoid*map(
            GLintptr   offset,
            GLsizeiptr size,
            GLbitfield access = GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);
        void unmap();
        void setData(
            const GLvoid*data      ,
            GLsizeiptr   size   = 0,
            GLintptr     offset = 0);
        void getData(
            GLvoid*     data      ,
            GLsizeiptr  size   = 0,
            GLintptr    offset = 0);
        void bind       (GLenum target);
        void bindRange  (GLenum target,GLuint index,GLintptr offset,GLsizeiptr size);
        void bindBase   (GLenum Target,GLuint index);
        void unbind     (GLenum target);
        void unbindRange(GLenum target,GLuint index);
        void unbindBase (GLenum target,GLuint index);
        void copy(BufferObject*buffer);
        void flushMapped(
            GLsizeiptr size   = 0,
            GLintptr   offset = 0);
        void invalidate(
            GLsizeiptr size   = 0,
            GLintptr   offset = 0);
        void clear(
            GLenum        internalFormat       ,
            GLenum        format               ,
            GLenum        type                 ,
            const GLvoid *Data           = NULL);
        void clear(
            GLenum        internalFormat          ,
            GLintptr      offset                  ,
            GLsizeiptr    size                    ,
            GLenum        format                  ,
            GLenum        type                    ,
            const GLvoid *Data           = NULL   );
        void operator &=(BufferObject*buffer);
        GLsizeiptr getSize       ();
        GLenum     getUsage      ();
        GLenum     getAccess     ();
        GLbitfield getAccessFlags();
        GLboolean  isMapped      ();
        GLintptr   getMapOffset  ();
        GLsizeiptr getMapSize    ();
        GLvoid*    getMapPointer ();
        GLboolean  isImmutable   ();
    };
  }
}

