#
# Module for finding FreeImagePlus
#
# The module will define:
# FreeImagePlus_FOUND - True if FreeImagePlus development files were found
# FREEIMAGEPLUS_INCLUDE_DIR - FreeImagePlus include directories
# FREEIMAGEPLUS_LIBRARY - FreeImagePlus libraries to link
#
# FreeImagePlus target will be created for cmake 3.0.0 and newer
#


# try config-based find first
find_package(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)

# use regular old-style approach
if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FOUND)

   if(WIN32)

      find_path(FREEIMAGEPLUS_INCLUDE_DIR FreeImagePlus.h
         ${FREEIMAGEPLUS_ROOT_DIR}/include
         ${FREEIMAGEPLUS_ROOT_DIR}
         DOC "The directory where FreeImagePlus.h resides")

      find_library(FREEIMAGEPLUS_LIBRARY
         NAMES FreeImagePlus freeimageplus
         PATHS
         ${FREEIMAGEPLUS_ROOT_DIR}/lib
         ${FREEIMAGEPLUS_ROOT_DIR}
         DOC "The FreeImagePlus library")

   else()

      find_path(FREEIMAGEPLUS_INCLUDE_DIR FreeImagePlus.h
         /usr/include
         /usr/local/include
         /sw/include
         /opt/local/include
         DOC "The directory where FreeImagePlus.h resides")

      find_library(FREEIMAGEPLUS_LIBRARY
         NAMES FreeImagePlus freeimageplus
         PATHS
         /usr/lib64
         /usr/lib
         /usr/local/lib64
         /usr/local/lib
         /sw/lib
         /opt/local/lib
         DOC "The FreeImagePlus library")

   endif()

   # set *_FOUND flag
   if(FREEIMAGEPLUS_INCLUDE_DIR AND FREEIMAGEPLUS_LIBRARY)
      set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)
   endif()

   # target for cmake 3.0.0 and newer
   if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
      if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
         if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
            add_library(${CMAKE_FIND_PACKAGE_NAME} INTERFACE IMPORTED)
            set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
               INTERFACE_INCLUDE_DIRECTORIES "${FREEIMAGEPLUS_INCLUDE_DIR}"
               INTERFACE_LINK_LIBRARIES "${FREEIMAGEPLUS_LIBRARY}"
            )
         endif()
      endif()
   endif()

endif()

# message
include(GEMacros)
ge_report_find_status("${FREEIMAGEPLUS_LIBRARY}")
