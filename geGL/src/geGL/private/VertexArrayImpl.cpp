#include <geGL/private/VertexArrayImpl.h>
#include <geGL/VertexArray.h>
#include <geGL/private/BufferImpl.h>

using namespace ge::gl;

VertexArrayImpl::VertexArrayImpl(VertexArray*v):vao(v){
  vao->getContext().glCreateVertexArrays(1,&vao->getId());
}

VertexArrayImpl::~VertexArrayImpl(){
  vao->getContext().glDeleteVertexArrays(1,&vao->getId());
  removeReferencesFromBuffers();
  removeReferenceFromElementBuffer();
}

size_t VertexArrayImpl::getNofBufferUsages(Buffer const*buffer)const{
  size_t counter = size_t(elementBuffer == buffer);
  for(auto const&x:buffers)
    if(x==buffer)++counter;
  return counter;
}

GLint VertexArrayImpl::getAttrib(GLuint index,GLenum pname)const{
  GLint param;
  vao->getContext().glGetVertexArrayIndexediv(vao->getId(),index,pname,&param);
  return param;
}
  
void VertexArrayImpl::addElementBuffer(Buffer*buffer){
  removeReferenceFromElementBufferIfItIsOnlyReference();
  elementBuffer = buffer;
  addReferenceToBuffer(buffer);
  vao->getContext().glVertexArrayElementBuffer(vao->getId(), buffer->getId());
}
  
void VertexArrayImpl::removeReferencesFromBuffers(){
  for(auto const&x:buffers)
    if(x)x->impl->vertexArrays.erase(vao);
}

void VertexArrayImpl::removeReferenceFromElementBuffer(){
  if(elementBuffer)elementBuffer->impl->vertexArrays.erase(vao);
}

void VertexArrayImpl::removeReferenceFromElementBufferIfItIsOnlyReference(){
  if (!elementBuffer) return;
  size_t nofBufferUsages = getNofBufferUsages(elementBuffer);
  if (nofBufferUsages == 1)
     elementBuffer->impl->vertexArrays.erase(vao);
}

void VertexArrayImpl::addReferenceToBuffer(Buffer*buffer)const{
  buffer->impl->vertexArrays.insert(vao);
}
  
void VertexArrayImpl::resizeBuffersForIndex(GLuint index){
  if (index >= buffers.size()) buffers.resize(index + 1, nullptr);
}
