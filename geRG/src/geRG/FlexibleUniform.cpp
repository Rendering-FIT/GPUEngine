#include <geRG/FlexibleUniform.h>

using namespace ge::rg;


thread_local std::shared_ptr<ge::gl::Program> FlexibleUseProgram::NoExport::_activeProgram;


void FlexibleUseProgram::operator()()
{
   _program->use();
   NoExport::_activeProgram=_program;
}
