#include<geGL/DrawCommandsBases.h>

using namespace ge::gl;

DrawMode::DrawMode(GLenum mode){
  this->setMode(mode);
}
GLenum DrawMode::getMode(){
  return this->_mode;
}
void DrawMode::setMode(GLenum mode){
  this->_mode = mode;
}

DrawModeType::DrawModeType(GLenum mode,GLenum type):DrawMode(mode){
  this->setType(type);
}
GLenum DrawModeType::getType(){
  return this->_type;
}
void DrawModeType::setType(GLenum type){
  this->_type = type;
}

DrawCount::DrawCount(GLsizei count){
  this->setCount(count);
}
GLsizei DrawCount::getCount(){
  return this->_count;
}
void DrawCount::setCount(GLsizei count){
  this->_count = count;
}

DrawInstanced::DrawInstanced(GLsizei instanceCount){
  this->setInstanceCount(instanceCount);
}
GLsizei DrawInstanced::getInstanceCount(){
  return this->_instanceCount;
}
void DrawInstanced::setInstanceCount(GLsizei instanceCount){
  this->_instanceCount = instanceCount;
}

DrawInstancedBaseInstance::DrawInstancedBaseInstance(
    GLuint baseInstance,GLsizei instanceCount):DrawInstanced(instanceCount){
  this->setBaseInstance(baseInstance);
}
GLuint DrawInstancedBaseInstance::getBaseInstance(){
  return this->_baseInstance;
}
void DrawInstancedBaseInstance::setBaseInstance(GLuint baseInstance){
  this->_baseInstance = baseInstance;
}

DrawIndirect::DrawIndirect(const GLvoid*indirect){
  this->setIndirect(indirect);
}
const GLvoid*DrawIndirect::getIndirect(){
  return this->_indirect;
}
void DrawIndirect::setIndirect(const GLvoid*indirect){
  this->_indirect = indirect;
}

MultiDrawCount::MultiDrawCount(GLsizei drawCount){
  this->setDrawCount(drawCount);
}
GLsizei MultiDrawCount::getDrawCount(){
  return this->_drawCount;
}
void MultiDrawCount::setDrawCount(GLsizei drawCount){
  this->_drawCount = drawCount;
}

MultiDrawIndirect::MultiDrawIndirect(
    const GLvoid*indirect ,
    GLsizei      drawCount,
    GLsizei      stride   ):DrawIndirect(indirect),MultiDrawCount(drawCount){
  this->setStride(stride);
}
GLsizei MultiDrawIndirect::getStride(){
  return this->_stride;
}
void MultiDrawIndirect::setStride(GLsizei stride){
  this->_stride = stride;
}

DrawRange::DrawRange(
    GLuint start,
    GLuint end  ){
  this->setStart(start);
  this->setEnd  (end  );
}
GLuint DrawRange::getStart(){
  return this->_start;
}
GLuint DrawRange::getEnd  (){
  return this->_end;
}
void DrawRange::setStart(GLuint start){
  this->_start = start;
}
void DrawRange::setEnd(GLuint end){
  this->_end = end;
}

