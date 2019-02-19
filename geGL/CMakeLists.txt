cmake_minimum_required(VERSION 3.10.1)

project(
  geGL
  VERSION 1.0.5
  )

SET(CMAKE_CXX_STANDARD 14)

set(SOURCES
  src/${PROJECT_NAME}/Buffer.cpp
  src/${PROJECT_NAME}/BufferImpl.cpp
  src/${PROJECT_NAME}/VertexArray.cpp
  src/${PROJECT_NAME}/VertexArrayImpl.cpp
  src/${PROJECT_NAME}/Framebuffer.cpp
  src/${PROJECT_NAME}/Texture.cpp
  src/${PROJECT_NAME}/Sampler.cpp
  src/${PROJECT_NAME}/ProgramPipeline.cpp
  src/${PROJECT_NAME}/Shader.cpp
  src/${PROJECT_NAME}/Program.cpp
  src/${PROJECT_NAME}/Renderbuffer.cpp
  src/${PROJECT_NAME}/AsynchronousQuery.cpp
  src/${PROJECT_NAME}/DebugMessage.cpp
  src/${PROJECT_NAME}/OpenGLObject.cpp
  src/${PROJECT_NAME}/geGL.cpp
  src/${PROJECT_NAME}/OpenGLContext.cpp
  src/${PROJECT_NAME}/OpenGL.cpp
  src/${PROJECT_NAME}/OpenGLUtil.cpp
  src/${PROJECT_NAME}/StaticCalls.cpp
  src/${PROJECT_NAME}/GLSLNoise.cpp
  )

set(INCLUDES
  src/${PROJECT_NAME}/Fwd.h
  src/${PROJECT_NAME}/Definitions.h
  src/${PROJECT_NAME}/Buffer.h
  src/${PROJECT_NAME}/BufferImpl.h
  src/${PROJECT_NAME}/VertexArray.h
  src/${PROJECT_NAME}/VertexArrayImpl.h
  src/${PROJECT_NAME}/Framebuffer.h
  src/${PROJECT_NAME}/Texture.h
  src/${PROJECT_NAME}/Sampler.h
  src/${PROJECT_NAME}/ProgramPipeline.h
  src/${PROJECT_NAME}/Shader.h
  src/${PROJECT_NAME}/ShaderImpl.h
  src/${PROJECT_NAME}/Program.h
  src/${PROJECT_NAME}/ProgramImpl.h
  src/${PROJECT_NAME}/ProgramInfo.h
  src/${PROJECT_NAME}/Renderbuffer.h
  src/${PROJECT_NAME}/OpenGL.h
  src/${PROJECT_NAME}/OpenGLUtil.h
  src/${PROJECT_NAME}/AsynchronousQuery.h
  src/${PROJECT_NAME}/DebugMessage.h
  src/${PROJECT_NAME}/OpenGLObject.h
  src/${PROJECT_NAME}/geGL.h
  src/${PROJECT_NAME}/OpenGLFunctionTable.h
  src/${PROJECT_NAME}/OpenGLContext.h
  src/${PROJECT_NAME}/OpenGLCapabilities.h
  src/${PROJECT_NAME}/FunctionLoaderInterface.h
  src/${PROJECT_NAME}/DefaultLoader.h
  src/${PROJECT_NAME}/LoaderTableDecorator.h
  src/${PROJECT_NAME}/DSATableDecorator.h
  src/${PROJECT_NAME}/TrapTableDecorator.h
  src/${PROJECT_NAME}/CapabilitiesTableDecorator.h
  src/${PROJECT_NAME}/StaticCalls.h
  src/${PROJECT_NAME}/GLSLNoise.h
  )

set(GENERATED_INCLUDES
  src/${PROJECT_NAME}/Generated/ContextCalls.h
  src/${PROJECT_NAME}/Generated/ContextDeclarations.h
  src/${PROJECT_NAME}/Generated/FunctionTableCalls.h
  src/${PROJECT_NAME}/Generated/LoaderImplementation.h
  src/${PROJECT_NAME}/Generated/LoaderLoadingCalls.h
  src/${PROJECT_NAME}/Generated/NumberOfFunctions.h
  src/${PROJECT_NAME}/Generated/MemberOpenGLFunctions.h
  src/${PROJECT_NAME}/Generated/MemberOpenGLPFN.h
  src/${PROJECT_NAME}/Generated/OpenGLConstants.h
  src/${PROJECT_NAME}/Generated/OpenGLFunctions.h
  src/${PROJECT_NAME}/Generated/OpenGLPFN.h
  src/${PROJECT_NAME}/Generated/OpenGLTypes.h
  src/${PROJECT_NAME}/Generated/TrapCalls.h
  src/${PROJECT_NAME}/Generated/TrapImplementation.h
  )

source_group("Header Files\\Generated" FILES ${GENERATED_INCLUDES})

option(BUILD_SHARED_LIBS "build this library as shared")

SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

add_library(${PROJECT_NAME} ${SOURCES} ${INCLUDES} ${GENERATED_INCLUDES})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

include(GNUInstallDirs)

target_include_directories(${PROJECT_NAME} PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

option(${PROJECT_NAME}_BUILD_TESTS "toggle building of unit tests")
if(${PROJECT_NAME}_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
  add_test(NAME baseTest COMMAND tests)
endif()

set(PROJECT_NAME_LOWER)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${PROJECT_NAME}/${PROJECT_NAME_LOWER}_export.h)

set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERFACE_${PROJECT_NAME}_MAJOR_VERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${PROJECT_NAME}_MAJOR_VERSION)

# Suppress warnings 'tautological-undefined-compare' for lines containing assert 'assert(this!=nullptr)'
# Semantic issue: 'this' pointer cannot be null in well-defined C++ code; comparison may be assumed to always evaluate to true
if(CMAKE_COMPILER_IS_GNUCXX)
   set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-tautological-undefined-compare")
endif()

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

install(
  FILES
  ${INCLUDES}
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME_LOWER}_export.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
  COMPONENT
  Devel
  )

install(
  FILES
  ${GENERATED_INCLUDES}
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/Generated
  COMPONENT
  Devel
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
  )

export(EXPORT ${PROJECT_NAME}Targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  )

set(ConfigPackageLocation lib/cmake/${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME}Targets
  FILE
  ${PROJECT_NAME}Targets.cmake
  NAMESPACE
  ${PROJECT_NAME}::
  DESTINATION
  ${ConfigPackageLocation}
  )

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake
  "include($" "{CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Targets.cmake)"
  )

install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION
  ${ConfigPackageLocation}
  COMPONENT
  Devel
  )

