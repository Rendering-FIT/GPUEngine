#include<geGL/ProgramObjectUniformCommands.h>

using namespace ge::gl;

//*
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLfloat a0){
  return new Uniform<1,GLfloat>(program->getUniform(name),a0);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1){
  return new Uniform<2,GLfloat>(program->getUniform(name),a0,a1);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1,GLfloat a2){
  return new Uniform<3,GLfloat>(program->getUniform(name),a0,a1,a2);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLfloat a0,GLfloat a1,GLfloat a2,GLfloat a3){
  return new Uniform<4,GLfloat>(program->getUniform(name),a0,a1,a2,a3);
}

ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLint a0){
  return new Uniform<1,GLint>(program->getUniform(name),a0);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLint a0,GLint a1){
  return new Uniform<2,GLint>(program->getUniform(name),a0,a1);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLint a0,GLint a1,GLint a2){
  return new Uniform<3,GLint>(program->getUniform(name),a0,a1,a2);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLint a0,GLint a1,GLint a2,GLint a3){
  return new Uniform<4,GLint>(program->getUniform(name),a0,a1,a2,a3);
}

ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLuint a0){
  return new Uniform<1,GLuint>(program->getUniform(name),a0);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1){
  return new Uniform<2,GLuint>(program->getUniform(name),a0,a1);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1,GLuint a2){
  return new Uniform<3,GLuint>(program->getUniform(name),a0,a1,a2);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLuint a0,GLuint a1,GLuint a2,GLuint a3){
  return new Uniform<4,GLuint>(program->getUniform(name),a0,a1,a2,a3);
}

ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLdouble a0){
  return new Uniform<1,GLdouble>(program->getUniform(name),a0);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1){
  return new Uniform<2,GLdouble>(program->getUniform(name),a0,a1);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1,GLdouble a2){
  return new Uniform<3,GLdouble>(program->getUniform(name),a0,a1,a2);
}
ge::core::Command*ge::gl::newUniform(ProgramObject*program,std::string name,GLdouble a0,GLdouble a1,GLdouble a2,GLdouble a3){
  return new Uniform<4,GLdouble>(program->getUniform(name),a0,a1,a2,a3);
}
// */
