FOREACH(mylibfolder
        geGL
        geCore
        geSG
  )

  ADD_SUBDIRECTORY(${mylibfolder})

ENDFOREACH()
