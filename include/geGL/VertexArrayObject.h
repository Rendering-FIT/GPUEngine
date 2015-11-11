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
        inline GLint _getAttrib(GLuint index,GLenum pname)const;
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
            enum AttribPointerType  attribPointerType = NONE    )const;
        void addElementBuffer(
            GLuint  buffer)const;
        void bind  ()const;
        void unbind()const;
        GLuint    getAttribBufferBinding (GLuint index)const;
        GLboolean isAttribEnabled        (GLuint index)const;
        GLint     getAttribSize          (GLuint index)const;
        GLsizei   getAttribStride        (GLuint index)const;
        GLenum    getAttribType          (GLuint index)const;
        GLboolean isAttribNormalized     (GLuint index)const;
        GLboolean isAttribInteger        (GLuint index)const;
        GLboolean isAttribLong           (GLuint index)const;
        GLuint    getAttribDivisor       (GLuint index)const;
        GLuint    getAttribBinding       (GLuint index)const;
        GLuint    getAttribRelativeOffset(GLuint index)const;
        GLuint    getElementBuffer()const;
        std::string getInfo()const;
        void addAttrib(
            ge::gl::BufferObject   *buffer                      ,
            GLuint                  index                       ,
            GLint                   nofComponentsa              ,
            GLenum                  type                        ,
            GLsizei                 stride            = 0       ,
            const GLvoid           *pointer           = NULL    ,
            GLboolean               normalized        = GL_FALSE,  
            GLuint                  divisor           = 0       ,
            enum AttribPointerType  attribPointerType = NONE    )const;
        void addElementBuffer(
            ge::gl::BufferObject *buffer)const;
    };
  }//gl
}//ge

