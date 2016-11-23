#pragma once

#include<geGL/OpenGLObject.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT ProgramPipeline: public OpenGLObject{
      public:
        ProgramPipeline();
        ProgramPipeline(FunctionTablePointer const&table);
        ProgramPipeline(ProgramPipeline const&) = delete;
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
  }//gl
}//ge

