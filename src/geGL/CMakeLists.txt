set(LIB_NAME geGL)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

IF   (GPUENGINE_DYNAMIC)
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
    ADD_DEFINITIONS(-D"${LIB_NAME_UPPER}"_LIBRARY)
ELSE ()
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
    ADD_DEFINITIONS(-DGE_LIBRARY_STATIC)
ENDIF()

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
    OpenGL.cpp
    AsynchronousQueryObject.cpp
    DebugMessage.cpp
    OpenGLObject.cpp
    geGL.cpp
  )


find_package(GLEW   REQUIRED)
find_package(OPENGL REQUIRED)
  
ADD_LIBRARY(${LIB_NAME}
    ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
    ${GL_INCLUDES}
    ${GL_SOURCES}
  )
  
################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_deps - other than 'ge' packages goes here (e.g. glew), it configures this package intra project dependencies and also configures the config file
# External_export_libs - probably not used right now or ever
# External_export_includes - probably not used right now or ever
# Internal_inc - Additional include directories
# Includes_to_export - includes to be exported from this target in current project - which is kinda weird

set(Internal_deps geCore)
set(External_deps GLEW OPENGL)
set(External_export_libs  ${OPENGL_LIBRARY} ${GLEW_LIBRARY})
set(External_export_includes  GLEW_INCLUDE_DIR OPENGL_INCLUDE_DIR)
set(Internal_inc ${GPUEngine_SOURCE_DIR}/include ${GLEW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
set(includes_to_export ${GPUEngine_SOURCE_DIR}/include)

target_link_libraries(${LIB_NAME} ${OPENGL_LIBRARY} ${GLEW_LIBRARY} ${Internal_deps})
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
#)

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
