#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<geGL/ProgramObject.h>
#include<geGL/UniformCommands.h>
#include<geCore/dtemplates.h>

namespace ge{
  namespace gl{
    /*

    template<typename... ARGS>
    ge::core::Command*newUniform(ProgramObject*program,std::string name,ARGS... args){
      return new ge::gl::Uniform<sizeof(args)...,GLfloat>(program->getUniform(name),args...);
    }
    
    template<typename... ARGS>
    ge::core::Command*newUniform(ProgramObject*program,std::string name,ARGS... args){
      return new ge::gl::Uniform<sizeof(args)...,GLint>(program->getUniform(name),args...);
    }
    template<typename... ARGS>
    ge::core::Command*newUniform(ProgramObject*program,std::string name,ARGS... args){
      return new ge::gl::Uniform<sizeof(args)...,GLuint>(program->getUniform(name),args...);
    }
    template<typename... ARGS>
    ge::core::Command*newUniform(ProgramObject*program,std::string name,ARGS... args){
      return new ge::gl::Uniform<sizeof(args)...,GLdouble>(program->getUniform(name),args...);
    }
    */

    
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLfloat a0);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1,GLfloat a2);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1,GLfloat a2,GLfloat a3);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLint a0);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLint a0,GLint a1);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLint a0,GLint a1,GLint a2);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLint a0,GLint a1,GLint a2,GLint a3);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLuint a0);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1,GLuint a2);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1,GLuint a2,GLuint a3);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLdouble a0);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1,GLdouble a2);
    GEGL_EXPORT ge::core::Command*newUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1,GLdouble a2,GLdouble a3);
    
  }
}
