#pragma once

#if  defined(REPLACE_GLEW)
#include<geGL/OpenGLFunctionProvider.h>
#else //defined(REPLACE_GLEW)
#include<geGL/OpenGL.h>
#endif//defined(REPLACE_GLEW)

namespace ge{
  namespace gl{
    class GEGL_EXPORT OpenGLObject
#if defined(REPLACE_GLEW)
    : protected OpenGLFunctionProvider
#endif//defined(REPLACE_GLEW)
      {
      protected:
        GLuint _id = 0u;///<object id
      public:
        OpenGLObject(GLuint id = 0u);
#if defined(REPLACE_GLEW)
        OpenGLObject(std::shared_ptr<OpenGLFunctionTable>const&table,GLuint id = 0u);
#endif//REPLACE_GLEW
        virtual ~OpenGLObject();
        GLuint getId()const;
    };
  }//gl
}//ge

