#include<GPUEngine/geGL/OpenGLContext.h>
#include<GPUEngine/geGL/OpenGLFunctionTable.h>

using namespace ge::gl;

Context::Context(FunctionTablePointer const&table){
  assert(this!=nullptr);
  if(table == nullptr)this->m_table = ge::gl::getDefaultFunctionTable();
  else this->m_table = table;
}

#include<GPUEngine/geGL/Generated/ContextCalls.h>
