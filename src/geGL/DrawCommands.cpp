#include <geGL/DrawCommands.h>

using namespace ge::gl;



DrawArrays::DrawArrays(
    GLenum  mode ,
    GLint   first,
    GLsizei count):DrawMode(mode),DrawCount(count){
  this->setFirst(first);
}
void DrawArrays::operator()(){
  glDrawArrays(
      this->_mode,
      this->_first,
      this->_count);
}
GLint DrawArrays::getFirst(){
  return this->_first;
}
void DrawArrays::setFirst(GLint first){
  this->_first = first;
}



DrawArraysInstancedBaseInstance::DrawArraysInstancedBaseInstance(
    GLenum  mode         ,
    GLint   first        ,
    GLsizei count        ,
    GLsizei instanceCount,
    GLuint  baseInstance ):DrawArrays(mode,first,count),DrawInstancedBaseInstance(instanceCount,baseInstance){
}
void DrawArraysInstancedBaseInstance::operator()(){
  glDrawArraysInstancedBaseInstance(
      this->_mode,
      this->_first,
      this->_count,
      this->_instanceCount,
      this->_baseInstance);
}

DrawArraysInstanced::DrawArraysInstanced(
    GLenum  mode         ,
    GLint   first        ,
    GLsizei count        ,
    GLsizei instanceCount):DrawArrays(mode,first,count),DrawInstanced(instanceCount){
}
void DrawArraysInstanced::operator()(){
  glDrawArraysInstanced(
      this->_mode         ,
      this->_first        ,
      this->_count        ,
      this->_instanceCount);
}

DrawArraysIndirect::DrawArraysIndirect(
    GLenum        mode    ,
    const GLvoid* indirect):DrawMode(mode),DrawIndirect(indirect){
}
void DrawArraysIndirect::operator()(){
  glDrawArraysIndirect(
      this->_mode,
      this->_indirect);
}

MultiDrawArrays::MultiDrawArrays(
    GLenum         mode     ,
    const GLint*   first    ,
    const GLsizei* count    ,
    GLsizei        drawCount):DrawMode(mode),MultiCount(count),MultiDrawCount(drawCount){
  this->setFirst(first);
}
void MultiDrawArrays::operator()(){
  glMultiDrawArrays(
      this->_mode,
      this->_first,
      this->_count,
      this->_drawCount);
}
const GLint*MultiDrawArrays::getFirst(){
  return this->_first;
}
void MultiDrawArrays::setFirst(const GLint*first){
  this->_first = first;
}



MultiDrawArraysIndirect::MultiDrawArraysIndirect(
    GLenum        mode     ,
    const GLvoid* indirect ,
    GLsizei       drawCount,
    GLsizei       stride   ):DrawMode(mode),MultiDrawIndirect(indirect,drawCount,stride){
}
void MultiDrawArraysIndirect::operator()(){
  glMultiDrawArraysIndirect(
      this->_mode     ,
      this->_indirect ,
      this->_drawCount,
      this->_stride   );
}

DrawElements::DrawElements(
    GLenum        mode   ,
    GLsizei       count  ,
    GLenum        type   ,
    const GLvoid* indices):DrawCount(count),DrawModeType(mode,type){
  this->setIndices(indices);
}
void DrawElements::operator()(){
  glDrawElements(
      this->_mode   ,
      this->_count  ,
      this->_type   ,
      this->_indices);
}
const GLvoid*DrawElements::getIndices(){
  return this->_indices;
}
void DrawElements::setIndices(const GLvoid*indices){
  this->_indices = indices;
}



DrawElementsInstancedBaseInstance::DrawElementsInstancedBaseInstance(
    GLenum        mode         ,
    GLsizei       count        ,
    GLenum        type         ,
    const GLvoid* indices      ,
    GLsizei       instanceCount,
    GLuint        baseInstance ):DrawElements(mode,count,type,indices),DrawInstancedBaseInstance(instanceCount,baseInstance){
}
void DrawElementsInstancedBaseInstance::operator()(){
  glDrawElementsInstancedBaseInstance(
      this->_mode         ,
      this->_count        ,
      this->_type         ,
      this->_indices      ,
      this->_instanceCount,
      this->_baseInstance );
}

DrawElementsInstanced::DrawElementsInstanced(
    GLenum        mode         ,
    GLsizei       count        ,
    GLenum        type         ,
    const GLvoid* indices      ,
    GLsizei       instanceCount):DrawElements(mode,count,type,indices),DrawInstanced(instanceCount){
}
void DrawElementsInstanced::operator()(){
  glDrawElementsInstanced(
      this->_mode         ,
      this->_count        ,
      this->_type         ,
      this->_indices      ,
      this->_instanceCount);
}

MultiDrawElements::MultiDrawElements(
    GLenum              mode     ,
    const GLsizei*      count    ,
    GLenum              type     ,
    const GLvoid*const* indices  ,
    GLsizei             drawCount):DrawModeType(mode,type),MultiCount(count),MultiDrawCount(drawCount){
  this->setIndices(indices);
}
void MultiDrawElements::operator()(){
  ((void(*)(GLenum,const GLsizei*,GLenum,const GLvoid*const*,GLsizei))glMultiDrawElements)(
      this->_mode     ,
      this->_count    ,
      this->_type     ,
      this->_indices  ,
      this->_drawCount);
}
const GLvoid*const*MultiDrawElements::getIndices(){
  return this->_indices;
}
void MultiDrawElements::setIndices(const GLvoid*const*indices){
  this->_indices = indices;
}
DrawRangeElements::DrawRangeElements(
    GLenum        mode   ,
    GLuint        start  ,
    GLuint        end    ,
    GLsizei       count  ,
    GLenum        type   ,
    const GLvoid* indices):DrawElements(mode,count,type,indices),DrawRange(start,end){
}
void DrawRangeElements::operator()(){
  glDrawRangeElements(
      this->_mode   ,
      this->_start  ,
      this->_end    ,
      this->_count  ,
      this->_type   ,
      this->_indices);
}

MultiCount::MultiCount(const GLsizei* count){
  this->setCount(count);
}
const GLsizei* MultiCount::getCount(){
  return this->_count;
}
void MultiCount::setCount(const GLsizei*count){
  this->_count = count;
}

DrawElementsBaseVertex::DrawElementsBaseVertex(
    GLenum        mode      ,
    GLsizei       count     ,
    GLenum        type      ,
    const GLvoid* indices   ,
    GLint         baseVertex):DrawElements(mode,count,type,indices){
  this->setBaseVertex(baseVertex);
}
void DrawElementsBaseVertex::operator()(){
  glDrawElementsBaseVertex(
      this->_mode      ,
      this->_count     ,
      this->_type      ,
      this->_indices   ,
      this->_baseVertex);
}
GLint DrawElementsBaseVertex::getBaseVertex(){
  return this->_baseVertex;
}
void DrawElementsBaseVertex::setBaseVertex(GLint baseVertex){
  this->_baseVertex = baseVertex;
}

DrawRangeElementsBaseVertex::DrawRangeElementsBaseVertex(
    GLenum        mode      ,
    GLuint        start     ,
    GLuint        end       ,
    GLsizei       count     ,
    GLenum        type      ,
    const GLvoid* indices   ,
    GLint         baseVertex):DrawElementsBaseVertex(mode,count,type,indices,baseVertex),DrawRange(start,end){
}
void DrawRangeElementsBaseVertex::operator()(){
  glDrawRangeElementsBaseVertex(
      this->_mode      ,
      this->_start     ,
      this->_end       ,
      this->_count     ,
      this->_type      ,
      this->_indices   ,
      this->_baseVertex);
}

DrawElementsInstancedBaseVertex::DrawElementsInstancedBaseVertex(
    GLenum        mode         ,
    GLsizei       count        ,
    GLenum        type         ,
    const GLvoid* indices      ,
    GLsizei       instanceCount,
    GLint         baseVertex   ):DrawElementsBaseVertex(mode,count,type,indices,baseVertex),DrawInstanced(instanceCount){
}
void DrawElementsInstancedBaseVertex::operator()(){
  glDrawElementsInstancedBaseVertex(
      this->_mode         ,
      this->_count        ,
      this->_type         ,
      this->_indices      ,
      this->_instanceCount,
      this->_baseVertex   );
}

DrawElementsInstancedBaseVertexBaseInstance::DrawElementsInstancedBaseVertexBaseInstance(
    GLenum        mode         ,
    GLsizei       count        ,
    GLenum        type         ,
    const GLvoid* indices      ,
    GLsizei       instanceCount,
    GLint         baseVertex   ,
    GLuint        baseInstance ):DrawElementsBaseVertex(mode,count,type,indices,baseVertex),DrawInstancedBaseInstance(instanceCount,baseInstance){
}
void DrawElementsInstancedBaseVertexBaseInstance::operator()(){
  glDrawElementsInstancedBaseVertexBaseInstance(
      this->_mode         ,
      this->_count        ,
      this->_type         ,
      this->_indices      ,
      this->_instanceCount,
      this->_baseVertex   ,
      this->_baseInstance );
}

DrawElementsIndirect::DrawElementsIndirect(
    GLenum        mode    ,
    GLenum        type    ,
    const GLvoid* indirect):DrawModeType(mode,type),DrawIndirect(indirect){
}
void DrawElementsIndirect::operator()(){
  glDrawElementsIndirect(
      this->_mode    ,
      this->_type    ,
      this->_indirect);
}
MultiDrawElementsIndirect::MultiDrawElementsIndirect(
    GLenum        mode     ,
    GLenum        type     ,
    const GLvoid* indirect ,
    GLsizei       drawCount,
    GLsizei       stride   ):DrawModeType(mode,type),MultiDrawIndirect(indirect,drawCount,stride){
}
void MultiDrawElementsIndirect::operator()(){
  glMultiDrawElementsIndirect(
      this->_mode     ,
      this->_type     ,
      this->_indirect ,
      this->_drawCount,
      this->_stride   );
}
MultiDrawElementsBaseVertex::MultiDrawElementsBaseVertex(
    GLenum              mode      ,
    const GLsizei*      count     ,
    GLenum              type      ,
    const GLvoid*const* indices   ,
    GLsizei             drawCount ,
    const GLint*        baseVertex):MultiDrawElements(mode,count,type,indices,drawCount){
  this->setBaseVertex(baseVertex);
}
void MultiDrawElementsBaseVertex::operator()(){
  glMultiDrawElementsBaseVertex(
      this->_mode      ,
      this->_count     ,
      this->_type      ,
      this->_indices   ,
      this->_drawCount ,
      this->_baseVertex);
}
const GLint*MultiDrawElementsBaseVertex::getBaseVertex(){
  return this->_baseVertex;
}
void MultiDrawElementsBaseVertex::setBaseVertex(const GLint*baseVertex){
  this->_baseVertex = baseVertex;
}
