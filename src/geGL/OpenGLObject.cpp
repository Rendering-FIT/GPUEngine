#include <geGL/OpenGLObject.h>

using namespace ge::gl;

OpenGLObject::OpenGLObject(GLuint id){
  this->_id = id;
}

OpenGLObject::~OpenGLObject(){
  this->_id = 0;
}

GLuint OpenGLObject::getId()const{
  return this->_id;
}

