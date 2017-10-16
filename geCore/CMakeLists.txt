cmake_minimum_required(VERSION 3.1.0)
cmake_policy(VERSION 3.1)

project(geCore LANGUAGES CXX)

set(LIB_NAME geCore)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

set(${LIB_NAME}_MAJOR_VERSION    1)
set(${LIB_NAME}_MINOR_VERSION    0)
set(${LIB_NAME}_PATH_VERSION     0)
set(${LIB_NAME}_REVISION_VERSION 0)

set(INCLUDES
  include/GPUEngine/${LIB_NAME}/CallStackPrinter.h
  include/GPUEngine/${LIB_NAME}/CopyOp.h
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

set(SOURCES
  src/Command.cpp
  src/CopyOp.cpp
  src/Dtemplates.cpp
  src/EnumRegister.cpp
  src/InitAndFinalize.cpp
  src/Object.cpp
  src/StandardSemanticsNames.cpp
  )

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_C_STANDARD   99)

OPTION(${LIB_NAME_UPPER}_DYNAMIC "Build dynamic library (dll,so,...). Use OFF for static lib." ON)
if(${LIB_NAME_UPPER}_DYNAMIC)
  set(${LIB_NAME_UPPER}_DYNAMIC_OR_STATIC "SHARED")
else()
  set(${LIB_NAME_UPPER}_DYNAMIC_OR_STATIC "STATIC")
endif()


#IN_LIST is operator in CMake 3.3, CMake 3.8.1 warns 
cmake_policy(SET CMP0057 NEW)
list(APPEND as_subproject PrettyFunctionName DisjointSet ValuePrinter ErrorPrinter FSA MealyMachine)
macro(find_package name)
  if(NOT "${name}" IN_LIST as_subproject)
    _find_package(${ARGV})
  endif()
endmacro()

set(MEALYMACHINE_DYNAMIC FALSE CACHE BOOL "")
set(FSA_DYNAMIC FALSE CACHE BOOL "")
set(TEXT_DYNAMIC FALSE CACHE BOOL "")

add_subdirectory(DisjointSet)
add_subdirectory(ErrorPrinter)
add_subdirectory(FSA)
add_subdirectory(MealyMachine)
add_subdirectory(PrettyFunctionName)
add_subdirectory(Text)
add_subdirectory(ValuePrinter)


add_library(${LIB_NAME} ${${LIB_NAME_UPPER}_DYNAMIC_OR_STATIC} ${INCLUDES} ${SOURCES})
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
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/FSA/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/FSA>
  )

#find_package(ErrorPrinter CONFIG)
target_link_libraries(${LIB_NAME} 
  PRIVATE
  ErrorPrinter::ErrorPrinter
  ValuePrinter::ValuePrinter
  PrettyFunctionName::PrettyFunctionName
  FSA::FSA
  DisjointSet::DisjointSet
  MealyMachine::MealyMachine
  Text::Text
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

