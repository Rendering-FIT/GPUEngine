#include<geGL/OpenGLFunctionProvider.h>
#include<geGL/geGL.h>

using namespace ge::gl;

OpenGLFunctionProvider::OpenGLFunctionProvider(std::shared_ptr<OpenGLFunctionTable>const&table){
  if(table == nullptr)this->_table = ge::gl::getDefaultOpenGLFunctionTable();
  else this->_table = table;
}

