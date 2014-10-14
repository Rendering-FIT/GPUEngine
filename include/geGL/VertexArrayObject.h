#ifndef _VERTEXARRAYOBJECT_H_
#define _VERTEXARRAYOBJECT_H_

#include<geGL/OpenGL.h>

#define VERTEXARRAYOBJECT_DEFAULT_STRIDE      0       
#define VERTEXARRAYOBJECT_DEFAULT_POINTER     NULL    
#define VERTEXARRAYOBJECT_DEFAULT_NORMALIZED  GL_FALSE
#define VERTEXARRAYOBJECT_DEFAULT_DIVISOR     0       
#define VERTExARRAYOBJECT_DEFAULT_ID          0       

namespace ge{
  namespace gl{
    class GE_EXPORT VertexArrayObject
    {
      inline GLint getAttrib(GLuint index,GLenum pname);
      protected:
      GLuint _id;
      public:
      VertexArrayObject ();
      ~VertexArrayObject();
      void addAttrib(
          GLuint        buffer,
          GLuint        index,
          GLint         size,
          GLenum        type,
          GLsizei       stride     = VERTEXARRAYOBJECT_DEFAULT_STRIDE,
          const GLvoid *pointer    = VERTEXARRAYOBJECT_DEFAULT_POINTER,
          GLboolean     normalized = VERTEXARRAYOBJECT_DEFAULT_NORMALIZED,  
          GLuint        divisor    = VERTEXARRAYOBJECT_DEFAULT_DIVISOR);
      void addElementBuffer(
          GLuint  buffer);
      void bind  ();
      void unbind();
      GLuint    getId();
      GLuint    getAttribBufferBinding (GLuint index);
      GLboolean getAttribEnable        (GLuint index);
      GLint     getAttribSize          (GLuint index);
      GLsizei   getAttribStride        (GLuint index);
      GLenum    getAttribType          (GLuint index);
      GLboolean getAttribNormalized    (GLuint index);
      GLuint    getAttribInteger       (GLuint index);
      GLuint    getAttribLong          (GLuint index);
      GLuint    getAttribDivisor       (GLuint index);
      GLuint    getAttribBinding       (GLuint index);
      GLuint    getAttribRelativeOffset(GLuint index);
      GLuint    getElementBuffer();
    };
  }//gl
}//ge

#endif//_VERTEXARRAYOBJECT_H_
