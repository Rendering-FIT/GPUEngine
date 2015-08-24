#pragma once

#include<geGL/OpenGL.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT OpenGLObject{
      protected:
        GLuint _id;///<object id
      public:
        OpenGLObject(GLuint id = 0);
        GLuint getId();
        virtual ~OpenGLObject(){};
    };
  }//gl
}//ge

