# GPUEngine Qt5 find wrapper

find_package(${CMAKE_FIND_PACKAGE_NAME} COMPONENTS ${${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS} CONFIG QUIET)

if(${${CMAKE_FIND_PACKAGE_NAME}_FOUND} AND NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
   add_library(${CMAKE_FIND_PACKAGE_NAME} INTERFACE)
   foreach(_mod ${${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS})
      list(APPEND qt5Targets "Qt5::${_mod}")
   endforeach()
   target_link_libraries(${CMAKE_FIND_PACKAGE_NAME} INTERFACE ${qt5Targets})
endif()

# message
include(GEMacros OPTIONAL RESULT_VARIABLE ge_macros_file)
if(ge_macros_file)
   ge_report_find_status()
endif()