set(APP_NAME geVuConsole)

project(${APP_NAME})

find_package(assimp)

find_package(AssimpModelLoader QUIET HINTS ${GPUEngine_SOURCE_DIR}/geAD/AssimpModelLoader/cmake)
find_package(FreeImageImageLoader QUIET HINTS ${GPUEngine_SOURCE_DIR}/geAD/FreeImageImageLoader/cmake)


set(dependencies geVu geSG geVuSG geUtil assimp AssimpModelLoader FreeImageImageLoader FreeImage FreeImagePlus)

foreach(dep ${dependencies})
  if(NOT TARGET ${dep})
	return()
  endif()
endforeach()
  
set(APP_SOURCES
	src/main.cpp
	src/app.cpp
	src/ConsoleSwapchain.cpp
	src/img.cpp
)




set(APP_INCLUDES
	src/app.h
	src/ConsoleSwapchain.h
	src/img.h
)

add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES})

################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_libs - external libs or targets to link with
# Internal_inc - additional include directories

set(Internal_deps geVu geSG geVuSG geUtil AssimpModelLoader FreeImageImageLoader)
set(External_libs assimp FreeImage FreeImagePlus)
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
