# This is part of the Findosg* suite used to find OpenSceneGraph components.
# Each component is separate and you must opt in to each module. You must
# also opt into OpenGL and OpenThreads (and Producer if needed) as these
# modules won't do it for you. This is to allow you control over your own
# system piece by piece in case you need to opt out of certain components
# or change the Find behavior for a particular module (perhaps because the
# default FindOpenGL.cmake module doesn't work with your system as an
# example).
# If you want to use a more convenient module that includes everything,
# use the FindOpenSceneGraph.cmake instead of the Findosg*.cmake modules.
#
# Locate osgDB
# This module defines
# osgDB_FOUND, if false, do not try to link to osgDB
# OSGDB_LIBRARY
# OSGDB_INCLUDE_DIR, where to find the headers
# osgDB target will be created for cmake 3.0.0 and newer
#
# $OSGDIR is an environment variable that would
# correspond to the ./configure --prefix=$OSGDIR
# used in building osg.
#
# Created by Eric Wing.
#
# Modified by PCJohn (Jan Peciva):
# Look for config file first. Create SDL2 target. Print GPUEngine style message.
# Updated code formatting to match the one used in GPUEngine.

# Header files are presumed to be included like
# #include <osg/PositionAttitudeTransform>
# #include <osgDB/DatabasePager>


# try config-based find first
find_package(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)

# use regular old-style approach
if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FOUND)

   # search paths
   if(!WIN32)
      set(SEARCH_PATHS
         ~/Library/Frameworks
         /Library/Frameworks
         /usr/local
         /usr
         /sw # Fink
         /opt/local # DarwinPorts
         /opt/csw # Blastwave
         /opt)
   else()
      set(SEARCH_PATHS)
   endif()

   # try the user's environment request before anything else
   find_path(OSGDB_INCLUDE_DIR osgDB/DatabasePager
      HINTS
      $ENV{OSGDB_DIR}
      $ENV{OSG_DIR}
      $ENV{OSGDIR}
      PATH_SUFFIXES include
      PATHS
         ${SEARCH_PATHS}
         [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OpenThreads_ROOT]
         [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]
   )

   find_library(OSGDB_LIBRARY_RELEASE
      NAMES osgDB
      HINTS
      $ENV{OSGDB_DIR}
      $ENV{OSG_DIR}
      $ENV{OSGDIR}
      PATH_SUFFIXES lib64 lib
      PATHS
         ${SEARCH_PATHS}
   )

   find_library(OSGDB_LIBRARY_DEBUG
      NAMES osgDBd
      HINTS
      $ENV{OSGDB_DIR}
      $ENV{OSG_DIR}
      $ENV{OSGDIR}
      PATH_SUFFIXES lib64 lib
      PATHS
         ${SEARCH_PATHS}
   )

   # set *_FOUND flag
   if(OSGDB_INCLUDE_DIR AND (OSGDB_LIBRARY_RELEASE OR OSGDB_LIBRARY_DEBUG))
      set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)
   endif()

   # substitute RELEASE and DEBUG libraries if one is missing
   if(NOT OSGDB_LIBRARY_RELEASE AND OSGDB_LIBRARY_DEBUG)
      set(OSGDB_LIBRARY_RELEASE ${OSGDB_LIBRARY_DEBUG})
   endif()
   if(NOT OSGDB_LIBRARY_DEBUG AND OSGDB_LIBRARY_RELEASE)
      set(OSGDB_LIBRARY_DEBUG ${OSGDB_LIBRARY_RELEASE})
   endif()

   # set OSGDB_LIBRARY
   set(OSGDB_LIBRARY optimized ${OSGDB_LIBRARY_RELEASE} debug ${OSGDB_LIBRARY_DEBUG})

   # target for cmake 3.0.0 and newer
   if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
      if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
         if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
            add_library(${CMAKE_FIND_PACKAGE_NAME} SHARED IMPORTED)
            set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
               INTERFACE_INCLUDE_DIRECTORIES "${OSGDB_INCLUDE_DIR}"
               IMPORTED_LOCATION_DEBUG "${OSGDB_LIBRARY_DEBUG}"
               IMPORTED_LOCATION_RELEASE "${OSGDB_LIBRARY_RELEASE}"
               IMPORTED_IMPLIB_DEBUG "${OSGDB_LIBRARY_DEBUG}c"
               IMPORTED_IMPLIB_RELEASE "${OSGDB_LIBRARY_RELEASE}"
            )
         endif()
      endif()
   endif()

endif()

# message
include(GEMacros)
if(OSGDB_LIBRARY_RELEASE)
   ge_report_find_status("${OSGDB_LIBRARY_RELEASE}")
elseif(OSGDB_LIBRARY_DEBUG)
   ge_report_find_status("${OSGDB_LIBRARY_DEBUG}")
else()
   ge_report_find_status("")
endif()
