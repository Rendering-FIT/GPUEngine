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


