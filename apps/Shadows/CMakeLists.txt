set(APP_NAME Shadows)

project(${APP_NAME})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Assimp)
find_package(FreeImage)
find_package(FreeImagePlus)
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

if(NOT TARGET SDLWindow OR 
   NOT TARGET Assimp OR
   NOT TARGET geGL OR
   NOT TARGET geUtil OR
   NOT TARGET FreeImage)
   return()
endif()

add_subdirectory(TSSV)
add_subdirectory(HSSV)
add_subdirectory(GSSV)
add_subdirectory(SM)
add_subdirectory(CSM)
add_subdirectory(FTS)
add_subdirectory(VSSV)
add_subdirectory(CSSV)
add_subdirectory(CSSVSOE)

set(APP_SOURCES
  main.cpp
  Model.cpp
  CameraPath.cpp
  CSV.cpp
  Shading.cpp
  ShadowMethod.cpp
  FastAdjacency.cpp
  TimeStamp.cpp
  Sintorn.cpp
  SintornTiles.cpp
  RSSV.cpp
  RSSVTiles.cpp
  DrawPrimitive.cpp
  ShadowVolumes.cpp
  GSCaps.cpp
  )

set(APP_INCLUDES
  CameraPath.h
  CSV.h
  Deferred.h
  Defines.h
  Model.h
  Shading.h
  ShadowMethod.h
  FastAdjacency.h
  TimeStamp.h
  Sintorn.h
  SintornTiles.h
  SintornShaders.h
  RSSV.h
  RSSVTiles.h
  RSSVShaders.h
  DrawPrimitive.h
  ProgramExtension.h
  ShadowVolumes.h
  ShadowVolumesShaders.h
  SilhouetteShaders.h
  Material.h
  Texture.h
  GSCaps.h
  GSCapsShaders.h
  IShadowMapping.h
  )

source_group("TSSV" FILES ${TSSV_FILES})
source_group("HSSV" FILES ${HSSV_FILES})
source_group("GSSV" FILES ${GSSV_FILES})
source_group("SM"   FILES ${SM_FILES})
source_group("CSM"  FILES ${CSM_FILES})
source_group("FTS"  FILES ${FTS_FILES})
source_group("VSSV" FILES ${VSSV_FILES})
source_group("CSSV" FILES ${CSSV_FILES})
source_group("CSSVSOE" FILES ${CSSVSOE_FILES})

add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES} 
	${TSSV_FILES} 
	${HSSV_FILES} 
	${GSSV_FILES} 
	${SM_FILES} 
	${CSM_FILES} 
	${FTS_FILES}
	${VSSV_FILES}
	${CSSV_FILES}
	${CSSVSOE_FILES})

################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_libs - external libs or targets to link with
# Internal_inc - additional include directories

set(Internal_deps geGL SDLWindow geUtil)
set(External_libs Assimp FreeImage)
set(Internal_inc
  ${GPUEngine_SOURCE_DIR}/include
  ${GPUEngine_SOURCE_DIR}
  )

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#      message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

target_link_libraries(${APP_NAME} ${Internal_deps} ${External_libs})

if (UNIX)
    target_link_libraries(${APP_NAME} -lstdc++fs)
endif (UNIX)

set_target_properties(${APP_NAME} PROPERTIES
  INCLUDE_DIRECTORIES "${Internal_inc}"
  )
