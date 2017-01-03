SET(PACKAGES 
  geCore
  #geGL
  #geRG
  #geSG
  #geUtil
  )

if(GPUENGINE_BUILD_GEGL)
  set(PACKAGES ${PACKAGES} geGL)
endif()

if(GPUENGINE_BUILD_GESG)
  set(PACKAGES ${PACKAGES} geSG)
endif()

if(GPUENGINE_BUILD_GERG)
  set(PACKAGES ${PACKAGES} geRG)
endif()

if(GPUENGINE_BUILD_GEUTIL)
  set(PACKAGES ${PACKAGES} geUtil)
endif()

if(GPUENGINE_BUILD_GEPARSER)
  set(PACKAGES ${PACKAGES} geParser)
endif()

if(GPUENGINE_BUILD_GEDE)
  set(PACKAGES ${PACKAGES} geDE)
endif()

if(GPUENGINE_BUILD_GEVU)
  set(PACKAGES ${PACKAGES} geVu)
endif()

FOREACH(mylibfolder ${PACKAGES}
    #geGL
    #geCore
    #geRG
    #geSG
    #geUtil
    )

  ADD_SUBDIRECTORY(${mylibfolder})

ENDFOREACH()
