IF   (DYNAMIC_GPUENGINE)
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
    ADD_DEFINITIONS(-DGESG_LIBRARY)
ELSE ()
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
    ADD_DEFINITIONS(-DGE_LIBRARY_STATIC)
ENDIF()

set(LIB_NAME geSG)

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})
set(SG_INCLUDES
    ${HEADER_PATH}/Export.h
    ${HEADER_PATH}/ParentChildList.h
    ${HEADER_PATH}/AllocationManagers.h
    ${HEADER_PATH}/FlexibleArrayList.h
    ${HEADER_PATH}/AttribType.h
    ${HEADER_PATH}/AttribConfig.h
    ${HEADER_PATH}/AttribReference.h
    ${HEADER_PATH}/AttribStorage.h
    ${HEADER_PATH}/SeparateBuffersAttribStorage.h
    ${HEADER_PATH}/InstanceGroup.h
    ${HEADER_PATH}/RenderingContext.h
    ${HEADER_PATH}/StateSet.h
    ${HEADER_PATH}/Transformation.h
    ${HEADER_PATH}/InstancingMatrices.h
  )

set(SG_SOURCES
    AllocationManagers.cpp
    AttribType.cpp
    AttribConfig.cpp
    AttribReference.cpp
    AttribStorage.cpp
    SeparateBuffersAttribStorage.cpp
    InstanceGroup.cpp
    RenderingContext.cpp
    StateSet.cpp
    Transformation.cpp
    InstancingMatrices.cpp
  )

find_package(GLEW   REQUIRED)

ADD_LIBRARY(${LIB_NAME}
    ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
    ${SG_INCLUDES}
    ${SG_SOURCES}
  )

include_directories()

set(Internal_deps geGL)
set(Internal_inc ${GLM_INCLUDE_DIR} ${GLEW_INCLUDE_PATH})
target_link_libraries(${LIB_NAME} ${Internal_deps})
set_target_properties(${LIB_NAME} PROPERTIES 
    INCLUDE_DIRECTORIES "${Internal_inc}"
    INTERFACE_INCLUDE_DIRECTORIES "${GPUEngine_SOURCE_DIR}/include"
)


install(FILES
    ${SG_INCLUDES}
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
   geSGConfig.cmake.in
   geSGConfig.cmake
   @ONLY
)

# INSTALL_CM_DIR is defined in master CMakeLists file

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/geSGConfig.cmake"
        DESTINATION "${INSTALL_CM_DIR}/geSG"
        )
