set(LIB_NAME geVuSG)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

if(GPUENGINE_DYNAMIC_LINKAGE)
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
   add_definitions(-D"${LIB_NAME_UPPER}"_LIBRARY)
else()
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
   add_definitions(-DGE_LIBRARY_STATIC)
endif()

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/geAd/${LIB_NAME}/include/${LIB_NAME})

find_package(ste)

set(dependencies geVu geSG ste)

foreach(dep ${dependencies})
  if(NOT TARGET ${dep})
	return()
  endif()
endforeach()


set(VUSG_INCLUDES
  ${HEADER_PATH}/geVuSG.h
  ${HEADER_PATH}/geVuSGClasses.h

  ${HEADER_PATH}/SceneManager.h
  ${HEADER_PATH}/PhongTechnique.h
  ${HEADER_PATH}/Drawable.h
  ${HEADER_PATH}/PipelineFactory.h
 )

set(VUSG_SOURCES
  src/PhongTechnique.cpp
  src/SceneManager.cpp
  src/Drawable.cpp
  src/PipelineFactory.cpp
)

################################################
# PACKAGES

add_library(${LIB_NAME}
  ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
  ${VUSG_INCLUDES}
  ${VUSG_SOURCES}
  )

################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_deps_Export - other than 'ge' packages goes here (e.g. glew), it configures this package extra project dependencies and also configures the config file
# External_libs - external libs or targets to link with
# Internal_inc - additional include directories
# Includes_to_export - includes to be exported from this target to application


#set(External_libs )
set(Internal_deps geSG geVu ste)
set(Internal_inc ${GPUEngine_SOURCE_DIR}/geAd/${LIB_NAME}/include/)
set(includes_to_export ${GPUEngine_SOURCE_DIR}/geAd/${LIB_NAME}/include/)
set(External_deps_Export ${External_libs})

target_link_libraries(${LIB_NAME} ${Internal_deps} ${External_libs} )
set_target_properties(${LIB_NAME} PROPERTIES
  INCLUDE_DIRECTORIES ${Internal_inc}
  INTERFACE_INCLUDE_DIRECTORIES ${includes_to_export}
  )

install(FILES
  ${VUSG_INCLUDES}
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
#   )

# @TODO fix this?

configure_file(
  ../../src/CMake/geConfig.cmake.in
  "${LIB_NAME}Config.cmake"
  @ONLY
  )


configure_file(
  ../../src/CMake/geExport.h.in
  "${GPUEngine_SOURCE_DIR}/geAd/${LIB_NAME}/include/${LIB_NAME}/Export.h"
  @ONLY
  )

# INSTALL_CM_DIR is defined in master CMakeLists file

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake"
  DESTINATION "${INSTALL_CM_DIR}/${LIB_NAME}"
  )
