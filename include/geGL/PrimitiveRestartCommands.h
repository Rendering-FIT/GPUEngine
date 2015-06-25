#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT PrimitiveRestartIndex: public ge::core::Command
    {
      public:
        GLuint index;
        PrimitiveRestartIndex(
            GLuint index);
        void operator()();
    };
  }//ogl
}//ge

