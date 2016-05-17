#include<geGL/OpenGL.h>

#include<geGL/OpenGLFunctionTable.h>
#include<geGL/LoaderTableDecorator.h>
#include<geGL/DSATableDecorator.h>
#include<geGL/CapabilitiesTableDecorator.h>
#include<geGL/TrapTableDecorator.h>
#include<geGL/OpenGLCapabilities.h>
#include<geGL/OpenGLFunctionProvider.h>

GEGL_EXPORT thread_local ge::gl::opengl::FunctionTablePointer    _defaultOpenGLFunctionTable    = nullptr;
GEGL_EXPORT thread_local ge::gl::opengl::FunctionProviderPointer _defaultOpenGLFunctionProvider = nullptr;

using namespace ge::gl;
using namespace ge::gl::opengl;

ge::gl::opengl::FunctionTablePointer const&ge::gl::opengl::getDefaultFunctionTable(){
  return _defaultOpenGLFunctionTable;
}

ge::gl::opengl::FunctionProviderPointer const& ge::gl::opengl::getDefaultFunctionProvider(){
  return _defaultOpenGLFunctionProvider;
}

void ge::gl::opengl::setDefaultFunctionTable   (FunctionTablePointer    const&table   ){
  _defaultOpenGLFunctionTable = table;
}

void ge::gl::opengl::setDefaultFunctionProvider(FunctionProviderPointer const&provider){
  _defaultOpenGLFunctionProvider = provider;
}

FunctionTablePointer ge::gl::opengl::createTable(FunctionLoaderInterfacePointer const&loader){
  auto table = std::make_shared<
    TrapTableDecorator<
    CapabilitiesTableDecorator<
    DSATableDecorator<
    LoaderTableDecorator<
    FunctionTable>>>>>(loader);
  table->construct();
  return table;
}

FunctionProviderPointer ge::gl::opengl::createProvider(FunctionTablePointer const&table){
  return std::make_shared<FunctionProvider>(table);
}



