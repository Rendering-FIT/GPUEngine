#pragma once

#include<geGL/OpenGLObject.h>
#include<iostream>

namespace ge{
  namespace gl{
    class GEGL_EXPORT BufferObject:public OpenGLObject{
      public:
        enum ReallocFlags{
          NEW_BUFFER = 0u    ,
          KEEP_ID    = 1u<<0u,
          KEEP_DATA  = 1u<<1u,
        };
      private:
        GLint   _getBufferParameter(GLenum pname);
        GLvoid* _getBufferPointer  (GLenum pname);
        void    _bufferData(GLsizeiptr size,const GLvoid*data,GLbitfield flags);
      public:
        BufferObject();
        BufferObject(
            GLsizeiptr    size                  ,
            const GLvoid* data  = NULL          ,
            GLbitfield    flags = GL_STATIC_DRAW);
        virtual ~BufferObject();
        void alloc(
            GLsizeiptr    size                  ,
            const GLvoid* data  = NULL          ,
            GLbitfield    flags = GL_STATIC_DRAW);
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
        void realloc(GLsizeiptr newSize,ReallocFlags flags = NEW_BUFFER);
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
        GLsizeiptr getSize       ();
        GLbitfield getUsage      ();
        GLenum     getAccess     ();
        GLbitfield getAccessFlags();
        GLboolean  isMapped      ();
        GLintptr   getMapOffset  ();
        GLsizeiptr getMapSize    ();
        GLvoid*    getMapPointer ();
        GLboolean  isImmutable   ();
        static std::string target2Str     (GLenum     target );
        static std::string binding2Str    (GLenum     binding);
        static GLenum      target2Binding (GLenum     target );
        static GLenum      binding2Target (GLenum     binding);
        static bool        areFlagsMutable(GLbitfield flags  );
    };
  }
}

