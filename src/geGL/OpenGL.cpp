#include<geGL/OpenGL.h>

#include<geGL/OpenGLFunctionTable.h>
#include<geGL/LoaderTableDecorator.h>
#include<geGL/DSATableDecorator.h>
#include<geGL/CapabilitiesTableDecorator.h>
#include<geGL/TrapTableDecorator.h>
#include<geGL/OpenGLCapabilities.h>
#include<geGL/OpenGLFunctionProvider.h>

thread_local ge::gl::opengl::FunctionTablePointer    _defaultOpenGLFunctionTable    = nullptr;
thread_local ge::gl::opengl::FunctionProviderPointer _defaultOpenGLFunctionProvider = nullptr;

using namespace ge::gl;
using namespace ge::gl::opengl;

/**
 * @brief Function returns default, global OpenGLFunctionTable
 *
 * @return default OpenGLFunctionTable
 */
ge::gl::opengl::FunctionTablePointer const&ge::gl::opengl::getDefaultFunctionTable(){
  return _defaultOpenGLFunctionTable;
}

/**
 * @brief Function returns default OpenGLFunctionProvider
 *
 * @return default OpenGLfunctionProvider
 */
ge::gl::opengl::FunctionProviderPointer const& ge::gl::opengl::getDefaultFunctionProvider(){
  return _defaultOpenGLFunctionProvider;
}

/**
 * @brief Function sets default, global OpenGLFunctionTable
 *
 * @param OpenGLFunctionTable
 */
void ge::gl::opengl::setDefaultFunctionTable   (FunctionTablePointer    const&table   ){
  _defaultOpenGLFunctionTable = table;
  if(_defaultOpenGLFunctionProvider)
    _defaultOpenGLFunctionProvider->setFunctionTable(table);
}

/**
 * @brief Function sets default, global OpenGLFunctionProvider
 *
 * @param provider OpenGLFunctionProvider
 */
void ge::gl::opengl::setDefaultFunctionProvider(FunctionProviderPointer const&provider){
  _defaultOpenGLFunctionProvider = provider;
}

/**
 * @brief Function creates OpenGL function table
 * Function table is decorated using LoaderTableDecorator, DSATableDecorator, CapabilitiesTableDecorator and TrapTableDecorator
 *
 * @param loader valid FunctionLoaderInterface that can load OpenGL functions
 *
 * @return OpenGLFunctionTable
 */
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

/**
 * @brief Function creates FunctionProvider instance
 *
 * @param table FunctionTable
 *
 * @return FunctionProvider
 */
FunctionProviderPointer ge::gl::opengl::createProvider(FunctionTablePointer const&table){
  return std::make_shared<FunctionProvider>(table);
}



