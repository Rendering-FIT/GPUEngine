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

ge::gl::BufferObject::BufferObject( const BufferObject& buf, const ge::core::CopyOp& copyop /*= ge::core::CopyOp::SHALLOW_COPY*/ )
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

void ge::gl::BufferObject::freeClientSideBuffer()
{
   //not checking if gl is mapped (waste of time)
   if(_data) free(_data);
}

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

void ge::gl::BufferObject::deleteGLObject()
{
   glDeleteBuffers(1, &_bufferObject);
   _bufferObject = 0;
}

void ge::gl::BufferObject::map( GLenum mapFlags/* = 0*/)
{
   //if(_data)
      //should be NULL
   _data = glMapNamedBufferRangeEXT(_bufferObject, 0, _size, mapFlags==0 ? _flags : mapFlags);
}

void ge::gl::BufferObject::unmap()
{
   glUnmapNamedBufferEXT(_bufferObject);
   _data = NULL;
}

GLboolean ge::gl::BufferObject::isMapped()
{
   GLboolean ret;
   glGetBooleanv(GL_BUFFER_MAPPED, &ret);
   return ret;
}

void ge::gl::BufferObject::bind()
{
   glBindBuffer(_target, _bufferObject);
}

void ge::gl::BufferObject::unbind()
{
   glBindBuffer(_target, 0);
}
