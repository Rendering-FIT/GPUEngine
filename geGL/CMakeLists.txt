set(LIB_NAME geGL)

set(Upstream_VERSION 1.0.0)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

set(LIB_NAME_LOWER)
string(TOLOWER ${LIB_NAME} LIB_NAME_LOWER)

set(GENERATED_INCLUDES
  include/Generated/ContextCalls.h
  include/Generated/ContextDeclarations.h
  include/Generated/FunctionTableCalls.h
  include/Generated/LoaderImplementation.h
  include/Generated/LoaderLoadingCalls.h
  include/Generated/NumberOfFunctions.h
  include/Generated/MemberOpenGLFunctions.h
  include/Generated/MemberOpenGLPFN.h
  include/Generated/OpenGLConstants.h
  include/Generated/OpenGLFunctions.h
  include/Generated/OpenGLPFN.h
  include/Generated/OpenGLTypes.h
  include/Generated/TrapCalls.h
  include/Generated/TrapImplementation.h
  )

set(GL_INCLUDES
  include/Fwd.h
  include/Definitions.h
  include/Buffer.h
  include/VertexArray.h
  include/Framebuffer.h
  include/Texture.h
  include/Sampler.h
  include/ProgramPipeline.h
  include/Shader.h
  include/Program.h
  include/ProgramInfo.h
  include/Renderbuffer.h
  include/OpenGL.h
  include/OpenGLUtil.h
  include/AsynchronousQuery.h
  include/DebugMessage.h
  include/OpenGLObject.h
  include/geGL.h
  include/ConvertTo.h
  include/OpenGLCommands.h
  include/OpenGLFunctionTable.h
  include/OpenGLContext.h
  include/OpenGLCapabilities.h
  include/FunctionLoaderInterface.h
  include/DefaultLoader.h
  include/LoaderTableDecorator.h
  include/DSATableDecorator.h
  include/TrapTableDecorator.h
  include/CapabilitiesTableDecorator.h
  include/StaticCalls.h
  include/GLSLNoise.h
  )

set(GL_SOURCES
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

find_package(geCore CONFIG REQUIRED)

add_library(${LIB_NAME}
  ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
  ${GL_INCLUDES}
  ${GENERATED_INCLUDES}
  ${GL_SOURCES}
  )
add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

target_link_libraries(${LIB_NAME} PUBLIC geCore)

include(GenerateExportHeader)

generate_export_header(${LIB_NAME})
set_property(TARGET ${LIB_NAME} APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING ${LIB_NAME}_MAJOR_VERSION
  )

target_include_directories(${LIB_NAME} PUBLIC  
  $<BUILD_INTERFACE:${GPUEngine_BINARY_DIR}/include/>  
  $<BUILD_INTERFACE:${GPUEngine_BINARY_DIR}/src/>  
  $<BUILD_INTERFACE:${GPUEngine_SOURCE_DIR}/include/>  
  $<INSTALL_INTERFACE:include/> 
)

install(TARGETS ${LIB_NAME} EXPORT ${LIB_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  )
install(FILES
  ${GENERATED_INCLUDES}
  DESTINATION include/${LIB_NAME}/Generated
  )
install(FILES
  ${GL_INCLUDES}
  DESTINATION include/${LIB_NAME}
  )
install(
  FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME_LOWER}_export.h"
  DESTINATION
  include/${LIB_NAME}
  COMPONENT
  Devel
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake"
  VERSION ${Upstream_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

export(EXPORT ${LIB_NAME}Targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}Targets.cmake"
  NAMESPACE ${LIB_NAME}::
  )
configure_file(cmake/${LIB_NAME}Config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}Config.cmake"
  COPYONLY
  )

set(ConfigPackageLocation lib/cmake/${LIB_NAME})
install(EXPORT ${LIB_NAME}Targets
  FILE
  ${LIB_NAME}Targets.cmake
  NAMESPACE
  ${LIB_NAME}::
  DESTINATION
  ${ConfigPackageLocation}
  )
install(
  FILES
  cmake/${LIB_NAME}Config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake"
  DESTINATION
  ${ConfigPackageLocation}
  COMPONENT
  Devel
  )

