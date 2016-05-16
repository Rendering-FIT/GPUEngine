#include<geGL/BufferObject.h>

using namespace ge::gl;
using namespace ge::gl::opengl;

/**
 * @brief Function translates buffer targets to strings
 *
 * @param target buffer targets
 *
 * @return string representation of target
 */
std::string BufferObject::target2Str(GLenum target){
  switch(target){
    case GL_ARRAY_BUFFER             :return "GL_ARRAY_BUFFER"             ;
    case GL_UNIFORM_BUFFER           :return "GL_UNIFORM_BUFFER"           ;
    case GL_ATOMIC_COUNTER_BUFFER    :return "GL_ATOMIC_COUNTER_BUFFER"    ;
    case GL_QUERY_BUFFER             :return "GL_QUERY_BUFFER"             ;
    case GL_COPY_READ_BUFFER         :return "GL_COPY_READ_BUFFER"         ;
    case GL_COPY_WRITE_BUFFER        :return "GL_COPY_WRITE_BUFFER"        ;
    case GL_DISPATCH_INDIRECT_BUFFER :return "GL_DISPATCH_INDIRECT_BUFFER" ;
    case GL_DRAW_INDIRECT_BUFFER     :return "GL_DRAW_INDIRECT_BUFFER"     ;
    case GL_ELEMENT_ARRAY_BUFFER     :return "GL_ELEMENT_ARRAY_BUFFER"     ;
    case GL_TEXTURE_BUFFER           :return "GL_TEXTURE_BUFFER"           ;
    case GL_PIXEL_PACK_BUFFER        :return "GL_PIXEL_PACK_BUFFER"        ;
    case GL_PIXEL_UNPACK_BUFFER      :return "GL_PIXEL_UNPACK_BUFFER"      ;
    case GL_SHADER_STORAGE_BUFFER    :return "GL_SHADER_STORAGE_BUFFER"    ;
    case GL_TRANSFORM_FEEDBACK_BUFFER:return "GL_TRANSFORM_FEEDBACK_BUFFER";
    default                          :return "unknown"                     ;
  }
}

/**
 * @brief Function translates buffer bindings to strings
 *
 * @param binding buffer binding
 *
 * @return string representation of buffer binding
 */
std::string BufferObject::binding2Str(GLenum binding){
  switch(binding){
    case GL_ARRAY_BUFFER_BINDING             :return "GL_ARRAY_BUFFER_BINDING"             ;
    case GL_UNIFORM_BUFFER_BINDING           :return "GL_UNIFORM_BUFFER_BINDING"           ;
    case GL_ATOMIC_COUNTER_BUFFER_BINDING    :return "GL_ATOMIC_COUNTER_BUFFER_BINDING"    ;
    case GL_QUERY_BUFFER_BINDING             :return "GL_QUERY_BUFFER_BINDING"             ;
    case GL_COPY_READ_BUFFER_BINDING         :return "GL_COPY_READ_BUFFER_BINDING"         ;
    case GL_COPY_WRITE_BUFFER_BINDING        :return "GL_COPY_WRITE_BUFFER_BINDING"        ;
    case GL_DISPATCH_INDIRECT_BUFFER_BINDING :return "GL_DISPATCH_INDIRECT_BUFFER_BINDING" ;
    case GL_DRAW_INDIRECT_BUFFER_BINDING     :return "GL_DRAW_INDIRECT_BUFFER_BINDING"     ;
    case GL_ELEMENT_ARRAY_BUFFER_BINDING     :return "GL_ELEMENT_ARRAY_BUFFER_BINDING"     ;
    case GL_TEXTURE_BUFFER_BINDING           :return "GL_TEXTURE_BUFFER_BINDING"           ;
    case GL_PIXEL_PACK_BUFFER_BINDING        :return "GL_PIXEL_PACK_BUFFER_BINDING"        ;
    case GL_PIXEL_UNPACK_BUFFER_BINDING      :return "GL_PIXEL_UNPACK_BUFFER_BINDING"      ;
    case GL_SHADER_STORAGE_BUFFER_BINDING    :return "GL_SHADER_STORAGE_BUFFER_BINDING"    ;
    case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING:return "GL_TRANSFORM_FEEDBACK_BUFFER_BINDING";
    default                                  :return "unknown"                             ;
  }
}

/**
 * @brief Function converts buffer target to buffer binding
 *
 * @param target buffer target
 *
 * @return buffer bingding for buffer target
 */
GLenum BufferObject::target2Binding(GLenum target){
  switch(target){
    case GL_ARRAY_BUFFER             :return GL_ARRAY_BUFFER_BINDING             ;
    case GL_UNIFORM_BUFFER           :return GL_UNIFORM_BUFFER_BINDING           ;
    case GL_ATOMIC_COUNTER_BUFFER    :return GL_ATOMIC_COUNTER_BUFFER_BINDING    ;
    case GL_QUERY_BUFFER             :return GL_QUERY_BUFFER_BINDING             ;
    case GL_COPY_READ_BUFFER         :return GL_COPY_READ_BUFFER_BINDING         ;
    case GL_COPY_WRITE_BUFFER        :return GL_COPY_WRITE_BUFFER_BINDING        ;
    case GL_DISPATCH_INDIRECT_BUFFER :return GL_DISPATCH_INDIRECT_BUFFER_BINDING ;
    case GL_DRAW_INDIRECT_BUFFER     :return GL_DRAW_INDIRECT_BUFFER_BINDING     ;
    case GL_ELEMENT_ARRAY_BUFFER     :return GL_ELEMENT_ARRAY_BUFFER_BINDING     ;
    case GL_TEXTURE_BUFFER           :return GL_TEXTURE_BUFFER_BINDING           ;
    case GL_PIXEL_PACK_BUFFER        :return GL_PIXEL_PACK_BUFFER_BINDING        ;
    case GL_PIXEL_UNPACK_BUFFER      :return GL_PIXEL_UNPACK_BUFFER_BINDING      ;
    case GL_SHADER_STORAGE_BUFFER    :return GL_SHADER_STORAGE_BUFFER_BINDING    ;
    case GL_TRANSFORM_FEEDBACK_BUFFER:return GL_TRANSFORM_FEEDBACK_BUFFER_BINDING;
    default                          :return 0                                   ;
  }
}

/**
 * @brief Function convertes buffer binding to buffer target
 *
 * @param binding buffer binding
 *
 * @return buffer target of buffer binding
 */
GLenum BufferObject::binding2Target(GLenum binding){
  switch(binding){
    case GL_ARRAY_BUFFER_BINDING             :return GL_ARRAY_BUFFER             ;
    case GL_UNIFORM_BUFFER_BINDING           :return GL_UNIFORM_BUFFER           ;
    case GL_ATOMIC_COUNTER_BUFFER_BINDING    :return GL_ATOMIC_COUNTER_BUFFER    ;
    case GL_QUERY_BUFFER_BINDING             :return GL_QUERY_BUFFER             ;
    case GL_COPY_READ_BUFFER_BINDING         :return GL_COPY_READ_BUFFER         ;
    case GL_COPY_WRITE_BUFFER_BINDING        :return GL_COPY_WRITE_BUFFER        ;
    case GL_DISPATCH_INDIRECT_BUFFER_BINDING :return GL_DISPATCH_INDIRECT_BUFFER ;
    case GL_DRAW_INDIRECT_BUFFER_BINDING     :return GL_DRAW_INDIRECT_BUFFER     ;
    case GL_ELEMENT_ARRAY_BUFFER_BINDING     :return GL_ELEMENT_ARRAY_BUFFER     ;
    case GL_TEXTURE_BUFFER_BINDING           :return GL_TEXTURE_BUFFER           ;
    case GL_PIXEL_PACK_BUFFER_BINDING        :return GL_PIXEL_PACK_BUFFER        ;
    case GL_PIXEL_UNPACK_BUFFER_BINDING      :return GL_PIXEL_UNPACK_BUFFER      ;
    case GL_SHADER_STORAGE_BUFFER_BINDING    :return GL_SHADER_STORAGE_BUFFER    ;
    case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING:return GL_TRANSFORM_FEEDBACK_BUFFER;
    default                                  :return 0                           ;
  }
}

/**
 * @brief detetermines if flags are mutable
 *
 * @param flags flags
 *
 * @return true if flags are combination of GL_{STATIC|STREAM|DYNAMIC}_{DRAW_COPY_READ}
 */
bool BufferObject::areFlagsMutable(GLbitfield flags){
  return 
    flags == GL_STATIC_DRAW ||
    flags == GL_STATIC_COPY ||
    flags == GL_STATIC_READ ||
    flags == GL_STREAM_DRAW ||
    flags == GL_STREAM_COPY ||
    flags == GL_STREAM_READ ||
    flags == GL_DYNAMIC_DRAW||
    flags == GL_DYNAMIC_COPY||
    flags == GL_DYNAMIC_READ;
}

/**
 * @brief Empty constructor, it sets ID=0
 */
BufferObject::BufferObject(){
  this->_id = 0;
}

/**
 * @brief Constructor
 *
 * @param size size of buffer in bytes
 * @param data optional pointer to data data
 * @param flags optional flags, right flags can make buffer immutable
 */
BufferObject::BufferObject(
    GLsizeiptr    size,
    const GLvoid *data,
    GLbitfield    flags){
  this->alloc(size,data,flags);
}

#if defined(REPLACE_GLEW)
BufferObject::BufferObject(FunctionTablePointer const&table):OpenGLObject(table){
  this->_id = 0;
}

BufferObject::BufferObject(
    FunctionTablePointer const&table,
    GLsizeiptr    size ,
    const GLvoid* data ,
    GLbitfield    flags):OpenGLObject(table){
  this->alloc(size,data,flags);
}
#endif


BufferObject::~BufferObject(){
  glDeleteBuffers(1,&this->_id);
}

void BufferObject::_bufferData(GLsizeiptr size,const GLvoid*data,GLbitfield flags)const{
  if(BufferObject::areFlagsMutable(flags))
    glNamedBufferData(this->_id,size,data,flags);
  else
    glNamedBufferStorage(this->_id,size,data,flags);
}

void BufferObject::alloc(
    GLsizeiptr    size,
    const GLvoid *data,
    GLbitfield    flags){
  glCreateBuffers(1,&this->_id);
  this->_bufferData(size,data,flags);
}

/**
 * @brief Binds buffer to specific target
 *
 * @param target target
 */
void BufferObject::bind(
    GLenum target)const{
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
void BufferObject::bindRange(
    GLenum     target,
    GLuint     index,
    GLintptr   offset,
    GLsizeiptr size)const{
  glBindBufferRange(target,index,this->_id,offset,size);
}

/**
 * @brief Binds buffer to specific indexed target
 *
 * @param target target
 * @param index index
 */
void BufferObject::bindBase(GLenum target,GLuint index)const{
  glBindBufferBase(target,index,this->_id);
}

/**
 * @brief Unbinds buffer from specific target
 *
 * @param target target
 */
void BufferObject::unbind(GLenum target)const{
  glBindBuffer(target,0);
}

/**
 * @brief Unbinds range of buffer from specific indexed target
 *
 * @param target target
 * @param index  index
 */
void BufferObject::unbindRange(GLenum target,GLuint index)const{
  glBindBufferBase(target,index,0);
}

/**
 * @brief Unbinds buffer from specific index target
 *
 * @param target target
 * @param index  index
 */
void BufferObject::unbindBase(GLenum target,GLuint index)const{
  glBindBufferBase(target,index,0);
}

/**
 * @brief Reallocates buffer
 *
 * @param newSize new size
 * @param flags KEEP_ID|KEEP_DATA
 */
void BufferObject::realloc(GLsizeiptr newSize,ReallocFlags flags){
  if((flags&KEEP_ID)&&this->isImmutable()){
    std::cerr<<"ERROR: can't sustain buffer id: "<<this->getId()<<", buffer is immutable"<<std::endl;
    return;
  }
  GLbitfield bufferFlags=this->getUsage();
  if      (flags==(KEEP_ID|KEEP_DATA)){
    BufferObject*temp=new BufferObject(newSize,nullptr,bufferFlags);
    temp->copy(this);
    this->_bufferData(newSize,nullptr,bufferFlags);
    this->copy(temp);
    delete temp;
  }else if(flags==KEEP_ID            ){
    this->_bufferData(newSize,nullptr,bufferFlags);
  }else if(flags==KEEP_DATA          ){
    BufferObject*newBuffer=new BufferObject(newSize,nullptr,bufferFlags);
    newBuffer->copy(this);
    this->~BufferObject();
    this->_id = newBuffer->_id;
    delete(char*)newBuffer;
  }else if(flags==NEW_BUFFER         ){
    this->~BufferObject();
    new(this)BufferObject(newSize,nullptr,bufferFlags);
  }else
    std::cerr<<"ERROR: invalid buffer reallocation flags: "<<flags<<std::endl;
}


/**
 * @brief Copies data from another buffer into this buffer
 *
 * @param buffer another buffer
 */
void BufferObject::copy(
    BufferObject*buffer)const{
  GLsizeiptr maxSize=(this->getSize()>buffer->getSize())?buffer->getSize():this->getSize();
  glCopyNamedBufferSubData(buffer->_id,this->_id,0,0,maxSize);
}

/**
 * @brief Flushes mapped buffer
 *
 * @param target target
 * @param offset offset into buffer in bytes
 * @param size   length of data in bytes
 */
void BufferObject::flushMapped(GLsizeiptr size,GLintptr offset)const{
  if(size==0)size=this->getSize();
  glFlushMappedNamedBufferRange(this->_id,offset,size);
}

/**
 * @brief Invalidates specific region of buffer
 *
 * @param offset offset of region in bytes
 * @param size   length of region in bytes
 */
void BufferObject::invalidate(GLsizeiptr size,GLintptr offset)const{
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
void BufferObject::clear(
    GLenum        internalFormat,
    GLenum        format,
    GLenum        type,
    const GLvoid *data)const{
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
void BufferObject::clear(
    GLenum        internalFormat,
    GLintptr      offset,
    GLsizeiptr    size,
    GLenum        format,
    GLenum        type,
    const GLvoid *data)const{
  glClearNamedBufferSubData(this->_id,internalFormat,offset,size,format,type,data);
}

GLvoid*BufferObject::map(
    GLbitfield access)const{
  if(access==GL_READ_ONLY )access=GL_MAP_READ_BIT ;
  if(access==GL_WRITE_ONLY)access=GL_MAP_WRITE_BIT;
  if(access==GL_READ_WRITE)access=GL_MAP_READ_BIT|GL_MAP_WRITE_BIT;
  return glMapNamedBufferRange(this->_id,0,this->getSize(),access);
}

GLvoid*BufferObject::map(
    GLintptr   offset,
    GLsizeiptr size,
    GLbitfield access)const{
  return glMapNamedBufferRange(this->_id,offset,size,access);
}

void BufferObject::unmap()const{
  glUnmapNamedBuffer(this->_id);
}

void BufferObject::setData(
    const GLvoid* data  ,
    GLsizeiptr    size  ,
    GLintptr      offset)const{
  if(size==0)size=this->getSize();
  glNamedBufferSubData(this->_id,offset,size,data);
}

void BufferObject::getData(
    GLvoid     *data,
    GLsizeiptr  size,
    GLintptr    offset)const{
  if(size==0)size=this->getSize();
  glGetNamedBufferSubData(this->_id,offset,size,data);
}

GLint BufferObject::_getBufferParameter(GLenum pname)const{
  GLint param;
  glGetNamedBufferParameteriv(this->_id,pname,&param);
  return param;
}

GLvoid*BufferObject::_getBufferPointer(GLenum pname)const{
  GLvoid *param;
  glGetNamedBufferPointerv(this->_id,pname,&param);
  return param;
}

/**
 * @brief gets size of this buffer
 *
 * @return size of thie buffer in bytes
 */
GLsizeiptr BufferObject::getSize()const{
  return this->_getBufferParameter(GL_BUFFER_SIZE);
}

/**
 * @brief gets usage of this buffer
 *
 * @return usage (GL_BUFFER_USAGE)
 */
GLenum BufferObject::getUsage()const{
  return this->_getBufferParameter(GL_BUFFER_USAGE);
}

/**
 * @brief gets access of thie buffer
 *
 * @return access (GL_BUFFER_ACCESS)
 */
GLbitfield BufferObject::getAccess()const{
  return this->_getBufferParameter(GL_BUFFER_ACCESS);
}

/**
 * @brief gets access flags of this buffer
 *
 * @return access flags (GL_BUFFER_ACCESS_FLAGS)
 */
GLbitfield BufferObject::getAccessFlags()const{
  return this->_getBufferParameter(GL_BUFFER_ACCESS_FLAGS);
}

/**
 * @brief is this buffer mapped
 *
 * @return true if this buffer is mapped
 */
GLboolean BufferObject::isMapped()const{
  return (GLboolean)this->_getBufferParameter(GL_BUFFER_MAPPED);
}

/**
 * @brief gets offset of mapped area of buffer
 *
 * @return offset of mapped area of buffer
 */
GLintptr BufferObject::getMapOffset()const{
  return this->_getBufferParameter(GL_BUFFER_MAP_OFFSET);
}

/**
 * @brief gets size of map of buffer
 *
 * @return size of mapped area of buffer
 */
GLsizeiptr BufferObject::getMapSize()const{
  return this->_getBufferParameter(GL_BUFFER_MAP_LENGTH);
}

/**
 * @brief is thie buffer immutable
 *
 * @return true if this buffer is immutable
 */
GLboolean BufferObject::isImmutable()const{
  return (GLboolean)this->_getBufferParameter(GL_BUFFER_IMMUTABLE_STORAGE);
}

/**
 * @brief gets map buffer pointer
 *
 * @return pointer to pinned memory
 */
GLvoid*BufferObject::getMapPointer()const{
  return this->_getBufferPointer(GL_BUFFER_MAP_POINTER);
}

