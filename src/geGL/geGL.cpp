#include<geGL/OpenGL.h>
#include<geGL/DefaultLoader.h>

namespace ge{
  namespace gl{
    GEGL_EXPORT void init(std::shared_ptr<opengl::FunctionLoaderInterface>const&loader){
      auto table = ge::gl::opengl::createTable(loader);
      ge::gl::opengl::setDefaultFunctionTable(table);
      ge::gl::opengl::setDefaultContext(ge::gl::opengl::createContext(table));
    }
    GEGL_EXPORT void init(opengl::GET_PROC_ADDRESS getProcAddress){
      auto loader = std::make_shared<opengl::DefaultLoader>(getProcAddress);
      init(loader);
    }
  }
}


