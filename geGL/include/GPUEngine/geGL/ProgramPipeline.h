#pragma once

#include<GPUEngine/geGL/OpenGLObject.h>

class GEGL_EXPORT ge::gl::ProgramPipeline: public OpenGLObject{
  public:
    ProgramPipeline();
    ProgramPipeline(FunctionTablePointer const&table);
    ~ProgramPipeline();
    void bind()const;
    void unbind()const;
    void useProgramStages(GLbitfield stages,GLuint program)const;
    void useVertexStage    (GLuint program)const;
    void useControlStage   (GLuint program)const;
    void useEvaluationStage(GLuint program)const;
    void useGeometryStage  (GLuint program)const;
    void useFragmentStage  (GLuint program)const;
    void useComputeStage   (GLuint program)const;
};

