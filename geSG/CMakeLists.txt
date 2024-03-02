cmake_minimum_required(VERSION 3.11.1)
cmake_policy(VERSION 3.11.1)

project(geSG)

set(LIB_NAME_UPPER)
string(TOUPPER ${PROJECT_NAME} LIB_NAME_UPPER)

include(GenerateExportHeader)
include(GNUInstallDirs)

set(HEADER_PATH ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME})
set(SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME})


set(SG_INCLUDES
   ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/Export.h
   ${HEADER_PATH}/AABB.h
   ${HEADER_PATH}/Animation.h
   ${HEADER_PATH}/AnimationChannel.h
   ${HEADER_PATH}/AnimationKeyFrame.h
   ${HEADER_PATH}/AnimationManager.h
   ${HEADER_PATH}/AttributeDescriptor.h
   ${HEADER_PATH}/BoundingSphere.h
   ${HEADER_PATH}/BoundingVolume.h
   ${HEADER_PATH}/DefaultImage.h
   ${HEADER_PATH}/KeyframeInterpolator.h
   ${HEADER_PATH}/Image.h
   ${HEADER_PATH}/Intersector.h
   ${HEADER_PATH}/Light.h
   ${HEADER_PATH}/Material.h
   ${HEADER_PATH}/MatrixTransform.h
   ${HEADER_PATH}/Mesh.h
   ${HEADER_PATH}/MeshPrimitiveIterator.h
   ${HEADER_PATH}/MeshTriangleIterators.h
   ${HEADER_PATH}/Model.h
   ${HEADER_PATH}/Node.h
   ${HEADER_PATH}/Ray.h
   ${HEADER_PATH}/RayAABBIntersector.h
   ${HEADER_PATH}/RayMeshIntersector.h
   ${HEADER_PATH}/RaySphereIntersector.h
   ${HEADER_PATH}/RayTriangleIntersector.h
   ${HEADER_PATH}/Sampler.h
   ${HEADER_PATH}/Scene.h
   ${HEADER_PATH}/Transform.h
   ${HEADER_PATH}/Camera.h
)

set(SG_SOURCES
   ${SRC_PATH}/AABB.cpp
   ${SRC_PATH}/Animation.cpp
   ${SRC_PATH}/AnimationChannel.cpp
   ${SRC_PATH}/AnimationManager.cpp
   ${SRC_PATH}/BoundingSphere.cpp
   ${SRC_PATH}/DefaultImage.cpp
   ${SRC_PATH}/MatrixTransform.cpp
   ${SRC_PATH}/RayAABBIntersector.cpp
   ${SRC_PATH}/RayMeshIntersector.cpp
   ${SRC_PATH}/RaySphereIntersector.cpp
   ${SRC_PATH}/RayTriangleIntersector.cpp
)

################################################
# PACKAGES

find_package(glm REQUIRED)
find_package(GPUEngine COMPONENTS geCore) #uses custom module to report if the util is not added as subdir from GPUE master CMake

#########################################
# Target

ADD_LIBRARY(${PROJECT_NAME}
    ${SG_INCLUDES}
    ${SG_SOURCES}
  )

GENERATE_EXPORT_HEADER(${PROJECT_NAME}
   EXPORT_FILE_NAME "${PROJECT_NAME}/Export.h"
)
  
# since we need to specify the ste library as the interface dependency for the export scripts to propagate it but we need cmake to know that this will be a target and not ste.lib since we need it later in the examples in this build tree
add_library(ste INTERFACE IMPORTED)

target_link_libraries(${PROJECT_NAME}
   PUBLIC geCore glm
   INTERFACE ste
)


target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${PROJECT_NAME}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

#########################################
# Install

install(FILES
   ${SG_INCLUDES}
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
set(Dependencies geCore glm ste)
configure_file(
   ${PROJECT_NAME}Config.cmake.in
   "${PROJECT_NAME}Config.cmake"
   @ONLY
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
        )
