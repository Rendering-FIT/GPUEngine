cmake_minimum_required(VERSION 3.1.0)
cmake_policy(VERSION 3.1)

#You should set up this variable
#Project name
project(geUtil LANGUAGES CXX)

#You should set up this variable
#Library name
set(LIB_NAME geUtil)

#You should set up these variables
#Library version
set(${LIB_NAME}_MAJOR_VERSION    1)
set(${LIB_NAME}_MINOR_VERSION    0)
set(${LIB_NAME}_PATH_VERSION     0)
set(${LIB_NAME}_REVISION_VERSION 0)

#You should set up this variable
#All includes
set(INCLUDES
  include/GPUEngine/${LIB_NAME}/algorithms.h
  include/GPUEngine/${LIB_NAME}/FPSPrinter.h
  include/GPUEngine/${LIB_NAME}/Intersector.h
  include/GPUEngine/${LIB_NAME}/macros.h
  include/GPUEngine/${LIB_NAME}/MatrixStack.h
  include/GPUEngine/${LIB_NAME}/OrbitManipulator.h
  include/GPUEngine/${LIB_NAME}/Progress.h
  include/GPUEngine/${LIB_NAME}/Ray.h
  include/GPUEngine/${LIB_NAME}/geUtil.h
  include/GPUEngine/${LIB_NAME}/Sampler.h
  include/GPUEngine/${LIB_NAME}/Timer.h
  )

#You should set up this variable
#All sources
set(SOURCES
  src/FPSPrinter.cpp
  src/OrbitManipulator.cpp
  src/Progress.cpp
  )

#You should set up this variable
#list of subprojects
list(APPEND ${LIB_NAME}_subprojects ArgumentViewer Camera)

#You should set up this variable
#list of subprojects that will be build as static library
list(APPEND ${LIB_NAME}_build_as_static ArgumentViewer Camera)

set(INSTALL_INCLUDE_DIRECTORY   include/GPUEngine/${LIB_NAME}/)
set(INSTALL_CONFIG_DIRECTORY    lib/cmake/GPUEngine/${LIB_NAME}/)
set(GENERATED_INCLUDE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/${LIB_NAME}/)
set(GENERATED_CONFIG_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/${LIB_NAME}/)

#You should set up this variable
#This variable contains external linking targets not build by this project
set(${LIB_NAME}_EXTERNAL_TARGETS geCore::geCore glm)

#You should set up this variable
#This variable contains extermal libraries that needs to be find by find_package
list(APPEND ${LIB_NAME}_EXTERNAL_LIBRARIES_TO_FIND geCore glm)

#You should set up this variable
#This variable contains compilation options for this library
set(${LIB_NAME}_COMPILATION_OPTION GLM_ENABLE_EXPERIMENTAL)

include(exports.cmake)
