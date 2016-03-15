#
# Module for finding Assimp
#
# The module will define:
# Assimp_FOUND - True if Assimp development files were found
# ASSIMP_INCLUDE_DIR - Assimp include directories
# ASSIMP_LIBRARY - Assimp libraries to link
#
# Assimp target will be created for cmake 3.0.0 and newer
#


# try config-based find first
# (version 3.1.1 includes config file, but no import target it created)
find_package(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)
if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)

   # adjust variable names according to GPUEngine customs
   #if(WIN32)
   #   set(ASSIMP_LIBRARY optimized ${ASSIMP_LIBRARY_DIRS}/assimp.lib
   #                      debug ${ASSIMP_LIBRARY_DIRS}/assimpd.lib)
   #else()
   #   set(ASSIMP_LIBRARY ${ASSIMP_LIBRARIES})
   #endif()
   #unset(ASSIMP_LIBRARIES)
   #set(ASSIMP_INCLUDE_DIR ${ASSIMP_INCLUDE_DIRS})
   #unset(ASSIMP_INCLUDE_DIRS)
   
   find_library(ASSIMP_LIBRARY_RELEASE assimp
      PATHS ${ASSIMP_ROOT_DIR}
	  PATH_SUFFIXES lib
	  DOC "pokus assimp"
	  NO_DEFAULT_PATH
   )
   
   find_library(ASSIMP_LIBRARY_DEBUG assimpd NAMES assimp
      PATHS ${ASSIMP_ROOT_DIR}
	  PATH_SUFFIXES lib
	  DOC "pokus assimp debug"
	  NO_DEFAULT_PATH
   )
   
   find_file(ASSIMP_DLL_RELEASE assimp.dll
      PATHS ${ASSIMP_ROOT_DIR}
	  PATH_SUFFIXES bin
	  DOC "pokus assimp dll"
	  NO_DEFAULT_PATH
   )
   
   find_file(ASSIMP_DLL_DEBUG assimpd.dll NAMES assimp.dll
      PATHS ${ASSIMP_ROOT_DIR}
	  PATH_SUFFIXES bin
	  DOC "pokus assimp dll debug"
	  NO_DEFAULT_PATH
   )

   # create target
   if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
      if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
         add_library(${CMAKE_FIND_PACKAGE_NAME} SHARED IMPORTED)
         #set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
         #   INTERFACE_INCLUDE_DIRECTORIES "${ASSIMP_INCLUDE_DIR}"
         #   INTERFACE_LINK_LIBRARIES "${ASSIMP_LIBRARY}"
         #)
         set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${ASSIMP_INCLUDE_DIRS}"
            IMPORTED_LOCATION_DEBUG "${ASSIMP_DLL_DEBUG}"
            IMPORTED_LOCATION_RELEASE "${ASSIMP_DLL_RELEASE}"
            IMPORTED_IMPLIB_DEBUG "${ASSIMP_LIBRARY_DEBUG}"
            IMPORTED_IMPLIB_RELEASE "${ASSIMP_LIBRARY_RELEASE}"
         )
      endif()
   endif()

endif()

# use regular old-style approach
if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FOUND)

   find_path(ASSIMP_INCLUDE_DIR assimp/mesh.h
      /usr/include
      /usr/local/include
      /opt/local/include
   )

   find_library(ASSIMP_LIBRARY assimp
      /usr/lib64
      /usr/lib
      /usr/local/lib
      /opt/local/lib
   )

   # set *_FOUND flag
   if(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY)
      set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)
   endif()

   # target for cmake 3.0.0 and newer
   if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
      if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
         if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
            add_library(${CMAKE_FIND_PACKAGE_NAME} INTERFACE IMPORTED)
            set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
               INTERFACE_INCLUDE_DIRECTORIES "${ASSIMP_INCLUDE_DIR}"
               IMPORTED_LOCATION_DEBUG "${ASSIMP_LIBRARY_DIRS}/assimpd.lib"
               IMPORTED_LOCATION_RELEASE "${ASSIMP_LIBRARY_DIRS}/assimp.lib"
               IMPORTED_IMPLIB_DEBUG "${ASSIMP_LIBRARY_DIRS}/assimpd.lib"
               IMPORTED_IMPLIB_RELEASE "${ASSIMP_LIBRARY_DIRS}/assimp.lib"
         )
         endif()
      endif()
   endif()

endif()

# message
include(GEMacros)
ge_report_find_status("${ASSIMP_LIBRARY}")
