#include <geGL/BufferObject.h>

//toggle usage of direct state access
//#define USE_DSA
//toggle saving previous bindings
#define SAVE_PREVIOUS_BINDING

//TODO remove after glew fix
#ifndef GL_COPY_READ_BUFFER_BINDING
#define GL_COPY_READ_BUFFER_BINDING 0x8F36
#endif//GL_COPY_READ_BUFFER_BINDING

#ifndef GL_COPY_WRITE_BUFFER_BINDING
#define GL_COPY_WRITE_BUFFER_BINDING 0x8F37
#endif//GL_COPY_WRITE_BUFFER_BINDING

using namespace ge::gl;

/**
 * @brief Function translates buffer targets to strings
 *
 * @param target buffer targets
 *
 * @return string representation of target
 */
std::string ge::gl::translateBufferTarget(GLenum target){
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
std::string ge::gl::translateBufferBinding(GLenum binding){
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
GLenum ge::gl::bufferTarget2Binding(GLenum target){
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
GLenum ge::gl::bufferBinding2Target(GLenum binding){
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

BufferObject::BufferObject(
    GLsizeiptr    size,
    const GLvoid *data,
    GLbitfield    flags){
#ifndef USE_DSA
  glGenBuffers(1,&this->_id);

#ifdef  SAVE_PREVIOUS_BINDING
  GLuint oldId;
  glGetIntegerv(bufferTarget2Binding(BUFFEROBJECT_DEFAULT_OPERTARGET),(GLint*)&oldId);
#endif//SAVE_PREVIOUS_BINDING

  glBindBuffer(BUFFEROBJECT_DEFAULT_OPERTARGET,this->_id);
  if(
      flags == GL_STATIC_DRAW ||
      flags == GL_STATIC_COPY ||
      flags == GL_STATIC_READ ||
      flags == GL_STREAM_DRAW ||
      flags == GL_STREAM_COPY ||
      flags == GL_STREAM_READ ||
      flags == GL_DYNAMIC_DRAW||
      flags == GL_DYNAMIC_COPY||
      flags == GL_DYNAMIC_READ)
    glBufferData(BUFFEROBJECT_DEFAULT_OPERTARGET,size,data,flags);
  else
    glBufferStorage(BUFFEROBJECT_DEFAULT_OPERTARGET,size,data,flags);

#ifdef  SAVE_PREVIOUS_BINDING
  glBindBuffer(BUFFEROBJECT_DEFAULT_OPERTARGET,oldId);
#endif//SAVE_PREVIOUS_BINDING

#else //USE_DSA
  glCreateBuffers(1,&this->_id);
  if(
      flags == GL_STATIC_DRAW ||
      flags == GL_STATIC_COPY ||
      flags == GL_STATIC_READ ||
      flags == GL_STREAM_DRAW ||
      flags == GL_STREAM_COPY ||
      flags == GL_STREAM_READ ||
      flags == GL_DYNAMIC_DRAW||
      flags == GL_DYNAMIC_COPY||
      flags == GL_DYNAMIC_READ)
    glNamedBufferData(this->_id,size,data,flags);
  else
    glNamedBufferStorage(this->_id,size,data,flags);
#endif//USE_DSA
}
BufferObject::~BufferObject(){
  glDeleteBuffers(1,&this->_id);
}

/**
 * @brief Binds buffer to specific target
 *
 * @param target target
 */
void BufferObject::bind(
    GLenum target){
  //we just bind buffer object to another binding point
  //original binding point stays the same
  glBindBuffer(
      target,
      this->_id);
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
    GLsizeiptr size){
  //we just bind buffer object to another binding point
  //original binding point stays the same
  glBindBufferRange(
      target,
      index,
      this->_id,
      offset,
      size);
}
/**
 * @brief Binds buffer to specific indexed target
 *
 * @param target target
 * @param index index
 */
void BufferObject::bindBase(
    GLenum target,
    GLuint index){
  glBindBufferBase(
      target,
      index,
      this->_id);
}
/**
 * @brief Unbinds buffer from specific target
 *
 * @param target target
 */
void BufferObject::unbind(
    GLenum target){
  glBindBuffer(
      target,
      BUFFEROBJECT_DEFAULT_EMPTY_TARGET);
}
/**
 * @brief Unbinds range of buffer from specific indexed target
 *
 * @param target target
 * @param index  index
 */
void BufferObject::unbindRange(
    GLenum target,
    GLuint index){
  glBindBufferBase(//NOTE: unbind whole buffer
      target,
      index,
      BUFFEROBJECT_DEFAULT_EMPTY_TARGET);
}
/**
 * @brief Unbinds buffer from specific index target
 *
 * @param target target
 * @param index  index
 */
void BufferObject::unbindBase(
    GLenum target,
    GLuint index){
  glBindBufferBase(
      target,
      index,
      BUFFEROBJECT_DEFAULT_EMPTY_TARGET);
}
/**
 * @brief Copies data from another buffer into this buffer
 *
 * @param buffer another buffer
 */
void BufferObject::copy(
    BufferObject*buffer){
  //compute size
  GLsizeiptr maxSize=(this->getSize()>buffer->getSize())?buffer->getSize():this->getSize();
#ifndef USE_DSA

#ifdef  SAVE_PREVIOUS_BINDING
  GLuint oldReadId;
  glGetIntegerv(bufferTarget2Binding(BUFFEROBJECT_DEFAULT_READBUFFER),(GLint*)&oldReadId);
  GLuint oldWriteId;
  glGetIntegerv(bufferTarget2Binding(BUFFEROBJECT_DEFAULT_WRITEBUFFER),(GLint*)&oldWriteId);
#endif//SAVE_PREVIOUS_BINDING

  //bind buffers
  glBindBuffer(BUFFEROBJECT_DEFAULT_READBUFFER ,buffer->_id);
  glBindBuffer(BUFFEROBJECT_DEFAULT_WRITEBUFFER,this  ->_id);
  //copy buffer
  glCopyBufferSubData(
      BUFFEROBJECT_DEFAULT_READBUFFER,
      BUFFEROBJECT_DEFAULT_WRITEBUFFER,
      BUFFEROBJECT_DEFAULT_READOFFSET,
      BUFFEROBJECT_DEFAULT_WRITEOFFSET,
      maxSize);
#ifdef  SAVE_PREVIOUS_BINDING
  //unbind buffers
  glBindBuffer(BUFFEROBJECT_DEFAULT_READBUFFER ,oldReadId);
  glBindBuffer(BUFFEROBJECT_DEFAULT_WRITEBUFFER,oldWriteId);
#endif//SAVE_PREVIOUS_BINDING

#else //USE_DSA
  glCopyNamedBufferSubData(
      buffer->_id,
      this->_id,
      BUFFEROBJECT_DEFAULT_READOFFSET,
      BUFFEROBJECT_DEFAULT_WRITEOFFSET,
      maxSize);
#endif//USE_DSA
}
/**
 * @brief Copies data from another buffer into this buffer
 *
 * @param buffer another buffer
 */
void BufferObject::operator &=(
    BufferObject*buffer){
  this->copy(buffer);
}
/**
 * @brief Flushes mapped buffer
 *
 * @param target target
 * @param offset offset into buffer in bytes
 * @param size   length of data in bytes
 */
void BufferObject::flushMapped(
    GLsizeiptr size,
    GLintptr   offset){
  if(size==BUFFEROBJECT_DEFAULT_SIZE)
    size=this->getSize();
#ifndef USE_DSA

#ifdef  SAVE_PREVIOUS_BINDING
  GLuint oldId;
  glGetIntegerv(bufferTarget2Binding(BUFFEROBJECT_DEFAULT_OPERTARGET),(GLint*)&oldId);
#endif//SAVE_PREVIOUS_BINDING

  glBindBuffer(BUFFEROBJECT_DEFAULT_OPERTARGET,this->_id);
  glFlushMappedBufferRange(BUFFEROBJECT_DEFAULT_OPERTARGET,offset,size);

#ifdef  SAVE_PREVIOUS_BINDING
  glBindBuffer(BUFFEROBJECT_DEFAULT_OPERTARGET,oldId);
#endif//SAVE_PREVIOUS_BINDING

#else //USE_DSA
  glFlushMappedNamedBufferRange(this->_id,offset,size);
#endif//USE_DSA
}
/**
 * @brief Invalidates specific region of buffer
 *
 * @param offset offset of region in bytes
 * @param size   length of region in bytes
 */
void BufferObject::invalidate(
    GLsizeiptr size,
    GLintptr offset){
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
    const GLvoid *data){
#ifndef USE_DSA

#ifdef  SAVE_PREVIOUS_BINDING
  GLuint oldId;
  glGetIntegerv(bufferTarget2Binding(BUFFEROBJECT_DEFAULT_OPERTARGET),(GLint*)&oldId);
#endif//SAVE_PREVIOUS_BINDING

  glBindBuffer     (BUFFEROBJECT_DEFAULT_OPERTARGET,this->_id);
  glClearBufferData(BUFFEROBJECT_DEFAULT_OPERTARGET,internalFormat,format,type,data);

#ifdef  SAVE_PREVIOUS_BINDING
  glBindBuffer     (BUFFEROBJECT_DEFAULT_OPERTARGET,oldId);
#endif//SAVE_PREVIOUS_BINDING

#else //USE_DSA
  glClearNamedBufferData(this->_id,internalFormat,format,type,data);
#endif//USE_DSA
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
    const GLvoid *data){
#ifndef USE_DSA

#ifdef  SAVE_PREVIOUS_BINDING
  GLuint oldId;
  glGetIntegerv(bufferTarget2Binding(BUFFEROBJECT_DEFAULT_OPERTARGET),(GLint*)&oldId);
#endif//SAVE_PREVIOUS_BINDING

  glBindBuffer        (BUFFEROBJECT_DEFAULT_OPERTARGET,this->_id);
  glClearBufferSubData(BUFFEROBJECT_DEFAULT_OPERTARGET,internalFormat,offset,size,format,type,data);

#ifdef  SAVE_PREVIOUS_BINDING
  glBindBuffer        (BUFFEROBJECT_DEFAULT_OPERTARGET,oldId);//unbin buffer
#endif//SAVE_PREVIOUS_BINDING

#else //USE_DSA
  glClearNamedBufferSubData(this->_id,internalFormat,offset,size,format,type,data);
#endif//USE_DSA
}
void*BufferObject::map(
    GLbitfield access){
  void*ptr;
  if(access==GL_READ_ONLY )access=GL_MAP_READ_BIT ;
  if(access==GL_WRITE_ONLY)access=GL_MAP_WRITE_BIT;
  if(access==GL_READ_ONLY )access=GL_MAP_READ_BIT|GL_MAP_WRITE_BIT;
#ifndef USE_DSA

#ifdef  SAVE_PREVIOUS_BINDING
  GLuint oldId;
  glGetIntegerv(bufferTarget2Binding(BUFFEROBJECT_DEFAULT_OPERTARGET),(GLint*)&oldId);
#endif//SAVE_PREVIOUS_BINDING

  glBindBuffer        (BUFFEROBJECT_DEFAULT_OPERTARGET,this->_id);
  ptr=glMapBufferRange(BUFFEROBJECT_DEFAULT_OPERTARGET,BUFFEROBJECT_DEFAULT_MAPOFFSET,this->getSize(),access);

#ifdef  SAVE_PREVIOUS_BINDING
  glBindBuffer        (BUFFEROBJECT_DEFAULT_OPERTARGET,oldId);//unbin buffer
#endif//SAVE_PREVIOUS_BINDING

#else //USE_DSA
  ptr=glMapNamedBuffer(this->_id,access);
#endif//USE_DSA
  return ptr;
}
void*BufferObject::map(
    GLintptr   offset,
    GLsizeiptr size,
    GLbitfield access){
  void*ptr;
#ifndef USE_DSA

#ifdef  SAVE_PREVIOUS_BINDING
  GLuint oldId;
  glGetIntegerv(bufferTarget2Binding(BUFFEROBJECT_DEFAULT_OPERTARGET),(GLint*)&oldId);
#endif//SAVE_PREVIOUS_BINDING

  glBindBuffer        (BUFFEROBJECT_DEFAULT_OPERTARGET,this->_id);
  ptr=glMapBufferRange(BUFFEROBJECT_DEFAULT_OPERTARGET,offset,size,access);

#ifdef  SAVE_PREVIOUS_BINDING
  glBindBuffer        (BUFFEROBJECT_DEFAULT_OPERTARGET,oldId);//unbin buffer
#endif//SAVE_PREVIOUS_BINDING

#else //USE_DSA
  ptr=glMapNamedBufferRange(this->_id,offset,size,access);
#endif//USE_DSA
  return ptr;
}

void BufferObject::unmap(){
#ifndef USE_DSA

#ifdef  SAVE_PREVIOUS_BINDING
  GLuint oldId;
  glGetIntegerv(bufferTarget2Binding(BUFFEROBJECT_DEFAULT_OPERTARGET),(GLint*)&oldId);
#endif//SAVE_PREVIOUS_BINDING

  glBindBuffer (BUFFEROBJECT_DEFAULT_OPERTARGET,this->_id);
  glUnmapBuffer(BUFFEROBJECT_DEFAULT_OPERTARGET);

#ifdef  SAVE_PREVIOUS_BINDING
  glBindBuffer (BUFFEROBJECT_DEFAULT_OPERTARGET,oldId);//unbin buffer
#endif//SAVE_PREVIOUS_BINDING

#else //USE_DSA
  glUnmapNamedBuffer(this->_id);
#endif//USE_DSA
}

void BufferObject::setData(
    GLvoid     *data,
    GLsizeiptr  size,
    GLintptr    offset){
  if(size==BUFFEROBJECT_DEFAULT_SIZE)
    size=this->getSize();
#ifndef USE_DSA

#ifdef  SAVE_PREVIOUS_BINDING
  GLuint oldId;
  glGetIntegerv(bufferTarget2Binding(BUFFEROBJECT_DEFAULT_OPERTARGET),(GLint*)&oldId);
#endif//SAVE_PREVIOUS_BINDING

  glBindBuffer   (BUFFEROBJECT_DEFAULT_OPERTARGET,this->_id);//bind buffer
  glBufferSubData(BUFFEROBJECT_DEFAULT_OPERTARGET,offset,size,data);//copy data

#ifdef  SAVE_PREVIOUS_BINDING
  glBindBuffer   (BUFFEROBJECT_DEFAULT_OPERTARGET,oldId);//unbin buffer
#endif//SAVE_PREVIOUS_BINDING

#else //USE_DSA
  glNamedBufferSubData(this->_id,offset,size,data);
#endif//USE_DSA

}
void BufferObject::getData(
    GLvoid     *data,
    GLsizeiptr  size,
    GLintptr    offset){
  if(size==BUFFEROBJECT_DEFAULT_SIZE)
    size=this->getSize();
#ifndef USE_DSA

#ifdef  SAVE_PREVIOUS_BINDING
  GLuint oldId;
  glGetIntegerv(bufferTarget2Binding(BUFFEROBJECT_DEFAULT_OPERTARGET),(GLint*)&oldId);
#endif//SAVE_PREVIOUS_BINDING

  glBindBuffer      (BUFFEROBJECT_DEFAULT_OPERTARGET,this->_id);//bind buffer
  glGetBufferSubData(BUFFEROBJECT_DEFAULT_OPERTARGET,offset,size,data);//obtain data

#ifdef  SAVE_PREVIOUS_BINDING
  glBindBuffer      (BUFFEROBJECT_DEFAULT_OPERTARGET,oldId);//unbin buffer
#endif//SAVE_PREVIOUS_BINDING

#else //USE_DSA
  glGetNamedBufferSubData(this->_id,offset,size,data);
#endif//USE_DSA
}
GLint BufferObject::_getBufferParameter(GLenum pname){
  GLint param;
#ifndef USE_DSA

#ifdef  SAVE_PREVIOUS_BINDING
  GLuint oldId;
  glGetIntegerv(bufferTarget2Binding(BUFFEROBJECT_DEFAULT_OPERTARGET),(GLint*)&oldId);
#endif//SAVE_PREVIOUS_BINDING

  glBindBuffer          (BUFFEROBJECT_DEFAULT_OPERTARGET,this->_id);
  glGetBufferParameteriv(BUFFEROBJECT_DEFAULT_OPERTARGET,pname,&param);

#ifdef  SAVE_PREVIOUS_BINDING
  glBindBuffer          (BUFFEROBJECT_DEFAULT_OPERTARGET,oldId);
#endif//SAVE_PREVIOUS_BINDING

#else //USE_DSA
  glGetNamedBufferParameteriv(this->_id,pname,&param);
#endif//USE_DSA
  return param;
}
GLsizeiptr BufferObject::getSize(){
  return this->_getBufferParameter(GL_BUFFER_SIZE);
}
GLuint BufferObject::getId(){
  return this->_id;
}
GLenum BufferObject::getUsage(){
  return this->_getBufferParameter(GL_BUFFER_USAGE);
}
GLenum BufferObject::getAccess(){
  return this->_getBufferParameter(GL_BUFFER_ACCESS);
}
GLbitfield BufferObject::getAccessFlags(){
  return this->_getBufferParameter(GL_BUFFER_ACCESS_FLAGS);
}
GLboolean BufferObject::isMapped(){
  return this->_getBufferParameter(GL_BUFFER_MAPPED);
}
GLintptr BufferObject::getMapOffset(){
  return this->_getBufferParameter(GL_BUFFER_MAP_OFFSET);
}
GLsizeiptr BufferObject::getMapSize(){
  return this->_getBufferParameter(GL_BUFFER_MAP_LENGTH);
}
GLboolean BufferObject::isImmutable(){
  return this->_getBufferParameter(GL_BUFFER_IMMUTABLE_STORAGE);
}

