set(APP_NAME geViewerAssimp)

project(${APP_NAME})

find_package(glfw3)
find_package(X11) # glfw3 requires linking with X11_LIBRARIES
find_package(Assimp)
find_package(FreeImage)
find_package(FreeImagePlus)

if(NOT glfw3_FOUND OR NOT Assimp_FOUND OR
   NOT FreeImage_FOUND OR NOT FreeImagePlus_FOUND)
   return()
endif()

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
  )

set(APP_INCLUDES
  )

add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES})

set(Internal_deps geGL geRG geSG geUtil geCore)
set(External_libs OpenGL GLEW glfw3 Assimp FreeImage FreeImagePlus
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
