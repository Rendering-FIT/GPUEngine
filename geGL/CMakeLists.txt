cmake_minimum_required(VERSION 3.1.0)
cmake_policy(VERSION 3.1)

  Text::Text
project(geGL LANGUAGES CXX)

set(LIB_NAME geGL)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

set(${LIB_NAME}_MAJOR_VERSION    1)
set(${LIB_NAME}_MINOR_VERSION    0)
set(${LIB_NAME}_PATH_VERSION     0)
set(${LIB_NAME}_REVISION_VERSION 0)

set(GENERATED_INCLUDES
  include/GPUEngine/geGL/Generated/ContextCalls.h
  include/GPUEngine/geGL/Generated/ContextDeclarations.h
  include/GPUEngine/geGL/Generated/FunctionTableCalls.h
  include/GPUEngine/geGL/Generated/LoaderImplementation.h
  include/GPUEngine/geGL/Generated/LoaderLoadingCalls.h
  include/GPUEngine/geGL/Generated/NumberOfFunctions.h
  include/GPUEngine/geGL/Generated/MemberOpenGLFunctions.h
  include/GPUEngine/geGL/Generated/MemberOpenGLPFN.h
  include/GPUEngine/geGL/Generated/OpenGLConstants.h
  include/GPUEngine/geGL/Generated/OpenGLFunctions.h
  include/GPUEngine/geGL/Generated/OpenGLPFN.h
  include/GPUEngine/geGL/Generated/OpenGLTypes.h
  include/GPUEngine/geGL/Generated/TrapCalls.h
  include/GPUEngine/geGL/Generated/TrapImplementation.h
  )

set(INCLUDES
  include/GPUEngine/geGL/Fwd.h
  include/GPUEngine/geGL/Definitions.h
  include/GPUEngine/geGL/Buffer.h
  include/GPUEngine/geGL/VertexArray.h
  include/GPUEngine/geGL/Framebuffer.h
  include/GPUEngine/geGL/Texture.h
  include/GPUEngine/geGL/Sampler.h
  include/GPUEngine/geGL/ProgramPipeline.h
  include/GPUEngine/geGL/Shader.h
  include/GPUEngine/geGL/Program.h
  include/GPUEngine/geGL/ProgramInfo.h
  include/GPUEngine/geGL/Renderbuffer.h
  include/GPUEngine/geGL/OpenGL.h
  include/GPUEngine/geGL/OpenGLUtil.h
  include/GPUEngine/geGL/AsynchronousQuery.h
  include/GPUEngine/geGL/DebugMessage.h
  include/GPUEngine/geGL/OpenGLObject.h
  include/GPUEngine/geGL/geGL.h
  include/GPUEngine/geGL/ConvertTo.h
  include/GPUEngine/geGL/OpenGLCommands.h
  include/GPUEngine/geGL/OpenGLFunctionTable.h
  include/GPUEngine/geGL/OpenGLContext.h
  include/GPUEngine/geGL/OpenGLCapabilities.h
  include/GPUEngine/geGL/FunctionLoaderInterface.h
  include/GPUEngine/geGL/DefaultLoader.h
  include/GPUEngine/geGL/LoaderTableDecorator.h
  include/GPUEngine/geGL/DSATableDecorator.h
  include/GPUEngine/geGL/TrapTableDecorator.h
  include/GPUEngine/geGL/CapabilitiesTableDecorator.h
  include/GPUEngine/geGL/StaticCalls.h
  include/GPUEngine/geGL/GLSLNoise.h
  )

set(SOURCES
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

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_C_STANDARD   99)

OPTION(${LIB_NAME_UPPER}_DYNAMIC "Build dynamic library (dll,so,...). Use OFF for static lib." ON)
if(${LIB_NAME_UPPER}_DYNAMIC)
  set(${LIB_NAME_UPPER}_DYNAMIC_OR_STATIC "SHARED")
else()
  set(${LIB_NAME_UPPER}_DYNAMIC_OR_STATIC "STATIC")
endif()

add_library(${LIB_NAME} ${${LIB_NAME_UPPER}_DYNAMIC_OR_STATIC} ${INCLUDES} ${SOURCES} ${GENERATED_INCLUDES})
add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

IF(CMAKE_COMPILER_IS_GNUCXX)
  if(${LIB_NAME_UPPER}_DYNAMIC)
  else()
    target_compile_options(${LIB_NAME} PUBLIC -fPIC)
  endif()
endif()

target_include_directories(${LIB_NAME} PUBLIC
  $<INSTALL_INTERFACE:include/>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  )

find_package(geCore CONFIG)
target_link_libraries(${LIB_NAME} 
  geCore::geCore
  )







set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

IF(CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(${LIB_NAME} PRIVATE -W)
  target_compile_options(${LIB_NAME} PRIVATE -Wall)
  target_compile_options(${LIB_NAME} PRIVATE -Wconversion)
  target_compile_options(${LIB_NAME} PRIVATE -pedantic)
ENDIF()

IF(CMAKE_COMPILER_IS_GNUCC)
  target_compile_options(${LIB_NAME} PRIVATE -W)
  target_compile_options(${LIB_NAME} PRIVATE -Wall)
  target_compile_options(${LIB_NAME} PRIVATE -Wconversion)
  target_compile_options(${LIB_NAME} PRIVATE -pedantic)
ENDIF()


set(${LIB_NAME}_VERSION ${${LIB_NAME}_MAJOR_VERSION}.${${LIB_NAME}_MINOR_VERSION}.${${LIB_NAME}_PATH_VERSION}.${${LIB_NAME}_REVISION_VERSION})

set(LIB_NAME_LOWER)
string(TOLOWER ${LIB_NAME} LIB_NAME_LOWER)

set_property(TARGET ${LIB_NAME}        PROPERTY VERSION                             ${${LIB_NAME}_VERSION}      )
set_property(TARGET ${LIB_NAME}        PROPERTY SOVERSION                           ${${LIB_NAME}_MAJOR_VERSION})
set_property(TARGET ${LIB_NAME}        PROPERTY INTERFACE_${LIB_NAME}_MAJOR_VERSION ${${LIB_NAME}_MAJOR_VERSION})
set_property(TARGET ${LIB_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING         ${LIB_NAME}_MAJOR_VERSION   )

install(TARGETS ${LIB_NAME} EXPORT ${LIB_NAME}Targets
  LIBRARY  DESTINATION lib
  ARCHIVE  DESTINATION lib
  RUNTIME  DESTINATION bin
  INCLUDES DESTINATION include
  )
include(GenerateExportHeader)
generate_export_header(${LIB_NAME} EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/${LIB_NAME}/${LIB_NAME_LOWER}_export.h)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/${LIB_NAME}/${LIB_NAME_LOWER}_export.h" DESTINATION include/GPUEngine/${LIB_NAME}/ COMPONENT Devel)


install(FILES
  ${INCLUDES}
  DESTINATION include/GPUEngine/${LIB_NAME}/
  )
install(FILES
  ${GENERATED_INCLUDES}
  DESTINATION include/GPUEngine/${LIB_NAME}/Generated
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake"
  VERSION ${${LIB_NAME}_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

export(EXPORT ${LIB_NAME}Targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/${LIB_NAME}/${LIB_NAME}Targets.cmake"
  NAMESPACE ${LIB_NAME}::
  )
configure_file(cmake/${LIB_NAME}Config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/${LIB_NAME}/${LIB_NAME}Config.cmake"
  COPYONLY
  )

set(ConfigPackageLocation lib/cmake/GPUEngine/${LIB_NAME})
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
  "${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake"
  DESTINATION
  ${ConfigPackageLocation}
  COMPONENT
  Devel
  )

