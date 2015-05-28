#include <geGL/DrawCommands.h>

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

MultiDraw::MultiDraw(GLsizei drawCount){
  this->setDrawCount(drawCount);
}
GLsizei MultiDraw::getDrawCount(){
  return this->_drawCount;
}
void MultiDraw::setDrawCount(GLsizei drawCount){
  this->_drawCount = drawCount;
}

MultiDrawIndirect::MultiDrawIndirect(
    const GLvoid*indirect ,
    GLsizei      drawCount,
    GLsizei      stride   ):DrawIndirect(indirect),MultiDraw(drawCount){
  this->setStride(stride);
}
GLsizei MultiDrawIndirect::getStride(){
  return this->_stride;
}
void MultiDrawIndirect::setStride(GLsizei stride){
  this->_stride = stride;
}

DrawArrays::DrawArrays(
    GLenum  mode ,
    GLint   first,
    GLsizei count):DrawMode(mode),DrawCount(count){
  this->setFirst(first);
}
void DrawArrays::apply(){
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
void DrawArraysInstancedBaseInstance::apply(){
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
void DrawArraysInstanced::apply(){
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
void DrawArraysIndirect::apply(){
  glDrawArraysIndirect(
      this->_mode,
      this->_indirect);
}

MultiDrawArrays::MultiDrawArrays(
    GLenum         mode     ,
    const GLint*   first    ,
    const GLsizei* count    ,
    GLsizei        drawCount){
  this->_mode      = mode;
  this->_first     = first;
  this->_count     = count;
  this->_drawCount = drawCount;
}

void MultiDrawArrays::apply(){
  glMultiDrawArrays(
      this->_mode,
      this->_first,
      this->_count,
      this->_drawCount);
}
MultiDrawArraysIndirect::MultiDrawArraysIndirect(
    GLenum        mode     ,
    const GLvoid* indirect ,
    GLsizei       drawCount,
    GLsizei       stride   ):DrawMode(mode),MultiDrawIndirect(indirect,drawCount,stride){
}
void MultiDrawArraysIndirect::apply(){
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
void DrawElements::apply(){
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
void DrawElementsInstancedBaseInstance::apply(){
  glDrawElementsInstancedBaseInstance(
      this->_mode         ,
      this->_count        ,
      this->_type         ,
      this->_indices      ,
      this->_instanceCount,
      this->_baseInstance );
}

DrawElementsInstanced::DrawElementsInstanced(
    GLenum   mode,
    GLsizei  count,
    GLenum   type,
    GLvoid  *indices,
    GLsizei  instanceCount){
  this->mode          = mode;
  this->count         = count;
  this->type          = type;
  this->indices       = indices;
  this->instanceCount = instanceCount;
}
void DrawElementsInstanced::apply(){
  glDrawElementsInstanced(
      this->mode,
      this->count,
      this->type,
      this->indices,
      this->instanceCount);
}
MultiDrawElements::MultiDrawElements(
    GLenum    mode,
    GLsizei  *count,
    GLenum    type,
    GLvoid  **indices,
    GLsizei   drawCount){
  this->mode      = mode;
  this->count     = count;
  this->type      = type;
  this->indices   = indices;
  this->drawCount = drawCount;
}
void MultiDrawElements::apply(){
  glMultiDrawElements(
      this->mode,
      this->count,
      this->type,
      (const GLvoid**)this->indices,
      this->drawCount);
}
DrawRangeElements::DrawRangeElements(
    GLenum   mode,
    GLuint   start,
    GLuint   end,
    GLsizei  count,
    GLenum   type,
    GLvoid  *indices){
  this->mode    = mode;
  this->start   = start;
  this->end     = end;
  this->count   = count;
  this->type    = type;
  this->indices = indices;
}
void DrawRangeElements::apply(){
  glDrawRangeElements(
      this->mode,
      this->start,
      this->end,
      this->count,
      this->type,
      this->indices);
}

DrawElementsBaseVertex::DrawElementsBaseVertex(
    GLenum        mode      ,
    GLsizei       count     ,
    GLenum        type      ,
    const GLvoid* indices   ,
    GLint         baseVertex):DrawElements(mode,count,type,indices){
  this->setBaseVertex(baseVertex);
}
void DrawElementsBaseVertex::apply(){
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
    GLenum   mode,
    GLuint   start,
    GLuint   end,
    GLsizei  count,
    GLenum   type,
    GLvoid  *indices,
    GLint    baseVertex){
  this->mode       = mode;
  this->start      = start;
  this->end        = end;
  this->count      = count;
  this->type       = type;
  this->indices    = indices;
  this->baseVertex = baseVertex;
}
void DrawRangeElementsBaseVertex::apply(){
  glDrawRangeElementsBaseVertex(
      this->mode,
      this->start,
      this->end,
      this->count,
      this->type,
      this->indices,
      this->baseVertex);
}

DrawElementsInstancedBaseVertex::DrawElementsInstancedBaseVertex(
    GLenum        mode         ,
    GLsizei       count        ,
    GLenum        type         ,
    const GLvoid* indices      ,
    GLsizei       instanceCount,
    GLint         baseVertex   ):DrawElementsBaseVertex(mode,count,type,indices,baseVertex),DrawInstanced(instanceCount){
}
void DrawElementsInstancedBaseVertex::apply(){
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
void DrawElementsInstancedBaseVertexBaseInstance::apply(){
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
void DrawElementsIndirect::apply(){
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
void MultiDrawElementsIndirect::apply(){
  glMultiDrawElementsIndirect(
      this->_mode     ,
      this->_type     ,
      this->_indirect ,
      this->_drawCount,
      this->_stride   );
}
MultiDrawElementsBaseVertex::MultiDrawElementsBaseVertex(
    GLenum    mode,
    GLsizei  *count,
    GLenum    type,
    GLvoid  **indices,
    GLsizei   drawCount,
    GLint    *baseVertex){
  this->mode       = mode;
  this->count      = count;
  this->type       = type;
  this->indices    = indices;
  this->drawCount  = drawCount;
  this->baseVertex = baseVertex;
}
void MultiDrawElementsBaseVertex::apply(){
  glMultiDrawElementsBaseVertex(
      this->mode,
      this->count,
      this->type,
      this->indices,
      this->drawCount,
      this->baseVertex);
}
