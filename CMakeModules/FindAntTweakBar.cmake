#
# Module for finding AntTweakBar
#
# The module will define:
# AntTweakBar_FOUND - True if AntTweakBar development files were found
# ANTTWEAKBAR_INCLUDE_DIR - AntTweakBar include directories
# ANTTWEAKBAR_LIBRARY - AntTweakBar libraries to link
#
# AntTweakBar target will be created for cmake 3.0.0 and newer
#


# try config-based find first
find_package(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)

# use regular old-style approach
if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FOUND)

   find_path(ANTTWEAKBAR_INCLUDE_DIR AntTweakBar.h
      DOC "Path to AntTweakBar include directory."
      HINTS $ENV{ANTTWEAKBAR_ROOT}
      PATH_SUFFIX include  # For finding the include file under the root of the glfw expanded archive, typically on Windows.
      PATHS /usr/include/
            /usr/local/include/
            ${ANTTWEAKBAR_ROOT_DIR}/include/
            ${CMAKE_SOURCE_DIR}/extlibs/headers
   )

   find_library(ANTTWEAKBAR_LIBRARY
      DOC "Absolute path to AntTweakBar library."
      NAMES AntTweakBar
      HINTS $ENV{ANTTWEAKBAR_ROOT}
      PATH_SUFFIXES lib/win32  # For finding the library file under the root of the glfw expanded archive, typically on Windows.
      PATHS /usr/local/lib
            /usr/lib
            ${ANTTWEAKBAR_ROOT_DIR}/lib-msvc100/release
   )

   # set *_FOUND flag
   if(ANTTWEAKBAR_INCLUDE_DIR AND ANTTWEAKBAR_LIBRARY)
      set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)
   endif()

   # target for cmake 3.0.0 and newer
   if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
      if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
         if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
            add_library(${CMAKE_FIND_PACKAGE_NAME} INTERFACE IMPORTED)
            set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
               INTERFACE_INCLUDE_DIRECTORIES "${ANTTWEAKBAR_INCLUDE_DIR}"
               INTERFACE_LINK_LIBRARIES "${ANTTWEAKBAR_LIBRARY}"
            )
         endif()
      endif()
   endif()

endif()

# message
include(GEMacros)
ge_report_find_status("${ANTTWEAKBAR_LIBRARY}")
