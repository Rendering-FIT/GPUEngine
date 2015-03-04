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
# OSG_LIBRARY
# OSG_FOUND, if false, do not try to link to osg
# OSG_INCLUDE_DIR, where to find the headers
#
# $OSGDIR is an environment variable that would
# correspond to the ./configure --prefix=$OSGDIR
# used in building osg.
#
# Created by Eric Wing.

# Header files are presumed to be included like
# #include <osg/PositionAttitudeTransform>
# #include <osgUtil/SceneView>

# Search paths
IF (!WIN32)
SET(SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt)
ELSE (!WIN32)
SET(SEARCH_PATHS)
ENDIF (!WIN32)

# Try the user's environment request before anything else.
FIND_PATH(OSG_INCLUDE_DIR osg/PositionAttitudeTransform
  HINTS
  $ENV{OSG_DIR}
  $ENV{OSGDIR}
  PATH_SUFFIXES include
  PATHS
    ${SEARCH_PATHS}
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OpenThreads_ROOT]
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]
)

FIND_LIBRARY(OSG_LIBRARY_RELEASE
  NAMES osg
  HINTS
  $ENV{OSG_DIR}
  $ENV{OSGDIR}
  PATH_SUFFIXES lib64 lib
  PATHS
    ${SEARCH_PATHS}
)

FIND_LIBRARY(OSG_LIBRARY_DEBUG
  NAMES osgd
  HINTS
  $ENV{OSG_DIR}
  $ENV{OSGDIR}
  PATH_SUFFIXES lib64 lib
  PATHS
    ${SEARCH_PATHS}
)

# set release to debug (if only debug found)
IF(NOT OSG_LIBRARY_RELEASE AND OSG_LIBRARY_DEBUG)
  SET(OSG_LIBRARY_RELEASE ${OSG_LIBRARY_DEBUG})
ENDIF(NOT OSG_LIBRARY_RELEASE AND OSG_LIBRARY_DEBUG)

# set debug to release (if only release found)
IF(NOT OSG_LIBRARY_DEBUG AND OSG_LIBRARY_RELEASE)
  SET(OSG_LIBRARY_DEBUG ${OSG_LIBRARY_RELEASE})
ENDIF(NOT OSG_LIBRARY_DEBUG AND OSG_LIBRARY_RELEASE)

# OSG_LIBRARY
SET(OSG_LIBRARY optimized ${OSG_LIBRARY_RELEASE} debug ${OSG_LIBRARY_DEBUG})

# OSG_FOUND
SET(OSG_FOUND "NO")
IF(OSG_LIBRARY AND OSG_INCLUDE_DIR)
  SET(OSG_FOUND "YES")
ENDIF(OSG_LIBRARY AND OSG_INCLUDE_DIR)

