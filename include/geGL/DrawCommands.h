#ifndef _DRAWCOMMANDS_H_
#define _DRAWCOMMANDS_H_

#include <geGL/OpenGL.h>

namespace ge
{
  namespace gl
  {
    class GEGL_EXPORT DrawMode{
      protected:
        GLenum _mode;
      public:
        DrawMode(GLenum mode = GL_TRIANGLES);
        GLenum getMode();
        void   setMode(GLenum mode = GL_TRIANGLES);
    };

    class GEGL_EXPORT DrawModeType: public DrawMode{
      protected:
        GLenum _type;
      public:
        DrawModeType(GLenum mode = GL_TRIANGLES,GLenum type = GL_UNSIGNED_INT);
        GLenum getType();
        void   setType(GLenum type = GL_UNSIGNED_INT);
    };

    class GEGL_EXPORT DrawCount{
      protected:
        GLsizei _count;
      public:
        DrawCount(GLsizei count = 3);
        GLsizei getCount();
        void    setCount(GLsizei count = 3);
    };

    class GEGL_EXPORT DrawInstanced{
      protected:
        GLsizei _instanceCount;
      public:
        DrawInstanced(GLsizei instanceCount = 1);
        GLsizei getInstanceCount();
        void    setInstanceCount(GLsizei instanceCount = 1);
    };

    class GEGL_EXPORT DrawInstancedBaseInstance: public DrawInstanced{
      protected:
        GLuint _baseInstance;
      public:
        DrawInstancedBaseInstance(GLuint baseInstance = 0,GLsizei instanceCount = 1);
        GLuint getBaseInstance();
        void   setBaseInstance(GLuint baseInstance = 0);
    };

    class GEGL_EXPORT DrawIndirect{
      protected:
        const GLvoid*_indirect;
      public:
        DrawIndirect(const GLvoid*indirect = NULL);
        const GLvoid*getIndirect();
        void setIndirect(const GLvoid*indirect = NULL);
    };

    class GEGL_EXPORT MultiDrawCount{
      protected:
        GLsizei _drawCount;
      public:
        MultiDrawCount(GLsizei drawCount = 1);
        GLsizei getDrawCount();
        void    setDrawCount(GLsizei drawCount = 1);
    };

    class GEGL_EXPORT MultiDrawIndirect: public DrawIndirect, public MultiDrawCount{
      protected:
        GLsizei _stride;
      public:
        MultiDrawIndirect(const GLvoid*_indirect = NULL,GLsizei drawCount = 1,GLsizei stride = sizeof(GLuint)*4);
        GLsizei getStride();
        void setStride(GLsizei stride = sizeof(GLuint)*4);
    };

    class GEGL_EXPORT DrawRange{
      protected:
        GLuint _start;
        GLuint _end  ;
      public:
        DrawRange(
            GLuint start = 0,
            GLuint end   = 3);
        GLuint getStart();
        GLuint getEnd  ();
        void   setStart(GLuint start = 0);
        void   setEnd  (GLuint end   = 3);
    };

    class GEGL_EXPORT MultiCount{
      protected:
        const GLsizei* _count;
      public:
        MultiCount(const GLsizei* count = NULL);
        const GLsizei* getCount();
        void setCount(const GLsizei*count = NULL);
    };



    class GEGL_EXPORT DrawArrays: public Command, public DrawMode, public DrawCount
    {
      protected:
        GLint _first;
      public:
        DrawArrays(
            GLenum  mode  = GL_TRIANGLES,
            GLint   first = 0           ,
            GLsizei count = 3           );
        void apply();
        GLint getFirst();
        void  setFirst(GLint first = 0);
    };

    class GEGL_EXPORT DrawArraysInstancedBaseInstance: public DrawArrays, public DrawInstancedBaseInstance
    {
      public:
        DrawArraysInstancedBaseInstance(
            GLenum  mode          = GL_TRIANGLES,
            GLint   first         = 0           ,
            GLsizei count         = 3           ,
            GLsizei instanceCount = 1           ,
            GLuint  baseInstance  = 0           );
        void apply();
    };
    class GEGL_EXPORT DrawArraysInstanced: public DrawArrays, public DrawInstanced
    {
      public:
        DrawArraysInstanced(
            GLenum  mode          = GL_TRIANGLES,
            GLint   first         = 0           ,
            GLsizei count         = 3           ,
            GLsizei instanceCount = 1           );
        void apply();
    };
    class GEGL_EXPORT DrawArraysIndirect: public DrawMode, public DrawIndirect, public Command
    {
      public:
        DrawArraysIndirect(
            GLenum        mode     = GL_TRIANGLES,
            const GLvoid* indirect = NULL        );
        void apply();
    };
    class GEGL_EXPORT MultiDrawArrays: public DrawMode, public MultiCount, public MultiDrawCount, public Command
    {
      protected:
        const GLint*   _first;
      public:
        MultiDrawArrays(
            GLenum         mode      = GL_TRIANGLES,
            const GLint*   first     = NULL        ,
            const GLsizei* count     = NULL        ,
            GLsizei        drawCount = 1           );
        void apply();
        const GLint*getFirst();
        void setFirst(const GLint*first = NULL);
    };
    class GEGL_EXPORT MultiDrawArraysIndirect: public DrawMode, public MultiDrawIndirect, public Command
    {
      public:
        MultiDrawArraysIndirect(
            GLenum        mode      = GL_TRIANGLES    ,
            const GLvoid* indirect  = NULL            ,
            GLsizei       drawCount = 1               ,
            GLsizei       stride    = sizeof(GLuint)*4);
        void apply();
    };
    class GEGL_EXPORT DrawElements: public Command, public DrawCount, public DrawModeType
    {
      protected:
        const GLvoid* _indices;
      public:
        DrawElements(
            GLenum        mode    = GL_TRIANGLES   ,
            GLsizei       count   = 3              ,
            GLenum        type    = GL_UNSIGNED_INT,
            const GLvoid* indices = NULL           );
        void apply();
        const GLvoid*getIndices();
        void setIndices(const GLvoid*indices = NULL);
    };
    class GEGL_EXPORT DrawElementsInstancedBaseInstance: public DrawElements, public DrawInstancedBaseInstance
    {
      public:
        DrawElementsInstancedBaseInstance(
            GLenum        mode          = GL_TRIANGLES   ,
            GLsizei       count         = 3              ,
            GLenum        type          = GL_UNSIGNED_INT,
            const GLvoid* indices       = NULL           ,
            GLsizei       instanceCount = 1              ,
            GLuint        baseInstance  = 0              );
        void apply();
    };
    class GEGL_EXPORT DrawElementsInstanced: public DrawElements, public DrawInstanced
    {
      public:
        DrawElementsInstanced(
            GLenum        mode          = GL_TRIANGLES   ,
            GLsizei       count         = 3              ,
            GLenum        type          = GL_UNSIGNED_INT,
            const GLvoid* indices       = NULL           ,
            GLsizei       instanceCount = 1              );
        void apply();
    };
    class GEGL_EXPORT MultiDrawElements: public DrawModeType, public MultiCount, public MultiDrawCount, public Command
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
        void apply();
        const GLvoid*const*getIndices();
        void setIndices(const GLvoid*const*indices = NULL);
    };
    class GEGL_EXPORT DrawRangeElements: public DrawElements, public DrawRange
    {
      public:
        DrawRangeElements(
            GLenum        mode    = GL_TRIANGLES   ,
            GLuint        start   = 0              ,
            GLuint        end     = 3              ,
            GLsizei       count   = 3              ,
            GLenum        type    = GL_UNSIGNED_INT,
            const GLvoid* indices = NULL           );
        void apply();
    };
    class GEGL_EXPORT DrawElementsBaseVertex: public DrawElements
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
        void apply();
        GLint getBaseVertex();
        void  setBaseVertex(GLint baseVertex = 0);
    };
    class GEGL_EXPORT DrawRangeElementsBaseVertex: public DrawElementsBaseVertex, public DrawRange
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
        void apply();
    };

    class GEGL_EXPORT DrawElementsInstancedBaseVertex: public DrawElementsBaseVertex, public DrawInstanced
    {
      public:
        DrawElementsInstancedBaseVertex(
            GLenum        mode          = GL_TRIANGLES   ,
            GLsizei       count         = 3              ,
            GLenum        type          = GL_UNSIGNED_INT,
            const GLvoid* indices       = NULL           ,
            GLsizei       instanceCount = 1              ,
            GLint         baseVertex    = 0              );
        void apply();
    };

    class GEGL_EXPORT DrawElementsInstancedBaseVertexBaseInstance: public DrawElementsBaseVertex, public DrawInstancedBaseInstance
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
        void apply();
    };

    class GEGL_EXPORT DrawElementsIndirect: public DrawModeType, public DrawIndirect, public Command
    {
      public:
        DrawElementsIndirect(
            GLenum        mode     = GL_TRIANGLES   ,
            GLenum        type     = GL_UNSIGNED_INT,
            const GLvoid* indirect = NULL           );
        void apply();
    };
    class GEGL_EXPORT MultiDrawElementsIndirect: public DrawModeType, public MultiDrawIndirect, public Command
    {
      public:
        MultiDrawElementsIndirect(
            GLenum        mode      = GL_TRIANGLES    ,
            GLenum        type      = GL_UNSIGNED_INT ,
            const GLvoid* indirect  = NULL            ,
            GLsizei       drawCount = 1               ,
            GLsizei       stride    = sizeof(GLuint)*5);
        void apply();
    };
    class GEGL_EXPORT MultiDrawElementsBaseVertex: public MultiDrawElements
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
        void apply();
        const GLint*getBaseVertex();
        void setBaseVertex(const GLint*baseVertex = NULL);
    };
  }//namespace ogl
}//namespace ge


#endif//_DRAWCOMMANDS_H_
