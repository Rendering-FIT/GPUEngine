#
# Try to find Assimp
# Once done, this will define
#
# [assimp|ASSIMP]_FOUND - system has Assimp
# ASSIMP_INCLUDE_DIRS - the Assimp include directories
# ASSIMP_LIBRARIES - link these to use Assimp

# try config-based find first
FIND_PACKAGE(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)
IF(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
   IF(NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
      MESSAGE(STATUS "Found ASSIMP: ${ASSIMP_LIBRARIES}")
   ENDIF()
   RETURN()
ENDIF()

# use regular old-style approach
FIND_PATH(ASSIMP_INCLUDE_DIRS assimp/mesh.h
  /usr/include
  /usr/local/include
  /opt/local/include
)

FIND_LIBRARY(ASSIMP_LIBRARIES assimp
  /usr/lib64
  /usr/lib
  /usr/local/lib
  /opt/local/lib
)

IF(ASSIMP_INCLUDE_DIRS AND ASSIMP_LIBRARIES)
  SET(${CMAKE_FIND_PACKAGE_NAME}_FOUND TRUE )
ENDIF()

IF(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
   IF(NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
      MESSAGE(STATUS "Found ASSIMP: ${ASSIMP_LIBRARIES}")
   ENDIF()
ELSE()
   IF(${CMAKE_FIND_PACKAGE_NAME}_FIND_REQUIRED)
      MESSAGE(SEND_ERROR "Could not find ASSIMP")
   ENDIF()
ENDIF()
