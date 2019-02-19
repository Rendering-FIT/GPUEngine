#include<geGL/OpenGL.h>

#include<geGL/OpenGLFunctionTable.h>
#include<geGL/LoaderTableDecorator.h>
#include<geGL/DSATableDecorator.h>
#include<geGL/CapabilitiesTableDecorator.h>
#include<geGL/TrapTableDecorator.h>
#include<geGL/OpenGLCapabilities.h>
#include<geGL/OpenGLContext.h>

thread_local ge::gl::FunctionTablePointer _defaultOpenGLFunctionTable = nullptr;
thread_local ge::gl::ContextPointer       _defaultOpenGLContext       = nullptr;

using namespace ge::gl;

/**
 * @brief Function returns default, global OpenGLFunctionTable
 *
 * @return default OpenGLFunctionTable
 */
ge::gl::FunctionTablePointer const&ge::gl::getDefaultFunctionTable(){
  return _defaultOpenGLFunctionTable;
}

/**
 * @brief Function returns default OpenGLContext
 *
 * @return default OpenGLfunctionProvider
 */
ge::gl::ContextPointer const& ge::gl::getDefaultContext(){
  return _defaultOpenGLContext;
}

/**
 * @brief Function sets default, global OpenGLFunctionTable
 *
 * @param OpenGLFunctionTable
 */
void ge::gl::setDefaultFunctionTable   (FunctionTablePointer    const&table   ){
  _defaultOpenGLFunctionTable = table;
  if(_defaultOpenGLContext)
    _defaultOpenGLContext->setFunctionTable(table);
}

/**
 * @brief Function sets default, global OpenGLContext
 *
 * @param provider OpenGLContext
 */
void ge::gl::setDefaultContext(ContextPointer const&provider){
  _defaultOpenGLContext = provider;
}

/**
 * @brief Function creates OpenGL function table
 * Function table is decorated using LoaderTableDecorator, DSATableDecorator, CapabilitiesTableDecorator and TrapTableDecorator
 *
 * @param loader valid FunctionLoaderInterface that can load OpenGL functions
 *
 * @return OpenGLFunctionTable
 */
FunctionTablePointer ge::gl::createTable(FunctionLoaderInterfacePointer const&loader){
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
 * @brief Function creates Context instance
 *
 * @param table FunctionTable
 *
 * @return Context
 */
ContextPointer ge::gl::createContext(FunctionTablePointer const&table){
  return std::make_shared<Context>(table);
}



