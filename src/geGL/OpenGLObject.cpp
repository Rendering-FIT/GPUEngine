#include <geGL/OpenGLObject.h>

using namespace ge::gl;

OpenGLObject::OpenGLObject(GLuint id){
  this->_id = id;
}

GLuint OpenGLObject::getId(){
  return this->_id;
}

