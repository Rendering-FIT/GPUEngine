#include<geGL/OpenGLContext.h>
#include<geGL/OpenGLFunctionTable.h>

using namespace ge::gl;

Context::Context(FunctionTablePointer const&table){
  assert(this!=nullptr);
  if(table == nullptr)this->m_table = ge::gl::getDefaultFunctionTable();
  else this->m_table = table;
}

#include<geGL/Generated/ContextCalls.h>
