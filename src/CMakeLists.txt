FOREACH( mylibfolder 
        geGL
    )

    ADD_SUBDIRECTORY(${mylibfolder})

ENDFOREACH()
