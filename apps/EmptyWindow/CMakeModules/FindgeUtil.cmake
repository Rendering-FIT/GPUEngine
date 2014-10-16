#
# Try to find geUtil library and include path.
# Once done this will define
#
# GEUTIL_FOUND
# GEUTIL_INCLUDE_PATH
# GEUTIL_LIBRARY
#

IF (WIN32)
  FIND_PATH( GEUTIL_INCLUDE_PATH geUtil
		$ENV{PROGRAMFILES}/geUtil/include
		${PROJECT_SOURCE_DIR}/src/nvgl/geUtil/include
    DOC "The directory where geUtil resides")
  FIND_LIBRARY( GEUTIL_LIBRARY
		NAMES geUtil
		PATHS
		$ENV{PROGRAMFILES}/geUtil/lib
		${PROJECT_SOURCE_DIR}/src/nvgl/geUtil/bin
		${PROJECT_SOURCE_DIR}/src/nvgl/geUtil/lib
		DOC "The geUtil library")
ELSE (WIN32)
  FIND_PATH( GEUTIL_INCLUDE_PATH geUtil
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		DOC "The directory where geUtil resides")
  FIND_LIBRARY( GEUTIL_LIBRARY
    NAMES GEUTIL geUtil
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		DOC "The geUtil library")
ENDIF (WIN32)

IF (GEUTIL_INCLUDE_PATH)
  SET( GEUTIL_FOUND 1 CACHE STRING "Set to 1 if geUtil is found, 0 otherwise")
ELSE (GEUTIL_INCLUDE_PATH)
  SET( GEUTIL_FOUND 0 CACHE STRING "Set to 1 if geUtil is found, 0 otherwise")
ENDIF (GEUTIL_INCLUDE_PATH)

MARK_AS_ADVANCED( GEUTIL_FOUND )
