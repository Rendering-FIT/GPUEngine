#include<geGL/UniformCommands.h>

using namespace ge::gl;

UniformCommand::UniformCommand(GLint location){
  this->_location=location;
}
UniformCommand::UniformCommand(ge::gl::ProgramObject*program,std::string name){
  this->_location=program->getUniform(name);
}

ProgramUniformCommand::ProgramUniformCommand(
    GLuint program,
    GLint location):UniformCommand(location){
  this->_program = program;
}
ProgramUniformCommand::ProgramUniformCommand(
    ge::gl::ProgramObject*program,
    std::string name):UniformCommand(program,name){
  this->_program = program->getId();
}

