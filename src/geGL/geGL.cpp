#include<geGL/geGL.h>

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

void ge::gl::init(std::shared_ptr<opengl::FunctionLoaderInterface>const&loader){
  if(loader){
    _defaultOpenGLFunctionTable = std::make_shared<
      TrapTableDecorator<
        CapabilitiesTableDecorator<
          DSATableDecorator<
            LoaderTableDecorator<
              FunctionTable>>>>>(loader);
    _defaultOpenGLFunctionTable->construct();
  }else
    _defaultOpenGLFunctionTable = nullptr;
  _defaultOpenGLFunctionProvider = 
    std::make_shared<FunctionProvider>(_defaultOpenGLFunctionTable);
}

ge::gl::opengl::FunctionTablePointer const&ge::gl::opengl::getDefaultFunctionTable(){
  return _defaultOpenGLFunctionTable;
}

ge::gl::opengl::FunctionProviderPointer const& ge::gl::opengl::getDefaultFunctionProvider(){
  return _defaultOpenGLFunctionProvider;
}

