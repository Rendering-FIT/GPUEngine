#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT VertexAttribFormat: public ge::core::Command
    {
      public:
        GLuint    attribIndex;
        GLint     size;
        GLenum    type;
        GLboolean normalized;
        GLuint    relativeOffset;
        VertexAttribFormat(
            GLuint    attribIndex,
            GLint     size,
            GLenum    type,
            GLboolean normalized,
            GLuint    relativeOffset);
        void operator()();
    };
    class GEGL_EXPORT VertexAttribIFormat: public ge::core::Command
    {
      public:
        GLuint attribIndex;
        GLint  size;
        GLenum type;
        GLuint relativeOffset;
        VertexAttribIFormat(
            GLuint attribIndex,
            GLint  size,
            GLenum type,
            GLuint relativeOffset);
        void operator()();
    };
    class GEGL_EXPORT VertexAttribLFormat: public ge::core::Command
    {
      public:
        GLuint attribIndex;
        GLint  size;
        GLenum type;
        GLuint relativeOffset;
        VertexAttribLFormat(
            GLuint attribIndex,
            GLint  size,
            GLenum type,
            GLuint relativeOffset);
        void operator()();
    };
    class GEGL_EXPORT BindVertexBuffer: public ge::core::Command
    {
      public:
        GLuint   bindingIndex;
        GLuint   buffer;
        GLintptr offset;
        GLsizei  stride;
        BindVertexBuffer(
            GLuint   bindingIndex,
            GLuint   buffer,
            GLintptr offset,
            GLsizei  stride);
        void operator()();
    };
    class GEGL_EXPORT BindVertexBuffers: public ge::core::Command
    {
      public:
        GLuint    first;
        GLsizei   count;
        GLuint   *buffers;
        GLintptr *offsets;
        GLsizei  *strides;
        BindVertexBuffers(
            GLuint    first,
            GLsizei   count,
            GLuint   *buffers,
            GLintptr *offsets,
            GLsizei  *strides);
        void operator()();
    };
    class GEGL_EXPORT VertexAttribBinding: public ge::core::Command
    {
      public:
        GLuint attribIndex;
        GLuint bindingIndex;
        VertexAttribBinding(
            GLuint attribIndex,
            GLuint bindingIndex);
        void operator()();
    };
    class GEGL_EXPORT VertexAttribPointer: public ge::core::Command
    {
      public:
        GLuint     index;
        GLint      size;
        GLenum     type;
        GLboolean  normalized;
        GLsizei    stride;
        GLvoid    *pointer;
        VertexAttribPointer(
            GLuint     index,
            GLint      size,
            GLenum     type,
            GLboolean  normalized,
            GLsizei    stride,
            GLvoid    *pointer);
        void operator()();
    };
    class GEGL_EXPORT VertexAttribIPointer: public ge::core::Command
    {
      public:
        GLuint   index;
        GLint    size;
        GLenum   type;
        GLsizei  stride;
        GLvoid  *pointer;
        VertexAttribIPointer(
            GLuint   index,
            GLint    size,
            GLenum   type,
            GLsizei  stride,
            GLvoid  *pointer);
        void operator()();
    };
    class GEGL_EXPORT VertexAttribLPointer: public ge::core::Command
    {
      public:
        GLuint   index;
        GLint    size;
        GLenum   type;
        GLsizei  stride;
        GLvoid  *pointer;
        VertexAttribLPointer(
            GLuint   index,
            GLint    size,
            GLenum   type,
            GLsizei  stride,
            GLvoid  *pointer);
        void operator()();
    };
    class GEGL_EXPORT EnableVertexAttribArray: public ge::core::Command
    {
      public:
        GLuint index;
        EnableVertexAttribArray(
            GLuint index);
        void operator()();
    };
    class GEGL_EXPORT DisableVertexAttribArray: public ge::core::Command
    {
      public:
        GLuint index;
        DisableVertexAttribArray(
            GLuint index);
        void operator()();
    };
  }//ogl
}//ge

