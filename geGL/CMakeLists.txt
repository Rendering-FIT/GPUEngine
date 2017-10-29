cmake_minimum_required(VERSION 3.1.0)
cmake_policy(VERSION 3.1)

#You should set up this variable
#Project name
project(geGL LANGUAGES CXX)

#You should set up this variable
#Library name
set(LIB_NAME geGL)

#You should set up these variables
#Library version
set(${LIB_NAME}_MAJOR_VERSION    1)
set(${LIB_NAME}_MINOR_VERSION    0)
set(${LIB_NAME}_PATH_VERSION     0)
set(${LIB_NAME}_REVISION_VERSION 0)

#You should set up this variable
#All includes
set(INCLUDES
  include/GPUEngine/${LIB_NAME}/Fwd.h
  include/GPUEngine/${LIB_NAME}/Definitions.h
  include/GPUEngine/${LIB_NAME}/Buffer.h
  include/GPUEngine/${LIB_NAME}/VertexArray.h
  include/GPUEngine/${LIB_NAME}/Framebuffer.h
  include/GPUEngine/${LIB_NAME}/Texture.h
  include/GPUEngine/${LIB_NAME}/Sampler.h
  include/GPUEngine/${LIB_NAME}/ProgramPipeline.h
  include/GPUEngine/${LIB_NAME}/Shader.h
  include/GPUEngine/${LIB_NAME}/Program.h
  include/GPUEngine/${LIB_NAME}/ProgramInfo.h
  include/GPUEngine/${LIB_NAME}/Renderbuffer.h
  include/GPUEngine/${LIB_NAME}/OpenGL.h
  include/GPUEngine/${LIB_NAME}/OpenGLUtil.h
  include/GPUEngine/${LIB_NAME}/AsynchronousQuery.h
  include/GPUEngine/${LIB_NAME}/DebugMessage.h
  include/GPUEngine/${LIB_NAME}/OpenGLObject.h
  include/GPUEngine/${LIB_NAME}/geGL.h
  include/GPUEngine/${LIB_NAME}/ConvertTo.h
  include/GPUEngine/${LIB_NAME}/OpenGLCommands.h
  include/GPUEngine/${LIB_NAME}/OpenGLFunctionTable.h
  include/GPUEngine/${LIB_NAME}/OpenGLContext.h
  include/GPUEngine/${LIB_NAME}/OpenGLCapabilities.h
  include/GPUEngine/${LIB_NAME}/FunctionLoaderInterface.h
  include/GPUEngine/${LIB_NAME}/DefaultLoader.h
  include/GPUEngine/${LIB_NAME}/LoaderTableDecorator.h
  include/GPUEngine/${LIB_NAME}/DSATableDecorator.h
  include/GPUEngine/${LIB_NAME}/TrapTableDecorator.h
  include/GPUEngine/${LIB_NAME}/CapabilitiesTableDecorator.h
  include/GPUEngine/${LIB_NAME}/StaticCalls.h
  include/GPUEngine/${LIB_NAME}/GLSLNoise.h
  include/GPUEngine/${LIB_NAME}/Generated/ContextCalls.h
  include/GPUEngine/${LIB_NAME}/Generated/ContextDeclarations.h
  include/GPUEngine/${LIB_NAME}/Generated/FunctionTableCalls.h
  include/GPUEngine/${LIB_NAME}/Generated/LoaderImplementation.h
  include/GPUEngine/${LIB_NAME}/Generated/LoaderLoadingCalls.h
  include/GPUEngine/${LIB_NAME}/Generated/NumberOfFunctions.h
  include/GPUEngine/${LIB_NAME}/Generated/MemberOpenGLFunctions.h
  include/GPUEngine/${LIB_NAME}/Generated/MemberOpenGLPFN.h
  include/GPUEngine/${LIB_NAME}/Generated/OpenGLConstants.h
  include/GPUEngine/${LIB_NAME}/Generated/OpenGLFunctions.h
  include/GPUEngine/${LIB_NAME}/Generated/OpenGLPFN.h
  include/GPUEngine/${LIB_NAME}/Generated/OpenGLTypes.h
  include/GPUEngine/${LIB_NAME}/Generated/TrapCalls.h
  include/GPUEngine/${LIB_NAME}/Generated/TrapImplementation.h
  )

#You should set up this variable
#All sources
set(SOURCES
  src/Buffer.cpp
  src/VertexArray.cpp
  src/Framebuffer.cpp
  src/Texture.cpp
  src/Sampler.cpp
  src/ProgramPipeline.cpp
  src/Shader.cpp
  src/Program.cpp
  src/Renderbuffer.cpp
  src/AsynchronousQuery.cpp
  src/DebugMessage.cpp
  src/OpenGLObject.cpp
  src/geGL.cpp
  src/OpenGLContext.cpp
  src/OpenGL.cpp
  src/OpenGLUtil.cpp
  src/StaticCalls.cpp
  src/GLSLNoise.cpp
  )

#You should set up this variable
#list of subprojects
list(APPEND ${LIB_NAME}_subprojects)

#You should set up this variable
#list of subprojects that will be build as static library
list(APPEND ${LIB_NAME}_build_as_static)

set(INSTALL_INCLUDE_DIRECTORY   include/GPUEngine/${LIB_NAME}/)
set(INSTALL_CONFIG_DIRECTORY    lib/cmake/GPUEngine/${LIB_NAME}/)
set(GENERATED_INCLUDE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/${LIB_NAME}/)
set(GENERATED_CONFIG_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/${LIB_NAME}/)

#You should set up this variable
#This variable contains external linking targets not build by this project
set(${LIB_NAME}_EXTERNAL_TARGETS geCore::geCore)

#You should set up this variable
#This variable contains extermal libraries that needs to be find by find_package
list(APPEND ${LIB_NAME}_EXTERNAL_LIBRARIES_TO_FIND geCore)

#You should set up this variable
#This variable contains compilation options for this library
set(${LIB_NAME}_COMPILATION_OPTION )

include(exports.cmake)
