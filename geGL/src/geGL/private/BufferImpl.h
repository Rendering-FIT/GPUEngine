#pragma once

#include <geGL/Buffer.h>
#include <set>

class ge::gl::BufferImpl {
 public:
  BufferImpl(Buffer* b);
  ~BufferImpl();
  GLint   getBufferParameter(GLenum pname) const;
  GLint64 getBufferParameter64(GLenum pname) const;
  GLvoid* getBufferPointer(GLenum pname) const;
  void bufferData(GLsizeiptr size, GLvoid const* data, GLbitfield flags) const;
  void updateVertexArrays();
  void realloc(GLsizeiptr size, Buffer::ReallocFlags f);
  void resizeBuffer(GLsizeiptr size, GLbitfield flags);
  void resizeBufferKeepData(GLsizeiptr size, GLbitfield flags);
  void resizeBufferKeepDataKeepId(GLsizeiptr size, GLbitfield flags);
  void newBuffer(GLsizeiptr size, GLbitfield flags);
  void removeReferences();
  Buffer*                buffer = nullptr;
  std::set<VertexArray*> vertexArrays;
};
