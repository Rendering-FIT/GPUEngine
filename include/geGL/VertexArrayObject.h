#ifndef _VERTEXARRAYOBJECT_H_
#define _VERTEXARRAYOBJECT_H_

#include<geGL/OpenGL.h>
#include<geGL/OpenGLObject.h>
#include<iostream>

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
    std::string translateAttribType(GLenum    type   );
    std::string translateBoolean   (GLboolean boolean);
    unsigned    getTypeSize        (GLenum    type   );
    void initVertexArrayObjects    ();
    class GEGL_EXPORT VertexArrayObject: public OpenGLObject
    {
      private:
        inline GLint getAttrib(GLuint index,GLenum pname);
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
        GLuint    getAttribBufferBinding (GLuint index);
        GLboolean isAttribEnabled        (GLuint index);
        GLint     getAttribSize          (GLuint index);
        GLsizei   getAttribStride        (GLuint index);
        GLenum    getAttribType          (GLuint index);
        GLboolean isAttribNormalized     (GLuint index);
        GLboolean isAttribInteger        (GLuint index);
        GLboolean isAttribLong           (GLuint index);
        GLuint    getAttribDivisor       (GLuint index);
        GLuint    getAttribBinding       (GLuint index);
        GLuint    getAttribRelativeOffset(GLuint index);
        GLuint    getElementBuffer();
        std::string getInfo();
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
