#pragma once

#include<geGL/OpenGLContext.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT OpenGLObject{
      public:
        OpenGLObject(GLuint id = 0u);
        OpenGLObject(opengl::FunctionTablePointer const&table,GLuint id = 0u);
        virtual ~OpenGLObject();
        GLuint getId()const;
        opengl::Context const&getContext()const;
      protected:
        GLuint _id = 0u;///<object id
        opengl::Context _gl;
    };
  }//gl
}//ge

