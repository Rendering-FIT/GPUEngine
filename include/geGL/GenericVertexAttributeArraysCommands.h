#ifndef _GENERICVERTEXATTRIBUTEARRAYSCOMMANDS_H_
#define _GENERICVERTEXATTRIBUTEARRAYSCOMMANDS_H_

#include<geGL/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GE_EXPORT VertexAttribFormat: public Command
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
        void apply();
    };
    class GE_EXPORT VertexAttribIFormat: public Command
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
        void apply();
    };
    class GE_EXPORT VertexAttribLFormat: public Command
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
        void apply();
    };
    class GE_EXPORT BindVertexBuffer: public Command
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
        void apply();
    };
    class GE_EXPORT BindVertexBuffers: public Command
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
        void apply();
    };
    class GE_EXPORT VertexAttribBinding: public Command
    {
      public:
        GLuint attribIndex;
        GLuint bindingIndex;
        VertexAttribBinding(
            GLuint attribIndex,
            GLuint bindingIndex);
        void apply();
    };
    class GE_EXPORT VertexAttribPointer: public Command
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
        void apply();
    };
    class GE_EXPORT VertexAttribIPointer: public Command
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
        void apply();
    };
    class GE_EXPORT VertexAttribLPointer: public Command
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
        void apply();
    };
    class GE_EXPORT EnableVertexAttribArray: public Command
    {
      public:
        GLuint index;
        EnableVertexAttribArray(
            GLuint index);
        void apply();
    };
    class GE_EXPORT DisableVertexAttribArray: public Command
    {
      public:
        GLuint index;
        DisableVertexAttribArray(
            GLuint index);
        void apply();
    };
  }//ogl
}//ge

#endif//_GENERICVERTEXATTRIBUTEARRAYSCOMMANDS_H_
