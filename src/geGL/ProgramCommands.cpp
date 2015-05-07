#include<geGL/ProgramCommands.h>

using namespace ge::gl;

UseProgram::UseProgram(GLuint program){this->program=program;}
void UseProgram::apply(){glUseProgram(this->program);}
