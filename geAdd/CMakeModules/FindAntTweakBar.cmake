# Locate anttweakbar library
# This module defines the following variables:
# ANTTWEAKBAR_LIBRARY, the name of the library;
# ANTTWEAKBAR_INCLUDE_DIR, where to find glfw include files.
# ANTTWEAKBAR_FOUND, true if both the ANTTWEAKBAR_LIBRARY and ANTTWEAKBAR_INCLUDE_DIR have been found.
#Search for the include file...
FIND_PATH( ANTTWEAKBAR_INCLUDE_DIR AntTweakBar.h
  DOC "Path to AntTweakBar include directory."
  HINTS
  $ENV{ANTTWEAKBAR_ROOT}
  PATH_SUFFIX include #For finding the include file under the root of the glfw expanded archive, typically on Windows.
  PATHS
  /usr/include/
  /usr/local/include/
  ${ANTTWEAKBAR_ROOT_DIR}/include/ # added by ptr
  ${CMAKE_SOURCE_DIR}/extlibs/headers
  )
FIND_LIBRARY(ANTTWEAKBAR_LIBRARY DOC "Absolute path to AntTweakBar library."
  NAMES AntTweakBar
  HINTS
  $ENV{ANTTWEAKBAR_ROOT}
  PATH_SUFFIXES lib/win32 #For finding the library file under the root of the glfw expanded archive, typically on Windows.
  PATHS
  /usr/local/lib
  /usr/lib
  ${ANTTWEAKBAR_ROOT_DIR}/lib-msvc100/release # added by ptr
  )

IF(ANTTWEAKBAR_LIBRARY AND ANTTWEAKBAR_INCLUDE_DIR)
  SET(ANTTWEAKBAR_FOUND TRUE)
  message(STATUS "Found AntTweakBar: ${ANTTWEAKBAR_LIBRARY}")
ELSE()
  return()
ENDIF(ANTTWEAKBAR_LIBRARY AND ANTTWEAKBAR_INCLUDE_DIR)

