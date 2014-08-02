set(LIB_NAME geSG)

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})
set(SG_INCLUDES
    ${HEADER_PATH}/Export.h
    ${HEADER_PATH}/ChildList.h
    ${HEADER_PATH}/Node.h
    ${HEADER_PATH}/Geometry.h
  )

set(SG_SOURCES
    Node.cpp
  )

ADD_LIBRARY(${LIB_NAME}
    ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
    ${SG_INCLUDES}
    ${SG_SOURCES}
  )

install(FILES
    ${SG_INCLUDES}
    DESTINATION include/ge/${LIB_NAME}
  )

install(TARGETS ${LIB_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
