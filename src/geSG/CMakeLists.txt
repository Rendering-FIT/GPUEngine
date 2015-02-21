set(LIB_NAME geSG)

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})
set(SG_INCLUDES
    ${HEADER_PATH}/Export.h
    ${HEADER_PATH}/ParentChildList.h
    ${HEADER_PATH}/Array.h
    ${HEADER_PATH}/AllocationManagers.h
    ${HEADER_PATH}/FlexibleArrayList.h
    ${HEADER_PATH}/AttribType.h
    ${HEADER_PATH}/AttribConfig.h
    ${HEADER_PATH}/AttribReference.h
    ${HEADER_PATH}/AttribStorage.h
    ${HEADER_PATH}/SeparateBuffersAttribStorage.h
    ${HEADER_PATH}/RenderingContext.h
    ${HEADER_PATH}/Node.h
    ${HEADER_PATH}/Mesh.h
    ${HEADER_PATH}/Group.h
    ${HEADER_PATH}/MatrixTransform.h
    ${HEADER_PATH}/Projection.h
    ${HEADER_PATH}/Camera.h
    ${HEADER_PATH}/StateSet.h
    ${HEADER_PATH}/NodeVisitor.h
  )

set(SG_SOURCES
    AllocationManagers.cpp
    AttribType.cpp
    AttribConfig.cpp
    AttribReference.cpp
    AttribStorage.cpp
    SeparateBuffersAttribStorage.cpp
    RenderingContext.cpp
    Node.cpp
    Mesh.cpp
    Group.cpp
    MatrixTransform.cpp
    Projection.cpp
    Camera.cpp
    NodeVisitor.cpp
  )

ADD_LIBRARY(${LIB_NAME}
    ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
    ${SG_INCLUDES}
    ${SG_SOURCES}
  )

include_directories(${GLM_INCLUDE_DIR} ${GLEW_INCLUDE_PATH})

install(FILES
    ${SG_INCLUDES}
    DESTINATION include/${LIB_NAME}
  )

install(TARGETS ${LIB_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
