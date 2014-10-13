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
    ${HEADER_PATH}/ShaderObject.h
    ${HEADER_PATH}/ShaderObjectParameter.h
    ${HEADER_PATH}/ShaderObjectSubroutine.h
    ${HEADER_PATH}/ShaderObjectSubroutineUniform.h
    ${HEADER_PATH}/PerFragmentOperation/Blend.h
    ${HEADER_PATH}/PerFragmentOperation/BlendCommands.h
    ${HEADER_PATH}/PerFragmentOperation/DepthCommands.h
    ${HEADER_PATH}/PerFragmentOperation/LogicalOperationsCommands.h
    ${HEADER_PATH}/PerFragmentOperation/MultisampleFragmentOperationsCommands.h
    ${HEADER_PATH}/PerFragmentOperation/OcclusionQueriesCommands.h
    ${HEADER_PATH}/PerFragmentOperation/ScissorCommands.h
    ${HEADER_PATH}/PerFragmentOperation/Stencil.h
    ${HEADER_PATH}/PerFragmentOperation/StencilCommands.h
    ${HEADER_PATH}/Standard/OpenGL.h
    ${HEADER_PATH}/Standard/OpenGLCommon.h
    ${HEADER_PATH}/VertexArrays/ConditionalRenderingCommands.h
    ${HEADER_PATH}/VertexArrays/DrawCommands.h
    ${HEADER_PATH}/VertexArrays/GenericVertexAttributeArraysCommands.h
    ${HEADER_PATH}/VertexArrays/PrimitiveRestartCommands.h
    ${HEADER_PATH}/VertexArrays/VertexArrayObjectsCommands.h
    ${HEADER_PATH}/VertexArrays/VertexArrayObjectsManager.h
    ${HEADER_PATH}/VertexArrays/VertexAttributeDivisorsCommands.h
    ${HEADER_PATH}/ShadersAndPrograms/ShaderObjectsCommands.h
    ${HEADER_PATH}/ShadersAndPrograms/ShaderObjectsManager.h
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
    PerFragmentOperation/Blend.cpp
    PerFragmentOperation/BlendCommands.cpp
    PerFragmentOperation/DepthCommands.cpp
    PerFragmentOperation/LogicalOperationsCommands.cpp
    PerFragmentOperation/MultisampleFragmentOperationsCommands.cpp
    PerFragmentOperation/OcclusionQueriesCommands.cpp
    PerFragmentOperation/ScissorCommands.cpp
    PerFragmentOperation/Stencil.cpp
    PerFragmentOperation/StencilCommands.cpp
    Standard/OpenGL.cpp
    Standard/OpenGLCommon.cpp
    VertexArrays/ConditionalRenderingCommands.cpp
    VertexArrays/DrawCommands.cpp
    VertexArrays/GenericVertexAttributeArraysCommands.cpp
    VertexArrays/PrimitiveRestartCommands.cpp
    VertexArrays/VertexArrayObjectsCommands.cpp
    VertexArrays/VertexArrayObjectsManager.cpp
    VertexArrays/VertexAttributeDivisorsCommands.cpp
    ShadersAndPrograms/ShaderObjectsCommands.cpp
    ShadersAndPrograms/ShaderObjectsManager.cpp
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
    DESTINATION include/ge/${LIB_NAME}
  )

install(TARGETS ${LIB_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
