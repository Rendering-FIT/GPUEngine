set(LIB_NAME OsgImport)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

if(GPUENGINE_DYNAMIC_LINKAGE)
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
   add_definitions(-DGEAD_LIBRARY)
else()
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
   add_definitions(-DGE_LIBRARY_STATIC)
endif()

find_package(glm    REQUIRED)
find_package(osg)
find_package(OpenThreads)

if(NOT osg_FOUND OR NOT OpenThreads_FOUND)
   return()
endif()

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/geAd/${LIB_NAME})

set(ADD_INCLUDES
   ${HEADER_PATH}/../Export.h
   ${HEADER_PATH}/OsgImport.h
)

set(ADD_SOURCES
   OsgImport.cpp
)


add_library(${LIB_NAME}
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

set(Internal_deps glm geRG geGL)
set(External_deps_Export)
set(External_libs osg OpenThreads)
set(Internal_inc ${GPUEngine_SOURCE_DIR}/include ${GPUEngine_SOURCE_DIR})
set(includes_to_export)

target_link_libraries(${LIB_NAME} ${Internal_deps} ${External_libs})
set_target_properties(${LIB_NAME} PROPERTIES
   INCLUDE_DIRECTORIES "${Internal_inc}"
   INTERFACE_INCLUDE_DIRECTORIES "${includes_to_export}"
)

install(FILES
   ${ADD_INCLUDES}
   DESTINATION include/geAd/${LIB_NAME}
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

# INSTALL_CM_DIR is defined in master CMakeLists file

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake"
        DESTINATION "${INSTALL_CM_DIR}/${LIB_NAME}"
)
