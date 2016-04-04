cmake_minimum_required(VERSION 3.0.0)

PROJECT(GPUEngine)

SET(GPUENGINE_MAJOR_VERSION 0)
SET(GPUENGINE_MINOR_VERSION 0)
SET(GPUENGINE_PATCH_VERSION 0)
SET(GPUENGINE_REVISION_VERSION 0)
SET(GPUENGINE_VERSION ${GPUENGINE_MAJOR_VERSION}.${GPUENGINE_MINOR_VERSION}.${GPUENGINE_PATCH_VERSION}.${GPUENGINE_REVISION_VERSION})

SET(GPUENGINE_MINIMAL_COMPATIBLE_VERSION "0.0.0.0")

SET(OUTPUT_LIBDIR ${PROJECT_BINARY_DIR}/lib)
SET(OUTPUT_BINDIR ${PROJECT_BINARY_DIR}/bin)

SET(GPUENGINE_BUILD_geAd OFF CACHE BOOL "Add geAd subdirectory. This is for addons.")
SET(GPUENGINE_BUILD_APPS OFF CACHE BOOL "Add apps subdirectory. This is for building applications.")
SET(GPUENGINE_BUILD_TESTS OFF CACHE BOOL "Add tests subdirectory. This is for building unit tests.")


SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

##################################################
#Set the output to one set of directories lib/ bin/
##################################################
FOREACH(CONF ${CMAKE_CONFIGURATION_TYPES})        # For each configuration (Debug, Release, MinSizeRel... and/or anything the user chooses)
   STRING(TOUPPER "${CONF}" CONF)                # Go uppercase (DEBUG, RELEASE...)
   SET("CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_LIBDIR}")
   SET("CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_BINDIR}")
   IF(WIN32)
       SET("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_LIBDIR}")
   ELSE()
       SET("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_LIBDIR}")
   ENDIF()
ENDFOREACH()

IF(MSVC)
   # 4800 - forcing value to bool
   # 4503 - 'identifier' : decorated name length exceeded, name was truncated, due to a template hell
   # 4996 - This function or variable may be unsafe. Due to using pointer instead of iterators (MatrixTransformBase)
   set(ignored_wrn "/wd4800 /wd4503 /wd4996")
   # enable multithreaded compilation
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP ${ignored_wrn}")

   # disable MSVC warning "LNK4221: This object file does not define any previously undefined public symbols,
   # so it will not be used by any link operation that consumes this library"
   SET(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} /ignore:4221")

   #OPTION(GLEW_STATIC "Link GLEW as static library (single lib) or shared library (lib+dll)." OFF)
   #IF(GLEW_STATIC)
   #   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DGLEW_STATIC")
   #ENDIF()

   # avoid "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_HAS_EXCEPTIONS=0")

   # workarounds for limited C++11 support of MSVC
   IF(MSVC_VERSION LESS 1800)
      MESSAGE(FATAL_ERROR "Microsoft Visual C++ 2012 and earlier are not supported "
              "as their support of C++11 is too limited.")
   ELSEIF(MSVC_VERSION LESS 1900)
      # MSVC 2013 Update 4:
      # - no constexpr support
      # - no local_thread storage
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Dconstexpr= /Dthread_local= /D_ALLOW_KEYWORD_MACROS")
   ELSE()
      # MSVC 2015 workarounds to be placed here (currently none)
   ENDIF()
ENDIF()

IF(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -W -Wall -pedantic")
ENDIF()

SET(CMAKE_MODULE_PATH "${GPUEngine_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
# Dynamic vs Static Linking
OPTION(GPUENGINE_DYNAMIC "Set to ON to build GPUEngine for dynamic linking.  Use OFF for static." ON)


##################################################
# Export Things
##################################################

SET(INSTALL_CM_DIR cmake)

configure_file(version.h.in "include/version.h" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/version.h"
        DESTINATION include
        )

configure_file(
   GPUEngineConfig.cmake.in
   GPUEngineConfig.cmake
   @ONLY
)

configure_file(
   GPUEngineConfigVersion.cmake.in
   GPUEngineConfigVersion.cmake
   @ONLY
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/GPUEngineConfig.cmake"
 #             "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/GEMacros.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/GPUEngineConfigVersion.cmake"
        DESTINATION ${INSTALL_CM_DIR}
        )

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/"
        DESTINATION "${INSTALL_CM_DIR}/CMakeModules"
       )


add_subdirectory(src)

if(GPUENGINE_BUILD_geAd)
  add_subdirectory(geAd)
endif()


if(GPUENGINE_BUILD_APPS)
   if(NOT GPUENGINE_BUILD_geAd)
      message(SEND_ERROR "GPUENGINE_BUILD_APPS requires GPUENGINE_BUILD_geAd set to ON.")
   endif() 
   add_subdirectory(apps)
endif()

if(GPUENGINE_BUILD_TESTS)
  add_subdirectory(tests)
endif()
