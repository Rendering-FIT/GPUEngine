set(LIB_NAME SDLWindow)

set(Upstream_VERSION 1.0.0)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

set(LIB_NAME_LOWER)
string(TOLOWER ${LIB_NAME} LIB_NAME_LOWER)


if(GPUENGINE_DYNAMIC_LINKAGE)
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
   add_definitions(-DGEAD_LIBRARY)
else()
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
   add_definitions(-DGE_LIBRARY_STATIC)
endif()

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/geAd/${LIB_NAME})

set(INCLUDES
  ${HEADER_PATH}/SDLWindow.h
  ${HEADER_PATH}/SDLMainLoop.h
  )
set(SOURCES
  SDLWindow.cpp
  SDLMainLoop.cpp
  )

find_package(SDL2 CONFIG REQUIRED)
find_package(geCore CONFIG REQUIRED)

add_library(${LIB_NAME}
  ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
  ${INCLUDES}
  ${SOURCES}
  )
add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

target_link_libraries(${LIB_NAME} 
  PUBLIC 
    SDL2::SDL2
    SDL2::SDL2main
    geCore
    )

include(GenerateExportHeader)

generate_export_header(${LIB_NAME})
set_property(TARGET ${LIB_NAME} APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING ${LIB_NAME}_MAJOR_VERSION
  )

target_include_directories(${LIB_NAME} PUBLIC  
  $<BUILD_INTERFACE:${GPUEngine_BINARY_DIR}/include/>  
  $<BUILD_INTERFACE:${GPUEngine_BINARY_DIR}/src/>  
  $<BUILD_INTERFACE:${GPUEngine_BINARY_DIR}>  
  $<BUILD_INTERFACE:${GPUEngine_SOURCE_DIR}/include/>  
  $<BUILD_INTERFACE:${GPUEngine_SOURCE_DIR}>  
  $<INSTALL_INTERFACE:include/> 
)

install(TARGETS ${LIB_NAME} EXPORT ${LIB_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  )
install(FILES
  ${INCLUDES}
  DESTINATION include/geAd/${LIB_NAME}
  )
install(
  FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME_LOWER}_export.h"
  DESTINATION
  include/geAd/${LIB_NAME}
  COMPONENT
  Devel
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake"
  VERSION ${Upstream_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

export(EXPORT ${LIB_NAME}Targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}Targets.cmake"
  NAMESPACE ${LIB_NAME}::
  )
configure_file(cmake/${LIB_NAME}Config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}Config.cmake"
  COPYONLY
  )

set(ConfigPackageLocation lib/cmake/${LIB_NAME})
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
  "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake"
  DESTINATION
  ${ConfigPackageLocation}
  COMPONENT
  Devel
  )

