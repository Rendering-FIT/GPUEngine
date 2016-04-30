#include<geGL/CheckOpenGLFunctions.h>

#include<iostream>

#include<geGL/OpenGLFunctionTable.h>
#include<geGL/Export.h>
#include<geGL/GeneratedOpenGLTrapFunctions.h>

using namespace ge::gl;

void ge::gl::checkOpenGLFunctions(std::shared_ptr<OpenGLFunctionTable>const&table){
#include<geGL/GeneratedCheckOpenGLFunctions.h>
}


