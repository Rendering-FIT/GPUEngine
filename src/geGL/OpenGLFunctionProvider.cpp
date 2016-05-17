#include<geGL/OpenGLFunctionProvider.h>
#include<geGL/OpenGLFunctionTable.h>

using namespace ge::gl::opengl;

FunctionProvider::FunctionProvider(FunctionTablePointer const&table){
  if(table == nullptr)this->m_table = ge::gl::opengl::getDefaultFunctionTable();
  else this->m_table = table;
}

#include<geGL/Generated/FunctionProviderCalls.h>
