#pragma once

#include<geGL/OpenGLObject.h>
#include<iostream>
#include<set>

namespace ge{
  namespace gl{
    class VertexArray;
    class GEGL_EXPORT Buffer:
      public OpenGLObject,
      public std::enable_shared_from_this<Buffer>{
        friend class VertexArray;
        public:
        enum ReallocFlags{
          NEW_BUFFER = 0u    ,
          KEEP_ID    = 1u<<0u,
          KEEP_DATA  = 1u<<1u,
        };
        Buffer();
        Buffer(
            GLsizeiptr    size                  ,
            const GLvoid* data  = nullptr       ,
            GLbitfield    flags = GL_STATIC_DRAW);
        Buffer(FunctionTablePointer const&table);
        Buffer(
            FunctionTablePointer const&table,
            GLsizeiptr    size                  ,
            const GLvoid* data  = nullptr       ,
            GLbitfield    flags = GL_STATIC_DRAW);
        virtual ~Buffer();
        void alloc(
            GLsizeiptr    size                  ,
            const GLvoid* data  = nullptr       ,
            GLbitfield    flags = GL_STATIC_DRAW);
        GLvoid*map(
            GLbitfield access = GL_MAP_READ_BIT|GL_MAP_WRITE_BIT)const;
        GLvoid*map(
            GLintptr   offset,
            GLsizeiptr size,
            GLbitfield access = GL_MAP_READ_BIT|GL_MAP_WRITE_BIT)const;
        void unmap()const;
        void setData(
            const GLvoid*data      ,
            GLsizeiptr   size   = 0,
            GLintptr     offset = 0)const;
        void getData(
            GLvoid*    data      ,
            GLsizeiptr size   = 0,
            GLintptr   offset = 0)const;
        void bind       (GLenum target)const;
        void bindRange  (GLenum target,GLuint index,GLintptr offset,GLsizeiptr size)const;
        void bindBase   (GLenum target,GLuint index)const;
        void unbind     (GLenum target)const;
        void unbindRange(GLenum target,GLuint index)const;
        void unbindBase (GLenum target,GLuint index)const;
        bool realloc(GLsizeiptr newSize,ReallocFlags flags = NEW_BUFFER);
        void copy(Buffer const&buffer)const;
        void flushMapped(
            GLsizeiptr size   = 0,
            GLintptr   offset = 0)const;
        void invalidate(
            GLsizeiptr size   = 0,
            GLintptr   offset = 0)const;
        void clear(
            GLenum        internalFormat          ,
            GLenum        format                  ,
            GLenum        type                    ,
            const GLvoid *Data           = nullptr)const;
        void clear(
            GLenum        internalFormat          ,
            GLintptr      offset                  ,
            GLsizeiptr    size                    ,
            GLenum        format                  ,
            GLenum        type                    ,
            const GLvoid *Data           = nullptr)const;
        GLsizeiptr getSize       ()const;
        GLbitfield getUsage      ()const;
        GLenum     getAccess     ()const;
        GLbitfield getAccessFlags()const;
        GLboolean  isMapped      ()const;
        GLintptr   getMapOffset  ()const;
        GLsizeiptr getMapSize    ()const;
        GLvoid*    getMapPointer ()const;
        GLboolean  isImmutable   ()const;
        private:
        GLint   _getBufferParameter(GLenum pname)const;
        GLvoid* _getBufferPointer  (GLenum pname)const;
        void    _bufferData(GLsizeiptr size,const GLvoid*data,GLbitfield flags)const;
        std::set<VertexArray*>_vertexArrays;
        void _updateVertexArrays();
      };
  }
}

