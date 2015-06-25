#include<geGL/GenericVertexAttributeArraysCommands.h>

namespace ge
{
  namespace gl
  {
    VertexAttribFormat::VertexAttribFormat(
        GLuint    attribIndex,
        GLint     size,
        GLenum    type,
        GLboolean normalized,
        GLuint    relativeOffset){
      this->attribIndex    = attribIndex;
      this->size           = size;
      this->type           = type;
      this->normalized     = normalized;
      this->relativeOffset = relativeOffset;
    }

    void VertexAttribFormat::operator()(){
      glVertexAttribFormat(
          this->attribIndex,
          this->size,
          this->type,
          this->normalized,
          this->relativeOffset);
    }
    VertexAttribIFormat::VertexAttribIFormat(
        GLuint attribIndex,
        GLint  size,
        GLenum type,
        GLuint relativeOffset){
      this->attribIndex    = attribIndex;
      this->size           = size;
      this->type           = type;
      this->relativeOffset = relativeOffset;
    }
    void VertexAttribIFormat::operator()(){
      glVertexAttribIFormat(
          this->attribIndex,
          this->size,
          this->type,
          this->relativeOffset);
    }
    VertexAttribLFormat::VertexAttribLFormat(
        GLuint attribIndex,
        GLint  size,
        GLenum type,
        GLuint relativeOffset){
      this->attribIndex    = attribIndex;
      this->size           = size;
      this->type           = type;
      this->relativeOffset = relativeOffset;
    }
    void VertexAttribLFormat::operator()(){
      glVertexAttribLFormat(
          this->attribIndex,
          this->size,
          this->type,
          this->relativeOffset);
    }
    BindVertexBuffer::BindVertexBuffer(
        GLuint   bindingIndex,
        GLuint   buffer,
        GLintptr offset,
        GLsizei  stride){
      this->bindingIndex = bindingIndex;
      this->buffer       = buffer;
      this->offset       = offset;
      this->stride       = stride;
    }
    void BindVertexBuffer::operator()(){
      glBindVertexBuffer(
          this->bindingIndex,
          this->buffer,
          this->offset,
          this->stride);
    }
    BindVertexBuffers::BindVertexBuffers(
        GLuint    first,
        GLsizei   count,
        GLuint   *buffers,
        GLintptr *offsets,
        GLsizei  *strides){
      this->first   = first;
      this->count   = count;
      this->buffers = buffers;
      this->offsets = offsets;
      this->strides = strides;
    }
    void BindVertexBuffers::operator()(){
      glBindVertexBuffers(
          this->first,
          this->count,
          this->buffers,
          this->offsets,
          this->strides);
    }
    VertexAttribBinding::VertexAttribBinding(
        GLuint attribIndex,
        GLuint bindingIndex){
      this->attribIndex  = attribIndex;
      this->bindingIndex = bindingIndex;
    }
    void VertexAttribBinding::operator()(){
      glVertexAttribBinding(
          this->attribIndex,
          this->bindingIndex);
    }
    VertexAttribPointer::VertexAttribPointer(
        GLuint     index,
        GLint      size,
        GLenum     type,
        GLboolean  normalized,
        GLsizei    stride,
        GLvoid    *pointer){
      this->index      = index;
      this->size       = size;
      this->type       = type;
      this->normalized = normalized;
      this->stride     = stride;
      this->pointer    = pointer;
    }
    void VertexAttribPointer::operator()(){
      glVertexAttribPointer(
          this->index,
          this->size,
          this->type,
          this->normalized,
          this->stride,
          this->pointer);
    }
    VertexAttribIPointer::VertexAttribIPointer(
        GLuint   index,
        GLint    size,
        GLenum   type,
        GLsizei  stride,
        GLvoid  *pointer){
      this->index   = index;
      this->size    = size;
      this->type    = type;
      this->stride  = stride;
      this->pointer = pointer;
    }
    void VertexAttribIPointer::operator()(){
      glVertexAttribIPointer(
          this->index,
          this->size,
          this->type,
          this->stride,
          this->pointer);
    }
    VertexAttribLPointer::VertexAttribLPointer(
        GLuint   index,
        GLint    size,
        GLenum   type,
        GLsizei  stride,
        GLvoid  *pointer){
      this->index   = index;
      this->size    = size;
      this->type    = type;
      this->stride  = stride;
      this->pointer = pointer;
    }
    void VertexAttribLPointer::operator()(){
      glVertexAttribLPointer(
          this->index,
          this->size,
          this->type,
          this->stride,
          this->pointer);
    }
    EnableVertexAttribArray::EnableVertexAttribArray(
        GLuint index){
      this->index = index;
    }
    void EnableVertexAttribArray::operator()(){
      glEnableVertexAttribArray(this->index);
    }
    DisableVertexAttribArray::DisableVertexAttribArray(
        GLuint index){
      this->index = index;
    }
    void DisableVertexAttribArray::operator()(){
      glDisableVertexAttribArray(this->index);
    }
  }//ogl
}//ge

