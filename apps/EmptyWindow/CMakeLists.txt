cmake_minimum_required(VERSION 2.8.0)


set(APP_NAME EmptyWindow.bin)

project(${APP_NAME})

set(APP_SOURCES
  src/main.cpp 
  src/shaderdir.cpp
  )

set(APP_INCLUDES
  src/main.h
  src/shaderdir.h
  )

SET(CMAKE_MODULE_PATH "CMakeModules;${CMAKE_MODULE_PATH}")

find_package(GLEW        REQUIRED)
find_package(OPENGL      REQUIRED)
find_package(SDL2        REQUIRED)
find_package(AntTweakBar REQUIRED)
find_package(geGL        REQUIRED)
find_package(geUtil      REQUIRED)



add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES})

include_directories(
  ${GEUTIL_INCLUDE_PATH} 
  ${GEGL_INCLUDE_PATH} 
  ${GLEW_INCLUDE_PATH} 
  ${OPENGL_INCLUDE_PATH} 
  ${SDL2_INCLUDE_PATH} 
  ${ANTTWEAKBAR_INCLUDE_PATH}
  )
target_link_libraries(${APP_NAME} 
  ${GEUTIL_LIBRARY}
  ${GEGL_LIBRARY}
  ${GLEW_LIBRARY} 
  ${OPENGL_LIBRARY} 
  ${SDL2_LIBRARY} 
  ${ANTTWEAKBAR_LIBRARY}
  )


