cmake_minimum_required(VERSION 3.11.1)
cmake_policy(VERSION 3.11.1)

project(geUtil)

set(LIB_NAME_UPPER)
string(TOUPPER ${PROJECT_NAME} LIB_NAME_UPPER)

include(GenerateExportHeader)
include(GNUInstallDirs)

set(HEADER_PATH ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME})
set(SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME})


set(UTIL_INCLUDES
   ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/Export.h
   ${HEADER_PATH}/Camera.h
   ${HEADER_PATH}/FPSPrinter.h
   ${HEADER_PATH}/ManipulatorInterfaces.h
   ${HEADER_PATH}/MatrixStack.h
   ${HEADER_PATH}/OrbitManipulator.h
   ${HEADER_PATH}/Progress.h
   ${HEADER_PATH}/geUtil.h
   ${HEADER_PATH}/Text.h
   ${HEADER_PATH}/Timer.h
)


set(UTIL_SOURCES
   ${SRC_PATH}/BasicCamera.cpp
   ${SRC_PATH}/FPSPrinter.cpp
   ${SRC_PATH}/OrbitManipulator.cpp
   ${SRC_PATH}/Progress.cpp
   ${SRC_PATH}/Text.cpp
)

add_library(${PROJECT_NAME}
   ${UTIL_INCLUDES}
   ${UTIL_SOURCES}
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
