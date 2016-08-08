#include <geGL/OpenGLObject.h>
#include<cassert>

using namespace ge::gl;
using namespace ge::gl::opengl;

OpenGLObject::OpenGLObject(GLuint id):Context(nullptr){
  assert(this!=nullptr);
  this->_id = id;
}

OpenGLObject::OpenGLObject(
    FunctionTablePointer const&table,
    GLuint id):Context(table){
  assert(this!=nullptr);
  this->_id = id;
}

OpenGLObject::~OpenGLObject(){
  assert(this!=nullptr);
  this->_id = 0;
}

GLuint OpenGLObject::getId()const{
  assert(this!=nullptr);
  return this->_id;
}

opengl::Context const*OpenGLObject::getContext()const{
  return this;
}
