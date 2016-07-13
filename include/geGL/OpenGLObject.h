#pragma once

#include<geGL/OpenGLFunctionProvider.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT OpenGLObject: protected opengl::FunctionProvider
      {
      protected:
        GLuint _id = 0u;///<object id
      public:
        OpenGLObject(GLuint id = 0u);
        OpenGLObject(opengl::FunctionTablePointer const&table,GLuint id = 0u);
        virtual ~OpenGLObject();
        GLuint getId()const;
    };
  }//gl
}//ge

