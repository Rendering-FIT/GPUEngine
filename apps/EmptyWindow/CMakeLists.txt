cmake_minimum_required(VERSION 2.8.0)


set(APP_NAME EmptyWindow)

project(${APP_NAME})

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

find_package(GLEW        REQUIRED)
find_package(OPENGL      REQUIRED)
find_package(SDL2        REQUIRED)
find_package(AntTweakBar REQUIRED)


add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES})

include_directories(${GLEW_INCLUDE_PATH} ${OPENGL_INCLUDE_PATH})
target_link_libraries(${APP_NAME} 
  ${GLEW_LIBRARY} 
  ${OPENGL_LIBRARY} 
  ${SDL2_LIBRARY} 
  ${ANTTWEAKBAR_LIBRARY})


