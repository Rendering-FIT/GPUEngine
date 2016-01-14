#
# Module for finding GLEW
#
# The module will define:
# GLEW_FOUND - True if GLEW development files were found
# GLEW_INCLUDE_DIR - GLEW include directories
# GLEW_LIBRARY - GLEW libraries to link
#
# GLEW target will be created for cmake 3.0.0 and newer
#


# try config-based find first
find_package(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)

# use regular old-style approach
if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FOUND)

   if(WIN32)

      find_path(GLEW_INCLUDE_DIR GL/glew.h
         $ENV{PROGRAMFILES}/GLEW/include
         ${PROJECT_SOURCE_DIR}/src/nvgl/glew/include
         DOC "The directory where GL/glew.h resides")

      find_library(GLEW_LIBRARY
         NAMES glew GLEW glew32 glew32s
         PATHS
         $ENV{PROGRAMFILES}/GLEW/lib
         ${PROJECT_SOURCE_DIR}/src/nvgl/glew/bin
         ${PROJECT_SOURCE_DIR}/src/nvgl/glew/lib
         DOC "The GLEW library")

   else()

      find_path(GLEW_INCLUDE_DIR GL/glew.h
         /usr/include
         /usr/local/include
         /sw/include
         /opt/local/include
         DOC "The directory where GL/glew.h resides")

      find_library(GLEW_LIBRARY
         NAMES GLEW glew
         PATHS
         /usr/lib64
         /usr/lib
         /usr/local/lib64
         /usr/local/lib
         /sw/lib
         /opt/local/lib
         DOC "The GLEW library")

   endif()

   # set *_FOUND flag
   if(GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
      set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)
   endif()

   # static vs. dynamic GLEW linkage
   set(GLEW_STATIC OFF CACHE BOOL "Link GLEW as static library (single lib) or shared library (lib+dll).")

   # set GLEW_STATIC preprocessor macro
   if(GLEW_STATIC)
      add_definitions(-DGLEW_STATIC)
   endif()

   # target for cmake 3.0.0 and newer
   if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
      if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
         if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
            add_library(${CMAKE_FIND_PACKAGE_NAME} INTERFACE IMPORTED)
            set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
               INTERFACE_INCLUDE_DIRECTORIES "${GLEW_INCLUDE_DIR}"
               INTERFACE_LINK_LIBRARIES "${GLEW_LIBRARY}"
            )
         endif()
      endif()
   endif()

endif()

# message
include(GEMacros)
ge_report_find_status("${GLEW_LIBRARY}")
