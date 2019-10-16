#pragma once

#include<geGL/OpenGLObject.h>

class ge::gl::ProgramPipeline: public OpenGLObject{
  public:
    GEGL_EXPORT ProgramPipeline();
	GEGL_EXPORT ProgramPipeline(FunctionTablePointer const&table);
	GEGL_EXPORT ~ProgramPipeline();
	GEGL_EXPORT void bind()const;
	GEGL_EXPORT void unbind()const;
	GEGL_EXPORT void useProgramStages(GLbitfield stages,GLuint program)const;
	GEGL_EXPORT void useVertexStage    (GLuint program)const;
	GEGL_EXPORT void useControlStage   (GLuint program)const;
	GEGL_EXPORT void useEvaluationStage(GLuint program)const;
	GEGL_EXPORT void useGeometryStage  (GLuint program)const;
	GEGL_EXPORT void useFragmentStage  (GLuint program)const;
	GEGL_EXPORT void useComputeStage   (GLuint program)const;
};

