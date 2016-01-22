#
# Module for finding GLFW3
#
# The module will define:
# glfw3_FOUND - True if GLFW3 development files were found
# GLFW3_INCLUDE_DIR - GLFW3 include directories
# GLFW3_LIBRARY - GLFW3 libraries to link
#
# glfw3 target will be created for cmake 3.0.0 and newer
#


# try config-based find first
# (GLFW version 3.1.2: although config is found, target is not created => we will create it ourselves)
# (even worse: GLFW does not all dependant libraries in GLFW_LIBRARY => should we append it ourselves?)
find_package(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)
if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
   if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
      if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
         add_library(${CMAKE_FIND_PACKAGE_NAME} INTERFACE IMPORTED)
         set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${GLFW3_INCLUDE_DIR}"
            INTERFACE_LINK_LIBRARIES "${GLFW3_LIBRARY}"
         )
      endif()
   endif()
endif()

# use regular old-style approach
if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FOUND)

   if(WIN32)

      find_path(GLFW3_INCLUDE_DIR GLFW/glfw3.h
         $ENV{PROGRAMFILES}/GLFW/include
         ${GLFW_ROOT_DIR}/include
         DOC "The directory where GLFW/glfw3.h resides")

      find_library(GLFW3_LIBRARY
         NAMES glfw3 GLFW
         PATHS
         $ENV{PROGRAMFILES}/GLFW/lib
         ${GLFW_ROOT_DIR}/lib
         DOC "The GLFW library")

   else()

      find_path(GLFW3_INCLUDE_DIR GLFW/glfw3.h
         /usr/include
         /usr/local/include
         /sw/include
         /opt/local/include
         ${GLFW_ROOT_DIR}/include
         DOC "The directory where GLFW/glfw3.h resides")

      # Prefer the static library.
      find_library(GLFW3_LIBRARY
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

   endif()

   # set *_FOUND flag
   if(GLFW3_INCLUDE_DIR AND GLFW3_LIBRARY)
      set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)
   endif()

   # target for cmake 3.0.0 and newer
   if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
      if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
         if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
            add_library(${CMAKE_FIND_PACKAGE_NAME} INTERFACE IMPORTED)
            set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
               INTERFACE_INCLUDE_DIRECTORIES "${GLFW3_INCLUDE_DIR}"
               INTERFACE_LINK_LIBRARIES "${GLFW3_LIBRARY}"
            )
         endif()
      endif()
   endif()

endif()

# message
include(GEMacros)
ge_report_find_status("${GLFW3_LIBRARY}")
