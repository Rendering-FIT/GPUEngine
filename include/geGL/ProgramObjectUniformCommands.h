#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<geGL/ProgramObject.h>
#include<geGL/UniformCommands.h>
#include<geCore/dtemplates.h>

namespace ge{
  namespace gl{
    /*
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
    GEGL_EXPORT ge::core::Command*newUniformV(ProgramObject*program,std::string name,const GLfloat* data,GLsizei count=1);
    GEGL_EXPORT ge::core::Command*newUniformV(ProgramObject*program,std::string name,const GLint*   data,GLsizei count=1);
    GEGL_EXPORT ge::core::Command*newUniformV(ProgramObject*program,std::string name,const GLuint*  data,GLsizei count=1);
    GEGL_EXPORT ge::core::Command*newUniformV(ProgramObject*program,std::string name,const GLdouble*data,GLsizei count=1);
    GEGL_EXPORT ge::core::Command*newUniformMatrix(ProgramObject*program,std::string name,const GLfloat* data,GLsizei count=1,GLboolean transpose = GL_FALSE);
    GEGL_EXPORT ge::core::Command*newUniformMatrix(ProgramObject*program,std::string name,const GLdouble*data,GLsizei count=1,GLboolean transpose = GL_FALSE);

    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLfloat a0);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1,GLfloat a2);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1,GLfloat a2,GLfloat a3);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLint a0);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLint a0,GLint a1);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLint a0,GLint a1,GLint a2);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLint a0,GLint a1,GLint a2,GLint a3);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLuint a0);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1,GLuint a2);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1,GLuint a2,GLuint a3);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLdouble a0);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1,GLdouble a2);
    GEGL_EXPORT ge::core::Command*newProgramUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1,GLdouble a2,GLdouble a3);
    GEGL_EXPORT ge::core::Command*newProgramUniformV(ProgramObject*program,std::string name,const GLfloat* data,GLsizei count=1);
    GEGL_EXPORT ge::core::Command*newProgramUniformV(ProgramObject*program,std::string name,const GLint*   data,GLsizei count=1);
    GEGL_EXPORT ge::core::Command*newProgramUniformV(ProgramObject*program,std::string name,const GLuint*  data,GLsizei count=1);
    GEGL_EXPORT ge::core::Command*newProgramUniformV(ProgramObject*program,std::string name,const GLdouble*data,GLsizei count=1);
    GEGL_EXPORT ge::core::Command*newProgramUniformMatrix(ProgramObject*program,std::string name,const GLfloat* data,GLsizei count=1,GLboolean transpose = GL_FALSE);
    GEGL_EXPORT ge::core::Command*newProgramUniformMatrix(ProgramObject*program,std::string name,const GLdouble*data,GLsizei count=1,GLboolean transpose = GL_FALSE);
    */
  }
}
