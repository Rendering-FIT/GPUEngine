cmake_minimum_required(VERSION 2.8.0)

set(APP_NAME EmptyWindow)

set(APP_SOURCES
  src/main.cpp 
  src/WindowObject.cpp 
  src/ArgumentObject.cpp 
  src/shaderdir.cpp
  )

set(APP_INCLUDES
  src/main.h
  src/WindowObject.h
  src/ArgumentObject.h
  src/shaderdir.h
  )

SET(CMAKE_MODULE_PATH "CMakeModules;${CMAKE_MODULE_PATH}")

find_package(GLEW   REQUIRED)
find_package(OPENGL REQUIRED)

include_directories(${GLEW_INCLUDE_PATH} ${OPENGL_INCLUDE_PATH})
set(LIBS ${LIBS} ${GLEW_LIBRARY} ${OPENGL_LIBRARY})

add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES})

