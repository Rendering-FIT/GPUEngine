#include <geGL/OpenGLObject.h>

using namespace ge::gl;

OpenGLObject::OpenGLObject(GLuint id)
#if defined(REPLACE_GLEW)
  :OpenGLFunctionProvider(nullptr)
#endif//REPLACE_GLEW
{
  this->_id = id;
}

#if defined(REPLACE_GLEW)
OpenGLObject::OpenGLObject(
    std::shared_ptr<OpenGLFunctionTable>const&table,
    GLuint id):OpenGLFunctionProvider(table){
  this->_id = id;
}
#endif//REPLACE_GLEW


OpenGLObject::~OpenGLObject(){
  this->_id = 0;
}

GLuint OpenGLObject::getId()const{
  return this->_id;
}

