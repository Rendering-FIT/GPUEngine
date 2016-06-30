set(LIB_NAME geGL)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

if(GPUENGINE_DYNAMIC)
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
   add_definitions(-D"${LIB_NAME_UPPER}"_LIBRARY)
else()
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
   add_definitions(-DGE_LIBRARY_STATIC)
endif()

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})

set(GENERATED_INCLUDES
  ${HEADER_PATH}/Generated/FunctionProviderCalls.h
  ${HEADER_PATH}/Generated/FunctionProviderDeclarations.h
  ${HEADER_PATH}/Generated/FunctionTableCalls.h
  ${HEADER_PATH}/Generated/LoaderImplementation.h
  ${HEADER_PATH}/Generated/LoaderLoadingCalls.h
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
  ${HEADER_PATH}/Export.h
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
  ${HEADER_PATH}/OpenGLFunctionProvider.h
  ${HEADER_PATH}/OpenGLCapabilities.h
  ${HEADER_PATH}/FunctionLoaderInterface.h
  ${HEADER_PATH}/DefaultLoader.h
  ${HEADER_PATH}/LoaderTableDecorator.h
  ${HEADER_PATH}/DSATableDecorator.h
  ${HEADER_PATH}/TrapTableDecorator.h
  ${HEADER_PATH}/CapabilitiesTableDecorator.h
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
  OpenGLFunctionProvider.cpp
  OpenGL.cpp
  OpenGLUtil.cpp
  )

################################################
# PACKAGES

if(GPUENGINE_REPLACE_GLEW)
else()
  find_package(GLEW   REQUIRED)
  find_package(OpenGL REQUIRED)
endif()


add_library(${LIB_NAME}
  ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
  ${GL_INCLUDES}
  ${GENERATED_INCLUDES}
  ${GL_SOURCES}
  )

################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_deps_Export - other than 'ge' packages goes here (e.g. glew), it configures this package extra project dependencies and also configures the config file
# External_libs - external libs or targets to link with
# Internal_inc - additional include directories
# Includes_to_export - includes to be exported from this target to application

set(Internal_deps geCore)
if(GPUENGINE_REPLACE_GLEW)
else()
  set(External_deps_Export "GLEW OpenGL")
  set(External_libs GLEW OpenGL)
endif()
set(Internal_inc ${GPUEngine_SOURCE_DIR}/include)
set(includes_to_export ${GPUEngine_SOURCE_DIR}/include)

target_link_libraries(${LIB_NAME} ${Internal_deps} ${External_libs} )
set_target_properties(${LIB_NAME} PROPERTIES
  INCLUDE_DIRECTORIES "${Internal_inc}"
  INTERFACE_INCLUDE_DIRECTORIES "${includes_to_export}"
  )

install(FILES
  ${GENERATED_INCLUDES}
  DESTINATION include/${LIB_NAME}/Generated
  )

install(FILES
  ${GL_INCLUDES}
  DESTINATION include/${LIB_NAME}
  )

install(TARGETS ${LIB_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  )

#########################################
#Export
#configure_package_config_file(
#   geGLConfig.cmake.in
#   geGLConfig.cmake
#   INSTALL_DESTINATION lib/cmake/geGL
#   )

configure_file(
  ../CMake/geConfig.cmake.in
  "${LIB_NAME}Config.cmake"
  @ONLY
  )


configure_file(
  ../CMake/geExport.h.in
  "${GPUEngine_SOURCE_DIR}/include/${LIB_NAME}/Export.h"
  @ONLY
  )

# INSTALL_CM_DIR is defined in master CMakeLists file

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake"
  DESTINATION "${INSTALL_CM_DIR}/${LIB_NAME}"
  )
