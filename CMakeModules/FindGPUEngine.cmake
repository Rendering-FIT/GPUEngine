#
#
#

message("FindGPUE - ${CMAKE_FIND_PACKAGE_NAME}  - ${GPUEngine_FIND_COMPONENTS}")
message("${${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS}")
foreach(module ${${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS})
   find_package(${module} ${FIND_QUIETLY} MODULE)
endforeach()