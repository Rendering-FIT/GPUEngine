#include<geGL/ProgramPipelineObject.h>

//#define USE_DSA

using namespace ge::gl;
using namespace ge::gl::opengl;

ProgramPipelineObject::ProgramPipelineObject(){
  glCreateProgramPipelines(1,&this->_id);
}

#if defined(REPLACE_GLEW)
ProgramPipelineObject::ProgramPipelineObject(
    FunctionTablePointer const&table):OpenGLObject(table){
  glCreateProgramPipelines(1,&this->_id);
}
#endif


ProgramPipelineObject::~ProgramPipelineObject(){
  glDeleteProgramPipelines(1,&this->_id);
}

void ProgramPipelineObject::bind()const{
  glBindProgramPipeline(this->_id);
}

void ProgramPipelineObject::unbind()const{
  glBindProgramPipeline(0);
}
void ProgramPipelineObject::useProgramStages(GLbitfield stages,GLuint program)const{
  glUseProgramStages(this->_id,stages,program);
}
void ProgramPipelineObject::useVertexStage    (GLuint program)const{
  glUseProgramStages(this->_id,GL_VERTEX_SHADER_BIT,program);
}
void ProgramPipelineObject::useControlStage   (GLuint program)const{
  glUseProgramStages(this->_id,GL_TESS_CONTROL_SHADER_BIT,program);
}
void ProgramPipelineObject::useEvaluationStage(GLuint program)const{
  glUseProgramStages(this->_id,GL_TESS_EVALUATION_SHADER_BIT,program);
}
void ProgramPipelineObject::useGeometryStage  (GLuint program)const{
  glUseProgramStages(this->_id,GL_GEOMETRY_SHADER_BIT,program);
}
void ProgramPipelineObject::useFragmentStage  (GLuint program)const{
  glUseProgramStages(this->_id,GL_FRAGMENT_SHADER_BIT,program);
}
void ProgramPipelineObject::useComputeStage   (GLuint program)const{
  glUseProgramStages(this->_id,GL_COMPUTE_SHADER_BIT,program);
}

