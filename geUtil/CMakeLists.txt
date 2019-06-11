cmake_minimum_required(VERSION 3.11.1)
cmake_policy(VERSION 3.11.1)

project(geUtil)

set(LIB_NAME_UPPER)
string(TOUPPER ${PROJECT_NAME} LIB_NAME_UPPER)

include(GenerateExportHeader)
include(GNUInstallDirs)

set(HEADER_PATH ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME})
set(SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME})


set(ARGUMENTMANAGER_SOURCES
   ${SRC_PATH}/ArgumentManager/ArgData.cpp
   ${SRC_PATH}/ArgumentManager/BaseData.cpp
   ${SRC_PATH}/ArgumentManager/ArrayData.cpp
   ${SRC_PATH}/ArgumentManager/StructData.cpp
   ${SRC_PATH}/ArgumentManager/ArgumentManager.cpp
)

set(ARGUMENTMANAGER_INCLUDES
   ${HEADER_PATH}/ArgumentManager/ArgData.h
   ${HEADER_PATH}/ArgumentManager/BaseData.h
   ${HEADER_PATH}/ArgumentManager/ArrayData.h
   ${HEADER_PATH}/ArgumentManager/StructData.h
   ${HEADER_PATH}/ArgumentManager/ArgumentManager.h
)

set(UTIL_INCLUDES
   ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/Export.h
   ${HEADER_PATH}/algorithms.h
   ${HEADER_PATH}/ArgumentObject.h
   ${HEADER_PATH}/ArgumentViewer.h
   ${HEADER_PATH}/CameraObject.h
   ${HEADER_PATH}/CameraPath.h
   ${HEADER_PATH}/FPSPrinter.h
   ${HEADER_PATH}/MatrixManipulatorInterface.h
   ${HEADER_PATH}/MatrixStack.h
   ${HEADER_PATH}/BasicManipulatorInterface.h
   ${HEADER_PATH}/OrbitManipulator.h
   ${HEADER_PATH}/Progress.h
   ${HEADER_PATH}/geUtil.h
   ${HEADER_PATH}/Camera.h
   ${HEADER_PATH}/OrbitCamera.h
   ${HEADER_PATH}/FreeLookCamera.h
   ${HEADER_PATH}/PerspectiveCamera.h
   ${HEADER_PATH}/Text.h
   ${HEADER_PATH}/Timer.h
)


set(UTIL_SOURCES
   ${SRC_PATH}/ArgumentObject.cpp
   ${SRC_PATH}/ArgumentViewer.cpp
   ${SRC_PATH}/CameraObject.cpp
   ${SRC_PATH}/CameraPath.cpp
   ${SRC_PATH}/FPSPrinter.cpp
   ${SRC_PATH}/OrbitManipulator.cpp
   ${SRC_PATH}/Progress.cpp
   ${SRC_PATH}/OrbitCamera.cpp
   ${SRC_PATH}/FreeLookCamera.cpp
   ${SRC_PATH}/PerspectiveCamera.cpp
   ${SRC_PATH}/Text.cpp
)

add_library(${PROJECT_NAME}
   ${UTIL_INCLUDES}
   ${ARGUMENTMANAGER_INCLUDES}
   ${UTIL_SOURCES}
   ${ARGUMENTMANAGER_SOURCES}
   ${LIBRARYLOADER_SOURCES}
)

GENERATE_EXPORT_HEADER(${PROJECT_NAME}
   EXPORT_FILE_NAME "${PROJECT_NAME}/Export.h"
)

################################################
# PACKAGES

find_package(glm REQUIRED)
find_package(GPUEngine COMPONENTS geCore)

################################################
# External_libs - external libs or targets to link with

set(External_libs glm)
if(UNIX)
  set(External_libs ${External_libs} dl)
endif()


target_link_libraries(${PROJECT_NAME} geCore ${External_libs})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${PROJECT_NAME}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

#########################################
# Install

install(FILES
   ${ARGUMENTMANAGER_INCLUDES}
   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/ArgumentManager
)

install(FILES
   ${UTIL_INCLUDES}
   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )


#########################################
#Export

install(EXPORT ${PROJECT_NAME}Targets
   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

#export(EXPORT ${PROJECT_NAME}Targets) #error https://stackoverflow.com/questions/5378528/install-export-problem-for-shared-lib-with-dependencies

set(Dependencies geCore glm)

configure_file(
   ${PROJECT_NAME}Config.cmake.in
   "${PROJECT_NAME}Config.cmake"
   @ONLY
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
        )
