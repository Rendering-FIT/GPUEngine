#
# Module for finding FreeImage
#
# The module will define:
# FreeImage_FOUND - True if FreeImage development files were found
# FREEIMAGE_INCLUDE_DIR - FreeImage include directories
# FREEIMAGE_LIBRARY - FreeImage libraries to link
#
# FreeImage target will be created for cmake 3.0.0 and newer
#


# try config-based find first
find_package(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)

# use regular old-style approach
if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FOUND)

   if(WIN32)

      find_path(FREEIMAGE_INCLUDE_DIR FreeImage.h
         ${FREEIMAGE_ROOT_DIR}/include
         ${FREEIMAGE_ROOT_DIR}
         DOC "The directory where FreeImage.h resides")

      find_library(FREEIMAGE_LIBRARY
         NAMES FreeImage freeimage
         PATHS
         ${FREEIMAGE_ROOT_DIR}/lib
         ${FREEIMAGE_ROOT_DIR}
         DOC "The FreeImage library")

   else()

      find_path(FREEIMAGE_INCLUDE_DIR FreeImage.h
         /usr/include
         /usr/local/include
         /sw/include
         /opt/local/include
         DOC "The directory where FreeImage.h resides")

      find_library(FREEIMAGE_LIBRARY
         NAMES FreeImage freeimage
         PATHS
         /usr/lib64
         /usr/lib
         /usr/local/lib64
         /usr/local/lib
         /sw/lib
         /opt/local/lib
         DOC "The FreeImage library")

   endif()

   # set *_FOUND flag
   if(FREEIMAGE_INCLUDE_DIR AND FREEIMAGE_LIBRARY)
      set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)
   endif()

   # target for cmake 3.0.0 and newer
   if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
      if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
         if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
            add_library(${CMAKE_FIND_PACKAGE_NAME} INTERFACE IMPORTED)
            set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
               INTERFACE_INCLUDE_DIRECTORIES "${FREEIMAGE_INCLUDE_DIR}"
               INTERFACE_LINK_LIBRARIES "${FREEIMAGE_LIBRARY}"
            )
         endif()
      endif()
   endif()

endif()

# message
include(GEMacros)
ge_report_find_status("${FREEIMAGE_LIBRARY}")
