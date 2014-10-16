#
# Try to find geGL library and include path.
# Once done this will define
#
# GEGL_FOUND
# GEGL_INCLUDE_PATH
# GEGL_LIBRARY
#

IF (WIN32)
  FIND_PATH( GEGL_INCLUDE_PATH geGL
		$ENV{PROGRAMFILES}/geGL/include
		${PROJECT_SOURCE_DIR}/src/nvgl/geGL/include
    DOC "The directory where geGL resides")
  FIND_LIBRARY( GEGL_LIBRARY
		NAMES geGL
		PATHS
		$ENV{PROGRAMFILES}/geGL/lib
		${PROJECT_SOURCE_DIR}/src/nvgl/geGL/bin
		${PROJECT_SOURCE_DIR}/src/nvgl/geGL/lib
		DOC "The geGL library")
ELSE (WIN32)
  FIND_PATH( GEGL_INCLUDE_PATH geGL
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		DOC "The directory where geGL resides")
  FIND_LIBRARY( GEGL_LIBRARY
    NAMES GEGL geGL
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		DOC "The geGL library")
ENDIF (WIN32)

IF (GEGL_INCLUDE_PATH)
  SET( GEGL_FOUND 1 CACHE STRING "Set to 1 if geGL is found, 0 otherwise")
ELSE (GEGL_INCLUDE_PATH)
  SET( GEGL_FOUND 0 CACHE STRING "Set to 1 if geGL is found, 0 otherwise")
ENDIF (GEGL_INCLUDE_PATH)

MARK_AS_ADVANCED( GEGL_FOUND )
