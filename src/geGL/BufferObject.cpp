#include <geGL/BufferObject.h>

#include <cstring>
//#include <malloc.h>

//#define USE_DSA

ge::gl::BufferObject::BufferObject()
   //: Object()
   : _mutable(BUFFEROBJECT_DEFAULT_MUTABLE)
   , _data   (BUFFEROBJECT_DEFAULT_DATA   )
   , _id     (BUFFEROBJECT_DEFAULT_ID     )
   , _target (BUFFEROBJECT_DEFAULT_TARGET )
   , _size   (BUFFEROBJECT_DEFAULT_SIZE   )
   , _usage  (BUFFEROBJECT_DEFAULT_USAGE  )
   , _flags  (BUFFEROBJECT_DEFAULT_FLAGS  )
{

}

/**
 * Copy constructor, doing only a shallow copy of the data.
 */
ge::gl::BufferObject::BufferObject( const BufferObject& buf/*, const ge::core::CopyOp& copyop /*= ge::core::CopyOp::SHALLOW_COPY*/ )
   //: Object(buf, copyop)
   : _mutable     (buf._mutable     )
   , _data        (buf._data        )
   , _id(buf._id)
   , _target      (buf._target      )
   , _size        (buf._size        )
   , _usage       (buf._usage       )
   , _flags       (buf._flags       )
{

}


ge::gl::BufferObject::~BufferObject()
{
   if(isMapped()) _data = BUFFEROBJECT_DEFAULT_DATA;
   //FIXME shouldn't we unmap buffer using glUnmapBuffer?
   deleteGLObject();
   this->freeClientSideBuffer();
}

/**
 * Allocates client-side buffer. Don't call this method if 
 * the buffer is mapped, because the same pointer is used.
 */
void ge::gl::BufferObject::allocateClientSideBuffer( GLsizeiptr size, void* dataSource/* = NULL*/ )
{
   //_data = malloc(size);
   _data = new char[size];
   if (!_data)
   {
      //make fuss
      return;
   }
   if (dataSource)
   {
      memcpy(_data, dataSource, size);
   }
   _size = size;
}

/**
 * Frees client-side buffer. Don't use if the buffer is mapped.
 */
void ge::gl::BufferObject::freeClientSideBuffer()
{
   //not checking if gl is mapped (waste of time)
   if(_data != BUFFEROBJECT_DEFAULT_DATA) delete[](char*)(_data);
   this->_data = BUFFEROBJECT_DEFAULT_DATA;
}

/**
 * Inits the OpenGL Buffer Object and uses internal client-side buffer to initialize it.
 * The allocateClientSideBuffer() should be called before.
 *
 * @param mutable_ Controls if the OGL BO is mutable (BufferData) or immutable (BufferStorage).
 */
void ge::gl::BufferObject::createAndInitGLBO( GLenum target, GLenum usage /*= GL_STATIC_DRAW*/, bool mutable_ /*= true*/, GLbitfield flags /*= 0*/ )
{
   if((!_mutable && _id) || (_size <= 0) )
   {
      //make some fuss
      return;
   }
   _target = target;
   _usage = usage;
   _mutable = mutable_;
   _flags = flags;

   if(!_id)
      glGenBuffers(BUFFEROBJECT_DEFAULT_NOF_BUFFERS, &_id);
   if(!_id)
   {
      //make fuss
      return;
   }

   if(_mutable)
   {
      glNamedBufferDataEXT(_id, _size, _data, _usage);
   }
   else
   {
      glNamedBufferStorageEXT(_id, _size, _data, _flags);
   }
}

/**
 * Inits the OpenGL Buffer Object with supplied data. This does NOT allocate the internal
 * client-side buffer (_data). This method can be used for preparing the buffer for mapping.
 *
 * @param mutable_ Controls if the OGL BO is mutable (BufferData) or immutable (BufferStorage).
 */
void ge::gl::BufferObject::createAndInitGLBO( GLenum target, GLsizeiptr size, GLenum usage /*= GL_STATIC_DRAW*/, void* data/* = NULL*/, bool mutable_ /*= true*/, GLbitfield flags/* = 0*/ )
{
   if(!_mutable && _id)
   {
      //make some fuss
      return;
   }
   _target = target;
   _size = size;
   _usage = usage;
   _mutable = mutable_;
   _flags = flags;

   if(!_id)
      glGenBuffers(BUFFEROBJECT_DEFAULT_NOF_BUFFERS, &_id);
   if(!_id)
   {
      //make fuss
      return;
   }

   if(_mutable)
   {
      glNamedBufferDataEXT(_id, _size, data, _usage);
   }
   else
   {
      glNamedBufferStorageEXT(_id, _size, data, _flags);
   }
}

/**
 * Calls the glDeleteBuffer and sets _id member to 0.
 */
void ge::gl::BufferObject::deleteGLObject()
{
   glDeleteBuffers(BUFFEROBJECT_DEFAULT_NOF_BUFFERS, &_id);
   _id = BUFFEROBJECT_DEFAULT_ID;
}

/**
 * Maps the buffer to it's internal _data member. If client-side buffer has been allocated, the
 * user is responsible for deallocation prior to calling this function.
 */
void ge::gl::BufferObject::map( GLintptr offset /*= 0*/, GLsizeiptr size /*= 0*/, GLenum mapFlags /*= 0*/ )
{
   //if(_data)
      //should be NULL
   _data = glMapNamedBufferRangeEXT(
         _id, 
         offset, 
         size     == BUFFEROBJECT_DEFAULT_SIZE     ? _size  : size, 
         mapFlags == BUFFEROBJECT_DEFAULT_MAPFLAGS ? _flags : mapFlags);
}

/**
 * Unmaps the buffer and sets _data to NULL.
 */
void ge::gl::BufferObject::unmap()
{
   glUnmapNamedBufferEXT(_id);
   _data = BUFFEROBJECT_DEFAULT_DATA;
}

/**
 * Asks OGL if the buffer is mapped.
 */
GLboolean ge::gl::BufferObject::isMapped()
{
   GLboolean ret;
   glGetBooleanv(GL_BUFFER_MAPPED, &ret);
   return ret;
}

/**
 * Binds the buffer.
 */
void ge::gl::BufferObject::bind()
{
   glBindBuffer(_target, _id);
}

/**
 * Unbinds the target. Note that this calls glBindBuffer(_target, 0) so it will effectively
 * unbind any buffer bind to the _target. _target is a member initialized in constructor.
 */
void ge::gl::BufferObject::unbind()
{
   glBindBuffer(_target, BUFFEROBJECT_DEFAULT_EMPTY_TARGET);
}

//const ge::gl::BufferObject::Mapping* ge::gl::BufferObject::createMapping( GLintptr offset, GLsizeiptr size, GLbitfield flags )
//{
//   void *data = glMapNamedBufferRangeEXT(_id, offset, size, flags);
//
//   if(data)
//   {   
//      ge::gl::BufferObject::Mapping m(offset, size, flags, _id, data);
//      _mappings.emplace_back(std::move(m));
//      _mappings.back().setPlace(--_mappings.end());
//      return &(_mappings.back());
//   }
//   return NULL;
//}
//
//void ge::gl::BufferObject::destroyMapping( Mapping &mapping )
//{
//
//}
namespace ge{
  namespace gl{
    BufferObject::BufferObject(
        GLsizeiptr    size,
        const GLvoid *data,
        GLenum        target,
        GLenum        usage){
      this->_data   = BUFFEROBJECT_DEFAULT_DATA;
      this->_size   = size;
      this->_target = target;
      this->_usage  = usage;
      this->_flags  = BUFFEROBJECT_DEFAULT_FLAGS;
#ifndef USE_DSA
      glGenBuffers(1,&this->_id);
      glBindBuffer(this->_target,this->_id);
      glBufferData(this->_target,this->_size,data,this->_usage);
      glBindBuffer(this->_target,BUFFEROBJECT_DEFAULT_ID);
#else //USE_DSA
      glCreateBuffers(1,&this->_id);
      glNamedBufferData(this->_id,this->_size,data,this->_usage);
#endif//USE_DSA
    }
    BufferObject::BufferObject(
        GLsizeiptr    size,
        GLbitfield    flags,
        const GLvoid *data){
      this->_data   = BUFFEROBJECT_DEFAULT_DATA;
      this->_size   = size;
      this->_target = BUFFEROBJECT_DEFAULT_TARGET;
      this->_usage  = BUFFEROBJECT_DEFAULT_USAGE;
      this->_flags  = flags;
#ifndef USE_DSA
      glGenBuffers(1,&this->_id);
      glBindBuffer(this->_target,this->_id);
      glBufferStorage(this->_target,this->_size,data,flags);
      glBindBuffer(this->_target,BUFFEROBJECT_DEFAULT_ID);
#else //USE_DSA
      glCreateBuffers(1,&this->_id);
      glNamedBufferStorage(this->_id,this->_size,data,this->_flags);
#endif//USE_DSA
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
      GLsizeiptr maxSize=(this->_size>buffer->_size)?buffer->_size:this->_size;
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
      //unbind buffers
      glBindBuffer(BUFFEROBJECT_DEFAULT_READBUFFER ,BUFFEROBJECT_DEFAULT_EMPTY_TARGET);
      glBindBuffer(BUFFEROBJECT_DEFAULT_WRITEBUFFER,BUFFEROBJECT_DEFAULT_EMPTY_TARGET);
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
     * @param length length of data in bytes
     */
    void BufferObject::flushMapped(
        GLenum     target,
        GLintptr   offset,
        GLsizeiptr length){
      glFlushMappedBufferRange(target,offset,length);
    }
    /**
     * @brief Invalidates specific region of buffer
     *
     * @param offset offset of region in bytes
     * @param length length of region in bytes
     */
    void BufferObject::invalidate(GLintptr offset,GLsizeiptr length){
      glInvalidateBufferSubData(this->_id,offset,length);
    }
    /**
     * @brief Invalidates buffer
     */
    void BufferObject::invalidate(){
      glInvalidateBufferData(this->_id);
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
      //bind buffer to clearbuffer binding point
      glBindBuffer(BUFFEROBJECT_DEFAULT_CLEARBUFFER,this->_id);
      //clear buffer
      glClearBufferSubData(
          BUFFEROBJECT_DEFAULT_CLEARBUFFER,
          internalFormat,
          BUFFEROBJECT_DEFAULT_CLEAROFFSET,
          this->_size,
          format,
          type,
          data);
      //unbind buffer from clearbuffer binding point
      glBindBuffer(BUFFEROBJECT_DEFAULT_CLEARBUFFER,BUFFEROBJECT_DEFAULT_EMPTY_TARGET);
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
      //bind buffer to clearbuffer binding point
      glBindBuffer(BUFFEROBJECT_DEFAULT_CLEARBUFFER,this->_id);
      //clear buffer
      glClearBufferSubData(
          BUFFEROBJECT_DEFAULT_CLEARBUFFER,
          internalFormat,
          offset,
          size,
          format,
          type,
          data);
      //unbind buffer from clearbuffer binding point
      glBindBuffer(BUFFEROBJECT_DEFAULT_CLEARBUFFER,BUFFEROBJECT_DEFAULT_EMPTY_TARGET);
    }
    GLint BufferObject::getParameter(GLenum pname){
      GLint param;
#ifndef USE_DSA
      GLuint oldId;
      glGetIntegerv(GL_ARRAY_BUFFER_BINDING,(GLint*)&oldId);
      glBindBuffer(GL_ARRAY_BUFFER,this->_id);
      glGetBufferParameteriv(GL_ARRAY_BUFFER,pname,&param);
      glBindBuffer(GL_ARRAY_BUFFER,oldId);
#else //USE_DSA
      glGetNamedBufferParameteriv(this->_id,pname,&param);
#endif//USE_DSA
      return param;
    }
    GLuint BufferObject::getId(){
      return this->_id;
    }
    void*BufferObject::map(
        GLenum target,
        GLenum access){
		  glBindBuffer(target,this->_id);//bind buffer to target
		  return glMapBuffer(target,access);//return mapped buffer
    }
    void*BufferObject::map(
        GLenum     target,
        GLintptr   offset,
        GLsizeiptr length,
        GLbitfield access){
		  glBindBuffer(target,this->_id);//bind buffer to target
		  return glMapBufferRange(target,offset,length,access);//return mapped region
    }
    void BufferObject::unmap(
        GLenum target){
		  glUnmapBuffer(target);//unmap buffer
		  glBindBuffer(target,0);//unbind buffer
    }
    void BufferObject::setData(
        GLvoid     *data,
        GLsizeiptr  size,
        GLintptr    offset){
      if(size==BUFFEROBJECT_DEFAULT_SIZE)
        size=this->_size;
#ifndef USE_DSA
      GLuint oldId;
      glGetIntegerv(GL_ARRAY_BUFFER_BINDING,(GLint*)&oldId);
      glBindBuffer(GL_ARRAY_BUFFER,this->_id);//bind buffer
  		glBufferSubData(GL_ARRAY_BUFFER,offset,size,data);//copy data
		  glBindBuffer(GL_ARRAY_BUFFER,oldId);//unbin buffer
#else //USE_DSA
      glNamedBufferSubData(this->_id,offset,size,data);
#endif//USE_DSA

    }
    void BufferObject::getData(
        GLvoid     *data,
        GLsizeiptr  size,
        GLintptr    offset){
      if(size==BUFFEROBJECT_DEFAULT_SIZE)
        size=this->_size;
#ifndef USE_DSA
      GLuint oldId;
      glGetIntegerv(GL_ARRAY_BUFFER_BINDING,(GLint*)&oldId);
      glBindBuffer(GL_ARRAY_BUFFER,this->_id);//bind buffer
      glGetBufferSubData(GL_ARRAY_BUFFER,offset,size,data);//obtain data
      glBindBuffer(GL_ARRAY_BUFFER,oldId);//unbin buffer
#else //USE_DSA
      glGetNamedBufferSubData(this->_id,offset,size,data);
#endif//USE_DSA
    }
  }
}

