cmake_minimum_required(VERSION 3.11.1)
cmake_policy(VERSION 3.11.1)

project(geRG)

set(LIB_NAME_UPPER)
string(TOUPPER ${PROJECT_NAME} LIB_NAME_UPPER)

include(GenerateExportHeader)
include(GNUInstallDirs)

set(HEADER_PATH ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME})
set(SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME})

set(RG_INCLUDES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/Export.h
    ${HEADER_PATH}/Basics.h
    ${HEADER_PATH}/ParentChildList.h
    ${HEADER_PATH}/AllocationManagers.h
    ${HEADER_PATH}/BufferStorage.h
    ${HEADER_PATH}/FlexibleArrayList.h
    ${HEADER_PATH}/AttribType.h
    ${HEADER_PATH}/AttribConfig.h
    ${HEADER_PATH}/AttribStorage.h
    ${HEADER_PATH}/Mesh.h
    ${HEADER_PATH}/Primitive.h
    ${HEADER_PATH}/Drawable.h
    ${HEADER_PATH}/DrawCommand.h
    ${HEADER_PATH}/RenderingContext.h
    ${HEADER_PATH}/StateSet.h
    ${HEADER_PATH}/StateSetManager.h
    ${HEADER_PATH}/Transformation.h
    ${HEADER_PATH}/MatrixList.h
    ${HEADER_PATH}/MatrixGpuData.h
    ${HEADER_PATH}/FlexibleUniform.h
    ${HEADER_PATH}/Model.h
    ${HEADER_PATH}/ProgressStamp.h
  )

set(RG_SOURCES
    ${SRC_PATH}/Basics.cpp
    ${SRC_PATH}/AllocationManagers.cpp
    ${SRC_PATH}/AttribType.cpp
    ${SRC_PATH}/AttribConfig.cpp
    ${SRC_PATH}/AttribStorage.cpp
    ${SRC_PATH}/Primitive.cpp
    ${SRC_PATH}/DrawCommand.cpp
    ${SRC_PATH}/RenderingContext.cpp
    ${SRC_PATH}/StateSet.cpp
    ${SRC_PATH}/StateSetManager.cpp
    ${SRC_PATH}/Transformation.cpp
    ${SRC_PATH}/MatrixList.cpp
    ${SRC_PATH}/FlexibleUniform.cpp
    ${SRC_PATH}/ProgressStamp.cpp
  )

################################################
# PACKAGES

find_package(glm REQUIRED)
find_package(GPUEngine COMPONENTS geGL geCore)

add_library(${PROJECT_NAME}
    ${RG_INCLUDES}
    ${RG_SOURCES}
  )

GENERATE_EXPORT_HEADER(${PROJECT_NAME}
   EXPORT_FILE_NAME "${PROJECT_NAME}/Export.h"
)
 
target_link_libraries(${PROJECT_NAME} glm geGL geCore)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${PROJECT_NAME}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

#########################################
# Install

install(FILES
   ${RG_INCLUDES}
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

#Dependencies to find in config
set(Dependencies glm geGL geCore)

configure_file(
   ${PROJECT_NAME}Config.cmake.in
   "${PROJECT_NAME}Config.cmake"
   @ONLY
)
  
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)