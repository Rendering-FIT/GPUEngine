#include<geGL/VertexArray.h>
#include<geGL/Buffer.h>
#include<geGL/OpenGLUtil.h>
#include<sstream>
#include<cassert>

using namespace ge::gl;
using namespace ge::gl::opengl;

/**
 * @brief Creates empty vertex array object
 */
VertexArray::VertexArray (){
  glCreateVertexArrays(1,&this->_id);
}

VertexArray::VertexArray (
    FunctionTablePointer const&table):OpenGLObject(table){
  glCreateVertexArrays(1,&this->_id);
}

/**
 * @brief Destroyes vertex array object
 */
VertexArray::~VertexArray(){
  glDeleteVertexArrays(1,&this->_id);
}

/**
 * @brief Adds vertex attrib into vertex array object
 *
 * @param buffer        a buffer where a attrib is stored
 * @param index         index of attrib layout(location=index)
 * @param nofComponents number of components of attrib vec3 = 3
 * @param type          type of attrib vec3 = float, ivec2 = int
 * @param stride        distance between attribs 
 * @param pointer       offset to the first attrib
 * @param normalized    should the attrib be normalized?
 * @param divisor       rate of incrementation of attrib per instance, 0 = per VS invocation
 * @param apt           NONE - glVertexAttribPointer, I - glVertexAttribIPointer, L - glVertexAttribLPointer
 */
void VertexArray::addAttrib(
    std::shared_ptr<Buffer>const&buffer           ,
    GLuint                       index            ,
    GLint                        nofComponents    ,
    GLenum                       type             ,
    GLsizei                      stride           ,
    const GLvoid*                pointer          ,
    GLboolean                    normalized       ,  
    GLuint                       divisor          ,
    enum AttribPointerType       apt              ){
  assert(this!=nullptr);
  if(stride==0)
    stride=ge::gl::getTypeSize(type)*nofComponents;
  glVertexArrayAttribBinding (this->_id,index,index);
  glEnableVertexArrayAttrib  (this->_id,index);

  if(apt==VertexArray::AttribPointerType::NONE)
    glVertexArrayAttribFormat  (this->_id,index,nofComponents,type,normalized,0);
  else if(apt==VertexArray::AttribPointerType::I)
    glVertexArrayAttribIFormat (this->_id,index,nofComponents,type,0);
  else if(apt==VertexArray::AttribPointerType::L)
    glVertexArrayAttribLFormat (this->_id,index,nofComponents,type,0);

  glVertexArrayVertexBuffer  (this->_id,index,buffer->getId(),(GLintptr)pointer,stride);
  glVertexArrayBindingDivisor(this->_id,index,divisor);
  this->_buffers[index]=buffer;
}

void VertexArray::addElementBuffer(
    std::shared_ptr<Buffer>const&buffer){
  assert(this!=nullptr);
  this->_elementBuffer = buffer;
  glVertexArrayElementBuffer(this->_id,buffer->getId());
}


void VertexArray::bind()const{
  assert(this!=nullptr);
  glBindVertexArray(this->_id);
}

void VertexArray::unbind()const{
  assert(this!=nullptr);
  glBindVertexArray(0);
}

GLint VertexArray::_getAttrib(GLuint index,GLenum pname)const{
  assert(this!=nullptr);
  GLint param;
  glGetVertexArrayIndexediv(this->_id,index,pname,&param);
  return param;
}

GLuint    VertexArray::getAttribBufferBinding (GLuint index)const{
  assert(this!=nullptr);
  return this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);
}

GLboolean VertexArray::isAttribEnabled        (GLuint index)const{
  assert(this!=nullptr);
  return (GLboolean)this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_ENABLED);
}

GLint     VertexArray::getAttribSize          (GLuint index)const{
  assert(this!=nullptr);
  return this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_SIZE);
}

GLsizei   VertexArray::getAttribStride        (GLuint index)const{
  assert(this!=nullptr);
  return this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_STRIDE);
}

GLenum    VertexArray::getAttribType          (GLuint index)const{
  assert(this!=nullptr);
  return this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_TYPE);
}

GLboolean VertexArray::isAttribNormalized    (GLuint index)const{
  assert(this!=nullptr);
  return (GLboolean)this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_NORMALIZED);
}

GLboolean VertexArray::isAttribInteger       (GLuint index)const{
  assert(this!=nullptr);
  return (GLboolean)this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_INTEGER);
}

GLboolean VertexArray::isAttribLong          (GLuint index)const{
  assert(this!=nullptr);
  return (GLboolean)this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_LONG);
}

GLuint    VertexArray::getAttribDivisor       (GLuint index)const{
  assert(this!=nullptr);
  return this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_DIVISOR);
}

GLuint    VertexArray::getAttribBinding       (GLuint index)const{
  assert(this!=nullptr);
  return this->_getAttrib(index,GL_VERTEX_ATTRIB_BINDING);
}

GLuint    VertexArray::getAttribRelativeOffset(GLuint index)const{
  assert(this!=nullptr);
  return this->_getAttrib(index,GL_VERTEX_ATTRIB_RELATIVE_OFFSET);
}

GLuint    VertexArray::getElementBuffer()const{
  assert(this!=nullptr);
  GLint id;
  glGetVertexArrayiv(this->_id,GL_ELEMENT_ARRAY_BUFFER_BINDING,&id);
  return id;
}

std::string VertexArray::getInfo()const{
  assert(this!=nullptr);
  std::stringstream ss;
  GLint maxVertexAttribs;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&maxVertexAttribs);
  ss<<"vao: "<<this->getId()<<std::endl;
  ss<<"GL_MAX_VERTEX_ATTRIBS: "<<maxVertexAttribs<<std::endl;
  for(GLint a=0;a<maxVertexAttribs;++a){
    if(this->isAttribEnabled(a)==GL_FALSE)continue;
    ss<<"attrib: "<<a<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_ENABLED:        "<<ge::gl::translateBoolean(
        /*                                         */this->isAttribEnabled        (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING: "<<this->getAttribBufferBinding (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_SIZE:           "<<this->getAttribSize          (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_STRIDE:         "<<this->getAttribStride        (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_TYPE:           "<<ge::gl::translateAttribType(
        /*                                         */this->getAttribType          (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:     "<<ge::gl::translateBoolean(
        /*                                         */this->isAttribNormalized     (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_INTEGER:        "<<ge::gl::translateBoolean(
        /*                                         */this->isAttribInteger        (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_LONG:           "<<ge::gl::translateBoolean(
        /*                                         */this->isAttribLong           (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_DIVISOR:        "<<this->getAttribDivisor       (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_BINDING:              "<<this->getAttribBinding       (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_RELATIVE_OFFSET:      "<<this->getAttribRelativeOffset(a) <<std::endl;
  }
  return ss.str();
}

std::shared_ptr<Buffer>const&VertexArray::getElement()const{
  assert(this!=nullptr);
  return this->_elementBuffer;
}

std::shared_ptr<Buffer>const&VertexArray::getBuffer(GLuint index)const{
  assert(this!=nullptr);
  assert(this->_buffers.count(index)!=0);
  return this->_buffers.find(index)->second;
}

//OpenGL 3.3
//glBindBuffer
//glBindVertexArray
//glDeleteVertexArrays
//glEnableVertexAttribArray
//glGenVertexArrays   
//glGetIntegerv
//glGetVertexAttribiv
//glVertexAttribPointer 
//glVertexAttribIPointer

//OpenGL 4.2
//glVertexAttribDivisor    
//glVertexAttribLPointer

//
//OpenGL 4.5
//glCreateVertexArrays
//glEnableVertexArrayAttrib  
//glGetVertexArrayIndexediv
//glGetVertexArrayiv
//glVertexArrayAttribBinding 
//glVertexArrayAttribFormat  
//glVertexArrayAttribIFormat 
//glVertexArrayAttribLFormat 
//glVertexArrayBindingDivisor
//glVertexArrayElementBuffer
//glVertexArrayVertexBuffer

