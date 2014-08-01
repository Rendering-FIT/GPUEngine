FOREACH( mylibfolder 
        geGL
        geCore
    )

    ADD_SUBDIRECTORY(${mylibfolder})

ENDFOREACH()
