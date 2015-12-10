#include <geRG/FlexibleUniform.h>

using namespace ge::rg;


thread_local std::shared_ptr<ge::gl::ProgramObject> FlexibleUseProgram::NoExport::_activeProgram;


void FlexibleUseProgram::operator()()
{
   inherited::operator()();
   NoExport::_activeProgram=inherited::program;
}
