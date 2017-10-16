#include<GPUEngine/geGL/ProgramPipeline.h>

using namespace ge::gl;

ProgramPipeline::ProgramPipeline(){
  assert(this!=nullptr);
  this->_gl.glCreateProgramPipelines(1,&this->_id);
}

ProgramPipeline::ProgramPipeline(
    FunctionTablePointer const&table):OpenGLObject(table){
  assert(this!=nullptr);
  this->_gl.glCreateProgramPipelines(1,&this->_id);
}

ProgramPipeline::~ProgramPipeline(){
  assert(this!=nullptr);
  this->_gl.glDeleteProgramPipelines(1,&this->_id);
}

void ProgramPipeline::bind()const{
  assert(this!=nullptr);
  this->_gl.glBindProgramPipeline(this->_id);
}

void ProgramPipeline::unbind()const{
  assert(this!=nullptr);
  this->_gl.glBindProgramPipeline(0);
}
void ProgramPipeline::useProgramStages(GLbitfield stages,GLuint program)const{
  assert(this!=nullptr);
  this->_gl.glUseProgramStages(this->_id,stages,program);
}
void ProgramPipeline::useVertexStage    (GLuint program)const{
  assert(this!=nullptr);
  this->_gl.glUseProgramStages(this->_id,GL_VERTEX_SHADER_BIT,program);
}
void ProgramPipeline::useControlStage   (GLuint program)const{
  assert(this!=nullptr);
  this->_gl.glUseProgramStages(this->_id,GL_TESS_CONTROL_SHADER_BIT,program);
}
void ProgramPipeline::useEvaluationStage(GLuint program)const{
  assert(this!=nullptr);
  this->_gl.glUseProgramStages(this->_id,GL_TESS_EVALUATION_SHADER_BIT,program);
}
void ProgramPipeline::useGeometryStage  (GLuint program)const{
  assert(this!=nullptr);
  this->_gl.glUseProgramStages(this->_id,GL_GEOMETRY_SHADER_BIT,program);
}
void ProgramPipeline::useFragmentStage  (GLuint program)const{
  assert(this!=nullptr);
  this->_gl.glUseProgramStages(this->_id,GL_FRAGMENT_SHADER_BIT,program);
}
void ProgramPipeline::useComputeStage   (GLuint program)const{
  assert(this!=nullptr);
  this->_gl.glUseProgramStages(this->_id,GL_COMPUTE_SHADER_BIT,program);
}

