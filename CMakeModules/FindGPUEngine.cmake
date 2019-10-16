#
# General GPUEngine find module used by internal cross package dependencies (eg. for geRG to find geGL which is standalone module)
#

foreach(module ${${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS})
   find_package(${module} ${FIND_QUIETLY} MODULE)
endforeach()