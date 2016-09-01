set(APP_NAME geViewerAssimp)

project(${APP_NAME})

find_package(SDL2)
find_package(Assimp)
find_package(FreeImage)
find_package(FreeImagePlus)

if(NOT SDL2_FOUND OR NOT Assimp_FOUND OR
   NOT FreeImage_FOUND OR NOT FreeImagePlus_FOUND OR
   NOT TARGET geRG)
   return()
endif()

if(WIN32)
   set(EXTRA_SOURCE_FILES UnicodeIOSystem_win32.cpp)
else()
   set(EXTRA_SOURCE_FILES UnicodeIOSystem_other.cpp)
endif(WIN32)

set(APP_SOURCES
  main.cpp
  AssimpModelLoader.cpp
  FreeImageImageLoader.cpp
  BVHGenerator.cpp
  CameraManipulator.cpp
  DefaultImage.cpp
  EnumToGL.cpp
  ForrysVisualizationTechniques.cpp
  InputController.cpp
  NFPlaneAdjustor.cpp
  UnicodeIOStream.cpp
  ${EXTRA_SOURCE_FILES}
  )

set(APP_INCLUDES
  )

add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES})

set(Internal_deps geGL geRG geSG geUtil geCore)
set(External_libs SDL Assimp FreeImage FreeImagePlus
  )
if(UNIX)
  # this is a list of libraries that are not properly included
  # in their ${..._LIBRARY} or ${..._LIBRARIES}
  set(External_libs ${External_libs}
      dl # required by geUtil
      X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL # required by GLFW3
      )
endif()
set(Internal_inc
  ${GPUEngine_SOURCE_DIR}/include
  ${GPUEngine_SOURCE_DIR}
  )

target_link_libraries(${APP_NAME} ${Internal_deps} ${External_libs})
set_target_properties(${APP_NAME} PROPERTIES
  INCLUDE_DIRECTORIES "${Internal_inc}"
  )
