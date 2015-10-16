set(LIB_NAME WindowObject)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

IF   (GPUENGINE_DYNAMIC)
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
    ADD_DEFINITIONS(-D"${LIB_NAME_UPPER}"_LIBRARY)
ELSE ()
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
    ADD_DEFINITIONS(-DGE_LIBRARY_STATIC)
ENDIF()

SET(CMAKE_MODULE_PATH "${GPUEngine_SOURCE_DIR}/geAdd/${LIB_NAME}/CMakeModules;${CMAKE_MODULE_PATH}")

set(SDL2_BUILDING_LIBRARY ON)
FIND_PACKAGE(SDL2        QUIET)
FIND_PACKAGE(AntTweakBar QUIET)

#if(NOT SDL2_FOUND OR NOT ANTTWEAKBAR_FOUND)
#   return()
#endif()

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/geAdd/${LIB_NAME})

set (ADD_INCLUDES
  ${HEADER_PATH}/Export.h
  ${HEADER_PATH}/WindowObject.h
  ) 
set (ADD_SOURCES
  WindowObject.cpp
  )


ADD_LIBRARY(${LIB_NAME}
    ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
    ${ADD_INCLUDES}
    ${ADD_SOURCES}
  )

################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_deps_Export - other than 'ge' packages goes here (e.g. glew), it configures this package extra project dependencies and also configures the config file
# External_libs - external libs or targets to link with
# Internal_inc - additional include directories
# Includes_to_export - includes to be exported from this target to application

set(Internal_deps)
set(External_deps_Export SDL2 AntTweakBar )
set(External_libs ${SDL2_LIBRARY} ${ANTTWEAKBAR_LIBRARY})
set(Internal_inc ${SDL2_INCLUDE_DIR} ${ANTTWEAKBAR_INCLUDE_DIR} ${GPUEngine_SOURCE_DIR} ${GPUEngine_SOURCE_DIR}/include)
set(includes_to_export)

target_link_libraries(${LIB_NAME} ${Internal_deps} ${External_libs} )
set_target_properties(${LIB_NAME} PROPERTIES
	INCLUDE_DIRECTORIES "${Internal_inc}"
	INTERFACE_INCLUDE_DIRECTORIES "${includes_to_export}"
)

install(FILES
    ${ADD_INCLUDES}
    DESTINATION include/geAdd/${LIB_NAME}
  )

install(TARGETS ${LIB_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
  )
  
#########################################
#Export
#configure_package_config_file( 
#   geGLConfig.cmake.in
#   geGLConfig.cmake
#   INSTALL_DESTINATION lib/cmake/geGL
#)

configure_file(
   ../../src/CMake/geConfig.cmake.in
   "${LIB_NAME}Config.cmake"
   @ONLY
)


configure_file(
   ../../src/CMake/geExport.h.in
   "${GPUEngine_SOURCE_DIR}/geAdd/${LIB_NAME}/Export.h"
   @ONLY
)

# INSTALL_CM_DIR is defined in master CMakeLists file

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake"
        DESTINATION "${INSTALL_CM_DIR}/${LIB_NAME}"
        )
