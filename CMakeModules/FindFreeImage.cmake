#
# Try to find the FreeImage library and include path.
# Once done this will define
#
# FREEIMAGE_FOUND
# FREEIMAGE_INCLUDE_DIR
# FREEIMAGE_LIBRARY
#
# original by castano
# https://code.google.com/p/nvidia-texture-tools/source/browse/trunk/cmake/FindFreeImage.cmake
# contributions: pcjohn

# try config-based approach first
# (this was not tested as FreeImage did not provided config-based approach)
FIND_PACKAGE(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)
IF(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
   IF(NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
      MESSAGE(STATUS "Found FreeImage: ${FREEIMAGE_LIBRARY}")
   ENDIF()
   RETURN()
ENDIF()

# use regular old-style approach
IF (WIN32)
   FIND_PATH(FREEIMAGE_INCLUDE_DIR FreeImage.h
      ${FREEIMAGE_ROOT_DIR}/include
      ${FREEIMAGE_ROOT_DIR}
      DOC "The directory where FreeImage.h resides")
   FIND_LIBRARY(FREEIMAGE_LIBRARY
      NAMES FreeImage freeimage
      PATHS
      ${FREEIMAGE_ROOT_DIR}/lib
      ${FREEIMAGE_ROOT_DIR}
      DOC "The FreeImage library")
ELSE (WIN32)
   FIND_PATH(FREEIMAGE_INCLUDE_DIR FreeImage.h
      /usr/include
      /usr/local/include
      /sw/include
      /opt/local/include
      DOC "The directory where FreeImage.h resides")
   FIND_LIBRARY(FREEIMAGE_LIBRARY
      NAMES FreeImage freeimage
      PATHS
      /usr/lib64
      /usr/lib
      /usr/local/lib64
      /usr/local/lib
      /sw/lib
      /opt/local/lib
      DOC "The FreeImage library")
ENDIF (WIN32)

SET(FREEIMAGE_LIBRARIES ${FREEIMAGE_LIBRARY})

SET(FREEIMAGE_FOUND OFF  BOOL "Set to TRUE if FreeImage is found, FALSE otherwise")

IF (FREEIMAGE_INCLUDE_DIR AND FREEIMAGE_LIBRARY)
   SET(FREEIMAGE_FOUND ON  BOOL "Set to TRUE if FreeImage is found, FALSE otherwise")
ENDIF ()

MARK_AS_ADVANCED(
   FREEIMAGE_FOUND
   FREEIMAGE_LIBRARY)
