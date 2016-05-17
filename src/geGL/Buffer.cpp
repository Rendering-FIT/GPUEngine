#include<geGL/Buffer.h>
#include<geGL/VertexArray.h>
#include<geGL/OpenGLUtil.h>
#include<cassert>
#include<vector>

using namespace ge::gl;
using namespace ge::gl::opengl;

/**
 * @brief Empty constructor, it sets ID=0
 */
Buffer::Buffer(){
  this->_id = 0;
}

/**
 * @brief Constructor
 *
 * @param size size of buffer in bytes
 * @param data optional pointer to data data
 * @param flags optional flags, right flags can make buffer immutable
 */
Buffer::Buffer(
    GLsizeiptr    size,
    const GLvoid *data,
    GLbitfield    flags){
  this->alloc(size,data,flags);
}

Buffer::Buffer(FunctionTablePointer const&table):OpenGLObject(table){
  this->_id = 0;
}

Buffer::Buffer(
    FunctionTablePointer const&table,
    GLsizeiptr    size ,
    const GLvoid* data ,
    GLbitfield    flags):OpenGLObject(table){
  this->alloc(size,data,flags);
}

Buffer::~Buffer(){
  glDeleteBuffers(1,&this->_id);
}

void Buffer::_bufferData(GLsizeiptr size,const GLvoid*data,GLbitfield flags)const{
  assert(this!=nullptr);
  if(ge::gl::areBufferFlagsMutable(flags))
    glNamedBufferData(this->_id,size,data,flags);
  else
    glNamedBufferStorage(this->_id,size,data,flags);
}

void Buffer::alloc(
    GLsizeiptr    size,
    const GLvoid *data,
    GLbitfield    flags){
  assert(this!=nullptr);
  glCreateBuffers(1,&this->_id);
  this->_bufferData(size,data,flags);
}

/**
 * @brief Binds buffer to specific target
 *
 * @param target target
 */
void Buffer::bind(
    GLenum target)const{
  assert(this!=nullptr);
  glBindBuffer(target,this->_id);
}

/**
 * @brief Binds range of buffer to specific indexed target
 *
 * @param target target
 * @param index target index
 * @param offset offset
 * @param size size of buffer
 */
void Buffer::bindRange(
    GLenum     target,
    GLuint     index,
    GLintptr   offset,
    GLsizeiptr size)const{
  assert(this!=nullptr);
  glBindBufferRange(target,index,this->_id,offset,size);
}

/**
 * @brief Binds buffer to specific indexed target
 *
 * @param target target
 * @param index index
 */
void Buffer::bindBase(GLenum target,GLuint index)const{
  assert(this!=nullptr);
  glBindBufferBase(target,index,this->_id);
}

/**
 * @brief Unbinds buffer from specific target
 *
 * @param target target
 */
void Buffer::unbind(GLenum target)const{
  assert(this!=nullptr);
  glBindBuffer(target,0);
}

/**
 * @brief Unbinds range of buffer from specific indexed target
 *
 * @param target target
 * @param index  index
 */
void Buffer::unbindRange(GLenum target,GLuint index)const{
  assert(this!=nullptr);
  glBindBufferBase(target,index,0);
}

/**
 * @brief Unbinds buffer from specific index target
 *
 * @param target target
 * @param index  index
 */
void Buffer::unbindBase(GLenum target,GLuint index)const{
  assert(this!=nullptr);
  glBindBufferBase(target,index,0);
}

/**
 * @brief Reallocates buffer
 *
 * @param newSize new size
 * @param flags KEEP_ID|KEEP_DATA
 */
bool Buffer::realloc(GLsizeiptr newSize,ReallocFlags flags){
  assert(this!=nullptr);
  if((flags&KEEP_ID)&&this->isImmutable()){
    std::cerr<<"ERROR: can't sustain buffer id: "<<this->getId()<<", buffer is immutable"<<std::endl;
    return false;
  }
  GLbitfield bufferFlags=this->getUsage();
  if      (flags==(KEEP_ID|KEEP_DATA)){
    Buffer*temp=new Buffer(newSize,nullptr,bufferFlags);
    temp->copy(*this);
    this->_bufferData(newSize,nullptr,bufferFlags);
    this->copy(*temp);
    delete temp;
  }else if(flags==KEEP_ID            ){
    this->_bufferData(newSize,nullptr,bufferFlags);
  }else if(flags==KEEP_DATA          ){
    Buffer*newBuffer=new Buffer(newSize,nullptr,bufferFlags);
    newBuffer->copy(*this);
    this->~Buffer();
    this->_id = newBuffer->_id;
    delete(char*)newBuffer;
    this->_updateVertexArrays();
  }else if(flags==NEW_BUFFER         ){
    this->~Buffer();
    new(this)Buffer(newSize,nullptr,bufferFlags);
    this->_updateVertexArrays();
  }else{
    std::cerr<<"ERROR: invalid buffer reallocation flags: "<<flags<<std::endl;
    return false;
  }
  return true;
}

void Buffer::_updateVertexArrays(){
  auto me = this->shared_from_this();
  for(auto const&x:this->_vertexArrays){
    if(x->_elementBuffer == me){
      x->addElementBuffer(me);
    }
    std::vector<decltype(x->_buffers)::key_type>attribs;
    for(auto const&y:x->_buffers)
      if(y.second == me)
        attribs.push_back(y.first);

    for(auto const&y:attribs)
      x->addAttrib(
          me,
          y,
          x->getAttribSize(y),
          x->getAttribType(y),
          x->getAttribStride(y),
          (const GLvoid*)(size_t)x->getAttribRelativeOffset(y),
          x->isAttribNormalized(y),
          x->getAttribDivisor(y),
          x->isAttribInteger(y)?VertexArray::I:(x->isAttribLong(y)?VertexArray::L:VertexArray::NONE));
  }
}

/**
 * @brief Copies data from another buffer into this buffer
 *
 * @param buffer another buffer
 */
void Buffer::copy(
    Buffer const&buffer)const{
  assert(this!=nullptr);
  GLsizeiptr maxSize=(this->getSize()>buffer.getSize())?buffer.getSize():this->getSize();
  glCopyNamedBufferSubData(buffer._id,this->_id,0,0,maxSize);
}

/**
 * @brief Flushes mapped buffer
 *
 * @param target target
 * @param offset offset into buffer in bytes
 * @param size   length of data in bytes
 */
void Buffer::flushMapped(GLsizeiptr size,GLintptr offset)const{
  assert(this!=nullptr);
  if(size==0)size=this->getSize();
  glFlushMappedNamedBufferRange(this->_id,offset,size);
}

/**
 * @brief Invalidates specific region of buffer
 *
 * @param offset offset of region in bytes
 * @param size   length of region in bytes
 */
void Buffer::invalidate(GLsizeiptr size,GLintptr offset)const{
  assert(this!=nullptr);
  glInvalidateBufferSubData(this->_id,offset,size);
}

/**
 * @brief Clears buffer
 *
 * @param internalFormat internal format of buffer
 * @param format format of data
 * @param type type of data
 * @param data optional data
 */
void Buffer::clear(
    GLenum        internalFormat,
    GLenum        format,
    GLenum        type,
    const GLvoid *data)const{
  assert(this!=nullptr);
  glClearNamedBufferData(this->_id,internalFormat,format,type,data);
}

/**
 * @brief Clears specific region of buffer
 *
 * @param internalFormat internal format of buffer
 * @param offset offset of region
 * @param size   size of region
 * @param format format of data
 * @param type   type of data
 * @param data   data
 */
void Buffer::clear(
    GLenum        internalFormat,
    GLintptr      offset,
    GLsizeiptr    size,
    GLenum        format,
    GLenum        type,
    const GLvoid *data)const{
  assert(this!=nullptr);
  glClearNamedBufferSubData(this->_id,internalFormat,offset,size,format,type,data);
}

GLvoid*Buffer::map(
    GLbitfield access)const{
  assert(this!=nullptr);
  if(access==GL_READ_ONLY )access=GL_MAP_READ_BIT ;
  if(access==GL_WRITE_ONLY)access=GL_MAP_WRITE_BIT;
  if(access==GL_READ_WRITE)access=GL_MAP_READ_BIT|GL_MAP_WRITE_BIT;
  return glMapNamedBufferRange(this->_id,0,this->getSize(),access);
}

GLvoid*Buffer::map(
    GLintptr   offset,
    GLsizeiptr size,
    GLbitfield access)const{
  assert(this!=nullptr);
  return glMapNamedBufferRange(this->_id,offset,size,access);
}

void Buffer::unmap()const{
  assert(this!=nullptr);
  glUnmapNamedBuffer(this->_id);
}

void Buffer::setData(
    const GLvoid* data  ,
    GLsizeiptr    size  ,
    GLintptr      offset)const{
  assert(this!=nullptr);
  if(size==0)size=this->getSize();
  glNamedBufferSubData(this->_id,offset,size,data);
}

void Buffer::getData(
    GLvoid     *data,
    GLsizeiptr  size,
    GLintptr    offset)const{
  assert(this!=nullptr);
  if(size==0)size=this->getSize();
  glGetNamedBufferSubData(this->_id,offset,size,data);
}

GLint Buffer::_getBufferParameter(GLenum pname)const{
  assert(this!=nullptr);
  GLint param;
  glGetNamedBufferParameteriv(this->_id,pname,&param);
  return param;
}

GLvoid*Buffer::_getBufferPointer(GLenum pname)const{
  assert(this!=nullptr);
  GLvoid *param;
  glGetNamedBufferPointerv(this->_id,pname,&param);
  return param;
}

/**
 * @brief gets size of this buffer
 *
 * @return size of thie buffer in bytes
 */
GLsizeiptr Buffer::getSize()const{
  assert(this!=nullptr);
  return this->_getBufferParameter(GL_BUFFER_SIZE);
}

/**
 * @brief gets usage of this buffer
 *
 * @return usage (GL_BUFFER_USAGE)
 */
GLenum Buffer::getUsage()const{
  assert(this!=nullptr);
  return this->_getBufferParameter(GL_BUFFER_USAGE);
}

/**
 * @brief gets access of thie buffer
 *
 * @return access (GL_BUFFER_ACCESS)
 */
GLbitfield Buffer::getAccess()const{
  assert(this!=nullptr);
  return this->_getBufferParameter(GL_BUFFER_ACCESS);
}

/**
 * @brief gets access flags of this buffer
 *
 * @return access flags (GL_BUFFER_ACCESS_FLAGS)
 */
GLbitfield Buffer::getAccessFlags()const{
  assert(this!=nullptr);
  return this->_getBufferParameter(GL_BUFFER_ACCESS_FLAGS);
}

/**
 * @brief is this buffer mapped
 *
 * @return true if this buffer is mapped
 */
GLboolean Buffer::isMapped()const{
  assert(this!=nullptr);
  return (GLboolean)this->_getBufferParameter(GL_BUFFER_MAPPED);
}

/**
 * @brief gets offset of mapped area of buffer
 *
 * @return offset of mapped area of buffer
 */
GLintptr Buffer::getMapOffset()const{
  assert(this!=nullptr);
  return this->_getBufferParameter(GL_BUFFER_MAP_OFFSET);
}

/**
 * @brief gets size of map of buffer
 *
 * @return size of mapped area of buffer
 */
GLsizeiptr Buffer::getMapSize()const{
  assert(this!=nullptr);
  return this->_getBufferParameter(GL_BUFFER_MAP_LENGTH);
}

/**
 * @brief is this buffer immutable
 *
 * @return true if this buffer is immutable
 */
GLboolean Buffer::isImmutable()const{
  assert(this!=nullptr);
  return (GLboolean)this->_getBufferParameter(GL_BUFFER_IMMUTABLE_STORAGE);
}

/**
 * @brief gets map buffer pointer
 *
 * @return pointer to pinned memory
 */
GLvoid*Buffer::getMapPointer()const{
  assert(this!=nullptr);
  return this->_getBufferPointer(GL_BUFFER_MAP_POINTER);
}

