set(APP_NAME MultiCubePerf)

project(${APP_NAME})

if(
    NOT TARGET SDLWindow OR 
    NOT TARGET geGL      OR 
    NOT TARGET geUtil
    )
   return()
endif()

if(NOT TARGET imgui)
	add_subdirectory(imgui)
endif()
  
set(APP_SOURCES
	src/main.cpp
	src/gui.cpp
	src/stats.cpp
	src/app.cpp
	src/appgl.cpp
	src/apprg.cpp
)

set(APP_INCLUDES
	src/gui.h
	src/stats.h
	src/app.h
	src/appgl.h
	src/apprg.h
)

add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES})

################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_libs - external libs or targets to link with
# Internal_inc - additional include directories

set(Internal_deps SDLWindow geGL geRG geUtil imgui)
set(External_libs )
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
