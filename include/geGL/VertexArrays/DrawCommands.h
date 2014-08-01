#ifndef _DRAWCOMMANDS_H_
#define _DRAWCOMMANDS_H_

#include <geGL/Standard/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GE_EXPORT DrawArrays: public Command
    {
      public:
        GLenum  mode;
        GLint   first;
        GLsizei count;
        DrawArrays(GLenum mode,GLint first,GLsizei count);
        void apply();
    };
    class GE_EXPORT DrawArraysInstancedBaseInstance: public Command
    {
      public:
        GLenum  mode;
        GLint   first;
        GLsizei count;
        GLsizei instanceCount;
        GLuint  baseInstance;
        DrawArraysInstancedBaseInstance(
            GLenum  mode,
            GLint   first,
            GLsizei count,
            GLsizei instanceCount,
            GLuint  baseInstance);
        void apply();
    };
    class GE_EXPORT DrawArraysInstanced: public Command
    {
      public:
        GLenum  mode;
        GLint   first;
        GLsizei count;
        GLsizei instanceCount;
        DrawArraysInstanced(
            GLenum  mode,
            GLint   first,
            GLsizei count,
            GLsizei instanceCount);
        void apply();
    };
    class GE_EXPORT DrawArraysIndirect: public Command
    {
      public:
        GLenum  mode;
        GLvoid *indirect;
        DrawArraysIndirect(GLenum mode,GLvoid*indirect);
        void apply();
    };
    class GE_EXPORT MultiDrawArrays: public Command
    {
      public:
        GLenum   mode;
        GLint   *first;
        GLsizei *count;
        GLsizei  drawCount;
        MultiDrawArrays(
            GLenum   mode,
            GLint   *first,
            GLsizei *count,
            GLsizei  drawCount);
        void apply();
    };
    class GE_EXPORT MultiDrawArraysIndirect: public Command
    {
      public:
        GLenum   mode;
        GLvoid  *indirect;
        GLsizei  drawCount;
        GLsizei  stride;
        MultiDrawArraysIndirect(
            GLenum   mode,
            GLvoid  *indirect,
            GLsizei  drawCount,
            GLsizei  stride);
        void apply();
    };
    class GE_EXPORT DrawElements: public Command
    {
      public:
        GLenum   mode;
        GLsizei  count;
        GLenum   type;
        GLvoid  *indices;
        DrawElements(
            GLenum   mode,
            GLsizei  count,
            GLenum   type,
            GLvoid  *indices);
        void apply();
    };
    class GE_EXPORT DrawElementsInstancedBaseInstance: public Command
    {
      public:
        GLenum   mode;
        GLsizei  count;
        GLenum   type;
        GLvoid  *indices;
        GLsizei  instanceCount;
        GLuint   baseInstance;
        DrawElementsInstancedBaseInstance(
            GLenum   mode,
            GLsizei  count,
            GLenum   type,
            GLvoid  *indices,
            GLsizei  instanceCount,
            GLuint   baseInstance);
        void apply();
    };
    class GE_EXPORT DrawElementsInstanced: public Command
    {
      public:
        GLenum   mode;
        GLsizei  count;
        GLenum   type;
        GLvoid  *indices;
        GLsizei  instanceCount;
        DrawElementsInstanced(
            GLenum   mode,
            GLsizei  count,
            GLenum   type,
            GLvoid  *indices,
            GLsizei  instanceCount);
        void apply();
    };
    class GE_EXPORT MultiDrawElements: public Command
    {
      public:
        GLenum    mode;
        GLsizei  *count;
        GLenum    type;
        GLvoid  **indices;
        GLsizei   drawCount;
        MultiDrawElements(
            GLenum    mode,
            GLsizei  *count,
            GLenum    type,
            GLvoid  **indices,
            GLsizei   drawCount);
        void apply();
    };
    class GE_EXPORT DrawRangeElements: public Command
    {
      public:
        GLenum   mode;
        GLuint   start;
        GLuint   end;
        GLsizei  count;
        GLenum   type;
        GLvoid  *indices;
        DrawRangeElements(
            GLenum   mode,
            GLuint   start,
            GLuint   end,
            GLsizei  count,
            GLenum   type,
            GLvoid  *indices);
        void apply();
    };
    class GE_EXPORT DrawElementsBaseVertex: public Command
    {
      public:
        GLenum   mode;
        GLsizei  count;
        GLenum   type;
        GLvoid  *indices;
        GLint    baseVertex;
        DrawElementsBaseVertex(
            GLenum   mode,
            GLsizei  count,
            GLenum   type,
            GLvoid  *indices,
            GLint    baseVertex);
        void apply();
    };
    class GE_EXPORT DrawRangeElementsBaseVertex: public Command
    {
      public:
        GLenum   mode;
        GLuint   start;
        GLuint   end;
        GLsizei  count;
        GLenum   type;
        GLvoid  *indices;
        GLint    baseVertex;
        DrawRangeElementsBaseVertex(
            GLenum   mode,
            GLuint   start,
            GLuint   end,
            GLsizei  count,
            GLenum   type,
            GLvoid  *indices,
            GLint    baseVertex);
        void apply();
    };
    class GE_EXPORT DrawElementsInstancedBaseVertex: public Command
    {
      public:
        GLenum   mode;
        GLsizei  count;
        GLenum   type;
        GLvoid  *indices;
        GLsizei  instanceCount;
        GLint    baseVertex;
        DrawElementsInstancedBaseVertex(
            GLenum   mode,
            GLsizei  count,
            GLenum   type,
            GLvoid  *indices,
            GLsizei  instanceCount,
            GLint    baseVertex);
        void apply();
    };
    class GE_EXPORT DrawElementsInstancedBaseVertexBaseInstance: public Command
    {
      public:
        GLenum   mode;
        GLsizei  count;
        GLenum   type;
        GLvoid  *indices;
        GLsizei  instanceCount;
        GLint    baseVertex;
        GLuint   baseInstance;
        DrawElementsInstancedBaseVertexBaseInstance(
            GLenum   mode,
            GLsizei  count,
            GLenum   type,
            GLvoid  *indices,
            GLsizei  instanceCount,
            GLint    baseVertex,
            GLuint   baseInstance);
        void apply();
    };
    class GE_EXPORT DrawElementsIndirect: public Command
    {
      public:
        GLenum  mode;
        GLenum  type;
        GLvoid *indirect;
        DrawElementsIndirect(
            GLenum  mode,
            GLenum  type,
            GLvoid *indirect);
        void apply();
    };
    class GE_EXPORT MultiDrawElementsIndirect: public Command
    {
      public:
        GLenum   mode;
        GLenum   type;
        GLvoid  *indirect;
        GLsizei  drawCount;
        GLsizei  stride;
        MultiDrawElementsIndirect(
            GLenum   mode,
            GLenum   type,
            GLvoid  *indirect,
            GLsizei  drawCount,
            GLsizei  stride);
        void apply();
    };
    class GE_EXPORT MultiDrawElementsBaseVertex: public Command
    {
      public:
        GLenum    mode;
        GLsizei  *count;
        GLenum    type;
        GLvoid  **indices;
        GLsizei   drawCount;
        GLint    *baseVertex;
        MultiDrawElementsBaseVertex(
            GLenum    mode,
            GLsizei  *count,
            GLenum    type,
            GLvoid  **indices,
            GLsizei   drawCount,
            GLint    *baseVertex);
        void apply();
    };
  }//namespace ogl
}//namespace ge


#endif//_DRAWCOMMANDS_H_
