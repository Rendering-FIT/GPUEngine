#include<geGL/LoadOpenGLFunctions.h>

#include<geGL/OpenGLFunctionTable.h>

using namespace ge::gl;

void ge::gl::loadOpenGLFunctions(std::shared_ptr<OpenGLFunctionTable>const&table,GET_PROC_ADDRESS getProcAddress){
#include<geGL/GeneratedLoadOpenGLFunctions.h>
}


