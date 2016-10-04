set(APP_NAME Shadows)

project(${APP_NAME})

find_package(SDL2)
find_package(Assimp)
find_package(FreeImage)
find_package(FreeImagePlus)
find_package(glm)

if(NOT SDL2_FOUND OR NOT TARGET Assimp OR
   NOT FreeImage_FOUND OR NOT FreeImagePlus_FOUND OR
   NOT TARGET geGL OR
   NOT TARGET glm OR
   NOT TARGET geUtil)
   return()
endif()


set(APP_SOURCES
  main.cpp
  Model.cpp
  PerspectiveCamera.cpp
  OrbitCamera.cpp
  Shading.cpp
  CubeShadowMapping.cpp
  FastAdjacency.cpp
  TimeStamp.cpp
  CSSV.cpp
  Sintorn.cpp
  SintornTiles.cpp
  )

set(APP_INCLUDES
  Camera.h
  PerspectiveCamera.h
  OrbitCamera.h
  Deferred.h
  Model.h
  Shading.h
  ShadowMethod.h
  CubeShadowMapping.h
  FastAdjacency.h
  TimeStamp.h
  CSSV.h
  CSSVShaders.h
  Sintorn.h
  SintornTiles.h
  SintornShaders.h
  )

add_executable(${APP_NAME} WIN32 ${APP_SOURCES} ${APP_INCLUDES})

################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_libs - external libs or targets to link with
# Internal_inc - additional include directories

set(Internal_deps geGL SDLWindow geUtil)
set(External_libs SDL2 Assimp FreeImage FreeImagePlus)
set(Internal_inc
  ${GPUEngine_SOURCE_DIR}/include
  ${GPUEngine_SOURCE_DIR}
  )

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#      message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

target_link_libraries(${APP_NAME} ${Internal_deps} ${External_libs})
set_target_properties(${APP_NAME} PROPERTIES
  INCLUDE_DIRECTORIES "${Internal_inc}"
  )
