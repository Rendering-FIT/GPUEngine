# Locate OpenThreads (part of OpenSceneGraph)
# This module defines
# OPENTHREADS_FOUND, if false, do not try to link to OpenThreads
# OPENTHREADS_INCLUDE_DIR, where to find the headers
# OPENTHREADS_LIBRARY_RELEASE
# OPENTHREADS_LIBRARY_DEBUG
# OpenThreads target will be created for cmake 3.0.0 and newer.
#
# $OPENTHREADS_DIR is an environment variable that would
# correspond to the ./configure --prefix=$OPENTHREADS_DIR
# used in building osg.
#
# Created by Eric Wing.
# Modified by PCJohn (Jan Peciva):
# Look for config file first. Create OpenThreads target. Print GPUEngine style message.
# Updated code formatting to match the one used in GPUEngine.

# try config-based find first
find_package(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)

# use regular old-style approach
if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FOUND)

   FIND_PATH(OPENTHREADS_INCLUDE_DIR OpenThreads/Thread
      PATHS
      $ENV{OPENTHREADS_INCLUDE_DIR}
      $ENV{OPENTHREADS_DIR}/include
      $ENV{OPENTHREADS_DIR}
      $ENV{OSG_INCLUDE_DIR}
      $ENV{OSG_DIR}/include
      $ENV{OSG_DIR}
      $ENV{OSGDIR}/include
      $ENV{OSGDIR}
      NO_DEFAULT_PATH
   )

   FIND_PATH(OPENTHREADS_INCLUDE_DIR OpenThreads/Thread
      PATHS ${CMAKE_PREFIX_PATH} # Unofficial: We are proposing this.
      NO_DEFAULT_PATH
      PATH_SUFFIXES include
   )

   FIND_PATH(OPENTHREADS_INCLUDE_DIR OpenThreads/Thread
      ~/Library/Frameworks
      /Library/Frameworks
      /usr/local/include
      /usr/include
      /sw/include # Fink
      /opt/local/include # DarwinPorts
      /opt/csw/include # Blastwave
      /opt/include
      [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OpenThreads_ROOT]/include
      [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]/include
   )


   FIND_LIBRARY(OPENTHREADS_LIBRARY_RELEASE
      NAMES OpenThreads OpenThreadsWin32 
      PATHS
      $ENV{OPENTHREADS_LIBRARY_DIR}
      $ENV{OPENTHREADS_DIR}/lib64
      $ENV{OPENTHREADS_DIR}/lib
      $ENV{OPENTHREADS_DIR}
      $ENV{OSG_LIBRARY_DIR}
      $ENV{OSG_DIR}/lib64
      $ENV{OSG_DIR}/lib
      $ENV{OSG_DIR}
      $ENV{OSGDIR}/lib64
      $ENV{OSGDIR}/lib
      $ENV{OSGDIR}
      NO_DEFAULT_PATH
   )

   FIND_LIBRARY(OPENTHREADS_LIBRARY_RELEASE
      NAMES OpenThreads OpenThreadsWin32 
      PATHS ${CMAKE_PREFIX_PATH} # Unofficial: We are proposing this.
      NO_DEFAULT_PATH
      PATH_SUFFIXES lib64 lib
   )

   FIND_LIBRARY(OPENTHREADS_LIBRARY_RELEASE
      NAMES OpenThreads OpenThreadsWin32 
      PATHS
      ~/Library/Frameworks
      /Library/Frameworks
      /usr/local/lib64
      /usr/local/lib
      /usr/lib64
      /usr/lib
      /sw/lib64
      /sw/lib
      /opt/local/lib64
      /opt/local/lib
      /opt/csw/lib64
      /opt/csw/lib
      /opt/lib64
      /opt/lib
      [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OpenThreads_ROOT]/lib
      [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]/lib
   )


   FIND_LIBRARY(OPENTHREADS_LIBRARY_DEBUG 
      NAMES OpenThreadsd OpenThreadsWin32d
      PATHS
      $ENV{OPENTHREADS_DEBUG_LIBRARY_DIR}
      $ENV{OPENTHREADS_LIBRARY_DIR}
      $ENV{OPENTHREADS_DIR}/lib64
      $ENV{OPENTHREADS_DIR}/lib
      $ENV{OPENTHREADS_DIR}
      $ENV{OSG_LIBRARY_DIR}
      $ENV{OSG_DIR}/lib64
      $ENV{OSG_DIR}/lib
      $ENV{OSG_DIR}
      $ENV{OSGDIR}/lib64
      $ENV{OSGDIR}/lib
      $ENV{OSGDIR}
      NO_DEFAULT_PATH
   )

   FIND_LIBRARY(OPENTHREADS_LIBRARY_DEBUG 
      NAMES OpenThreadsd OpenThreadsWin32d
      PATHS ${CMAKE_PREFIX_PATH} # Unofficial: We are proposing this.
      NO_DEFAULT_PATH
      PATH_SUFFIXES lib64 lib
   )

   FIND_LIBRARY(OPENTHREADS_LIBRARY_DEBUG 
      NAMES OpenThreadsd OpenThreadsWin32d
      PATHS
      /usr/local/lib64
      /usr/local/lib
      /usr/lib64
      /usr/lib
      /sw/lib64
      /sw/lib
      /opt/local/lib64
      /opt/local/lib
      /opt/csw/lib64
      /opt/csw/lib
      /opt/lib64
      /opt/lib
      [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OpenThreads_ROOT]/lib
      [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]/lib
   )


   # set *_FOUND flag
   if(OPENTHREADS_INCLUDE_DIR AND (OPENTHREADS_LIBRARY_RELEASE OR OPENTHREADS_LIBRARY_DEBUG))
      set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)
   endif()

   # substitute RELEASE and DEBUG libraries if one is missing
   if(NOT OPENTHREADS_LIBRARY_RELEASE AND OPENTHREADS_LIBRARY_DEBUG)
      set(OPENTHREADS_LIBRARY_RELEASE ${OPENTHREADS_LIBRARY_DEBUG})
   endif()
   if(NOT OPENTHREADS_LIBRARY_DEBUG AND OPENTHREADS_LIBRARY_RELEASE)
      set(OPENTHREADS_LIBRARY_DEBUG ${OPENTHREADS_LIBRARY_RELEASE})
   endif()

   # target for cmake 3.0.0 and newer
   if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
      if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
         if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
            add_library(${CMAKE_FIND_PACKAGE_NAME} SHARED IMPORTED)
            set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
               INTERFACE_INCLUDE_DIRECTORIES "${OPENTHREADS_INCLUDE_DIR}"
               IMPORTED_LOCATION_DEBUG "${OPENTHREADS_LIBRARY_DEBUG}"
               IMPORTED_LOCATION_RELEASE "${OPENTHREADS_LIBRARY_RELEASE}"
               IMPORTED_IMPLIB_DEBUG "${OPENTHREADS_LIBRARY_DEBUG}"
               IMPORTED_IMPLIB_RELEASE "${OPENTHREADS_LIBRARY_RELEASE}"
            )
         endif()
      endif()
   endif()

endif()

# message
include(GEMacros)
if(OPENTHREADS_LIBRARY_RELEASE)
   ge_report_find_status("${OPENTHREADS_LIBRARY_RELEASE}")
elseif(OPENTHREADS_LIBRARY_DEBUG)
   ge_report_find_status("${OPENTHREADS_LIBRARY_DEBUG}")
else()
   ge_report_find_status("")
endif()
