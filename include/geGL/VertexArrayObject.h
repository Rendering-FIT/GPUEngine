#ifndef _VERTEXARRAYOBJECT_H_
#define _VERTEXARRAYOBJECT_H_

#include<geGL/OpenGL.h>

//#define REMOVE_FUNCTIONS_WITH_OBJECTS_AS_PARAMETERS

#ifndef REMOVE_FUNCTIONS_WITH_OBJECTS_AS_PARAMETERS
#include<geGL/BufferObject.h>
#endif//REMOVE_FUNCTIONS_WITH_OBJECTS_AS_PARAMETERS

#define VERTEXARRAYOBJECT_DEFAULT_STRIDE      0       
#define VERTEXARRAYOBJECT_DEFAULT_POINTER     NULL    
#define VERTEXARRAYOBJECT_DEFAULT_NORMALIZED  GL_FALSE
#define VERTEXARRAYOBJECT_DEFAULT_DIVISOR     0       
#define VERTExARRAYOBJECT_DEFAULT_ID          0       
#define VERTEXARRAYOBJECT_DEFAULT_APT         VertexArrayObject::AttribPointerType::NONE

namespace ge{
  namespace gl{
    class GE_EXPORT VertexArrayObject
    {
      private:
        inline GLint getAttrib(GLuint index,GLenum pname);
      protected:
        GLuint _id;
      public:
        enum AttribPointerType{
          NONE,
          I,
          L
        };
        VertexArrayObject ();
        ~VertexArrayObject();
        void addAttrib(
            GLuint                  buffer                                                  ,
            GLuint                  index                                                   ,
            GLint                   nofComponents                                           ,
            GLenum                  type                                                    ,
            GLsizei                 stride            = VERTEXARRAYOBJECT_DEFAULT_STRIDE    ,
            const GLvoid           *pointer           = VERTEXARRAYOBJECT_DEFAULT_POINTER   ,
            GLboolean               normalized        = VERTEXARRAYOBJECT_DEFAULT_NORMALIZED,  
            GLuint                  divisor           = VERTEXARRAYOBJECT_DEFAULT_DIVISOR   ,
            enum AttribPointerType  attribPointerType = VERTEXARRAYOBJECT_DEFAULT_APT       );
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
#ifndef REMOVE_FUNCTIONS_WITH_OBJECTS_AS_PARAMETERS
        void addAttrib(
            ge::gl::BufferObject   *buffer                                                  ,
            GLuint                  index                                                   ,
            GLint                   nofComponentsa                                          ,
            GLenum                  type                                                    ,
            GLsizei                 stride            = VERTEXARRAYOBJECT_DEFAULT_STRIDE    ,
            const GLvoid           *pointer           = VERTEXARRAYOBJECT_DEFAULT_POINTER   ,
            GLboolean               normalized        = VERTEXARRAYOBJECT_DEFAULT_NORMALIZED,  
            GLuint                  divisor           = VERTEXARRAYOBJECT_DEFAULT_DIVISOR   ,
            enum AttribPointerType  attribPointerType = VERTEXARRAYOBJECT_DEFAULT_APT       );
        void addElementBuffer(
            ge::gl::BufferObject *buffer);
#endif//REMOVE_FUNCTIONS_WITH_OBJECTS_AS_PARAMETERS
    };
  }//gl
}//ge

#endif//_VERTEXARRAYOBJECT_H_
