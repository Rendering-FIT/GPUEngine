add_subdirectory(geViewerOSG)
add_subdirectory(MultiCubeTest)
add_subdirectory(Shadows)

if(GPUENGINE_BUILD_APP_geViewerAssimp)
  add_subdirectory(geViewerAssimp)
endif()
