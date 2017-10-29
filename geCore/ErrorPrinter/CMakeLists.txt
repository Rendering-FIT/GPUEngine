cmake_minimum_required(VERSION 3.1.0)
cmake_policy(VERSION 3.1)

#You should set up this variable
#Project name
project(ErrorPrinter LANGUAGES CXX)

#You should set up this variable
#Library name
set(LIB_NAME ErrorPrinter)

#You should set up these variables
#Library version
set(${LIB_NAME}_MAJOR_VERSION    1)
set(${LIB_NAME}_MINOR_VERSION    0)
set(${LIB_NAME}_PATH_VERSION     0)
set(${LIB_NAME}_REVISION_VERSION 0)

#You should set up this variable
#All includes
set(INCLUDES
  include/GPUEngine/geCore/${LIB_NAME}/ErrorPrinter.h
  )

#You should set up this variable
#All sources
set(SOURCES
  )

#You should set up this variable
#list of subprojects
list(APPEND ${LIB_NAME}_subprojects)

#You should set up this variable
#list of subprojects that will be build as static library
list(APPEND ${LIB_NAME}_build_as_static)

set(INSTALL_INCLUDE_DIRECTORY   include/GPUEngine/geCore/${LIB_NAME}/)
set(INSTALL_CONFIG_DIRECTORY    lib/cmake/GPUEngine/geCore/${LIB_NAME}/)
set(GENERATED_INCLUDE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/geCore/${LIB_NAME}/)
set(GENERATED_CONFIG_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/geCore/${LIB_NAME}/)

#You should set up this variable
#This variable contains external linking targets not build by this project
set(${LIB_NAME}_EXTERNAL_TARGETS PrettyFunctionName::PrettyFunctionName ValuePrinter::ValuePrinter)

#You should set up this variable
#This variable contains extermal libraries that needs to be find by find_package
set(${LIB_NAME}_EXTERNAL_LIBRARIES_TO_FIND PrettyFunctionName ValuePrinter)

#You should set up this variable
#This variable contains compilation options for this library
set(${LIB_NAME}_COMPILATION_OPTION )

include(exports.cmake)

