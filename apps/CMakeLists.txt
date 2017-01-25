set(apps 
  geViewerAssimp
  geViewerOSG
  geVuConsole
  geVuViewer
  MultiCubePerf
  RgProfiling
  Shadows
)

foreach(app ${apps})
	set(GPUENGINE_BUILD_APP_${app} OFF  CACHE BOOL "Build ${app} application.")
	if(GPUENGINE_BUILD_APP_${app})
		add_subdirectory(${app})
	endif()
endforeach()