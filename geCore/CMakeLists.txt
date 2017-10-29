cmake_minimum_required(VERSION 3.1.0)
cmake_policy(VERSION 3.1)

#You should set up this variable
#Project name
project(geCore LANGUAGES CXX)

#You should set up this variable
#Library name
set(LIB_NAME geCore)

#You should set up these variables
#Library version
set(${LIB_NAME}_MAJOR_VERSION    1)
set(${LIB_NAME}_MINOR_VERSION    0)
set(${LIB_NAME}_PATH_VERSION     0)
set(${LIB_NAME}_REVISION_VERSION 0)

#You should set up this variable
#All includes
set(INCLUDES
  include/GPUEngine/${LIB_NAME}/CallStackPrinter.h
  include/GPUEngine/${LIB_NAME}/CopyOp.h
  include/GPUEngine/${LIB_NAME}/Command.h
  include/GPUEngine/${LIB_NAME}/Dtemplates.h
  include/GPUEngine/${LIB_NAME}/EnumRegister.h
  include/GPUEngine/${LIB_NAME}/Functor.h
  include/GPUEngine/${LIB_NAME}/InitAndFinalize.h
  include/GPUEngine/${LIB_NAME}/Interval.h
  include/GPUEngine/${LIB_NAME}/KeyPoint.h
  include/GPUEngine/${LIB_NAME}/Object.h
  include/GPUEngine/${LIB_NAME}/StandardSemanticsNames.h
  include/GPUEngine/${LIB_NAME}/TypeTraits.h
  include/GPUEngine/${LIB_NAME}/Updatable.h
  include/GPUEngine/${LIB_NAME}/geCore.h
  include/GPUEngine/${LIB_NAME}/idlist.h
  )

#You should set up this variable
#All sources
set(SOURCES
  src/Command.cpp
  src/CopyOp.cpp
  src/Dtemplates.cpp
  src/EnumRegister.cpp
  src/InitAndFinalize.cpp
  src/Object.cpp
  src/StandardSemanticsNames.cpp
  )

#You should set up this variable
#list of subprojects
list(APPEND ${LIB_NAME}_subprojects PrettyFunctionName DisjointSet ValuePrinter ErrorPrinter FSA MealyMachine Text)

#You should set up this variable
#list of subprojects that will be build as static library
list(APPEND ${LIB_NAME}_build_as_static MealyMachine FSA Text)

set(INSTALL_INCLUDE_DIRECTORY   include/GPUEngine/${LIB_NAME}/)
set(INSTALL_CONFIG_DIRECTORY    lib/cmake/GPUEngine/${LIB_NAME}/)
set(GENERATED_INCLUDE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/${LIB_NAME}/)
set(GENERATED_CONFIG_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/${LIB_NAME}/)

#You should set up this variable
#This variable contains external linking targets not build by this project
set(${LIB_NAME}_EXTERNAL_TARGETS )

#You should set up this variable
#This variable contains extermal libraries that needs to be find by find_package
list(APPEND ${LIB_NAME}_EXTERNAL_LIBRARIES_TO_FIND )

#You should set up this variable
#This variable contains compilation options for this library
set(${LIB_NAME}_COMPILATION_OPTION )

include(exports.cmake)
