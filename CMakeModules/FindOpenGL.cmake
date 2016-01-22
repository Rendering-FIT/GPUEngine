#
# Module for finding OpenGL
#
# The module will define:
# OpenGL_FOUND - True if OpenGL development files were found
# OPENGL_INCLUDE_DIR - OpenGL include directories
# OPENGL_LIBRARY - OpenGL libraries to link
#
# OpenGL target will be created for cmake 3.0.0 and newer
#


# try config-based find first
find_package(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)

# use regular old-style approach
if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FOUND)

   if(WIN32)

      if(CYGWIN)

         find_path(OPENGL_INCLUDE_DIR GL/gl.h
            /usr/include
            /usr/X11R6/include
         )

         find_library(OPENGL_LIBRARY opengl32
            /usr/lib64
            /usr/lib
            /usr/lib/w32api
         )

      else()

         set(OPENGL_INCLUDE_DIR "")  # OpenGL includes are with the system includes
         set(OPENGL_LIBRARY opengl32)

         # explicitly set *_FOUND flag to true
         # as following routines would fail on OPENGL_INCLUDE_DIR equal to ""
         set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)

      endif()

   elseif(APPLE)

      # On OSX, OpenGL is always there - this will need refining for those
      # using OpenGL with X11
      set(OPENGL_INCLUDE_DIR "")
      set(OPENGL_LIBRARY "-framework AGL -framework OpenGL")

      # explicitly set *_FOUND flag to true
      # as following routines would fail on OPENGL_INCLUDE_DIR equal to ""
      set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)

   else()

      # The first line below is to make sure that the proper headers
      # are used on a Linux machine with the NVidia drivers installed.
      # They replace Mesa with NVidia's own library but normally do not
      # install headers and that causes the linking to
      # fail since the compiler finds the Mesa headers but NVidia's library.
      # Make sure the NVIDIA directory comes BEFORE the others.
      #  - Atanas Georgiev <atanas@cs.columbia.edu>

      find_path(OPENGL_INCLUDE_DIR GL/gl.h
         /usr/share/doc/NVIDIA_GLX-1.0/include
         /usr/include
         /usr/local/include
         /usr/openwin/share/include
         /opt/graphics/OpenGL/include
         /usr/X11R6/include
      )

      find_library(OPENGL_LIBRARY
         NAMES MesaGL GL
         PATHS /usr/lib64
               /usr/lib
               /usr/local/lib
               /opt/graphics/OpenGL/lib
               /usr/openwin/lib
               /usr/X11R6/lib
      )

      # On Unix OpenGL most certainly always requires X11.
      # Feel free to tighten up these conditions ifyou don't
      # think this is always true.

      #if(OPENGL_LIBRARY)
      #  include(${MODULE_PATH}/FindX11.cmake)
      #  if(X11_FOUND)
      #    set(OPENGL_LIBRARY ${OPENGL_LIBRARY} ${X11_LIBRARIES})
      #  endif(X11_FOUND)
      #endif(OPENGL_LIBRARY)

   endif(WIN32)

   # set *_FOUND flag
   if(OPENGL_INCLUDE_DIR AND OPENGL_LIBRARY)
      set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)
   endif()

   # target for cmake 3.0.0 and newer
   if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
      if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
         if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
            add_library(${CMAKE_FIND_PACKAGE_NAME} INTERFACE IMPORTED)
            set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
               INTERFACE_INCLUDE_DIRECTORIES "${OPENGL_INCLUDE_DIR}"
               INTERFACE_LINK_LIBRARIES "${OPENGL_LIBRARY}"
            )
         endif()
      endif()
   endif()

endif()

# message
include(GEMacros)
ge_report_find_status("${OPENGL_LIBRARY}")
