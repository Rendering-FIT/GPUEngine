set(LIB_NAME geSG)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

IF   (GPUENGINE_DYNAMIC)
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
    ADD_DEFINITIONS(-D"${LIB_NAME_UPPER}"_LIBRARY)
ELSE ()
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
    ADD_DEFINITIONS(-DGE_LIBRARY_STATIC)
ENDIF()

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})

set(SG_INCLUDES
   ${HEADER_PATH}/Export.h
   ${HEADER_PATH}/Animation.h
   ${HEADER_PATH}/AnimationChannel.h
   ${HEADER_PATH}/AnimationKeyFrame.h
   ${HEADER_PATH}/AnimationManager.h
   ${HEADER_PATH}/AttributeDescriptor.h
   ${HEADER_PATH}/BoundingVolumes.h
   ${HEADER_PATH}/DefaultImage.h
   ${HEADER_PATH}/Drawable.h
   ${HEADER_PATH}/Image.h
   ${HEADER_PATH}/Light.h
   ${HEADER_PATH}/Material.h
   ${HEADER_PATH}/MatrixTransform.h
   ${HEADER_PATH}/Mesh.h
   ${HEADER_PATH}/Model.h
   ${HEADER_PATH}/Node.h
   ${HEADER_PATH}/Scene.h
   ${HEADER_PATH}/Transform.h
)

set(SG_SOURCES
   AttributeDescriptor.cpp
   Animation.cpp
   AnimationChannel.cpp
   AnimationManager.cpp
   DefaultImage.cpp
   Material.cpp
   MatrixTransform.cpp
)

################################################
# PACKAGES

find_package(glm)


ADD_LIBRARY(${LIB_NAME}
    ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
    ${SG_INCLUDES}
    ${SG_SOURCES}
  )
  
################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_deps_Export - other than 'ge' packages goes here (e.g. glew), it configures this package extra project dependencies and also configures the config file
# External_libs - external libs or targets to link with
# Internal_inc - additional include directories
# Includes_to_export - includes to be exported from this target to application

set(Internal_deps geCore)
set(External_deps_Export glm)
set(External_libs glm)
set(Internal_inc ${GLM_INCLUDE_DIR} ${GPUEngine_SOURCE_DIR}/include)
set(Includes_to_export ${GPUEngine_SOURCE_DIR}/include)

target_link_libraries(${LIB_NAME} ${Internal_deps} ${External_libs})
 
set_target_properties(${LIB_NAME} PROPERTIES
   INCLUDE_DIRECTORIES "${Internal_inc}"
	INTERFACE_INCLUDE_DIRECTORIES "${Includes_to_export}"
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
