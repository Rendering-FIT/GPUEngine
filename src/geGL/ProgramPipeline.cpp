#include<geGL/ProgramPipeline.h>

using namespace ge::gl;
using namespace ge::gl::opengl;

ProgramPipeline::ProgramPipeline(){
  glCreateProgramPipelines(1,&this->_id);
}

ProgramPipeline::ProgramPipeline(
    FunctionTablePointer const&table):OpenGLObject(table){
  glCreateProgramPipelines(1,&this->_id);
}

ProgramPipeline::~ProgramPipeline(){
  glDeleteProgramPipelines(1,&this->_id);
}

void ProgramPipeline::bind()const{
  glBindProgramPipeline(this->_id);
}

void ProgramPipeline::unbind()const{
  glBindProgramPipeline(0);
}
void ProgramPipeline::useProgramStages(GLbitfield stages,GLuint program)const{
  glUseProgramStages(this->_id,stages,program);
}
void ProgramPipeline::useVertexStage    (GLuint program)const{
  glUseProgramStages(this->_id,GL_VERTEX_SHADER_BIT,program);
}
void ProgramPipeline::useControlStage   (GLuint program)const{
  glUseProgramStages(this->_id,GL_TESS_CONTROL_SHADER_BIT,program);
}
void ProgramPipeline::useEvaluationStage(GLuint program)const{
  glUseProgramStages(this->_id,GL_TESS_EVALUATION_SHADER_BIT,program);
}
void ProgramPipeline::useGeometryStage  (GLuint program)const{
  glUseProgramStages(this->_id,GL_GEOMETRY_SHADER_BIT,program);
}
void ProgramPipeline::useFragmentStage  (GLuint program)const{
  glUseProgramStages(this->_id,GL_FRAGMENT_SHADER_BIT,program);
}
void ProgramPipeline::useComputeStage   (GLuint program)const{
  glUseProgramStages(this->_id,GL_COMPUTE_SHADER_BIT,program);
}

