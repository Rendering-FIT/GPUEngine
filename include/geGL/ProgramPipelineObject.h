#ifndef _PROGRAMPIPELINEOBJECT_H_
#define _PROGRAMPIPELINEOBJECT_H_

#include <geGL/Standard/OpenGL.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class ProgramPipelineObject
    {
      protected:
        GLuint _id;
      public:
        ProgramPipelineObject();
        ~ProgramPipelineObject();
        GLuint getId();
        void bind();
        void unbind();
        void useProgramStages(GLbitfield stages,GLuint program);
        void useVertexStage    (GLuint program);
        void useControlStage   (GLuint program);
        void useEvaluationStage(GLuint program);
        void useGeometryStage  (GLuint program);
        void useFragmentStage  (GLuint program);
        void useComputeStage   (GLuint program);
    };
  }//gl
}//ge

#endif//_PROGRAMPIPELINEOBJECT_H_
