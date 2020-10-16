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

if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
    if(TARGET glm::glm)
        add_library(glm ALIAS glm::glm)
        set(TARGET_NAME glm::glm)
    endif()
endif()

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
            set(TARGET_NAME glm)
            add_library(${CMAKE_FIND_PACKAGE_NAME} INTERFACE IMPORTED)
            set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
               INTERFACE_INCLUDE_DIRECTORIES "${GLM_INCLUDE_DIR}"
            )
         endif()
      endif()
   endif()

endif()

if(TARGET ${TARGET_NAME})
   set_property(TARGET ${TARGET_NAME} APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS "GLM_ENABLE_EXPERIMENTAL")
endif()

# message
include(GEMacros OPTIONAL RESULT_VARIABLE ge_macros_file)
if(ge_macros_file)
   ge_report_find_status()
endif()
