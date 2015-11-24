#
# Try to find the FreeImagePlus library and include path.
# Once done this will define
#
# FREEIMAGEPLUS_FOUND
# FREEIMAGEPLUS_INCLUDE_DIR
# FREEIMAGEPLUS_LIBRARY
#
# original by castano
# https://code.google.com/p/nvidia-texture-tools/source/browse/trunk/cmake/FindFreeImage.cmake

# try config-based approach first
# (this was not tested as FreeImage did not provided config-based approach)
FIND_PACKAGE(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)
IF(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
   IF(NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
      MESSAGE(STATUS "Found FreeImagePlus: ${FREEIMAGEPLUS_LIBRARY}")
   ENDIF()
   RETURN()
ENDIF()

# use regular old-style approach
IF (WIN32)
	FIND_PATH(FREEIMAGEPLUS_INCLUDE_DIR FreeImagePlus.h
		${FREEIMAGEPLUS_ROOT_DIR}/include
		${FREEIMAGEPLUS_ROOT_DIR}
		DOC "The directory where FreeImagePlus.h resides")
	FIND_LIBRARY(FREEIMAGEPLUS_LIBRARY
		NAMES FreeImagePlus freeimageplus
		PATHS
		${FREEIMAGEPLUS_ROOT_DIR}/lib
		${FREEIMAGEPLUS_ROOT_DIR}
		DOC "The FreeImagePlus library")
ELSE (WIN32)
	FIND_PATH(FREEIMAGEPLUS_INCLUDE_DIR FreeImagePlus.h
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		DOC "The directory where FreeImagePlus.h resides")
	FIND_LIBRARY(FREEIMAGEPLUS_LIBRARY
		NAMES FreeImagePlus freeimageplus
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		DOC "The FreeImagePlus library")
ENDIF (WIN32)

SET(FREEIMAGEPLUS_FOUND OFF  BOOL "Set to TRUE if FreeImagePlus is found, FALSE otherwise")

IF (FREEIMAGEPLUS_INCLUDE_DIR AND FREEIMAGEPLUS_LIBRARY)
	SET(FREEIMAGEPLUS_FOUND ON  BOOL "Set to TRUE if FreeImagePlus is found, FALSE otherwise")
ENDIF ()

MARK_AS_ADVANCED(FREEIMAGEPLUS_FOUND)
