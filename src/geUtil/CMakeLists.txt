set(LIB_NAME geUtil)

project(${LIB_NAME})

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})
set(GL_INCLUDES
  ${HEADER_PATH}/ArgumentObject.h
  ${HEADER_PATH}/CameraObject.h
  ${HEADER_PATH}/CameraPath.h
  )

set(GL_SOURCES
  ArgumentObject.cpp  
  CameraObject.cpp
  CameraPath.cpp
  )

if(ANTTWEAKBAR_FOUND)
set(GL_INCLUDES ${GL_INCLUDES} ${HEADER_PATH}/WindowObject.h)
set(GL_SOURCES ${GL_SOURCES} WindowObject.cpp)
include_directories(${ANTTWEAKBAR_INCLUDE_DIR})
endif()

ADD_LIBRARY(${LIB_NAME}
    ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
    ${GL_INCLUDES}
    ${GL_SOURCES}
  )

find_package(GLEW   REQUIRED)
find_package(OPENGL REQUIRED)

include_directories(${GLEW_INCLUDE_PATH} ${OPENGL_INCLUDE_PATH})
target_link_libraries(${LIB_NAME} ${GLEW_LIBRARY} ${OPENGL_LIBRARY})

install(FILES
    ${GL_INCLUDES}
    DESTINATION include/${LIB_NAME}
  )

install(TARGETS ${LIB_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
  )
