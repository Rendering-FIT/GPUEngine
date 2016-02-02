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
# Locate osg
# This module defines
# osg_FOUND, if false, do not try to link to osg
# OSG_LIBRARY
# OSG_INCLUDE_DIR, where to find the headers
# osg target will be created for cmake 3.0.0 and newer
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
   find_path(OSG_INCLUDE_DIR osg/PositionAttitudeTransform
      HINTS
      $ENV{OSG_DIR}
      $ENV{OSGDIR}
      PATH_SUFFIXES include
      PATHS
         ${SEARCH_PATHS}
         [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OpenThreads_ROOT]
         [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]
   )

   find_library(OSG_LIBRARY_RELEASE
      NAMES osg
      HINTS
      $ENV{OSG_DIR}
      $ENV{OSGDIR}
      PATH_SUFFIXES lib64 lib
      PATHS
         ${SEARCH_PATHS}
   )

   find_library(OSG_LIBRARY_DEBUG
      NAMES osgd
      HINTS
      $ENV{OSG_DIR}
      $ENV{OSGDIR}
      PATH_SUFFIXES lib64 lib
      PATHS
         ${SEARCH_PATHS}
   )

   # set *_FOUND flag
   if(OSG_INCLUDE_DIR AND (OSG_LIBRARY_RELEASE OR OSG_LIBRARY_DEBUG))
      set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)
   endif()

   # substitute RELEASE and DEBUG libraries if one is missing
   if(NOT OSG_LIBRARY_RELEASE AND OSG_LIBRARY_DEBUG)
      set(OSG_LIBRARY_RELEASE ${OSG_LIBRARY_DEBUG})
   endif()
   if(NOT OSG_LIBRARY_DEBUG AND OSG_LIBRARY_RELEASE)
      set(OSG_LIBRARY_DEBUG ${OSG_LIBRARY_RELEASE})
   endif()

   # set OSG_LIBRARY
   set(OSG_LIBRARY optimized ${OSG_LIBRARY_RELEASE} debug ${OSG_LIBRARY_DEBUG})

   # target for cmake 3.0.0 and newer
   if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
      if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
         if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
            add_library(${CMAKE_FIND_PACKAGE_NAME} SHARED IMPORTED)
            set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
               INTERFACE_INCLUDE_DIRECTORIES "${OSG_INCLUDE_DIR}"
               IMPORTED_LOCATION_DEBUG "${OSG_LIBRARY_DEBUG}"
               IMPORTED_LOCATION_RELEASE "${OSG_LIBRARY_RELEASE}"
               IMPORTED_IMPLIB_DEBUG "${OSG_LIBRARY_DEBUG}"
               IMPORTED_IMPLIB_RELEASE "${OSG_LIBRARY_RELEASE}"
            )
         endif()
      endif()
   endif()

endif()

# message
include(GEMacros)
if(OSG_LIBRARY_RELEASE)
   ge_report_find_status("${OSG_LIBRARY_RELEASE}")
elseif(OSG_LIBRARY_DEBUG)
   ge_report_find_status("${OSG_LIBRARY_DEBUG}")
else()
   ge_report_find_status("")
endif()
