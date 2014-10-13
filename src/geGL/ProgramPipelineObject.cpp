#include<geGL/ProgramPipelineObject.h>

//#define USE_DSA
namespace ge{
  namespace gl{
    ProgramPipelineObject::ProgramPipelineObject(){
#ifndef USE_DSA
      glGenProgramPipelines(1,&this->_id);
#else //USE_DSA
      glCreateProgramPipelines(1,&this->id);
#endif//USE_DSA
    }

    ProgramPipelineObject::~ProgramPipelineObject(){
      glDeleteProgramPipelines(1,&this->_id);
    }

    GLuint ProgramPipelineObject::getId(){
      return this->_id;
    }

    void ProgramPipelineObject::bind(){
      glBindProgramPipeline(this->_id);
    }

    void ProgramPipelineObject::unbind(){
      glBindProgramPipeline(0);
    }
    void ProgramPipelineObject::useProgramStages(GLbitfield stages,GLuint program){
      glUseProgramStages(this->_id,stages,program);
    }
    void ProgramPipelineObject::useVertexStage    (GLuint program){
      glUseProgramStages(this->_id,GL_VERTEX_SHADER_BIT,program);
    }
    void ProgramPipelineObject::useControlStage   (GLuint program){
      glUseProgramStages(this->_id,GL_TESS_CONTROL_SHADER_BIT,program);
    }
    void ProgramPipelineObject::useEvaluationStage(GLuint program){
      glUseProgramStages(this->_id,GL_TESS_EVALUATION_SHADER_BIT,program);
    }
    void ProgramPipelineObject::useGeometryStage  (GLuint program){
      glUseProgramStages(this->_id,GL_GEOMETRY_SHADER_BIT,program);
    }
    void ProgramPipelineObject::useFragmentStage  (GLuint program){
      glUseProgramStages(this->_id,GL_FRAGMENT_SHADER_BIT,program);
    }
    void ProgramPipelineObject::useComputeStage   (GLuint program){
      glUseProgramStages(this->_id,GL_COMPUTE_SHADER_BIT,program);
    }
  }//gl
}//ge
