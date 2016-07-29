#include <geGL/OpenGLObject.h>
#include<cassert>

using namespace ge::gl;
using namespace ge::gl::opengl;

OpenGLObject::OpenGLObject(GLuint id):FunctionProvider(nullptr){
  assert(this!=nullptr);
  this->_id = id;
}

OpenGLObject::OpenGLObject(
    FunctionTablePointer const&table,
    GLuint id):FunctionProvider(table){
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

