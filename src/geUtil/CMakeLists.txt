set(LIB_NAME geUtil)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

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
   ${HEADER_PATH}/Export.h
   ${HEADER_PATH}/algorithms.h
   ${HEADER_PATH}/ArgumentObject.h
   ${HEADER_PATH}/CameraObject.h
   ${HEADER_PATH}/CameraPath.h
   ${HEADER_PATH}/FPSPrinter.h
   ${HEADER_PATH}/Timer.h
   ${HEADER_PATH}/Interpolator.h
   ${HEADER_PATH}/Intersector.h
   ${HEADER_PATH}/macros.h
   ${HEADER_PATH}/MatrixStack.h
   ${HEADER_PATH}/OrbitManipulator.h
   ${HEADER_PATH}/Progress.h
   ${HEADER_PATH}/Ray.h
   ${HEADER_PATH}/geUtil.h
)


set(GL_SOURCES
   ArgumentObject.cpp
   CameraObject.cpp
   CameraPath.cpp
   FPSPrinter.cpp
   OrbitManipulator.cpp
   Progress.cpp
)

add_library(${LIB_NAME}
   ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
   ${UTIL_INCLUDES}
   ${ARGUMENTMANAGER_INCLUDES}
   ${GL_SOURCES}
   ${ARGUMENTMANAGER_SOURCES}
   ${LIBRARYLOADER_SOURCES}
)

################################################
# PACKAGES

find_package(glm REQUIRED)

################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_deps_Export - other than 'ge' packages goes here (e.g. glew), it configures this package extra project dependencies and also configures the config file
# External_libs - external libs or targets to link with
# Internal_inc - additional include directories
# Includes_to_export - includes to be exported from this target to application

set(Internal_deps)
set(External_deps_Export glm)
set(External_libs glm)
set(Internal_inc ${GPUEngine_SOURCE_DIR}/include)
set(Includes_to_export ${GPUEngine_SOURCE_DIR}/include)

if(UNIX)
  set(External_libs ${External_libs} dl)
endif()


target_link_libraries(${LIB_NAME} ${Internal_deps} ${External_libs})
set_target_properties(${LIB_NAME} PROPERTIES
   INCLUDE_DIRECTORIES "${Internal_inc}"
   INTERFACE_INCLUDE_DIRECTORIES "${Includes_to_export}"
)

install(FILES
   ${ARGUMENTMANAGER_INCLUDES}
   DESTINATION include/${LIB_NAME}/ArgumentManager
)

install(FILES
   ${UTIL_INCLUDES}
   DESTINATION include/${LIB_NAME}
)

install(TARGETS ${LIB_NAME}
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
   RUNTIME DESTINATION bin
)


#########################################
#Export

configure_file(
   ../CMake/geConfig.cmake.in
   "${LIB_NAME}Config.cmake"
   @ONLY
)


configure_file(
   ../CMake/geExport.h.in
   "${GPUEngine_SOURCE_DIR}/include/${LIB_NAME}/Export.h"
   @ONLY
)

# INSTALL_CM_DIR is defined in master CMakeLists file

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake"
        DESTINATION "${INSTALL_CM_DIR}/${LIB_NAME}"
        )
