set(LIB_NAME geUtil)

set(Upstream_VERSION 1.0.0)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

set(LIB_NAME_LOWER)
string(TOLOWER ${LIB_NAME} LIB_NAME_LOWER)


if(GPUENGINE_DYNAMIC_LINKAGE)
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
   add_definitions(-D"${LIB_NAME_UPPER}"_LIBRARY)
else()
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
   add_definitions(-DGE_LIBRARY_STATIC)
endif()

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})

set(ARGUMENTMANAGER_SOURCES
   ArgumentManager/ArgData.cpp
   ArgumentManager/BaseData.cpp
   ArgumentManager/ArrayData.cpp
   ArgumentManager/StructData.cpp
   ArgumentManager/ArgumentManager.cpp
)

set(ARGUMENTMANAGER_INCLUDES
   ${HEADER_PATH}/ArgumentManager/ArgData.h
   ${HEADER_PATH}/ArgumentManager/BaseData.h
   ${HEADER_PATH}/ArgumentManager/ArrayData.h
   ${HEADER_PATH}/ArgumentManager/StructData.h
   ${HEADER_PATH}/ArgumentManager/ArgumentManager.h
)

set(UTIL_INCLUDES
   ${HEADER_PATH}/algorithms.h
   ${HEADER_PATH}/ArgumentObject.h
   ${HEADER_PATH}/ArgumentViewer.h
   ${HEADER_PATH}/CameraObject.h
   ${HEADER_PATH}/CameraPath.h
   ${HEADER_PATH}/FPSPrinter.h
   ${HEADER_PATH}/Intersector.h
   ${HEADER_PATH}/macros.h
   ${HEADER_PATH}/MatrixStack.h
   ${HEADER_PATH}/OrbitManipulator.h
   ${HEADER_PATH}/Progress.h
   ${HEADER_PATH}/Ray.h
   ${HEADER_PATH}/geUtil.h
   ${HEADER_PATH}/Camera.h
   ${HEADER_PATH}/OrbitCamera.h
   ${HEADER_PATH}/FreeLookCamera.h
   ${HEADER_PATH}/PerspectiveCamera.h
   ${HEADER_PATH}/Sampler.h
   ${HEADER_PATH}/Timer.h
)


set(GL_SOURCES
   ArgumentObject.cpp
   ArgumentViewer.cpp
   CameraObject.cpp
   CameraPath.cpp
   FPSPrinter.cpp
   OrbitManipulator.cpp
   Progress.cpp
   OrbitCamera.cpp
   FreeLookCamera.cpp
   PerspectiveCamera.cpp
)

find_package(geCore CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_library(${LIB_NAME}
   ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
   ${UTIL_INCLUDES}
   ${ARGUMENTMANAGER_INCLUDES}
   ${GL_SOURCES}
   ${ARGUMENTMANAGER_SOURCES}
   ${LIBRARYLOADER_SOURCES}
)
add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

target_compile_definitions(${LIB_NAME} PUBLIC GLM_ENABLE_EXPERIMENTAL)

target_link_libraries(${LIB_NAME} PUBLIC geCore glm)

if(UNIX)
  target_link_libraries(${LIB_NAME} PUBLIC dl)
endif()


include(GenerateExportHeader)

generate_export_header(${LIB_NAME})
set_property(TARGET ${LIB_NAME} APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING ${LIB_NAME}_MAJOR_VERSION
  )

target_include_directories(${LIB_NAME} PUBLIC  
  $<BUILD_INTERFACE:${GPUEngine_BINARY_DIR}/include/>  
  $<BUILD_INTERFACE:${GPUEngine_BINARY_DIR}/src/>  
  $<BUILD_INTERFACE:${GPUEngine_SOURCE_DIR}/include/>  
  $<INSTALL_INTERFACE:include/> 
)

install(TARGETS ${LIB_NAME} EXPORT ${LIB_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  )
install(FILES
   ${ARGUMENTMANAGER_INCLUDES}
   DESTINATION include/${LIB_NAME}/ArgumentManager
)
install(FILES
   ${UTIL_INCLUDES}
   DESTINATION include/${LIB_NAME}
)
install(
  FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME_LOWER}_export.h"
  DESTINATION
  include/${LIB_NAME}
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

