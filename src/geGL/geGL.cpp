#include<geGL/OpenGL.h>
#include<geGL/DefaultLoader.h>

namespace ge{
  namespace gl{
    GEGL_EXPORT void init(std::shared_ptr<FunctionLoaderInterface>const&loader){
      auto table = ge::gl::createTable(loader);
      ge::gl::setDefaultFunctionTable(table);
      ge::gl::setDefaultContext(ge::gl::createContext(table));
    }
    GEGL_EXPORT void init(GET_PROC_ADDRESS getProcAddress){
      auto loader = std::make_shared<DefaultLoader>(getProcAddress);
      init(loader);
    }
  }
}


