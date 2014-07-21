cmake_minimum_required (VERSION 2.6)
project (ogl)

add_library(ogl STATIC
  ogl/PerFragmentOperation/Blend.cpp
  ogl/PerFragmentOperation/BlendCommands.cpp
  ogl/PerFragmentOperation/DepthCommands.cpp
  ogl/PerFragmentOperation/LogicalOperationsCommands.cpp
  ogl/PerFragmentOperation/MultisampleFragmentOperationsCommands.cpp
  ogl/PerFragmentOperation/OcclusionQueriesCommands.cpp
  ogl/PerFragmentOperation/ScissorCommands.cpp
  ogl/PerFragmentOperation/Stencil.cpp
  ogl/PerFragmentOperation/StencilCommands.cpp
  ogl/Standard/OpenGL.cpp
  ogl/Standard/OpenGLCommon.cpp
  ogl/VertexArrays/DrawCommands.cpp
  )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/modules/")

find_package(GLEW REQUIRED)
if(GLEW_FOUND)
  message("GLEW found")
  include_directories(${GLEW_INCLUDE_DIR})
  target_link_libraries(ogl ${GLEW_LIBRARY})
else(GLEW_FOUND)
  message("GLEW not found")
endif(GLEW_FOUND)

install(FILES
  ogl/PerFragmentOperation/Blend.h
  ogl/PerFragmentOperation/BlendCommands.h
  ogl/PerFragmentOperation/DepthCommands.h
  ogl/PerFragmentOperation/LogicalOperationsCommands.h
  ogl/PerFragmentOperation/MultisampleFragmentOperationsCommands.h
  ogl/PerFragmentOperation/OcclusionQueriesCommands.h
  ogl/PerFragmentOperation/ScissorCommands.h
  ogl/PerFragmentOperation/Stencil.h
  ogl/PerFragmentOperation/StencilCommands.h
  ogl/Standard/OpenGL.h
  ogl/Standard/OpenGLCommon.h
  ogl/VertexArrays/DrawCommands.h
  DESTINATION include/ge/ogl
  )

install(TARGETS ogl
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
