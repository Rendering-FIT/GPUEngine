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
set(GL_INCLUDES
    ${HEADER_PATH}/Export.h
    ${HEADER_PATH}/Definitions.h
    ${HEADER_PATH}/BufferObject.h
    ${HEADER_PATH}/VertexArrayObject.h
    ${HEADER_PATH}/FramebufferObject.h
    ${HEADER_PATH}/TextureObject.h
    ${HEADER_PATH}/SamplerObject.h
    ${HEADER_PATH}/ProgramPipelineObject.h
    ${HEADER_PATH}/Shader.h
    ${HEADER_PATH}/ShaderObject.h
    ${HEADER_PATH}/Program.h
    ${HEADER_PATH}/ProgramObject.h
    ${HEADER_PATH}/ProgramObjectMacro.h
    ${HEADER_PATH}/ProgramObjectParameter.h
    ${HEADER_PATH}/ProgramObjectSubroutine.h
    ${HEADER_PATH}/ProgramObjectSubroutineUniform.h
    ${HEADER_PATH}/ProgramObjectSubroutineUniform.h
    ${HEADER_PATH}/RenderbufferObject.h
    ${HEADER_PATH}/OpenGL.h
    ${HEADER_PATH}/AsynchronousQueryObject.h
    ${HEADER_PATH}/DebugMessage.h
    ${HEADER_PATH}/OpenGLObject.h
    ${HEADER_PATH}/geGL.h
    ${HEADER_PATH}/AllAttribs.h
    ${HEADER_PATH}/OpenGLCommands.h
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
    BufferObject.cpp
    VertexArrayObject.cpp
    FramebufferObject.cpp
    TextureObject.cpp
    SamplerObject.cpp
    ProgramPipelineObject.cpp
    Shader.cpp
    ShaderObject.cpp
    Program.cpp
    ProgramObject.cpp
    ProgramObjectParameter.cpp
    ProgramObjectSubroutine.cpp
    ProgramObjectSubroutineUniform.cpp
    RenderbufferObject.cpp
    AsynchronousQueryObject.cpp
    DebugMessage.cpp
    OpenGLObject.cpp
    geGL.cpp
    OpenGLFunctionProvider.cpp
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
