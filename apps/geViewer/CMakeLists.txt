set(APP_NAME geViewer)

project(${APP_NAME})

find_package(SDL2)
find_package(AntTweakBar)
find_package(osg)
find_package(osgDB)

if(NOT OSG_FOUND OR NOT OSGDB_FOUND OR
   NOT SDL2_FOUND OR NOT ANTTWEAKBAR_FOUND)
   return()
endif()

set(APP_SOURCES
  main.cpp
  )

set(APP_INCLUDES
  )

add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES})

set(Internal_deps geRG geGL geUtil WindowObject)
set(External_libs
  ${GLEW_LIBRARY}
  ${OPENGL_LIBRARY}
  ${SDL2_LIBRARY}
  ${ANTTWEAKBAR_LIBRARY}
  ${X11_LIBRARIES}
  ${OSG_LIBRARY}
  ${OSGDB_LIBRARY}
  )
set(Internal_inc
  ${GPUEngine_SOURCE_DIR}/include
  ${GPUEngine_SOURCE_DIR}
  ${GLEW_INCLUDE_DIR}
  ${OPENGL_INCLUDE_DIR}
  ${SDL2_INCLUDE_DIR}
  ${ANTTWEAKBAR_INCLUDE_DIR}
  ${OSG_INCLUDE_DIR}
  ${OSGDB_INCLUDE_DIR}
  )

target_link_libraries(${APP_NAME} ${Internal_deps} ${External_libs})
set_target_properties(${APP_NAME} PROPERTIES
  INCLUDE_DIRECTORIES "${Internal_inc}"
  )
