#include<geGL/VertexArrayObject.h>

namespace ge{
  namespace gl{
    VertexArrayObject::VertexArrayObject (){
#ifndef USE_DSA
      glGenVertexArrays   (1,&this->_id);
#else //USE_DSA
      glCreateVertexArrays(1,&this->_id);
#endif//USE_DSA
    }
    VertexArrayObject::~VertexArrayObject(){
      glDeleteVertexArrays(1,&this->_id);
    }
    void VertexArrayObject::addAttrib(
        GLuint        buffer,
        GLuint        index,
        GLint         size,
        GLenum        type,
        GLsizei       stride,
        const GLvoid *pointer,
        GLboolean     normalized,
        GLuint        divisor){
#ifndef USE_DSA
      this->bind();
      glBindBuffer(GL_ARRAY_BUFFER,buffer);
      glEnableVertexAttribArray(index);
      glVertexAttribPointer    (index,size,type,normalized,stride,pointer);
      glVertexAttribDivisor    (index,divisor);
      this->unbind();
#else //USE_DSA
      if(stride==VERTEXARRAYOBJECT_DEFAULT_STRIDE){
        switch(type){
          case GL_BYTE:
            stride=sizeof(GLbyte);
            break;
          case GL_UNSIGNED_BYTE:
            stride=sizeof(GLubyte);
            break;
          case GL_SHORT:
            stride=sizeof(GLshort);
            break;
          case GL_UNSIGNED_SHORT:
            stride=sizeof(GLushort);
            break;
          case GL_INT:
            stride=sizeof(GLint);
            break;
          case GL_UNSIGNED_INT:
            stride=sizeof(GLuint);
            break;
          case GL_FLOAT:
            stride=sizeof(GLfloat);
            break;
          case GL_HALF_FLOAT:
            stride=sizeof(GLhalf);
            break;
          case GL_DOUBLE:
            stride=sizeof(GLdouble);
            break;
        }
        stride*=size;
      }
      glVertexArrayAttribBinding (this->_id,index,index);
      glEnableVertexArrayAttrib  (this->_id,index);
      glVertexArrayAttribFormat  (this->_id,index,size,type,normalized,0);
      glVertexArrayVertexBuffer  (this->_id,index,buffer,(GLintptr)pointer,stride);
      glVertexArrayBindingDivisor(this->_id,index,divisor);
#endif//USE_DSA
    }
    void VertexArrayObject::addElementBuffer(
        GLuint buffer){
#ifndef USE_DSA
      this->bind();
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer);
      this->unbind();
#else //USE_DSA
      glVertexArrayElementBuffer(this->_id,buffer);
#endif//USE_DSA
    }
    void VertexArrayObject::bind(){
      glBindVertexArray(this->_id);
    }
    void VertexArrayObject::unbind(){
      glBindVertexArray(VERTExARRAYOBJECT_DEFAULT_ID);
    }

    GLuint VertexArrayObject::getId(){
      return this->_id;
    }

    GLint     VertexArrayObject::getAttrib(GLuint index,GLenum pname){
      GLint param;
#ifndef USE_DSA
      this->bind();
      glGetVertexAttribiv(index,pname,&param);
      this->unbind();
#else //USE_DSA
      glGetVertexArrayIndexediv(this->_id,index,pname,&param);
#endif//USE_DSA
      return param;
    }

    GLuint    VertexArrayObject::getAttribBufferBinding (GLuint index){
      return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);
    }
    GLboolean VertexArrayObject::getAttribEnable        (GLuint index){
      return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_ENABLED);
    }
    GLint     VertexArrayObject::getAttribSize          (GLuint index){
      return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_SIZE);
    }
    GLsizei   VertexArrayObject::getAttribStride        (GLuint index){
      return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_STRIDE);
    }
    GLenum    VertexArrayObject::getAttribType          (GLuint index){
      return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_TYPE);
    }
    GLboolean VertexArrayObject::getAttribNormalized    (GLuint index){
      return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_NORMALIZED);
    }
    GLuint    VertexArrayObject::getAttribInteger       (GLuint index){
      return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_INTEGER);
    }
    GLuint    VertexArrayObject::getAttribLong          (GLuint index){
      return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_LONG);
    }
    GLuint    VertexArrayObject::getAttribDivisor       (GLuint index){
      return this->getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_DIVISOR);
    }
    GLuint    VertexArrayObject::getAttribBinding       (GLuint index){
      return this->getAttrib(index,GL_VERTEX_ATTRIB_BINDING);
    }
    GLuint    VertexArrayObject::getAttribRelativeOffset(GLuint index){
      return this->getAttrib(index,GL_VERTEX_ATTRIB_RELATIVE_OFFSET);
    }
    GLuint    VertexArrayObject::getElementBuffer(){
      GLint id;
#ifndef USE_DSA
      this->bind();
      glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER,&id);
      this->unbind();
#else //USE_DSA
      glGetVertexArrayiv(this->_id,GL_ELEMENT_ARRAY_BUFFER_BINDING,&id);
#endif//USE_DSA
      return id;
    }
  }//gl
}//ge
