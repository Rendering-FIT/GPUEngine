FOREACH(mylibfolder
        geGL
        geCore
        #geRG
        geSG
        geUtil
  )

  ADD_SUBDIRECTORY(${mylibfolder})

ENDFOREACH()
