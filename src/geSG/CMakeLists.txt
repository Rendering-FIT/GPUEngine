set(LIB_NAME geSG)

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})
set(SG_INCLUDES
    ${HEADER_PATH}/Export.h
    ${HEADER_PATH}/ParentChildList.h
    ${HEADER_PATH}/Array.h
    ${HEADER_PATH}/AttribType.h
    ${HEADER_PATH}/AttribConfig.h
    ${HEADER_PATH}/AttribReference.h
    ${HEADER_PATH}/AttribStorage.h
    ${HEADER_PATH}/SeparateBuffersAttribStorage.h
    ${HEADER_PATH}/AttribManager.h
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
    AttribType.cpp
    AttribConfig.cpp
    AttribStorage.cpp
    SeparateBuffersAttribStorage.cpp
    AttribManager.cpp
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

include_directories(${GLM_INCLUDE_DIR})
  
install(FILES
    ${SG_INCLUDES}
    DESTINATION include/${LIB_NAME}
  )

install(TARGETS ${LIB_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
