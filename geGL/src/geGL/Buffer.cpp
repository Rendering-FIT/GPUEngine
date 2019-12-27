#include <geGL/private/BufferImpl.h>
#include <geGL/private/VertexArrayImpl.h>
#include <geGL/Buffer.h>
#include <geGL/OpenGLUtil.h>
#include <geGL/VertexArray.h>
#include <algorithm>
#include <cassert>
#include <vector>

using namespace ge::gl;

/**
 * @brief Empty constructor, it sets ID=0
 */
Buffer::Buffer() : Buffer(nullptr) {}

/**
 * @brief Constructor
 *
 * @param size size of buffer in bytes
 * @param data optional pointer to data data
 * @param flags optional flags, right flags can make buffer immutable
 */
Buffer::Buffer(GLsizeiptr size, GLvoid const *data, GLbitfield flags)
    : Buffer(nullptr, size, data, flags)
{
}

/**
 * @brief creates new empty buffer
 *
 * @param table opengl function table
 */
Buffer::Buffer(FunctionTablePointer const &table) : OpenGLObject(table)
{
  impl = new BufferImpl(this);
}

/**
 * @brief create new buffer
 *
 * @param table opengl function table
 * @param size size of buffer in bytes
 * @param data optional data
 * @param flags optional flags
 */
Buffer::Buffer(FunctionTablePointer const &table,
               GLsizeiptr                  size,
               GLvoid const *              data,
               GLbitfield                  flags)
    : Buffer(table)
{
  alloc(size, data, flags);
}

/**
 * @brief destructor
 */
Buffer::~Buffer()
{
  delete impl;
}

/**
 * @brief allocates buffer, this function can only be used on empty buffer
 *
 * @param size size of buffer in bytes
 * @param data optional data
 * @param flags optional flags
 */
void Buffer::alloc(GLsizeiptr size, GLvoid const *data, GLbitfield flags)
{
  getContext().glCreateBuffers(1, &getId());
  impl->bufferData(size, data, flags);
}

/**
 * @brief Binds buffer to specific target
 *
 * @param target target
 */
void Buffer::bind(GLenum target) const
{
  getContext().glBindBuffer(target, getId());
}

/**
 * @brief Binds range of buffer to specific indexed target
 *
 * @param target target
 * @param index target index
 * @param offset offset
 * @param size size of buffer
 */
void Buffer::bindRange(GLenum     target,
                       GLuint     index,
                       GLintptr   offset,
                       GLsizeiptr size) const
{
  getContext().glBindBufferRange(target, index, getId(), offset, size);
}

/**
 * @brief Binds buffer to specific indexed target
 *
 * @param target target
 * @param index index
 */
void Buffer::bindBase(GLenum target, GLuint index) const
{
  getContext().glBindBufferBase(target, index, getId());
}

/**
 * @brief Unbinds buffer from specific target
 *
 * @param target target
 */
void Buffer::unbind(GLenum target) const
{
  getContext().glBindBuffer(target, 0);
}

/**
 * @brief Unbinds range of buffer from specific indexed target
 *
 * @param target target
 * @param index  index
 */
void Buffer::unbindRange(GLenum target, GLuint index) const
{
  getContext().glBindBufferBase(target, index, 0);
}

/**
 * @brief Unbinds buffer from specific index target
 *
 * @param target target
 * @param index  index
 */
void Buffer::unbindBase(GLenum target, GLuint index) const
{
  getContext().glBindBufferBase(target, index, 0);
}

/**
 * @brief This function reallocates buffer.
 *
 * @param newSize new size
 * @param flags KEEP_ID|KEEP_DATA
 */
void Buffer::realloc(GLsizeiptr newSize, ReallocFlags flags)
{
  impl->realloc(newSize, flags);
}

/**
 * @brief Copies data from another buffer into this buffer
 *
 * @param buffer another buffer
 */
void Buffer::copy(Buffer const &buffer) const
{
  GLsizeiptr maxSize = std::min(getSize(), buffer.getSize());
  getContext().glCopyNamedBufferSubData(buffer.getId(), getId(), 0, 0, maxSize);
}

/**
 * @brief Flushes mapped buffer
 *
 * @param target target
 * @param offset offset into buffer in bytes
 * @param size   length of data in bytes
 */
void Buffer::flushMapped(GLsizeiptr size, GLintptr offset) const
{
  auto s = size;
  if (s == 0) s = getSize();
  getContext().glFlushMappedNamedBufferRange(getId(), offset, s);
}

/**
 * @brief Invalidates specific region of buffer
 *
 * @param offset offset of region in bytes
 * @param size   length of region in bytes
 */
void Buffer::invalidate(GLsizeiptr size, GLintptr offset) const
{
  getContext().glInvalidateBufferSubData(getId(), offset, size);
}

/**
 * @brief Clears buffer
 *
 * @param internalFormat internal format of buffer
 * @param format format of data
 * @param type type of data
 * @param data optional data
 */
void Buffer::clear(GLenum        internalFormat,
                   GLenum        format,
                   GLenum        type,
                   GLvoid const *data) const
{
  getContext().glClearNamedBufferData(getId(), internalFormat, format, type,
                                      data);
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
void Buffer::clear(GLenum        internalFormat,
                   GLintptr      offset,
                   GLsizeiptr    size,
                   GLenum        format,
                   GLenum        type,
                   GLvoid const *data) const
{
  getContext().glClearNamedBufferSubData(getId(), internalFormat, offset, size,
                                         format, type, data);
}

/**
 * @brief maps buffer
 *
 * @param access access type
 *
 * @return pointer to pinned memory
 */
GLvoid *Buffer::map(GLbitfield access) const
{
  GLbitfield a = access;
  if (access == GL_READ_ONLY) a = GL_MAP_READ_BIT;
  if (access == GL_WRITE_ONLY) a = GL_MAP_WRITE_BIT;
  if (access == GL_READ_WRITE) a = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
  return getContext().glMapNamedBufferRange(getId(), 0, getSize(), a);
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
GLvoid *Buffer::map(GLintptr offset, GLsizeiptr size, GLbitfield access) const
{
  return getContext().glMapNamedBufferRange(getId(), offset, size, access);
}

/**
 * @brief unmaps buffer
 */
void Buffer::unmap() const { getContext().glUnmapNamedBuffer(getId()); }

/**
 * @brief uploads data into buffer
 *
 * @param data data pointer
 * @param size size of data in bytes
 * @param offset offset into buffer
 */
void Buffer::setData(GLvoid const *data, GLsizeiptr size, GLintptr offset) const
{
  auto const bs = getSize();
  if (size == 0) size = bs-offset;
  if (size + offset > bs)size = bs - offset;
  getContext().glNamedBufferSubData(getId(), offset, size, data);
}

/**
 * @brief gets buffer data
 *
 * @param data data pointer
 * @param size size of obtained data in bytes
 * @param offset offset into buffer
 */
void Buffer::getData(GLvoid *data, GLsizeiptr size, GLintptr offset) const
{
  auto const bs = getSize();
  if (size == 0)size = bs - offset;
  if (size + offset > bs) size = bs - offset;
  getContext().glGetNamedBufferSubData(getId(), offset, size, data);
}

/**
 * @brief gets size of this buffer
 *
 * @return size of thie buffer in bytes
 */
GLsizeiptr Buffer::getSize() const
{
  return impl->getBufferParameter64(GL_BUFFER_SIZE);
}

/**
 * @brief gets usage of this buffer
 *
 * @return usage (GL_BUFFER_USAGE)
 */
GLenum Buffer::getUsage() const
{
  return static_cast<GLenum>(impl->getBufferParameter(GL_BUFFER_USAGE));
}

/**
 * @brief gets access of thie buffer
 *
 * @return access (GL_BUFFER_ACCESS)
 */
GLbitfield Buffer::getAccess() const
{
  return static_cast<GLbitfield>(impl->getBufferParameter(GL_BUFFER_ACCESS));
}

/**
 * @brief gets access flags of this buffer
 *
 * @return access flags (GL_BUFFER_ACCESS_FLAGS)
 */
GLbitfield Buffer::getAccessFlags() const
{
  return static_cast<GLbitfield>(
      impl->getBufferParameter(GL_BUFFER_ACCESS_FLAGS));
}

/**
 * @brief is this buffer mapped
 *
 * @return true if this buffer is mapped
 */
GLboolean Buffer::isMapped() const
{
  return static_cast<GLboolean>(impl->getBufferParameter(GL_BUFFER_MAPPED));
}

/**
 * @brief gets offset of mapped area of buffer
 *
 * @return offset of mapped area of buffer
 */
GLintptr Buffer::getMapOffset() const
{
  return static_cast<GLintptr>(impl->getBufferParameter(GL_BUFFER_MAP_OFFSET));
}

/**
 * @brief gets size of map of buffer
 *
 * @return size of mapped area of buffer
 */
GLsizeiptr Buffer::getMapSize() const
{
  return impl->getBufferParameter(GL_BUFFER_MAP_LENGTH);
}

/**
 * @brief is this buffer immutable
 *
 * @return true if this buffer is immutable
 */
GLboolean Buffer::isImmutable() const
{
  return static_cast<GLboolean>(
      impl->getBufferParameter(GL_BUFFER_IMMUTABLE_STORAGE));
}

/**
 * @brief gets map buffer pointer
 *
 * @return pointer to pinned memory
 */
GLvoid *Buffer::getMapPointer() const
{
  return impl->getBufferPointer(GL_BUFFER_MAP_POINTER);
}
