#include<geGL/CheckOpenGLFunctions.h>

#include<iostream>

#include<geGL/OpenGLFunctionTable.h>
#include<geGL/Export.h>
#include<geGL/Generated/OpenGLTrapFunctions.h>

using namespace ge::gl::opengl;

void ge::gl::opengl::checkFunctions(FunctionTablePointer const&table){
#include<geGL/Generated/CheckOpenGLFunctions.h>
}


