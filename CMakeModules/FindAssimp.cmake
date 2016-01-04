#
# Try to find Assimp
# Once done, this will define
#
# [assimp|ASSIMP]_FOUND - system has Assimp
# ASSIMP_INCLUDE_DIR - the Assimp include directories
# ASSIMP_LIBRARY - link these to use Assimp

# try config-based find first
FIND_PACKAGE(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)
IF(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
   IF(WIN32)
      SET(ASSIMP_LIBRARY optimized ${ASSIMP_LIBRARY_DIRS}/assimp.lib
                         debug ${ASSIMP_LIBRARY_DIRS}/assimpd.lib)
   ELSE()
      SET(ASSIMP_LIBRARY ${ASSIMP_LIBRARIES})
   ENDIF()
   UNSET(ASSIMP_LIBRARIES)
   SET(ASSIMP_INCLUDE_DIR ${ASSIMP_INCLUDE_DIRS})
   UNSET(ASSIMP_INCLUDE_DIRS)

   IF(NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
      MESSAGE(STATUS "Found ASSIMP: ${ASSIMP_LIBRARY}")
   ENDIF()
   RETURN()
ENDIF()

# use regular old-style approach
FIND_PATH(ASSIMP_INCLUDE_DIR assimp/mesh.h
  /usr/include
  /usr/local/include
  /opt/local/include
)

FIND_LIBRARY(ASSIMP_LIBRARY assimp
  /usr/lib64
  /usr/lib
  /usr/local/lib
  /opt/local/lib
)

IF(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY)
  SET(${CMAKE_FIND_PACKAGE_NAME}_FOUND TRUE )
ENDIF()

#TARGET
if(CMAKE_VERSION VERSION_EQUAL 3.0.0 OR CMAKE_VERSION VERSION_GREATER 3.0.0)
   if(NOT TARGET Assimp)
      add_library(Assimp INTERFACE IMPORTED)
      set_target_properties(Assimp PROPERTIES
         INTERFACE_INCLUDE_DIRECTORIES "${ASSIMP_INCLUDE_DIR}"
         INTERFACE_LINK_LIBRARIES "${ASSIMP_LIBRARY}"
      )
   endif()
endif()

IF(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
   IF(NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
      MESSAGE(STATUS "Found ASSIMP: ${ASSIMP_LIBRARY}")
   ENDIF()
ELSE()
   IF(${CMAKE_FIND_PACKAGE_NAME}_FIND_REQUIRED)
      MESSAGE(SEND_ERROR "Could not find ASSIMP")
   ENDIF()
ENDIF()
