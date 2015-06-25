#pragma once

#include<geCore/Command.h>
#include<geGL/DrawCommandsBases.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT DrawArrays: 
      public ge::core::Command,
      public DrawMode,
      public DrawCount
    {
      protected:
        GLint _first;
      public:
        DrawArrays(
            GLenum  mode  = GL_TRIANGLES,
            GLint   first = 0           ,
            GLsizei count = 3           );
        void operator()();
        GLint getFirst();
        void  setFirst(GLint first = 0);
    };

    class GEGL_EXPORT DrawArraysInstancedBaseInstance: 
      public DrawArrays, 
      public DrawInstancedBaseInstance
    {
      public:
        DrawArraysInstancedBaseInstance(
            GLenum  mode          = GL_TRIANGLES,
            GLint   first         = 0           ,
            GLsizei count         = 3           ,
            GLsizei instanceCount = 1           ,
            GLuint  baseInstance  = 0           );
        void operator()();
    };
    class GEGL_EXPORT DrawArraysInstanced: 
      public DrawArrays, 
      public DrawInstanced
    {
      public:
        DrawArraysInstanced(
            GLenum  mode          = GL_TRIANGLES,
            GLint   first         = 0           ,
            GLsizei count         = 3           ,
            GLsizei instanceCount = 1           );
        void operator()();
    };
    class GEGL_EXPORT DrawArraysIndirect: 
      public DrawMode, 
      public DrawIndirect, 
      public ge::core::Command
    {
      public:
        DrawArraysIndirect(
            GLenum        mode     = GL_TRIANGLES,
            const GLvoid* indirect = NULL        );
        void operator()();
    };
    class GEGL_EXPORT MultiDrawArrays: 
      public DrawMode, 
      public MultiCount, 
      public MultiDrawCount, 
      public ge::core::Command
    {
      protected:
        const GLint*   _first;
      public:
        MultiDrawArrays(
            GLenum         mode      = GL_TRIANGLES,
            const GLint*   first     = NULL        ,
            const GLsizei* count     = NULL        ,
            GLsizei        drawCount = 1           );
        void operator()();
        const GLint*getFirst();
        void setFirst(const GLint*first = NULL);
    };
    class GEGL_EXPORT MultiDrawArraysIndirect: 
      public DrawMode, 
      public MultiDrawIndirect, 
      public ge::core::Command
    {
      public:
        MultiDrawArraysIndirect(
            GLenum        mode      = GL_TRIANGLES    ,
            const GLvoid* indirect  = NULL            ,
            GLsizei       drawCount = 1               ,
            GLsizei       stride    = sizeof(GLuint)*4);
        void operator()();
    };
    class GEGL_EXPORT DrawElements: 
      public ge::core::Command, 
      public DrawCount, 
      public DrawModeType
    {
      protected:
        const GLvoid* _indices;
      public:
        DrawElements(
            GLenum        mode    = GL_TRIANGLES   ,
            GLsizei       count   = 3              ,
            GLenum        type    = GL_UNSIGNED_INT,
            const GLvoid* indices = NULL           );
        void operator()();
        const GLvoid*getIndices();
        void setIndices(const GLvoid*indices = NULL);
    };
    class GEGL_EXPORT DrawElementsInstancedBaseInstance: 
      public DrawElements, 
      public DrawInstancedBaseInstance
    {
      public:
        DrawElementsInstancedBaseInstance(
            GLenum        mode          = GL_TRIANGLES   ,
            GLsizei       count         = 3              ,
            GLenum        type          = GL_UNSIGNED_INT,
            const GLvoid* indices       = NULL           ,
            GLsizei       instanceCount = 1              ,
            GLuint        baseInstance  = 0              );
        void operator()();
    };
    class GEGL_EXPORT DrawElementsInstanced: 
      public DrawElements, 
      public DrawInstanced
    {
      public:
        DrawElementsInstanced(
            GLenum        mode          = GL_TRIANGLES   ,
            GLsizei       count         = 3              ,
            GLenum        type          = GL_UNSIGNED_INT,
            const GLvoid* indices       = NULL           ,
            GLsizei       instanceCount = 1              );
        void operator()();
    };
    class GEGL_EXPORT MultiDrawElements: 
      public DrawModeType, 
      public MultiCount, 
      public MultiDrawCount, 
      public ge::core::Command
    {
      protected:
        const GLvoid*const* _indices;
      public:
        MultiDrawElements(
            GLenum              mode      = GL_TRIANGLES   ,
            const GLsizei*      count     = NULL           ,
            GLenum              type      = GL_UNSIGNED_INT,
            const GLvoid*const* indices   = NULL           ,
            GLsizei             drawCount = 1              );
        void operator()();
        const GLvoid*const*getIndices();
        void setIndices(const GLvoid*const*indices = NULL);
    };
    class GEGL_EXPORT DrawRangeElements: 
      public DrawElements, 
      public DrawRange
    {
      public:
        DrawRangeElements(
            GLenum        mode    = GL_TRIANGLES   ,
            GLuint        start   = 0              ,
            GLuint        end     = 3              ,
            GLsizei       count   = 3              ,
            GLenum        type    = GL_UNSIGNED_INT,
            const GLvoid* indices = NULL           );
        void operator()();
    };
    class GEGL_EXPORT DrawElementsBaseVertex: 
      public DrawElements
    {
      protected:
        GLint _baseVertex;
      public:
        DrawElementsBaseVertex(
            GLenum        mode       = GL_TRIANGLES   ,
            GLsizei       count      = 3              ,
            GLenum        type       = GL_UNSIGNED_INT,
            const GLvoid* indices    = NULL           ,
            GLint         baseVertex = 0              );
        void operator()();
        GLint getBaseVertex();
        void  setBaseVertex(GLint baseVertex = 0);
    };
    class GEGL_EXPORT DrawRangeElementsBaseVertex: 
      public DrawElementsBaseVertex, 
      public DrawRange
    {
      public:
        DrawRangeElementsBaseVertex(
            GLenum        mode       = GL_TRIANGLES   ,
            GLuint        start      = 0              ,
            GLuint        end        = 3              ,
            GLsizei       count      = 3              ,
            GLenum        type       = GL_UNSIGNED_INT,
            const GLvoid* indices    = NULL           ,
            GLint         baseVertex = 0              );
        void operator()();
    };

    class GEGL_EXPORT DrawElementsInstancedBaseVertex: 
      public DrawElementsBaseVertex, 
      public DrawInstanced
    {
      public:
        DrawElementsInstancedBaseVertex(
            GLenum        mode          = GL_TRIANGLES   ,
            GLsizei       count         = 3              ,
            GLenum        type          = GL_UNSIGNED_INT,
            const GLvoid* indices       = NULL           ,
            GLsizei       instanceCount = 1              ,
            GLint         baseVertex    = 0              );
        void operator()();
    };

    class GEGL_EXPORT DrawElementsInstancedBaseVertexBaseInstance: 
      public DrawElementsBaseVertex, 
      public DrawInstancedBaseInstance
    {
      public:
        DrawElementsInstancedBaseVertexBaseInstance(
            GLenum        mode          = GL_TRIANGLES   ,
            GLsizei       count         = 3              ,
            GLenum        type          = GL_UNSIGNED_INT,
            const GLvoid* indices       = NULL           ,
            GLsizei       instanceCount = 1              ,
            GLint         baseVertex    = 0              ,
            GLuint        baseInstance  = 0              );
        void operator()();
    };

    class GEGL_EXPORT DrawElementsIndirect: 
      public DrawModeType, 
      public DrawIndirect, 
      public ge::core::Command
    {
      public:
        DrawElementsIndirect(
            GLenum        mode     = GL_TRIANGLES   ,
            GLenum        type     = GL_UNSIGNED_INT,
            const GLvoid* indirect = NULL           );
        void operator()();
    };
    class GEGL_EXPORT MultiDrawElementsIndirect: 
      public DrawModeType, 
      public MultiDrawIndirect, 
      public ge::core::Command
    {
      public:
        MultiDrawElementsIndirect(
            GLenum        mode      = GL_TRIANGLES    ,
            GLenum        type      = GL_UNSIGNED_INT ,
            const GLvoid* indirect  = NULL            ,
            GLsizei       drawCount = 1               ,
            GLsizei       stride    = sizeof(GLuint)*5);
        void operator()();
    };
    class GEGL_EXPORT MultiDrawElementsBaseVertex: 
      public MultiDrawElements
    {
      protected:
        const GLint* _baseVertex;
      public:
        MultiDrawElementsBaseVertex(
            GLenum              mode       = GL_TRIANGLES,
            const GLsizei*      count      = NULL,
            GLenum              type       = GL_UNSIGNED_INT,
            const GLvoid*const* indices    = NULL,
            GLsizei             drawCount  = 1,
            const GLint*        baseVertex = NULL);
        void operator()();
        const GLint*getBaseVertex();
        void setBaseVertex(const GLint*baseVertex = NULL);
    };
  }//namespace ogl
}//namespace ge

