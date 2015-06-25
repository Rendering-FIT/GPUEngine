#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
namespace ge{
  namespace gl  {
    class GEGL_EXPORT LogicOp: public ge::core::Command
    {
      public:
        GLenum op;
        LogicOp(GLenum op);
        void operator()();
    };
  }//ogl
}//ge

