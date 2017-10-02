
set(MODULE_NAME "SDLWindow")
set(MODULE_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

#If target was already defined then return. Perhaps it was included from another package.
IF(TARGET ${MODULE_NAME})
   return()
ENDIF()

IF(NOT TARGET geCore)
  find_package(GPUEngine COMPONENTS geCore)
ENDIF()


find_package(SDL2 QUIET)

if(NOT SDL2_FOUND)
   return()
endif()

add_library(${MODULE_NAME} INTERFACE )

get_filename_component(_geCore_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
include(${_geCore_install_prefix}/cmake/CMakeModules/GEMacros.cmake)

if(WIN32)
  _ge_check_and_import(${target} IMPORTED_LOCATION_RELEASE "${${install_prefix}}/bin/${MODULE_NAME}.dll" ${ARGV3} ${ARGV4})
  _ge_check_and_import(${target} IMPORTED_LOCATION_DEBUG "${${install_prefix}}/bin/${MODULE_NAME}d.dll" FALSE ${ARGV4})
  _ge_check_and_import(${target} IMPORTED_IMPLIB_RELEASE "${${install_prefix}}/lib/${MODULE_NAME}.lib" ${ARGV3} ${ARGV4})
  _ge_check_and_import(${target} IMPORTED_IMPLIB_DEBUG "${${install_prefix}}/lib/${MODULE_NAME}d.lib" FALSE ${ARGV4})
else()
  set(_postfix "")
  if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(_postfix "d")
  endif()
  _ge_check_and_import(${target} IMPORTED_LOCATION_RELEASE "${${install_prefix}}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}${MODULE_NAME}${_postfix}.so" ${ARGV3} ${ARGV4})
endif()

#target_sources(${MODULE_NAME} INTERFACE ${${MODULE_NAME}_SOURCE_FILES})
target_include_directories(${MODULE_NAME} INTERFACE "${MODULE_DIR}../include/")
#set_property(TARGET geGL APPEND PROPERTY INTERFACE_LINK_LIBRARIES "${${_dep}_LIBRARY}")
target_link_libraries(${MODULE_NAME} INTERFACE geCore SDL2)

target_link_libraries(${MODULE_NAME} INTERFACE optimized ${ASSIMP_LIBRARY_DIRS}/assimp.lib
  debug ${ASSIMP_LIBRARY_DIRS}/assimpd.lib
  )
