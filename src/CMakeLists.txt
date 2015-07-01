FOREACH(mylibfolder
        geGL
        geCore
        geRG
        geUtil
  )

  ADD_SUBDIRECTORY(${mylibfolder})

ENDFOREACH()
