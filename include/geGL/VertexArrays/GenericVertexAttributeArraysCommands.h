#ifndef _GENERICVERTEXATTRIBUTEARRAYSCOMMANDS_H_
#define _GENERICVERTEXATTRIBUTEARRAYSCOMMANDS_H_

#include<geGL/Standard/OpenGL.h>

namespace ge
{
  namespace ogl
  {
    class VertexAttribFormat: public Command
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
    class VertexAttribIFormat: public Command
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
    class VertexAttribLFormat: public Command
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
    class BindVertexBuffer: public Command
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
    class BindVertexBuffers: public Command
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
    class VertexAttribBinding: public Command
    {
      public:
        GLuint attribIndex;
        GLuint bindingIndex;
        VertexAttribBinding(
            GLuint attribIndex,
            GLuint bindingIndex);
        void apply();
    };
    class VertexAttribPointer: public Command
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
    class VertexAttribIPointer: public Command
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
    class VertexAttribLPointer: public Command
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
    class EnableVertexAttribArray: public Command
    {
      public:
        GLuint index;
        EnableVertexAttribArray(
            GLuint index);
        void apply();
    };
    class DisableVertexAttribArray: public Command
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
