#include<geGL/ProgramPipeline.h>

using namespace ge::gl;

ProgramPipeline::ProgramPipeline(){
  assert(this!=nullptr);
  this->getContext().glCreateProgramPipelines(1,&this->getId());
}

ProgramPipeline::ProgramPipeline(
    FunctionTablePointer const&table):OpenGLObject(table){
  assert(this!=nullptr);
  this->getContext().glCreateProgramPipelines(1,&this->getId());
}

ProgramPipeline::~ProgramPipeline(){
  assert(this!=nullptr);
  this->getContext().glDeleteProgramPipelines(1,&this->getId());
}

void ProgramPipeline::bind()const{
  assert(this!=nullptr);
  this->getContext().glBindProgramPipeline(this->getId());
}

void ProgramPipeline::unbind()const{
  assert(this!=nullptr);
  this->getContext().glBindProgramPipeline(0);
}
void ProgramPipeline::useProgramStages(GLbitfield stages,GLuint program)const{
  assert(this!=nullptr);
  this->getContext().glUseProgramStages(this->getId(),stages,program);
}
void ProgramPipeline::useVertexStage    (GLuint program)const{
  assert(this!=nullptr);
  this->getContext().glUseProgramStages(this->getId(),GL_VERTEX_SHADER_BIT,program);
}
void ProgramPipeline::useControlStage   (GLuint program)const{
  assert(this!=nullptr);
  this->getContext().glUseProgramStages(this->getId(),GL_TESS_CONTROL_SHADER_BIT,program);
}
void ProgramPipeline::useEvaluationStage(GLuint program)const{
  assert(this!=nullptr);
  this->getContext().glUseProgramStages(this->getId(),GL_TESS_EVALUATION_SHADER_BIT,program);
}
void ProgramPipeline::useGeometryStage  (GLuint program)const{
  assert(this!=nullptr);
  this->getContext().glUseProgramStages(this->getId(),GL_GEOMETRY_SHADER_BIT,program);
}
void ProgramPipeline::useFragmentStage  (GLuint program)const{
  assert(this!=nullptr);
  this->getContext().glUseProgramStages(this->getId(),GL_FRAGMENT_SHADER_BIT,program);
}
void ProgramPipeline::useComputeStage   (GLuint program)const{
  assert(this!=nullptr);
  this->getContext().glUseProgramStages(this->getId(),GL_COMPUTE_SHADER_BIT,program);
}

