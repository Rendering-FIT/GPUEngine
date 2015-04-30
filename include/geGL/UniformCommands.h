#pragma once

#include<geGL/OpenGL.h>
#include<geGL/ProgramObject.h>

namespace ge{
  namespace gl{
    /* How to share UniformCommands among more programs
     * 1. non DSA variant
     * Uniform require location and data
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     */
    class GEGL_EXPORT UniformCommand: public Command{
      protected:
        ge::gl::ProgramObject*_program;
        std::string           _name   ;
      public:
        UniformCommand(ge::gl::ProgramObject*program,std::string name);
        ge::gl::ProgramObject*getProgram();
        std::string getName();
    };
    class GEGL_EXPORT Uniform1F: public UniformCommand{
      public:
        float data;
        Uniform1F(ge::gl::ProgramObject,std::string name,float data);
    };
    class GEGL_EXPORT UniformCommandList: public CommandList{
      public:
        UniformCommandList(ge::gl::ProgramObject*program);
        UniformCommandList(UniformCommandList*set,ge::gl::ProgramObject*program);
    };

  }
}
