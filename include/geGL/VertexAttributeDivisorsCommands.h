#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT VertexBindingDivisor: public ge::core::Command
    {
      public:
        GLuint bindingIndex;
        GLuint divisor;
        VertexBindingDivisor(
            GLuint bindingIndex,
            GLuint divisor);
        void operator()();
    };
    class GEGL_EXPORT VertexAttribDivisor: public ge::core::Command
    {
      public:
        GLuint index;
        GLuint divisor;
        VertexAttribDivisor(
            GLuint index,
            GLuint divisor);
        void operator()();
    };
  }//ogl
}//ge

