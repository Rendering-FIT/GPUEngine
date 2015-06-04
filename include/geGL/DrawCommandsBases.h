#pragma once

#include<geGL/OpenGL.h>

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

  }
}
