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
    ${HEADER_PATH}/GenericVertexAttributeArraysCommands.h
    ${HEADER_PATH}/PrimitiveRestartCommands.h
    ${HEADER_PATH}/VertexArrayObjectsCommands.h
    ${HEADER_PATH}/VertexArrayObjectsManager.h
    ${HEADER_PATH}/VertexAttributeDivisorsCommands.h
    ${HEADER_PATH}/ShaderObjectsCommands.h
    ${HEADER_PATH}/ShaderObjectsManager.h
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
    GenericVertexAttributeArraysCommands.cpp
    PrimitiveRestartCommands.cpp
    VertexArrayObjectsCommands.cpp
    VertexArrayObjectsManager.cpp
    VertexAttributeDivisorsCommands.cpp
    ShaderObjectsCommands.cpp
    ShaderObjectsManager.cpp
  )

ADD_LIBRARY(${LIB_NAME}
    ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
    ${GL_INCLUDES}
    ${GL_SOURCES}
  )

find_package(GLEW   REQUIRED)
find_package(OPENGL REQUIRED)

include_directories(${GLEW_INCLUDE_PATH} ${OPENGL_INCLUDE_PATH})
target_link_libraries(${LIB_NAME} ${GLEW_LIBRARY} ${OPENGL_LIBRARY} geCore)

install(FILES
    ${GL_INCLUDES}
    DESTINATION include/${LIB_NAME}
  )

install(TARGETS ${LIB_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
