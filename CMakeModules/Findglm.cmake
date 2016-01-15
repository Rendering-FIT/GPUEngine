#
# Module for finding GLM
#
# The module will define:
# glm_FOUND - True if GLM development files were found
# GLM_INCLUDE_DIR - GLM include directories
# GLM_LIBRARY - GLM libraries to link
#
# glm target will be created for cmake 3.0.0 and newer
#


# try config-based find first
# (this provides target glm (tested on GLM version 0.9.7.0))
find_package(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)

# use regular old-style approach
if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FOUND)

   find_path(GLM_INCLUDE_DIR glm/glm.hpp
      /usr/include
      /usr/local/include
      /opt/local/include
   )

   # set *_FOUND flag
   if(GLM_INCLUDE_DIR)
      set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)
   endif()
   # target for cmake 3.0.0 and newer
   if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
      if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
         if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
            add_library(${CMAKE_FIND_PACKAGE_NAME} INTERFACE IMPORTED)
            set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
               INTERFACE_INCLUDE_DIRECTORIES "${GLM_INCLUDE_DIR}"
            )
         endif()
      endif()
   endif()

endif()

# message
include(GEMacros)
ge_report_find_status("${GLM_INCLUDE_DIR}")
