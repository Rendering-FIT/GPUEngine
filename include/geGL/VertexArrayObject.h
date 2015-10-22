#pragma once

#include<geGL/OpenGL.h>
#include<geGL/OpenGLObject.h>
#include<geGL/BufferObject.h>
#include<iostream>

namespace ge{
  namespace gl{
    GEGL_EXPORT std::string translateAttribType(GLenum    type   );
    GEGL_EXPORT std::string translateBoolean   (GLboolean boolean);
    GEGL_EXPORT unsigned    getTypeSize        (GLenum    type   );
    class GEGL_EXPORT VertexArrayObject: public OpenGLObject{
      protected:
        inline GLint _getAttrib(GLuint index,GLenum pname);
      public:
        enum AttribPointerType{
          NONE,
          I,
          L
        };
        VertexArrayObject ();
        ~VertexArrayObject();
        void addAttrib(
            GLuint                  buffer                      ,
            GLuint                  index                       ,
            GLint                   nofComponents               ,
            GLenum                  type                        ,
            GLsizei                 stride            = 0       ,
            const GLvoid           *pointer           = NULL    ,
            GLboolean               normalized        = GL_FALSE,  
            GLuint                  divisor           = 0       ,
            enum AttribPointerType  attribPointerType = NONE    );
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
        void addAttrib(
            ge::gl::BufferObject   *buffer                      ,
            GLuint                  index                       ,
            GLint                   nofComponentsa              ,
            GLenum                  type                        ,
            GLsizei                 stride            = 0       ,
            const GLvoid           *pointer           = NULL    ,
            GLboolean               normalized        = GL_FALSE,  
            GLuint                  divisor           = 0       ,
            enum AttribPointerType  attribPointerType = NONE    );
        void addElementBuffer(
            ge::gl::BufferObject *buffer);
    };
  }//gl
}//ge

