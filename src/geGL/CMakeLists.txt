set(LIB_NAME geGL)

set(Upstream_VERSION 1.0.0)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

set(LIB_NAME_LOWER)
string(TOLOWER ${LIB_NAME} LIB_NAME_LOWER)


if(GPUENGINE_DYNAMIC_LINKAGE)
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
   add_definitions(-D"${LIB_NAME_UPPER}"_LIBRARY)
else()
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
   add_definitions(-DGE_LIBRARY_STATIC)
endif()

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})

set(GENERATED_INCLUDES
  ${HEADER_PATH}/Generated/ContextCalls.h
  ${HEADER_PATH}/Generated/ContextDeclarations.h
  ${HEADER_PATH}/Generated/FunctionTableCalls.h
  ${HEADER_PATH}/Generated/LoaderImplementation.h
  ${HEADER_PATH}/Generated/LoaderLoadingCalls.h
  ${HEADER_PATH}/Generated/NumberOfFunctions.h
  ${HEADER_PATH}/Generated/MemberOpenGLFunctions.h
  ${HEADER_PATH}/Generated/MemberOpenGLPFN.h
  ${HEADER_PATH}/Generated/OpenGLConstants.h
  ${HEADER_PATH}/Generated/OpenGLFunctions.h
  ${HEADER_PATH}/Generated/OpenGLPFN.h
  ${HEADER_PATH}/Generated/OpenGLTypes.h
  ${HEADER_PATH}/Generated/TrapCalls.h
  ${HEADER_PATH}/Generated/TrapImplementation.h
  )

set(GL_INCLUDES
  ${HEADER_PATH}/Fwd.h
  ${HEADER_PATH}/Definitions.h
  ${HEADER_PATH}/Buffer.h
  ${HEADER_PATH}/VertexArray.h
  ${HEADER_PATH}/Framebuffer.h
  ${HEADER_PATH}/Texture.h
  ${HEADER_PATH}/Sampler.h
  ${HEADER_PATH}/ProgramPipeline.h
  ${HEADER_PATH}/Shader.h
  ${HEADER_PATH}/Program.h
  ${HEADER_PATH}/ProgramInfo.h
  ${HEADER_PATH}/Renderbuffer.h
  ${HEADER_PATH}/OpenGL.h
  ${HEADER_PATH}/OpenGLUtil.h
  ${HEADER_PATH}/AsynchronousQuery.h
  ${HEADER_PATH}/DebugMessage.h
  ${HEADER_PATH}/OpenGLObject.h
  ${HEADER_PATH}/geGL.h
  ${HEADER_PATH}/ConvertTo.h
  ${HEADER_PATH}/OpenGLCommands.h
  ${HEADER_PATH}/OpenGLFunctionTable.h
  ${HEADER_PATH}/OpenGLContext.h
  ${HEADER_PATH}/OpenGLCapabilities.h
  ${HEADER_PATH}/FunctionLoaderInterface.h
  ${HEADER_PATH}/DefaultLoader.h
  ${HEADER_PATH}/LoaderTableDecorator.h
  ${HEADER_PATH}/DSATableDecorator.h
  ${HEADER_PATH}/TrapTableDecorator.h
  ${HEADER_PATH}/CapabilitiesTableDecorator.h
  ${HEADER_PATH}/StaticCalls.h
  ${HEADER_PATH}/GLSLNoise.h
  )

set(GL_SOURCES
  Buffer.cpp
  VertexArray.cpp
  Framebuffer.cpp
  Texture.cpp
  Sampler.cpp
  ProgramPipeline.cpp
  Shader.cpp
  Program.cpp
  Renderbuffer.cpp
  AsynchronousQuery.cpp
  DebugMessage.cpp
  OpenGLObject.cpp
  geGL.cpp
  OpenGLContext.cpp
  OpenGL.cpp
  OpenGLUtil.cpp
  StaticCalls.cpp
  GLSLNoise.cpp
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

