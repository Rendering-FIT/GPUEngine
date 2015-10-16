set(APP_NAME emptyWindow)

project(${APP_NAME})

set(APP_SOURCES
  main.cpp
  )

set(APP_INCLUDES
  )

add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES})

################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_deps_Export - other than 'ge' packages goes here (e.g. glew), it configures this package extra project dependencies and also configures the config file
# External_libs - external libs or targets to link with
# Internal_inc - additional include directories
# Includes_to_export - includes to be exported from this target to application


set(Internal_deps geGL geUtil WindowObject)
set(External_deps_Export)
set(External_libs 
  ${GLEW_LIBRARY}
  ${OPENGL_LIBRARY}
  ${SDL2_LIBRARY}
  ${ANTTWEAKBAR_LIBRARY}
  ${X11_LIBRARIES}
  )
set(Internal_inc
  ${GLEW_INCLUDE_DIR}
  ${OPENGL_INCLUDE_DIR}
  ${SDL2_INCLUDE_DIR}
  ${ANTTWEAKBAR_INCLUDE_DIR}
  ${GPUEngine_SOURCE_DIR}/include
  ${GPUEngine_SOURCE_DIR}
  )
set(Includes_to_export)

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#      message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

target_link_libraries(${APP_NAME} ${Internal_deps} ${External_libs})
set_target_properties(${APP_NAME} PROPERTIES
  INCLUDE_DIRECTORIES "${Internal_inc}"
  INTERFACE_INCLUDE_DIRECTORIES "${Includes_to_export}"
  )
