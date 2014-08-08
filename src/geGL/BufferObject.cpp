#include <geGL/BufferObject.h>

#include <malloc.h>

ge::gl::BufferObject::BufferObject()
   //: Object()
   : _mutable(true)
   , _data(NULL)
   , _bufferObject(0)
   , _target(0)
   , _size(0)
   , _usage(GL_STATIC_DRAW)
   , _flags(0)
{

}

/**
 * Copy constructor, doing only a shallow copy of the data.
 */
ge::gl::BufferObject::BufferObject( const BufferObject& buf/*, const ge::core::CopyOp& copyop /*= ge::core::CopyOp::SHALLOW_COPY*/ )
   //: Object(buf, copyop)
   : _mutable(buf._mutable)
   , _data(buf._data)
   , _bufferObject(buf._bufferObject)
   , _target(buf._target)
   , _size(buf._size)
   , _usage(buf._usage)
   , _flags(buf._flags)
{

}

ge::gl::BufferObject::~BufferObject()
{
   if(isMapped()) _data = NULL;
   deleteGLObject();
   if(_data) delete _data;
}

/**
 * Allocates client-side buffer. Don't call this method if 
 * the buffer is mapped, because the same pointer is used.
 */
void ge::gl::BufferObject::allocateClientSideBuffer( GLsizeiptr size, void* dataSource/* = NULL*/ )
{
   _data = malloc(size);
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
   if(_data) free(_data);
}

/**
 * Inits the OpenGL Buffer Object and uses internal client-side buffer to initialize it.
 * The allocateClientSideBuffer() should be called before.
 *
 * @param mutable_ Controls if the OGL BO is mutable (BufferData) or immutable (BufferStorage).
 */
void ge::gl::BufferObject::createAndInitGLBO( GLenum target, GLenum usage /*= GL_STATIC_DRAW*/, bool mutable_ /*= true*/, GLbitfield flags /*= 0*/ )
{
   if((!_mutable && _bufferObject) || (_size <= 0) )
   {
      //make some fuss
      return;
   }
   _target = target;
   _usage = usage;
   _mutable = mutable_;
   _flags = flags;

   if(!_bufferObject)
      glGenBuffers(1, &_bufferObject);
   if(!_bufferObject)
   {
      //make fuss
      return;
   }

   if(_mutable)
   {
      glNamedBufferDataEXT(_bufferObject, _size, _data, _usage);
   }
   else
   {
      glNamedBufferStorageEXT(_bufferObject, _size, _data, _flags);
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
   if(!_mutable && _bufferObject)
   {
      //make some fuss
      return;
   }
   _target = target;
   _size = size;
   _usage = usage;
   _mutable = mutable_;
   _flags = flags;

   if(!_bufferObject)
      glGenBuffers(1, &_bufferObject);
   if(!_bufferObject)
   {
      //make fuss
      return;
   }

   if(_mutable)
   {
      glNamedBufferDataEXT(_bufferObject, _size, data, _usage);
   }
   else
   {
      glNamedBufferStorageEXT(_bufferObject, _size, data, _flags);
   }
}

/**
 * Calls the glDeleteBuffer and sets _bufferObject member to 0.
 */
void ge::gl::BufferObject::deleteGLObject()
{
   glDeleteBuffers(1, &_bufferObject);
   _bufferObject = 0;
}

/**
 * Maps the buffer to it's internal _data member. If client-side buffer has been allocated, the
 * user is responsible for deallocation prior to calling this function.
 */
void ge::gl::BufferObject::map( GLintptr offset /*= 0*/, GLsizeiptr size /*= 0*/, GLenum mapFlags /*= 0*/ )
{
   //if(_data)
      //should be NULL
   _data = glMapNamedBufferRangeEXT(_bufferObject, offset, size==0 ? _size : size, mapFlags==0 ? _flags : mapFlags);
}

/**
 * Unmaps the buffer and sets _data to NULL.
 */
void ge::gl::BufferObject::unmap()
{
   glUnmapNamedBufferEXT(_bufferObject);
   _data = NULL;
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
   glBindBuffer(_target, _bufferObject);
}

/**
 * Unbinds the target. Note that this calls glBindBuffer(_target, 0) so it will effectively
 * unbind any buffer bind to the _target. _target is a member initialized in constructor.
 */
void ge::gl::BufferObject::unbind()
{
   glBindBuffer(_target, 0);
}

//const ge::gl::BufferObject::Mapping* ge::gl::BufferObject::createMapping( GLintptr offset, GLsizeiptr size, GLbitfield flags )
//{
//   void *data = glMapNamedBufferRangeEXT(_bufferObject, offset, size, flags);
//
//   if(data)
//   {   
//      ge::gl::BufferObject::Mapping m(offset, size, flags, _bufferObject, data);
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
