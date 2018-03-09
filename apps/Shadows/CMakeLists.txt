set(APP_NAME Shadows)

project(${APP_NAME})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Assimp)
find_package(FreeImage)
find_package(FreeImagePlus)

if(NOT TARGET SDLWindow OR 
   NOT TARGET Assimp OR
   NOT TARGET geGL OR
   NOT TARGET geUtil)
   return()
endif()

add_subdirectory(TSSV)


set(APP_SOURCES
  main.cpp
  Model.cpp
  CameraPath.cpp
  CSV.cpp
  Shading.cpp
  ShadowMethod.cpp
  CubeShadowMapping.cpp
  FastAdjacency.cpp
  TimeStamp.cpp
  CSSV.cpp
  CSSVSOE.cpp
  Sintorn.cpp
  SintornTiles.cpp
  RSSV.cpp
  RSSVTiles.cpp
  VSSV.cpp
  DrawPrimitive.cpp
  ShadowVolumes.cpp
  )

set(APP_INCLUDES
  CameraPath.h
  CSV.h
  Deferred.h
  Model.h
  Shading.h
  ShadowMethod.h
  CubeShadowMapping.h
  CubeShadowMappingShaders.h
  FastAdjacency.h
  TimeStamp.h
  CSSV.h
  CSSVShaders.h
  CSSVSOE.h
  Sintorn.h
  SintornTiles.h
  SintornShaders.h
  RSSV.h
  RSSVTiles.h
  RSSVShaders.h
  VSSV.h
  VSSVShaders.h
  DrawPrimitive.h
  ProgramExtension.h
  ShadowVolumes.h
  ShadowVolumesShaders.h
  SilhouetteShaders.h
  )

source_group("TSSV" FILES ${TSSV_FILES})

add_executable(${APP_NAME} WIN32 ${APP_SOURCES} ${APP_INCLUDES} ${TSSV_FILES})

################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_libs - external libs or targets to link with
# Internal_inc - additional include directories

set(Internal_deps geGL SDLWindow geUtil)
set(External_libs Assimp)
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
