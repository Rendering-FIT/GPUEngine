#include<GPUEngine/geGL/Buffer.h>
#include<GPUEngine/geGL/VertexArray.h>
#include<GPUEngine/geGL/OpenGLUtil.h>
#include<GPUEngine/geCore/ErrorPrinter/ErrorPrinter.h>
#include<cassert>
#include<vector>

using namespace ge::gl;

/**
 * @brief Empty constructor, it sets ID=0
 */
Buffer::Buffer(){
  assert(this!=nullptr);
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
    GLsizeiptr       const&size,
    GLvoid     const*const&data,
    GLbitfield       const&flags){
  assert(this!=nullptr);
  this->alloc(size,data,flags);
}

/**
 * @brief creates new empty buffer
 *
 * @param table opengl function table
 */
Buffer::Buffer(
    FunctionTablePointer const&table):
  OpenGLObject(table)
{
  assert(this!=nullptr);
  this->_id = 0;
}

/**
 * @brief create new buffer
 *
 * @param table opengl function table
 * @param size size of buffer in bytes
 * @param data optional data
 * @param flags optional flags
 */
Buffer::Buffer(
    FunctionTablePointer       const&table,
    GLsizeiptr                 const&size ,
    GLvoid               const*const&data ,
    GLbitfield                 const&flags):
  OpenGLObject(table)
{
  assert(this!=nullptr);
  this->alloc(size,data,flags);
}

/**
 * @brief destructor
 */
Buffer::~Buffer(){
  assert(this!=nullptr);
  this->_gl.glDeleteBuffers(1,&this->_id);
}

/**
 * @brief allocates buffer, this function can only be used on empty buffer
 *
 * @param size size of buffer in bytes
 * @param data optional data
 * @param flags optional flags
 */
void Buffer::alloc(
    GLsizeiptr       const&size,
    GLvoid     const*const&data,
    GLbitfield       const&flags){
  assert(this!=nullptr);
  this->_gl.glCreateBuffers(1,&this->_id);
  this->_bufferData(size,data,flags);
}

/**
 * @brief Binds buffer to specific target
 *
 * @param target target
 */
void Buffer::bind(
    GLenum const&target)const{
  assert(this!=nullptr);
  this->_gl.glBindBuffer(target,this->_id);
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
    GLenum     const&target,
    GLuint     const&index ,
    GLintptr   const&offset,
    GLsizeiptr const&size  )const{
  assert(this!=nullptr);
  this->_gl.glBindBufferRange(target,index,this->_id,offset,size);
}

/**
 * @brief Binds buffer to specific indexed target
 *
 * @param target target
 * @param index index
 */
void Buffer::bindBase(
    GLenum const&target,
    GLuint const&index )const{
  assert(this!=nullptr);
  this->_gl.glBindBufferBase(target,index,this->_id);
}

/**
 * @brief Unbinds buffer from specific target
 *
 * @param target target
 */
void Buffer::unbind(
    GLenum const&target)const{
  assert(this!=nullptr);
  this->_gl.glBindBuffer(target,0);
}

/**
 * @brief Unbinds range of buffer from specific indexed target
 *
 * @param target target
 * @param index  index
 */
void Buffer::unbindRange(
    GLenum const&target,
    GLuint const&index )const{
  assert(this!=nullptr);
  this->_gl.glBindBufferBase(target,index,0);
}

/**
 * @brief Unbinds buffer from specific index target
 *
 * @param target target
 * @param index  index
 */
void Buffer::unbindBase(
    GLenum const&target,
    GLuint const&index )const{
  assert(this!=nullptr);
  this->_gl.glBindBufferBase(target,index,0);
}

/**
 * @brief This function reallocates buffer.
 *
 * @param newSize new size
 * @param flags KEEP_ID|KEEP_DATA
 */
bool Buffer::realloc(
    GLsizeiptr   const&newSize,
    ReallocFlags const&flags  ){
  assert(this!=nullptr);
  if((flags&KEEP_ID)&&this->isImmutable()){
    ge::core::printError(
        GE_CORE_FCENAME,
        "can't sustain buffer id: "+ge::core::value2str(this->getId())+
        ", buffer is immutable",newSize,flags);
    return false;
  }
  GLbitfield bufferFlags=this->getUsage();
  if      (flags==(KEEP_ID|KEEP_DATA)){
    Buffer*temp=new Buffer(newSize,nullptr,bufferFlags);
    assert(temp!=nullptr);
    temp->copy(*this);
    this->_bufferData(newSize,nullptr,bufferFlags);
    this->copy(*temp);
    delete temp;
  }else if(flags==KEEP_ID            ){
    this->_bufferData(newSize,nullptr,bufferFlags);
  }else if(flags==KEEP_DATA          ){
    auto newBuffer = new Buffer(newSize,nullptr,bufferFlags);
    assert(newBuffer!=nullptr);
    newBuffer->copy(*this);
    auto swapId = this->_id;
    this->_id = newBuffer->_id;
    newBuffer->_id = swapId;
    delete newBuffer;
    this->_updateVertexArrays();
  }else if(flags==NEW_BUFFER         ){
    this->_gl.glDeleteBuffers(1,&this->_id);
    this->alloc(newSize,nullptr,bufferFlags);
    this->_updateVertexArrays();
  }else{
    ge::core::printError(
        GE_CORE_FCENAME,
        "invalid buffer reallocation flags: "+
        ge::core::value2str(flags),newSize,flags);
    return false;
  }
  return true;
}

void Buffer::_bufferData(
    GLsizeiptr       const&size,
    GLvoid     const*const&data,
    GLbitfield       const&flags)const{
  assert(this!=nullptr);
  if(ge::gl::areBufferFlagsMutable(flags))
    this->_gl.glNamedBufferData(this->_id,size,data,flags);
  else
    this->_gl.glNamedBufferStorage(this->_id,size,data,flags);
}

void Buffer::_updateVertexArrays(){
  assert(this!=nullptr);
  auto const me = this->shared_from_this();
  for(auto const&vao:this->_vertexArrays){
    if(vao->_elementBuffer == me){
      vao->addElementBuffer(me);
    }
    std::vector<GLuint>attribs;
    GLuint attribId = 0;
    for(auto const&y:vao->_buffers){
      if(y == me)attribs.push_back(attribId);
      attribId++;
    }
    for(auto const&attribIndex:attribs){
      auto                                 type = VertexArray::NONE;
      if(vao->isAttribInteger(attribIndex))type = VertexArray::I   ;
      if(vao->isAttribLong   (attribIndex))type = VertexArray::L   ;
      vao->addAttrib(
          me,
          attribIndex,
          vao->getAttribSize          (attribIndex),
          vao->getAttribType          (attribIndex),
          vao->getAttribStride        (attribIndex),
          vao->getAttribRelativeOffset(attribIndex),
          vao->isAttribNormalized     (attribIndex),
          vao->getAttribDivisor       (attribIndex),
          type);
    }
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
  GLsizeiptr maxSize;
  if(this->getSize()>buffer.getSize())
    maxSize = buffer.getSize();
  else
    maxSize = this->getSize();
  this->_gl.glCopyNamedBufferSubData(buffer._id,this->_id,0,0,maxSize);
}

/**
 * @brief Flushes mapped buffer
 *
 * @param target target
 * @param offset offset into buffer in bytes
 * @param size   length of data in bytes
 */
void Buffer::flushMapped(
    GLsizeiptr const&size  ,
    GLintptr   const&offset)const{
  assert(this!=nullptr);
  if(size==0){
    this->_gl.glFlushMappedNamedBufferRange(this->_id,offset,
        this->getSize());
    return;
  }
  this->_gl.glFlushMappedNamedBufferRange(this->_id,offset,size);
}

/**
 * @brief Invalidates specific region of buffer
 *
 * @param offset offset of region in bytes
 * @param size   length of region in bytes
 */
void Buffer::invalidate(
    GLsizeiptr const&size  ,
    GLintptr   const&offset)const{
  assert(this!=nullptr);
  this->_gl.glInvalidateBufferSubData(this->_id,offset,size);
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
    GLenum       const&internalFormat,
    GLenum       const&format        ,
    GLenum       const&type          ,
    GLvoid const*const&data          )const{
  assert(this!=nullptr);
  this->_gl.glClearNamedBufferData(this->_id,
      internalFormat,format,type,data);
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
    GLenum           const&internalFormat,
    GLintptr         const&offset        ,
    GLsizeiptr       const&size          ,
    GLenum           const&format        ,
    GLenum           const&type          ,
    GLvoid     const*const&data          )const{
  assert(this!=nullptr);
  this->_gl.glClearNamedBufferSubData(this->_id,
      internalFormat,offset,size,format,type,data);
}

/**
 * @brief maps buffer
 *
 * @param access access type
 *
 * @return pointer to pinned memory
 */
GLvoid*Buffer::map(
    GLbitfield const&access)const{
  assert(this!=nullptr);
  GLbitfield a = access;
  if(access==GL_READ_ONLY )a=GL_MAP_READ_BIT ;
  if(access==GL_WRITE_ONLY)a=GL_MAP_WRITE_BIT;
  if(access==GL_READ_WRITE)a=GL_MAP_READ_BIT|GL_MAP_WRITE_BIT;
  return this->_gl.glMapNamedBufferRange(this->_id,0,this->getSize(),a);
}

/**
 * @brief maps buffer
 *
 * @param offset offset in buffer
 * @param size size of mapping
 * @param access acccess type
 *
 * @return pointer to pinned memory
 */
GLvoid*Buffer::map(
    GLintptr   const&offset,
    GLsizeiptr const&size  ,
    GLbitfield const&access)const{
  assert(this!=nullptr);
  return this->_gl.glMapNamedBufferRange(this->_id,offset,size,access);
}

/**
 * @brief unmaps buffer
 */
void Buffer::unmap()const{
  assert(this!=nullptr);
  this->_gl.glUnmapNamedBuffer(this->_id);
}

/**
 * @brief uploads data into buffer
 *
 * @param data data pointer
 * @param size size of data in bytes
 * @param offset offset into buffer
 */
void Buffer::setData(
    GLvoid     const*const&data  ,
    GLsizeiptr       const&size  ,
    GLintptr         const&offset)const{
  assert(this!=nullptr);
  GLsizeiptr s = size;
  if(s==0)s = this->getSize();
  this->_gl.glNamedBufferSubData(this->_id,offset,s,data);
}

/**
 * @brief gets buffer data
 *
 * @param data data pointer
 * @param size size of obtained data in bytes
 * @param offset offset into buffer
 */
void Buffer::getData(
    GLvoid     *const&data,
    GLsizeiptr  const&size,
    GLintptr    const&offset)const{
  assert(this!=nullptr);
  GLsizeiptr s = size;
  if(s==0)s=this->getSize();
  this->_gl.glGetNamedBufferSubData(this->_id,offset,s,data);
}

GLint Buffer::_getBufferParameter(
    GLenum const&pname)const{
  assert(this!=nullptr);
  GLint param;
  this->_gl.glGetNamedBufferParameteriv(this->_id,pname,&param);
  return param;
}

GLvoid*Buffer::_getBufferPointer(
    GLenum const&pname)const{
  assert(this!=nullptr);
  GLvoid *param;
  this->_gl.glGetNamedBufferPointerv(this->_id,pname,&param);
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

