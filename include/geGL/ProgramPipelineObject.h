#ifndef _PROGRAMPIPELINEOBJECT_H_
#define _PROGRAMPIPELINEOBJECT_H_

#include <geGL/OpenGL.h>
#include<geGL/OpenGLObject.h>
namespace ge{
  namespace gl{
    class GEGL_EXPORT ProgramPipelineObject: public OpenGLObject
    {
      public:
        ProgramPipelineObject();
        ~ProgramPipelineObject();
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
