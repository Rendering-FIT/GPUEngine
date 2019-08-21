#include<geGL/geGL.h>
#include<geGL/OpenGL.h>
#include<geGL/DefaultLoader.h>
#include<cassert>
#include<string>

#include <geGL/private/linux_OpenGLFunctionLoader.h>
#include <geGL/private/windows_OpenGLFunctionLoader.h>
#include <geGL/private/mac_OpenGLFunctionLoader.h>

void ge::gl::init(std::shared_ptr<FunctionLoaderInterface>const&loader){
  auto table = ge::gl::createTable(loader);
  ge::gl::setDefaultFunctionTable(table);
  ge::gl::setDefaultContext(ge::gl::createContext(table));
}

void ge::gl::init(GET_PROC_ADDRESS getProcAddress){
  auto loader = std::make_shared<DefaultLoader>(getProcAddress);
  init(loader);
}

void*ge::gl::getProcAddress(char const*name){
  static OpenGLFunctionLoader loader{};
  return loader(name);
}
