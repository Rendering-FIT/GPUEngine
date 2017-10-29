SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_C_STANDARD   99)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

if(NOT "${SOURCES}" STREQUAL "")
  set(HEADER_ONLY_LIBRARY OFF)
else()
  set(HEADER_ONLY_LIBRARY ON)
endif()

if(NOT ${HEADER_ONLY_LIBRARY})
  OPTION(${LIB_NAME_UPPER}_DYNAMIC "Build dynamic library (dll,so,...). Use OFF for static lib." ON)
  if(${LIB_NAME_UPPER}_DYNAMIC)
    set(${LIB_NAME_UPPER}_DYNAMIC_OR_STATIC "SHARED")
  else()
    set(${LIB_NAME_UPPER}_DYNAMIC_OR_STATIC "STATIC")
  endif()
endif()

if("${as_subproject}" STREQUAL "")
  #IN_LIST is operator in CMake 3.3, CMake 3.8.1 warns 
  cmake_policy(SET CMP0057 NEW)
  list(APPEND as_subproject ${${LIB_NAME}_subprojects})
  macro(find_package name)
    if(NOT "${name}" IN_LIST as_subproject)
      _find_package(${ARGV})
    endif()
  endmacro()
else()
  list(APPEND as_subproject ${${LIB_NAME}_subprojects})
endif()

#build sub projects as static libs
foreach(subProj ${${LIB_NAME}_build_as_static})
  set(subProjUpper)
  string(TOUPPER ${subProj} subProjUpper)
  set(${subProjUpper}_DYNAMIC FALSE CACHE BOOL "")
endforeach()

#add subprojects
foreach(subdir ${${LIB_NAME}_subprojects})
  add_subdirectory(${subdir})
endforeach()

#create this library
if(NOT ${HEADER_ONLY_LIBRARY})
  add_library(${LIB_NAME} ${${LIB_NAME_UPPER}_DYNAMIC_OR_STATIC} ${INCLUDES} ${SOURCES})
else()
  add_library(${LIB_NAME} INTERFACE)
endif()
add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

#if this library is build as static, and that it is linked to dynamic library it needs to be build with -fPIC flag
if(NOT ${HEADER_ONLY_LIBRARY})
  IF(CMAKE_COMPILER_IS_GNUCXX)
    if(NOT ${LIB_NAME_UPPER}_DYNAMIC)
      target_compile_options(${LIB_NAME} PUBLIC -fPIC)
    endif()
  endif()
endif()

if(${HEADER_ONLY_LIBRARY})
  set(INTERFACE_TYPE INTERFACE)
else()
  set(INTERFACE_TYPE PUBLIC)
endif()

#set include directories from this library for building
target_include_directories(${LIB_NAME} ${INTERFACE_TYPE}
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  )

#set include directories from subdirectories for building
foreach(subdir ${${LIB_NAME}_subprojects})
  target_include_directories(${LIB_NAME} ${INTERFACE_TYPE}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${subdir}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/include>
    )
endforeach()

#all subdirectories are linked to this library as private
foreach(subdir ${${LIB_NAME}_subprojects})
  target_link_libraries(${LIB_NAME} PRIVATE ${subdir}::${subdir})
endforeach()

foreach(lib ${${LIB_NAME}_EXTERNAL_LIBRARIES_TO_FIND})
  find_package(${lib} CONFIG)
endforeach()

target_link_libraries (${LIB_NAME} ${INTERFACE_TYPE} ${${LIB_NAME}_EXTERNAL_TARGETS})
target_compile_definitions(${LIB_NAME} ${INTERFACE_TYPE} ${${LIB_NAME}_COMPILATION_OPTION})

#generate compile commands json file (usefull for vim pluggin YCM)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#sets postfixes for built libraries
SET(CMAKE_DEBUG_POSTFIX          "d"  CACHE STRING "add a postfix, usually d on windows"    )
SET(CMAKE_RELEASE_POSTFIX        ""   CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX     "s"  CACHE STRING "add a postfix, usually empty on windows")

#set building flags
IF(NOT ${HEADER_ONLY_LIBRARY})
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
ENDIF()

#construct library version from version components
set(${LIB_NAME}_VERSION ${${LIB_NAME}_MAJOR_VERSION}.${${LIB_NAME}_MINOR_VERSION}.${${LIB_NAME}_PATH_VERSION}.${${LIB_NAME}_REVISION_VERSION})

#construct library name in UPPER letters
set(LIB_NAME_LOWER)
string(TOLOWER ${LIB_NAME} LIB_NAME_LOWER)

#set library version
#set *.so version
#set library major version
#set version compatibility
IF(NOT ${HEADER_ONLY_LIBRARY})
  set_property(TARGET ${LIB_NAME}        PROPERTY VERSION                             ${${LIB_NAME}_VERSION}      )
  set_property(TARGET ${LIB_NAME}        PROPERTY SOVERSION                           ${${LIB_NAME}_MAJOR_VERSION})
ENDIF()
set_property(TARGET ${LIB_NAME}        PROPERTY INTERFACE_${LIB_NAME}_MAJOR_VERSION ${${LIB_NAME}_MAJOR_VERSION})
set_property(TARGET ${LIB_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING         ${LIB_NAME}_MAJOR_VERSION   )

install(
  TARGETS  ${LIB_NAME} EXPORT ${LIB_NAME}Targets
  LIBRARY  DESTINATION lib
  ARCHIVE  DESTINATION lib
  RUNTIME  DESTINATION bin
  INCLUDES DESTINATION include
  )


IF(NOT ${HEADER_ONLY_LIBRARY})
  #generate _export.h file
  include(GenerateExportHeader)
  generate_export_header(${LIB_NAME} EXPORT_FILE_NAME ${GENERATED_INCLUDE_DIRECTORY}${LIB_NAME_LOWER}_export.h)
  #install _export.h file
  install(FILES ${GENERATED_INCLUDE_DIRECTORY}${LIB_NAME_LOWER}_export.h DESTINATION ${INSTALL_INCLUDE_DIRECTORY} COMPONENT Devel)
ENDIF()

#install includes
install(FILES
  ${INCLUDES}
  DESTINATION ${INSTALL_INCLUDE_DIRECTORY}
  )

#generate Version config
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${GENERATED_CONFIG_DIRECTORY}${LIB_NAME}ConfigVersion.cmake
  VERSION       ${${LIB_NAME}_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

export(
  EXPORT    ${LIB_NAME}Targets
  FILE      ${GENEREATED_CONFIG_DIRECTORY}${LIB_NAME}Targets.cmake
  NAMESPACE ${LIB_NAME}::
  )

install(
  EXPORT      ${LIB_NAME}Targets
  DESTINATION ${INSTALL_CONFIG_DIRECTORY}
  NAMESPACE   ${LIB_NAME}::
  FILE        ${LIB_NAME}Targets.cmake
  )

#install Config and ConfigVersion files
install(
  FILES 
    cmake/${LIB_NAME}Config.cmake
    ${GENERATED_CONFIG_DIRECTORY}${LIB_NAME}ConfigVersion.cmake
  DESTINATION
    ${INSTALL_CONFIG_DIRECTORY}
  COMPONENT
    Devel
  )

