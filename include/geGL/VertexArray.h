#pragma once

#include<geGL/OpenGLObject.h>
#include<iostream>
#include<map>
#include<memory>

namespace ge{
  namespace gl{
    class Buffer;
    class GEGL_EXPORT VertexArray: public OpenGLObject{
      public:
        enum AttribPointerType{
          NONE,
          I,
          L
        };
        VertexArray ();
        VertexArray (opengl::FunctionTablePointer const&table);
        ~VertexArray();
        void addAttrib(
            std::shared_ptr<Buffer>const&buffer                      ,
            GLuint                       index                       ,
            GLint                        nofComponentsa              ,
            GLenum                       type                        ,
            GLsizei                      stride            = 0       ,
            const GLvoid*                pointer           = NULL    ,
            GLboolean                    normalized        = GL_FALSE,  
            GLuint                       divisor           = 0       ,
            enum AttribPointerType       attribPointerType = NONE    );
        void addElementBuffer(
            std::shared_ptr<Buffer>const&buffer);
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
        std::shared_ptr<Buffer>const&getElement()const;
        std::shared_ptr<Buffer>const&getBuffer(GLuint index)const;
      protected:
        std::map<GLuint,std::shared_ptr<Buffer>>_buffers;
        std::shared_ptr<Buffer>_elementBuffer = nullptr;
        inline GLint _getAttrib(GLuint index,GLenum pname)const;

    };
  }//gl
}//ge

