add_subdirectory(geViewerOSG)
add_subdirectory(MultiCubePerf)
add_subdirectory(Shadows)

if(GPUENGINE_BUILD_APP_geViewerAssimp)
  add_subdirectory(geViewerAssimp)
endif()
