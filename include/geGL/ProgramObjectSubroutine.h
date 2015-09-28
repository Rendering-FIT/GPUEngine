#pragma once

#include<iostream>
#include<map>
#include<geGL/ProgramObjectSubroutineUniform.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT ShaderObjectSubroutine{
      protected:
        std::map<std::string,ShaderObjectSubroutineUniform>_subroutineUniformList;
        std::map<std::string,GLuint>                       _subroutineList;
        GLuint* _indices    = nullptr;
        GLsizei _numIndices = 0      ;
      public:
        ~ShaderObjectSubroutine();
        ShaderObjectSubroutine();
        void addUniform(std::string name,ShaderObjectSubroutineUniform const&uniform);
        void addSubroutine(std::string name,GLuint location);
        void allocInidices(unsigned num);
        void set(GLenum type,std::string uniform,unsigned offset,std::string subroutine);
    };
  }//gl
}//ge

