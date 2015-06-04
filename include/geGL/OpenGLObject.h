#ifndef _GE_GL_OPENGLOBJECT_H_
#define _GE_GL_OPENGLOBJECT_H_

#include <geGL/OpenGL.h>
#include <geCore/Object.h>

#include <iostream>

namespace ge{
  namespace gl{
    class GEGL_EXPORT OpenGLObject
    {
      protected:
        GLuint _id;///<object id
      public:
        GLuint getId();
        virtual ~OpenGLObject(){};
    };
  }//gl
}//ge


#endif//_GE_GL_OPENGLOBJECT_H_
