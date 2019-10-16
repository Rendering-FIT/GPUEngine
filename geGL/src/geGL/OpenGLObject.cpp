#include<geGL/OpenGLObject.h>
#include<cassert>

using namespace ge::gl;

class ge::gl::OpenGLObjectImpl {
public:
  GLuint id = 0u;///<object id
  Context gl;
  OpenGLObjectImpl(FunctionTablePointer const&table, GLuint id = 0u) :id(id), gl(table) {}
  GLuint getId()const {
    return id;
  }
  GLuint&getId() {
    return id;
  }
  Context const&getContext()const {
    return gl;
  }
};

OpenGLObject::OpenGLObject(GLuint id) :OpenGLObject(nullptr, id) {}

OpenGLObject::OpenGLObject(
    FunctionTablePointer const&table,
    GLuint id){
  impl = new OpenGLObjectImpl(table, id);
}

OpenGLObject::~OpenGLObject(){
  assert(this!=nullptr);
  delete impl;
}

GLuint OpenGLObject::getId()const{
  assert(this!=nullptr);
  return this->impl->getId();
}

GLuint&OpenGLObject::getId(){
  assert(this != nullptr);
  return this->impl->getId();
}

ge::gl::Context const&OpenGLObject::getContext()const{
  return this->impl->getContext();
}
