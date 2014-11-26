#ifndef GE_GL_BUFFEROBJECT
#define GE_GL_BUFFEROBJECT

#include <geGL/OpenGL.h>
#include <geCore/Object.h>

#include <iostream>

#define BUFFEROBJECT_DEFAULT_MUTABLE         true
#define BUFFEROBJECT_DEFAULT_DATA            NULL
#define BUFFEROBJECT_DEFAULT_ID              0
#define BUFFEROBJECT_DEFAULT_TARGET          GL_ARRAY_BUFFER
#define BUFFEROBJECT_DEFAULT_ACCESS          (GL_MAP_READ_BIT|GL_MAP_WRITE_BIT)
#define BUFFEROBJECT_DEFAULT_EMPTY_TARGET    0
#define BUFFEROBJECT_DEFAULT_OFFSET          0
#define BUFFEROBJECT_DEFAULT_MAPOFFSET       0
#define BUFFEROBJECT_DEFAULT_SIZE            0
#define BUFFEROBJECT_DEFAULT_USAGE           GL_STATIC_DRAW
#define BUFFEROBJECT_DEFAULT_FLAGS           GL_STATIC_DRAW
#define BUFFEROBJECT_DEFAULT_MAPFLAGS        0
#define BUFFEROBJECT_DEFAULT_DATASOURCE      NULL
#define BUFFEROBJECT_DEFAULT_READBUFFER      GL_COPY_READ_BUFFER
#define BUFFEROBJECT_DEFAULT_WRITEBUFFER     GL_COPY_WRITE_BUFFER
#define BUFFEROBJECT_DEFAULT_READOFFSET      0
#define BUFFEROBJECT_DEFAULT_WRITEOFFSET     0
#define BUFFEROBJECT_DEFAULT_OPERTARGET      GL_COPY_WRITE_BUFFER
#define BUFFEROBJECT_DEFAULT_NOF_BUFFERS     1

namespace ge{
  namespace gl{
    std::string translateBufferTarget(GLenum target);
    std::string translateBufferBinding(GLenum binding);
    GLenum bufferTarget2Binding(GLenum target);
    GLenum bufferBinding2Target(GLenum binding);

    /**
     * Abstraction of the OpenGL Buffer Object.
     */
    class GE_EXPORT BufferObject// : public ge::core::Object
    {
      private:
        GLint _getBufferParameter(GLenum pname);
      protected:
        GLuint     _id; ///< Buffer Object OpenGL ID
      public:
        BufferObject(
            GLsizeiptr    size,
            const GLvoid *data  = BUFFEROBJECT_DEFAULT_DATA,
            GLbitfield    flags = BUFFEROBJECT_DEFAULT_FLAGS);
        ~BufferObject();
        void*map(
            GLbitfield access = BUFFEROBJECT_DEFAULT_ACCESS);
        void*map(
            GLintptr   offset,
            GLsizeiptr size,
            GLbitfield access = BUFFEROBJECT_DEFAULT_ACCESS);
        void unmap();
        void setData(
            GLvoid     *data,
            GLsizeiptr  size   = BUFFEROBJECT_DEFAULT_SIZE,
            GLintptr    offset = BUFFEROBJECT_DEFAULT_OFFSET);
        void getData(
            GLvoid     *data,
            GLsizeiptr  size   = BUFFEROBJECT_DEFAULT_SIZE,
            GLintptr    offset = BUFFEROBJECT_DEFAULT_OFFSET);
        void bind       (GLenum target);
        void bindRange  (GLenum target,GLuint index,GLintptr offset,GLsizeiptr size);
        void bindBase   (GLenum Target,GLuint index);
        void unbind     (GLenum target);
        void unbindRange(GLenum target,GLuint index);
        void unbindBase (GLenum target,GLuint index);
        void copy(BufferObject*buffer);
        void flushMapped(
            GLsizeiptr size   = BUFFEROBJECT_DEFAULT_SIZE,
            GLintptr   offset = BUFFEROBJECT_DEFAULT_OFFSET);
        void invalidate(
            GLsizeiptr size   = BUFFEROBJECT_DEFAULT_SIZE,
            GLintptr   offset = BUFFEROBJECT_DEFAULT_OFFSET);
        void clear(
            GLenum        internalFormat,
            GLenum        format,
            GLenum        type,
            const GLvoid *Data = BUFFEROBJECT_DEFAULT_DATA);
        void clear(
            GLenum        internalFormat,
            GLintptr      offset,
            GLsizeiptr    size,
            GLenum        format,
            GLenum        type,
            const GLvoid *Data = BUFFEROBJECT_DEFAULT_DATA);
        void operator &=(BufferObject*buffer);
        GLsizeiptr getSize       ();
        GLuint     getId         ();
        GLenum     getUsage      ();
        GLenum     getAccess     ();
        GLbitfield getAccessFlags();
        GLboolean  isMapped      ();
        GLintptr   getMapOffset  ();
        GLsizeiptr getMapSize    ();
        GLboolean  isImmutable   ();
    };
  }
}

#endif //GE_GL_BUFFEROBJECT
