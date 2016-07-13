#include <geGL/OpenGLObject.h>

using namespace ge::gl;
using namespace ge::gl::opengl;

OpenGLObject::OpenGLObject(GLuint id):FunctionProvider(nullptr){
  this->_id = id;
}

OpenGLObject::OpenGLObject(
    FunctionTablePointer const&table,
    GLuint id):FunctionProvider(table){
  this->_id = id;
}

OpenGLObject::~OpenGLObject(){
  this->_id = 0;
}

GLuint OpenGLObject::getId()const{
  return this->_id;
}

