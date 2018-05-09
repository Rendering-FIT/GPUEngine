#
# Internal Find geCore module
#

if(TARGET ${CMAKE_FIND_PACKAGE_NAME})
   set(${${CMAKE_FIND_PACKAGE_NAME}_FOUND} true)
else()
   message("Cannot find ${CMAKE_FIND_PACKAGE_NAME} package")
endif()
