#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT GenVertexArrays: public ge::core::Command
    {
      public:
        GLsizei  n;
        GLuint  *arrays;
        GenVertexArrays(
            GLsizei  n,
            GLuint  *arrays);
        void operator()();
    };
    class GEGL_EXPORT DeleteVertexArrays: public ge::core::Command
    {
      public:
        GLsizei  n;
        GLuint  *arrays;
        DeleteVertexArrays(
            GLsizei  n,
            GLuint  *arrays);
        void operator()();
    };
    class GEGL_EXPORT BindVertexArray: public ge::core::Command
    {
      public:
        GLuint *array;
        BindVertexArray(GLuint *array);
        void operator()();
    };
    class GEGL_EXPORT CreateVertexArrays: public ge::core::Command
    {
      public:
        GLsizei  n;
        GLuint  *arrays;
        CreateVertexArrays(
            GLsizei  n,
            GLuint  *arrays);
        void operator()();
    };
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
    class VertexAttribLFormat: public ge::core::Command
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
    class BindVertexBuffer: public ge::core::Command
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
        void operator()();
    };
    class BindVertexBuffers: public ge::core::Command
    {
      public:
        GLuint   first;
        GLsizei  count;
        GLuint  *buffers;
    };

  }//ogl
}//ge

