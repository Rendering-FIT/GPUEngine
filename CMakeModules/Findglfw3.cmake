#
# Try to find GLFW library and include path.
# Once done this will define
#
# [glfw3|GLFW]_FOUND
# GLFW3_INCLUDE_DIR
# GLFW3_LIBRARY
#

# try config-based find first
FIND_PACKAGE(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)
IF(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
   IF(NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
      MESSAGE(STATUS "Found GLFW: ${GLFW3_LIBRARY}")
   ENDIF()
   RETURN()
ENDIF()

# use regular old-style approach
IF(WIN32)

   FIND_PATH(GLFW3_INCLUDE_DIR GLFW/glfw3.h
      $ENV{PROGRAMFILES}/GLFW/include
      ${GLFW_ROOT_DIR}/include
      DOC "The directory where GLFW/glfw3.h resides")

   FIND_LIBRARY(GLFW3_LIBRARY
      NAMES glfw3 GLFW
      PATHS
      $ENV{PROGRAMFILES}/GLFW/lib
      ${GLFW_ROOT_DIR}/lib
      DOC "The GLFW library")

ELSE(WIN32)

   FIND_PATH(GLFW3_INCLUDE_DIR GLFW/glfw3.h
      /usr/include
      /usr/local/include
      /sw/include
      /opt/local/include
      ${GLFW_ROOT_DIR}/include
      DOC "The directory where GLFW/glfw3.h resides")

   # Prefer the static library.
   FIND_LIBRARY(GLFW3_LIBRARY
      NAMES libglfw3.a libGLFW.a GLFW libGLFW3.a GLFW3 libglfw3.so libglfw.so libglfw.so.3 libglfw.so.3.0
      PATHS
      /usr/lib64
      /usr/lib
      /usr/local/lib64
      /usr/local/lib
      /sw/lib
      /opt/local/lib
      ${GLFW_ROOT_DIR}/lib
      DOC "The GLFW library")

ENDIF(WIN32)

SET(${CMAKE_FIND_PACKAGE_NAME}_FOUND "NO")
IF(GLFW3_INCLUDE_DIR AND GLFW3_LIBRARY)
   SET(GLFW_LIBRARIES ${GLFW3_LIBRARY})
   SET(${CMAKE_FIND_PACKAGE_NAME}_FOUND "YES")
   
   #TARGET
  if(CMAKE_VERSION VERSION_EQUAL 3.0.0 OR CMAKE_VERSION VERSION_GREATER 3.0.0)
   if(NOT TARGET glfw3)
      add_library(glfw3 INTERFACE IMPORTED)
      set_target_properties(glfw3 PROPERTIES
         INTERFACE_INCLUDE_DIRECTORIES "${GLFW3_INCLUDE_DIR}"
         INTERFACE_LINK_LIBRARIES "${GLFW3_LIBRARY}"
      )
   endif()
  endif()
   
   MESSAGE(STATUS "Found GLFW: ${GLFW3_LIBRARY}")
ENDIF(GLFW3_INCLUDE_DIR AND GLFW3_LIBRARY)
