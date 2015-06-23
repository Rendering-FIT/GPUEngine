#ifndef _VERTEXARRAYOBJECTSCOMMANDS_H_
#define _VERTEXARRAYOBJECTSCOMMANDS_H_

#include<geGL/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GEGL_EXPORT GenVertexArrays: public Command
    {
      public:
        GLsizei  n;
        GLuint  *arrays;
        GenVertexArrays(
            GLsizei  n,
            GLuint  *arrays);
        void apply();
    };
    class GEGL_EXPORT DeleteVertexArrays: public Command
    {
      public:
        GLsizei  n;
        GLuint  *arrays;
        DeleteVertexArrays(
            GLsizei  n,
            GLuint  *arrays);
        void apply();
    };
    class GEGL_EXPORT BindVertexArray: public Command
    {
      public:
        GLuint array;
        BindVertexArray(GLuint array);
        void apply();
    };
    class GEGL_EXPORT CreateVertexArrays: public Command
    {
      public:
        GLsizei  n;
        GLuint  *arrays;
        CreateVertexArrays(
            GLsizei  n,
            GLuint  *arrays);
        void apply();
    };
    class GEGL_EXPORT VertexAttribFormat: public Command
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
    class GEGL_EXPORT VertexAttribIFormat: public Command
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
        GLuint    bindingIndex;
        GLuint   *buffer;
        GLintptr  offset;
        GLsizei   stride;
        BindVertexBuffer(
            GLuint    bindingIndex,
            GLuint   *buffer,
            GLintptr  offset,
            GLsizei   stride);
        void apply();
    };
    class BindVertexBuffers: public Command
    {
      public:
        GLuint   first;
        GLsizei  count;
        GLuint  *buffers;
    };

  }//ogl
}//ge

#endif//_VERTEXARRAYOBJECTSCOMMANDS_H_
