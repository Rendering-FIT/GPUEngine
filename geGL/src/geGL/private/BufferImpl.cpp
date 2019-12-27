#include <geGL/private/BufferImpl.h>
#include <geGL/private/VertexArrayImpl.h>
#include <geGL/Buffer.h>
#include <geGL/OpenGLUtil.h>
#include <geGL/VertexArray.h>

using namespace ge::gl;
using namespace std;

BufferImpl::BufferImpl(Buffer *b) : buffer(b) {}

void BufferImpl::bufferData(GLsizeiptr    size,
                            GLvoid const *data,
                            GLbitfield    flags) const
{
  auto const &gl = buffer->getContext();
  if (areBufferFlagsMutable(flags))
    gl.glNamedBufferData(buffer->getId(), size, data, flags);
  else
    gl.glNamedBufferStorage(buffer->getId(), size, data, flags);
}

BufferImpl::~BufferImpl(){
  buffer->getContext().glDeleteBuffers(1, &buffer->getId());
  removeReferences();
}

void BufferImpl::updateVertexArrays()
{
  auto const me = buffer;
  for (auto const &vao : vertexArrays) {
    if (vao->impl->elementBuffer == me) {
      vao->addElementBuffer(me);
    }
    vector<GLuint> attribs;
    GLuint         attribId = 0;
    for (auto const &y : vao->impl->buffers) {
      if (y == me) attribs.push_back(attribId);
      attribId++;
    }
    for (auto const &attribIndex : attribs) {
      auto type = VertexArray::NONE;
      if (vao->isAttribInteger(attribIndex)) type = VertexArray::I;
      if (vao->isAttribLong(attribIndex)) type = VertexArray::L;
      vao->addAttrib(me, attribIndex, vao->getAttribSize(attribIndex),
                     vao->getAttribType(attribIndex),
                     vao->getAttribStride(attribIndex),
                     vao->getAttribRelativeOffset(attribIndex),
                     vao->isAttribNormalized(attribIndex),
                     vao->getAttribDivisor(attribIndex), type);
    }
  }
}

GLint BufferImpl::getBufferParameter(GLenum pname) const
{
  GLint       param;
  auto const &gl = buffer->getContext();
  gl.glGetNamedBufferParameteriv(buffer->getId(), pname, &param);
  return param;
}

GLint64 BufferImpl::getBufferParameter64(GLenum pname) const
{
  GLint64       param;
  auto const &gl = buffer->getContext();
  gl.glGetNamedBufferParameteri64v(buffer->getId(), pname, &param);
  return param;
}

GLvoid *BufferImpl::getBufferPointer(GLenum pname) const
{
  GLvoid *    param;
  auto const &gl = buffer->getContext();
  gl.glGetNamedBufferPointerv(buffer->getId(), pname, &param);
  return param;
}

void throwIfReallocFlagsAreIncompatible(Buffer *buffer, Buffer::ReallocFlags f)
{
  if (!((f & Buffer::KEEP_ID) && buffer->isImmutable())) return;
  throw runtime_error(
      "Buffer::realloc - can't sustain buffer id, buffer is immutable");
}

void throwIfReallocFlagsAreInvalid(){
  throw runtime_error("Buffer::realloc - invalid buffer reallocation flags.");
}

void BufferImpl::realloc(GLsizeiptr size, Buffer::ReallocFlags f)
{
  throwIfReallocFlagsAreIncompatible(buffer, f);

  GLbitfield bufferFlags = buffer->getUsage();
  if (f == Buffer::KEEP_DATA_ID )
    resizeBufferKeepDataKeepId(size, bufferFlags);
  else if (f == Buffer::KEEP_ID)
    resizeBuffer(size, bufferFlags);
  else if (f == Buffer::KEEP_DATA)
    resizeBufferKeepData(size, bufferFlags);
  else if (f == Buffer::NEW_BUFFER)
    newBuffer(size, bufferFlags);
  else
    throwIfReallocFlagsAreInvalid();
}

void BufferImpl::resizeBuffer(GLsizeiptr size, GLbitfield flags)
{
  bufferData(size, nullptr, flags);
}

void BufferImpl::resizeBufferKeepData(GLsizeiptr size, GLbitfield flags)
{
  auto newBuffer = new Buffer(size, nullptr, flags);
  assert(newBuffer != nullptr);
  newBuffer->copy(*buffer);
  auto swapId        = buffer->getId();
  buffer->getId()    = newBuffer->getId();
  newBuffer->getId() = swapId;
  delete newBuffer;
  updateVertexArrays();
}

void BufferImpl::resizeBufferKeepDataKeepId(GLsizeiptr size, GLbitfield flags)
{
  Buffer *temp = new Buffer(size, nullptr, flags);
  assert(temp != nullptr);
  temp->copy(*buffer);
  bufferData(size, nullptr, flags);
  buffer->copy(*temp);
  delete temp;
}

void BufferImpl::newBuffer(GLsizeiptr size, GLbitfield flags)
{
  buffer->getContext().glDeleteBuffers(1, &buffer->getId());
  buffer->alloc(size, nullptr, flags);
  updateVertexArrays();
}

void BufferImpl::removeReferences(){
  auto vaos = vertexArrays;
  for(auto const&vao:vaos){
    if(vao->impl->elementBuffer == buffer)
      vao->removeElementBuffer();
    for(size_t i=0;i<vao->impl->buffers.size();++i)
      if(vao->impl->buffers.at(i) == buffer)
        vao->removeAttrib((GLuint)i);
  }
}
