set(LIB_NAME_UPPER GEAD)

configure_file(
   ../src/CMake/geExport.h.in
   "${GPUEngine_SOURCE_DIR}/geAd/Export.h"
   @ONLY
)

install(FILES
   "${GPUEngine_SOURCE_DIR}/geAd/Export.h"
   DESTINATION include/geAd
)

add_subdirectory(OsgImport)
add_subdirectory(SDLWindow)
add_subdirectory(SDLOrbitManipulator)
add_subdirectory(DEUtil)
add_subdirectory(LibraryLoader)

if(GPUENGINE_BUILD_geVuSG)
	add_subdirectory(geVuSG)
endif()
