set(APP_NAME geViewerOSG)

project(${APP_NAME})

find_package(glm    REQUIRED)
find_package(SDL2)
find_package(osg)
find_package(osgDB)
find_package(OpenThreads)

if(NOT SDL2_FOUND OR NOT osg_FOUND OR NOT osgDB_FOUND OR NOT OpenThreads_FOUND OR
   NOT TARGET geRG OR NOT TARGET OsgImport)
   return()
endif()

set(APP_SOURCES
  main.cpp
  OrbitCameraManipulator.h OrbitCameraManipulator.cpp
  )

set(APP_INCLUDES
  )

add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES})

set(Internal_deps geRG geGL geUtil SDLWindow OsgImport)
set(External_libs SDL2 osg osgDB OpenThreads)
set(Internal_inc
  ${GPUEngine_SOURCE_DIR}/include
  ${GPUEngine_SOURCE_DIR}
  )

target_link_libraries(${APP_NAME} ${Internal_deps} ${External_libs})
set_target_properties(${APP_NAME} PROPERTIES
  INCLUDE_DIRECTORIES "${Internal_inc}"
  )
