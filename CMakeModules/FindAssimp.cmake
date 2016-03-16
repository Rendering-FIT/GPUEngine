#
# Module for finding Assimp
#
# The module will define:
# Assimp_FOUND - True if Assimp development files were found
# ASSIMP_INCLUDE_DIR - Assimp include directories
# ASSIMP_LIBRARY_RELEASE - Assimp libraries to link in release configuration
# ASSIMP_LIBRARY_DEBUG - Assimp libraries to link in debug configuration
# ASSIMP_DLL_RELEASE - Assimp DLL library (Windows only)
# ASSIMP_DLL_DEBUG - Assimp DLL library (Windows only)
#
# Assimp target will be created for cmake 3.0.0 and newer
#


# try config-based find first
# (Assimp version 3.1.1 includes config file, but no import target it created)
find_package(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)


if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)

   # adjust variable names according to GPUEngine customs
   # and clean cache from non-sense stuff (config file is poorly written as of version 3.1.1)
   set(ASSIMP_INCLUDE_DIR ${ASSIMP_INCLUDE_DIRS})
   unset(ASSIMP_INCLUDE_DIRS)
   unset(ASSIMP_LIBRARIES)
   unset(ASSIMP_LIBRARY_SUFFIX CACHE)

else()

   # find Assimp includes
   find_path(ASSIMP_INCLUDE_DIR assimp/mesh.h
      /usr/include
      /usr/local/include
      /opt/local/include
   )

endif()


# find Assimp libraries
find_library(ASSIMP_LIBRARY_RELEASE assimp
   PATHS ${ASSIMP_ROOT_DIR}
   PATH_SUFFIXES lib
   DOC "Assimp release library"
   NO_DEFAULT_PATH
)
find_library(ASSIMP_LIBRARY_DEBUG assimpd NAMES assimp
   PATHS ${ASSIMP_ROOT_DIR}
   PATH_SUFFIXES lib
   DOC "Assimp debug library (optional)"
   NO_DEFAULT_PATH
)

if(WIN32)

   # find Assimp DLLs
   find_file(ASSIMP_DLL_RELEASE assimp.dll
      PATHS ${ASSIMP_ROOT_DIR}
      PATH_SUFFIXES bin
      DOC "Assimp release DLL"
      NO_DEFAULT_PATH
   )
   find_file(ASSIMP_DLL_DEBUG assimpd.dll NAMES assimp.dll
      PATHS ${ASSIMP_ROOT_DIR}
      PATH_SUFFIXES bin
      DOC "Assimp debug DLL (optional)"
      NO_DEFAULT_PATH
   )

endif()

# create target
if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
   if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
      add_library(${CMAKE_FIND_PACKAGE_NAME} SHARED IMPORTED)
      if(WIN32)
         set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${ASSIMP_INCLUDE_DIR}"
            IMPORTED_LOCATION_DEBUG "${ASSIMP_DLL_DEBUG}"
            IMPORTED_LOCATION_RELEASE "${ASSIMP_DLL_RELEASE}"
            IMPORTED_IMPLIB_DEBUG "${ASSIMP_LIBRARY_DEBUG}"
            IMPORTED_IMPLIB_RELEASE "${ASSIMP_LIBRARY_RELEASE}"
         )
      else()
         set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${ASSIMP_INCLUDE_DIR}"
            IMPORTED_LOCATION_DEBUG "${ASSIMP_LIBRARY_DEBUG}"
            IMPORTED_LOCATION_RELEASE "${ASSIMP_LIBRARY_RELEASE}"
         )
      endif()
   endif()
endif()

# set *_FOUND flag
if(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY_RELEASE)
   set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)
endif()

# message
include(GEMacros)
if(ASSIMP_LIBRARY_RELEASE)
   ge_report_find_status("${ASSIMP_LIBRARY_RELEASE}")
else()
   ge_report_find_status("")
endif()
