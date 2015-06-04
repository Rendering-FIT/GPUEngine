IF   (DYNAMIC_GPUENGINE)
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
    ADD_DEFINITIONS(-DGEGL_LIBRARY)
ELSE ()
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
    ADD_DEFINITIONS(-DGE_LIBRARY_STATIC)
ENDIF()


set(LIB_NAME geGL)

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})
set(GL_INCLUDES
    ${HEADER_PATH}/Export.h
    ${HEADER_PATH}/BufferObject.h
    ${HEADER_PATH}/VertexArrayObject.h
    ${HEADER_PATH}/FramebufferObject.h
    ${HEADER_PATH}/TextureObject.h
    ${HEADER_PATH}/SamplerObject.h
    ${HEADER_PATH}/ProgramPipelineObject.h
    ${HEADER_PATH}/ProgramObject.h
    ${HEADER_PATH}/ProgramObjectMacro.h
    ${HEADER_PATH}/ShaderObject.h
    ${HEADER_PATH}/ShaderObjectParameter.h
    ${HEADER_PATH}/ShaderObjectSubroutine.h
    ${HEADER_PATH}/ShaderObjectSubroutineUniform.h
    ${HEADER_PATH}/ShaderObjectSubroutineUniform.h
    ${HEADER_PATH}/RenderbufferObject.h
    ${HEADER_PATH}/Blend.h
    ${HEADER_PATH}/BlendCommands.h
    ${HEADER_PATH}/DepthCommands.h
    ${HEADER_PATH}/LogicalOperationsCommands.h
    ${HEADER_PATH}/MultisampleFragmentOperationsCommands.h
    ${HEADER_PATH}/OcclusionQueriesCommands.h
    ${HEADER_PATH}/ScissorCommands.h
    ${HEADER_PATH}/Stencil.h
    ${HEADER_PATH}/StencilCommands.h
    ${HEADER_PATH}/OpenGL.h
    ${HEADER_PATH}/OpenGLCommon.h
    ${HEADER_PATH}/ConditionalRenderingCommands.h
    ${HEADER_PATH}/DrawCommands.h
    ${HEADER_PATH}/DrawCommandsBases.h
    ${HEADER_PATH}/UniformCommands.h
    ${HEADER_PATH}/GenericVertexAttributeArraysCommands.h
    ${HEADER_PATH}/PrimitiveRestartCommands.h
    ${HEADER_PATH}/VertexArrayObjectsCommands.h
    ${HEADER_PATH}/VertexArrayObjectsManager.h
    ${HEADER_PATH}/VertexAttributeDivisorsCommands.h
    ${HEADER_PATH}/ShaderObjectsCommands.h
    ${HEADER_PATH}/ShaderObjectsManager.h
    ${HEADER_PATH}/AsynchronousQueryObject.h
    ${HEADER_PATH}/DebugMessage.h
    ${HEADER_PATH}/RasterizationState.h
    ${HEADER_PATH}/OpenGLObject.h
    ${HEADER_PATH}/geGL.h
    ${HEADER_PATH}/ProgramCommands.h
    ${HEADER_PATH}/BufferCommands.h
  )

set(GL_SOURCES
    BufferObject.cpp  
    VertexArrayObject.cpp
    FramebufferObject.cpp
    TextureObject.cpp
    SamplerObject.cpp
    ProgramPipelineObject.cpp
    ProgramObject.cpp
    ShaderObject.cpp
    ShaderObjectParameter.cpp
    ShaderObjectSubroutine.cpp
    ShaderObjectSubroutineUniform.cpp
    RenderbufferObject.cpp
    Blend.cpp
    BlendCommands.cpp
    DepthCommands.cpp
    LogicalOperationsCommands.cpp
    MultisampleFragmentOperationsCommands.cpp
    OcclusionQueriesCommands.cpp
    ScissorCommands.cpp
    Stencil.cpp
    StencilCommands.cpp
    OpenGL.cpp
    OpenGLCommon.cpp
    ConditionalRenderingCommands.cpp
    DrawCommands.cpp
    DrawCommandsBases.cpp
    UniformCommands.cpp
    GenericVertexAttributeArraysCommands.cpp
    PrimitiveRestartCommands.cpp
    VertexArrayObjectsCommands.cpp
    VertexArrayObjectsManager.cpp
    VertexAttributeDivisorsCommands.cpp
    ShaderObjectsCommands.cpp
    ShaderObjectsManager.cpp
    AsynchronousQueryObject.cpp
    DebugMessage.cpp
    RasterizationState.cpp
    OpenGLObject.cpp
    ProgramCommands.cpp
    BufferCommands.cpp
  )


find_package(GLEW   REQUIRED)
find_package(OPENGL REQUIRED)
  
ADD_LIBRARY(${LIB_NAME}
    ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
    ${GL_INCLUDES}
    ${GL_SOURCES}
  )

set(Internal_deps geCore)
set(Internal_inc ${GLEW_INCLUDE_PATH} ${OPENGL_INCLUDE_PATH})
set(includes_to_export ${GPUEngine_SOURCE_DIR}/include)

target_link_libraries(${LIB_NAME} ${GLEW_LIBRARY} ${OPENGL_LIBRARY} ${Internal_deps})
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
   geGLConfig.cmake.in
   geGLConfig.cmake
   @ONLY
)

# INSTALL_CM_DIR is defined in master CMakeLists file

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/geGLConfig.cmake"
        DESTINATION "${INSTALL_CM_DIR}/geGL"
        )
