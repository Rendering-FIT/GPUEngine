#include<GPUEngine/geGL/VertexArray.h>
#include<GPUEngine/geGL/Buffer.h>
#include<GPUEngine/geGL/OpenGLUtil.h>
#include<GPUEngine/geCore/ErrorPrinter/ErrorPrinter.h>
#include<sstream>
#include<cassert>

using namespace ge::gl;

/**
 * @brief Creates empty vertex array object
 */
VertexArray::VertexArray (){
  assert(this!=nullptr);
  this->_gl.glCreateVertexArrays(1,&this->_id);
}

VertexArray::VertexArray (
    FunctionTablePointer const&table):OpenGLObject(table){
  assert(this!=nullptr);
  this->_gl.glCreateVertexArrays(1,&this->_id);
}

/**
 * @brief Destroyes vertex array object
 */
VertexArray::~VertexArray(){
  assert(this!=nullptr);
  this->_gl.glDeleteVertexArrays(1,&this->_id);
  for(auto const&x:this->_buffers)
    if(x)x->_vertexArrays.erase(this);
  if(this->_elementBuffer)this->_elementBuffer->_vertexArrays.erase(this);
}

/**
 * @brief Adds vertex attrib into vertex array object
 *
 * @param buffer        a buffer where a attrib is stored
 * @param index         index of attrib layout(location=index)
 * @param nofComponents number of components of attrib vec3 = 3
 * @param type          type of attrib vec3 = float, ivec2 = int
 * @param stride        distance between attribs 
 * @param offset        offset to the first attrib
 * @param normalized    should the attrib be normalized?
 * @param divisor       rate of incrementation of attrib per instance, 0 = per VS invocation
 * @param apt           NONE - this->_gl.glVertexAttribPointer, I - this->_gl.glVertexAttribIPointer, L - this->_gl.glVertexAttribLPointer
 */
void VertexArray::addAttrib(
    std::shared_ptr<Buffer>const&buffer           ,
    GLuint                       index            ,
    GLint                        nofComponents    ,
    GLenum                       type             ,
    GLsizei                      stride           ,
    GLintptr                     offset           ,
    GLboolean                    normalized       ,  
    GLuint                       divisor          ,
    enum AttribPointerType       apt              ){
  assert(this!=nullptr);
  if(buffer==nullptr){
    ge::core::printError(GE_CORE_FCENAME,"buffer is nullptr!",buffer,index,nofComponents,type,stride,offset,normalized,divisor,apt);
    return;
  }
  //std::cout<<this<<"->addAttrib("<<buffer<<","<<index<<","<<nofComponents<<","<<type<<","<<stride<<","<<offset<<","<<normalized<<","<<divisor<<","<<apt<<")"<<std::endl;
  if(stride==0)
    stride=ge::gl::getTypeSize(type)*nofComponents;
  this->_gl.glVertexArrayAttribBinding (this->_id,index,index);
  this->_gl.glEnableVertexArrayAttrib  (this->_id,index);

  if(apt==VertexArray::AttribPointerType::NONE)
    this->_gl.glVertexArrayAttribFormat  (this->_id,index,nofComponents,type,normalized,0);
  else if(apt==VertexArray::AttribPointerType::I)
    this->_gl.glVertexArrayAttribIFormat (this->_id,index,nofComponents,type,0);
  else if(apt==VertexArray::AttribPointerType::L)
    this->_gl.glVertexArrayAttribLFormat (this->_id,index,nofComponents,type,0);

  this->_gl.glVertexArrayVertexBuffer  (this->_id,index,buffer->getId(),offset,stride);
  this->_gl.glVertexArrayBindingDivisor(this->_id,index,divisor);
  if(index>=this->_buffers.size())this->_buffers.resize(index+1,nullptr);
  if(this->_buffers.at(index)){
    size_t nofBufferUsages = this->_getNofBufferUsages(this->_buffers.at(index));
    if(nofBufferUsages==1)
      this->_buffers[index]->_vertexArrays.erase(this);
  }
  this->_buffers[index] = buffer;
  buffer->_vertexArrays.insert(this);
}

void VertexArray::addElementBuffer(
    std::shared_ptr<Buffer>const&buffer){
  assert(this!=nullptr);
  if(this->_elementBuffer){
    size_t nofBufferUsages = this->_getNofBufferUsages(this->_elementBuffer);
    if(nofBufferUsages == 1)
      this->_elementBuffer->_vertexArrays.erase(this);
  }
  this->_elementBuffer = buffer;
  this->_gl.glVertexArrayElementBuffer(this->_id,buffer->getId());
  buffer->_vertexArrays.insert(this);
}

void VertexArray::bind()const{
  assert(this!=nullptr);
  //std::cout<<this<<"->bind()"<<std::endl;
  this->_gl.glBindVertexArray(this->_id);
}

void VertexArray::unbind()const{
  assert(this!=nullptr);
  //std::cout<<this<<"->unbind()"<<std::endl;
  this->_gl.glBindVertexArray(0);
}

GLint VertexArray::_getAttrib(GLuint index,GLenum pname)const{
  assert(this!=nullptr);
  GLint param;
  this->_gl.glGetVertexArrayIndexediv(this->_id,index,pname,&param);
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
//return this->_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_TYPE);
//AMD bug in 15.9 on Linux this->_gl.glGetVertexArrayIndexediv return type's number instead of type
  GLuint oldId;
  this->_gl.glGetIntegerv(GL_VERTEX_ARRAY_BINDING,(GLint*)&oldId);
  this->_gl.glBindVertexArray(this->_id);
  GLint data;
  this->_gl.glGetVertexAttribiv(index,GL_VERTEX_ATTRIB_ARRAY_TYPE,&data);
  this->_gl.glBindVertexArray(oldId);
  return data;

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
  this->_gl.glGetVertexArrayiv(this->_id,GL_ELEMENT_ARRAY_BUFFER_BINDING,&id);
  return id;
}

std::string VertexArray::getInfo()const{
  assert(this!=nullptr);
  std::stringstream ss;
  GLint maxVertexAttribs;
  this->_gl.glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&maxVertexAttribs);
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
  assert(index<this->_buffers.size());
  return this->_buffers.at(index);
}

size_t VertexArray::getNofBuffers()const{
  assert(this!=nullptr);
  return this->_buffers.size();
}


size_t VertexArray::_getNofBufferUsages(std::shared_ptr<Buffer>const&buffer)const{
  assert(this!=nullptr);
  size_t counter = size_t(this->_elementBuffer == buffer);
  for(auto const&x:this->_buffers)
    if(x==buffer)++counter;
  return counter;
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

