add_subdirectory(geViewerOSG)
add_subdirectory(MultiCubePerf)
add_subdirectory(RgProfiling)
add_subdirectory(Shadows)

add_subdirectory(geVuViewer)


if(GPUENGINE_BUILD_APP_geViewerAssimp)
  add_subdirectory(geViewerAssimp)
endif()
