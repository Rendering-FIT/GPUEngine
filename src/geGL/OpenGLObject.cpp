#include <geGL/OpenGLObject.h>

using namespace ge::gl;
using namespace ge::gl::opengl;

OpenGLObject::OpenGLObject(GLuint id)
#if defined(REPLACE_GLEW)
  :FunctionProvider(nullptr)
#endif//REPLACE_GLEW
{
  this->_id = id;
}

#if defined(REPLACE_GLEW)
OpenGLObject::OpenGLObject(
    FunctionTablePointer const&table,
    GLuint id):FunctionProvider(table){
  this->_id = id;
}
#endif//REPLACE_GLEW


OpenGLObject::~OpenGLObject(){
  this->_id = 0;
}

GLuint OpenGLObject::getId()const{
  return this->_id;
}

