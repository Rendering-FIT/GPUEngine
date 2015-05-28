#include<geGL/ProgramCommands.h>

using namespace ge::gl;

UseProgram::UseProgram(GLuint program){
  this->set(program);
}

void UseProgram::apply(){
  glUseProgram(this->_program);
}

void UseProgram::set(GLuint program){
  this->_program = program;
}

GLuint UseProgram::get(){
  return this->_program;
}

UseProgramR::UseProgramR(GLuint*program){
  this->set(program);
}
void UseProgramR::apply(){
  if(this->_program)glUseProgram(*this->_program);
}
void UseProgramR::set(GLuint*program){
  this->_program=program;
}
GLuint*UseProgramR::get(){
  return this->_program;
}

