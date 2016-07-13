#include<geGL/OpenGL.h>

namespace ge{
  namespace gl{
    void init(std::shared_ptr<opengl::FunctionLoaderInterface>const&loader){
      auto table = ge::gl::opengl::createTable(loader);
      ge::gl::opengl::setDefaultFunctionTable(table);
      ge::gl::opengl::setDefaultFunctionProvider(ge::gl::opengl::createProvider(table));
    }
  }
}


