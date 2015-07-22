set(LIB_NAME geSG)
set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

IF   (DYNAMIC_GPUENGINE)
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
    ADD_DEFINITIONS(-D"${LIB_NAME_UPPER}"_LIBRARY)
ELSE ()
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
    ADD_DEFINITIONS(-DGE_LIBRARY_STATIC)
ENDIF()

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})

set(SG_INCLUDES
   ${HEADER_PATH}/Export.h
   ${HEADER_PATH}/AttributeDescriptor.h
   ${HEADER_PATH}/Drawable.h
   ${HEADER_PATH}/Image.h
   ${HEADER_PATH}/Material.h
   ${HEADER_PATH}/MatrixTransform.h
   ${HEADER_PATH}/Mesh.h
   ${HEADER_PATH}/Model.h
   ${HEADER_PATH}/Node.h
   ${HEADER_PATH}/Transform.h
)

set(SG_SOURCES
   AttributeDescriptor.cpp
   Material.cpp
   MatrixTransform.cpp
)

find_package(ste)

ADD_LIBRARY(${LIB_NAME}
    ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
    ${SG_INCLUDES}
    ${SG_SOURCES}
  )

set(Internal_deps geCore)
set(External_deps ste)
set(External_export_libs )
set(External_export_includes )
set(Internal_inc ${GPUEngine_SOURCE_DIR}/include ${GLM_INCLUDE_DIR})
set(includes_to_export ${GPUEngine_SOURCE_DIR}/include)  

target_link_libraries(${LIB_NAME} ${Internal_deps} ste)
 
set_target_properties(${LIB_NAME} PROPERTIES
   INCLUDE_DIRECTORIES "${Internal_inc}"
	INTERFACE_INCLUDE_DIRECTORIES "${includes_to_export}"
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