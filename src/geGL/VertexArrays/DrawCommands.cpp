#include <geGL/VertexArrays/DrawCommands.h>

namespace ge
{
  namespace gl
  {
    DrawArrays::DrawArrays(GLenum mode,GLint first,GLsizei count){
      this->mode  = mode;
      this->first = first;
      this->count = count;
    }
    void DrawArrays::apply(){
      glDrawArrays(
          this->mode,
          this->first,
          this->count);
    }
    DrawArraysInstancedBaseInstance::DrawArraysInstancedBaseInstance(
        GLenum  mode,
        GLint   first,
        GLsizei count,
        GLsizei instanceCount,
        GLuint  baseInstance){
      this->mode  = mode;
      this->first = first;
      this->count = count;
      this->instanceCount = instanceCount;
      this->baseInstance = baseInstance;
    }
    void DrawArraysInstancedBaseInstance::apply(){
      glDrawArraysInstancedBaseInstance(
          this->mode,
          this->first,
          this->count,
          this->instanceCount,
          this->baseInstance);
    }
    DrawArraysInstanced::DrawArraysInstanced(
        GLenum  mode,
        GLint   first,
        GLsizei count,
        GLsizei instanceCount){
      this->mode          = mode;
      this->first         = first;
      this->count         = count;
      this->instanceCount = instanceCount;
    }
    void DrawArraysInstanced::apply(){
      glDrawArraysInstanced(
          this->mode,
          this->first,
          this->count,
          this->instanceCount);
    }
    DrawArraysIndirect::DrawArraysIndirect(GLenum mode,GLvoid*indirect){
      this->mode     = mode;
      this->indirect = indirect;
    }
    void DrawArraysIndirect::apply(){
      glDrawArraysIndirect(
          this->mode,
          this->indirect);
    }
    MultiDrawArrays::MultiDrawArrays(
        GLenum   mode,
        GLint   *first,
        GLsizei *count,
        GLsizei  drawCount){
      this->mode      = mode;
      this->first     = first;
      this->count     = count;
      this->drawCount = drawCount;
    }
    void MultiDrawArrays::apply(){
      glMultiDrawArrays(
          this->mode,
          this->first,
          this->count,
          this->drawCount);
    }
    MultiDrawArraysIndirect::MultiDrawArraysIndirect(
        GLenum   mode,
        GLvoid  *indirect,
        GLsizei  drawCount,
        GLsizei  stride){
      this->mode      = mode;
      this->indirect  = indirect;
      this->drawCount = drawCount;
      this->stride    = stride;
    }
    void MultiDrawArraysIndirect::apply(){
      glMultiDrawArraysIndirect(
          this->mode,
          this->indirect,
          this->drawCount,
          this->stride);
    }
    DrawElements::DrawElements(
        GLenum   mode,
        GLsizei  count,
        GLenum   type,
        GLvoid  *indices){
      this->mode    = mode;
      this->count   = count;
      this->type    = type;
      this->indices = indices;
    }
    void DrawElements::apply(){
      glDrawElements(
          this->mode,
          this->count,
          this->type,
          this->indices);
    }
    DrawElementsInstancedBaseInstance::DrawElementsInstancedBaseInstance(
        GLenum   mode,
        GLsizei  count,
        GLenum   type,
        GLvoid  *indices,
        GLsizei  instanceCount,
        GLuint   baseInstance){
      this->mode          = mode;
      this->count         = count;
      this->type          = type;
      this->indices       = indices;
      this->instanceCount = instanceCount;
      this->baseInstance  = baseInstance;
    }
    void DrawElementsInstancedBaseInstance::apply(){
      glDrawElementsInstancedBaseInstance(
          this->mode,
          this->count,
          this->type,
          this->indices,
          this->instanceCount,
          this->baseInstance);
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
        GLenum   mode,
        GLsizei  count,
        GLenum   type,
        GLvoid  *indices,
        GLint    baseVertex){
      this->mode       = mode;
      this->count      = count;
      this->type       = type;
      this->indices    = indices;
      this->baseVertex = baseVertex;
    }
    void DrawElementsBaseVertex::apply(){
      glDrawElementsBaseVertex(
          this->mode,
          this->count,
          this->type,
          this->indices,
          this->baseVertex);
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
        GLenum   mode,
        GLsizei  count,
        GLenum   type,
        GLvoid  *indices,
        GLsizei  instanceCount,
        GLint    baseVertex){
      this->mode          = mode;
      this->count         = count;
      this->type          = type;
      this->indices       = indices;
      this->instanceCount = instanceCount;
      this->baseVertex    = baseVertex;
    }
    void DrawElementsInstancedBaseVertex::apply(){
      glDrawElementsInstancedBaseVertex(
          this->mode,
          this->count,
          this->type,
          this->indices,
          this->instanceCount,
          this->baseVertex);
    }
    DrawElementsInstancedBaseVertexBaseInstance::DrawElementsInstancedBaseVertexBaseInstance(
        GLenum   mode,
        GLsizei  count,
        GLenum   type,
        GLvoid  *indices,
        GLsizei  instanceCount,
        GLint    baseVertex,
        GLuint   baseInstance){
      this->mode          = mode;
      this->count         = count;
      this->type          = type;
      this->indices       = indices;
      this->instanceCount = instanceCount;
      this->baseVertex    = baseVertex;
      this->baseInstance  = baseInstance;
    }
    void DrawElementsInstancedBaseVertexBaseInstance::apply(){
      glDrawElementsInstancedBaseVertexBaseInstance(
          this->mode,
          this->count,
          this->type,
          this->indices,
          this->instanceCount,
          this->baseVertex,
          this->baseInstance);
    }
    DrawElementsIndirect::DrawElementsIndirect(
        GLenum  mode,
        GLenum  type,
        GLvoid *indirect){
      this->mode     = mode;
      this->type     = type;
      this->indirect = indirect;
    }
    void DrawElementsIndirect::apply(){
      glDrawElementsIndirect(
          this->mode,
          this->type,
          this->indirect);
    }
    MultiDrawElementsIndirect::MultiDrawElementsIndirect(
        GLenum   mode,
        GLenum   type,
        GLvoid  *indirect,
        GLsizei  drawCount,
        GLsizei  stride){
      this->mode      = mode;
      this->type      = type;
      this->indirect  = indirect;
      this->drawCount = drawCount;
      this->stride    = stride;
    }
    void MultiDrawElementsIndirect::apply(){
      glMultiDrawElementsIndirect(
          this->mode,
          this->type,
          this->indirect,
          this->drawCount,
          this->stride);
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
  }//ogl
}//ge
