#include <geGL/ScissorCommands.h>

using namespace ge::gl;

ScissorArrayv::ScissorArrayv(GLuint first,GLsizei count,GLint*v){
  this->first = first;
  this->count = count;
  this->v     = v;
}
void ScissorArrayv::operator()(){
  glScissorArrayv(this->first,this->count,this->v);
}
ScissorIndexed::ScissorIndexed(
    GLuint  index,
    GLint   left,
    GLint   bottom,
    GLsizei width,
    GLsizei height){
  this->index  = index;
  this->left   = left;
  this->bottom = bottom;
  this->width  = width;
  this->height = height;
}
void ScissorIndexed::operator()(){
  glScissorIndexed(this->index,this->left,this->bottom,this->width,this->height);
}
ScissorIndexedv::ScissorIndexedv(GLuint index,GLint*v){
  this->index=index;
  this->v=v;
}
void ScissorIndexedv::operator()(){
  glScissorIndexedv(this->index,this->v);
}
Scissor::Scissor(GLint left,GLint bottom,GLsizei width,GLsizei height){
  this->left=left;
  this->bottom=bottom;
  this->width=width;
  this->height=height;
}
void Scissor::operator()()
{
  glScissor(this->left,this->bottom,this->width,this->height);
}

