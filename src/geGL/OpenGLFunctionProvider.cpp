#include<geGL/OpenGLFunctionProvider.h>
#include<geGL/geGL.h>

using namespace ge::gl::opengl;

FunctionProvider::FunctionProvider(FunctionTablePointer const&table){
  if(table == nullptr)this->_table = ge::gl::opengl::getDefaultFunctionTable();
  else this->_table = table;
}

