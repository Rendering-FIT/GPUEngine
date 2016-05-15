#include<geGL/LoadOpenGLFunctions.h>

#include<geGL/OpenGLFunctionTable.h>

using namespace ge::gl::opengl;

void ge::gl::opengl::loadFunctions(
    FunctionTablePointer const&table,
    GET_PROC_ADDRESS getProcAddress){
#include<geGL/Generated/LoadOpenGLFunctions.h>
}


