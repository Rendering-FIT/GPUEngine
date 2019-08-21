#pragma once

#include<vector>
#include<geGL/OpenGL.h>

class ge::gl::VertexArrayImpl {
public:
  VertexArrayImpl(VertexArray*v);
  ~VertexArrayImpl();
  size_t getNofBufferUsages(Buffer const* buffer) const;
  GLint  getAttrib(GLuint index, GLenum pname) const;
  void   addElementBuffer(Buffer*buffer);
  void   removeReferencesFromBuffers();
  void   removeReferenceFromElementBuffer();
  void   removeReferenceFromElementBufferIfItIsOnlyReference();
  void   addReferenceToBuffer(Buffer*buffer)const;
  void   resizeBuffersForIndex(GLuint index);
  std::vector<Buffer*>buffers;
  Buffer*elementBuffer = nullptr;
  VertexArray*vao = nullptr;
};
