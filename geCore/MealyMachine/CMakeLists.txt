cmake_minimum_required(VERSION 3.1.0)
cmake_policy(VERSION 3.1)

project(MealyMachine LANGUAGES CXX)

set(LIB_NAME MealyMachine)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

set(${LIB_NAME}_MAJOR_VERSION    1)
set(${LIB_NAME}_MINOR_VERSION    0)
set(${LIB_NAME}_PATH_VERSION     0)
set(${LIB_NAME}_REVISION_VERSION 0)

set(INCLUDES
  include/GPUEngine/geCore/${LIB_NAME}/MealyMachine.h
  include/GPUEngine/geCore/${LIB_NAME}/MapTransitionChooser.h
  include/GPUEngine/geCore/${LIB_NAME}/TransitionChooser.h
  )

set(SOURCES
  src/MealyMachine.cpp
  )

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_C_STANDARD   99)

set(${LIB_NAME_UPPER}_DYNAMIC TRUE CACHE BOOL "Build dynamic library (dll,so,...). Use OFF for static lib.")
if(${LIB_NAME_UPPER}_DYNAMIC)
  set(${LIB_NAME_UPPER}_DYNAMIC_OR_STATIC "SHARED")
else()
  set(${LIB_NAME_UPPER}_DYNAMIC_OR_STATIC "STATIC")
endif()

list(APPEND this_project_subprojects)
if("${as_subproject}" STREQUAL "")
  #IN_LIST is operator in CMake 3.3, CMake 3.8.1 warns 
  cmake_policy(SET CMP0057 NEW)
  list(APPEND as_subproject ${this_project_subprojects})
  macro(find_package name)
    if(NOT "${name}" IN_LIST as_subproject)
      _find_package(${ARGV})
    endif()
  endmacro()
else()
  list(APPEND as_subproject ${this_project_subprojects})
endif()
unset(this_project_subprojects)

add_library(${LIB_NAME} ${${LIB_NAME_UPPER}_DYNAMIC_OR_STATIC} ${INCLUDES} ${SOURCES})
add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

target_include_directories(${LIB_NAME} PUBLIC
  $<INSTALL_INTERFACE:include/>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  )

find_package(ErrorPrinter CONFIG)
target_link_libraries(${LIB_NAME} ErrorPrinter::ErrorPrinter)


IF(CMAKE_COMPILER_IS_GNUCXX)
  if(${LIB_NAME_UPPER}_DYNAMIC)
  else()
    target_compile_options(${LIB_NAME} PUBLIC -fPIC)
  endif()
endif()





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

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

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
generate_export_header(${LIB_NAME} EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/geCore/${LIB_NAME}/${LIB_NAME_LOWER}_export.h)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/geCore/${LIB_NAME}/${LIB_NAME_LOWER}_export.h" DESTINATION include/GPUEngine/geCore/${LIB_NAME}/ COMPONENT Devel)


install(FILES
  ${INCLUDES}
  DESTINATION include/GPUEngine/geCore/${LIB_NAME}/
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/geCore/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake"
  VERSION ${${LIB_NAME}_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

export(EXPORT ${LIB_NAME}Targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/geCore/${LIB_NAME}/${LIB_NAME}Targets.cmake"
  NAMESPACE ${LIB_NAME}::
  )
configure_file(cmake/${LIB_NAME}Config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/geCore/${LIB_NAME}/${LIB_NAME}Config.cmake"
  COPYONLY
  )

set(ConfigPackageLocation lib/cmake/GPUEngine/geCore/${LIB_NAME})
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
  "${CMAKE_CURRENT_BINARY_DIR}/GPUEngine/geCore/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake"
  DESTINATION
  ${ConfigPackageLocation}
  COMPONENT
  Devel
  )

