macro(_ge_check_file_exists file target)
   if(NOT EXISTS "${file}")
      message(FATAL_ERROR "The imported target ${target} references file ${file} which doesn't seem to exist. Reported by ${CMAKE_CURRENT_LIST_FILE}")
   endif()
endmacro()

macro(_ge_check_file_exists_weak file target)
   if(NOT EXISTS "${file}")
      message("The imported target ${target} references file ${file} which doesn't seem to exist. Reported by ${CMAKE_CURRENT_LIST_FILE}")
   endif()
endmacro()

macro(_ge_check_and_import target prop path)
   if(EXISTS "${path}")
      set_target_properties( ${target} PROPERTIES ${prop} ${path})
   else()
      message("The imported target ${target} references file ${file} which doesn't seem to exist. Reported by ${CMAKE_CURRENT_LIST_FILE}")
   endif()
endmacro()

macro(_ge_populate_imported_target target install_prefix name)
   set_property(TARGET ${target} APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
   set_property(TARGET ${target} APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
   #_ge_check_file_exists_weak("${_geGL_install_prefix}/bin/${name}.dll" ${target})
   #_ge_check_file_exists_weak("${_geGL_install_prefix}/bin/${name}d.dll" ${target})
   #_ge_check_file_exists_weak("${_geGL_install_prefix}/lib/${name}.lib" ${target})
   #_ge_check_file_exists_weak("${_geGL_install_prefix}/lib/${name}d.lib" ${target})
   #set_target_properties( ${target} PROPERTIES
   #   INTERFACE_INCLUDE_DIRECTORIES "${_geGL_install_prefix}/include"
   #   IMPORTED_LOCATION_RELEASE "${_geGL_install_prefix}/bin/${name}.dll"
   #   IMPORTED_LOCATION_DEBUG "${_geGL_install_prefix}/bin/${name}d.dll"
   #   IMPORTED_IMPLIB_RELEASE "${_geGL_install_prefix}/lib/${name}.lib"
   #   IMPORTED_IMPLIB_DEBUG "${_geGL_install_prefix}/lib/${name}d.lib"
   #)
   _ge_check_and_import(${target} INTERFACE_INCLUDE_DIRECTORIES "${_geGL_install_prefix}/include")
   _ge_check_and_import(${target} IMPORTED_LOCATION_RELEASE "${_geGL_install_prefix}/bin/${name}.dll")
   _ge_check_and_import(${target} IMPORTED_LOCATION_DEBUG "${_geGL_install_prefix}/bin/${name}d.dll")
   _ge_check_and_import(${target} IMPORTED_IMPLIB_RELEASE "${_geGL_install_prefix}/lib/${name}.lib")
   _ge_check_and_import(${target} IMPORTED_IMPLIB_DEBUG "${_geGL_install_prefix}/lib/${name}d.lib")
endmacro()

macro(ge_use_modules target)
   set(_modules ${ARGN})
   foreach(_module ${_modules})
      message("${_module}")
   endforeach()
endmacro()