add_subdirectory(geCore)

if(GPUENGINE_BUILD_GEGL)
  add_subdirectory(geGL)
endif()

if(GPUENGINE_BUILD_GESG)
  add_subdirectory(geSG)
endif()

if(GPUENGINE_BUILD_GERG)
  add_subdirectory(geRG)
endif()

if(GPUENGINE_BUILD_GEUTIL)
  add_subdirectory(geUtil)
endif()

if(GPUENGINE_BUILD_GEPARSER)
  add_subdirectory(geParser)
endif()

if(GPUENGINE_BUILD_GEDE)
  add_subdirectory(geDE)
endif()

