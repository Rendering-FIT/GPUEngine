set(APP_NAME geViewerOSG)

project(${APP_NAME})

find_package(OpenGL REQUIRED)
find_package(SDL2)
find_package(AntTweakBar)
find_package(osg)
find_package(osgDB)

if(NOT osg_FOUND OR NOT osgDB_FOUND OR
   NOT SDL2_FOUND OR NOT AntTweakBar_FOUND)
   return()
endif()

set(APP_SOURCES
  main.cpp
  )

set(APP_INCLUDES
  )

add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES})

set(Internal_deps geRG geGL geUtil WindowObject OsgImport)
set(External_libs OpenGL GLEW SDL2 AntTweakBar osg osgDB)
set(Internal_inc
  ${GPUEngine_SOURCE_DIR}/include
  ${GPUEngine_SOURCE_DIR}
  )

target_link_libraries(${APP_NAME} ${Internal_deps} ${External_libs})
set_target_properties(${APP_NAME} PROPERTIES
  INCLUDE_DIRECTORIES "${Internal_inc}"
  )
