FOREACH(mylibfolder
        geGL
        geCore
        geSG
        geUtil
  )

  ADD_SUBDIRECTORY(${mylibfolder})

ENDFOREACH()
