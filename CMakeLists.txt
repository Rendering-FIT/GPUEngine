cmake_minimum_required(VERSION 3.1.0)

###########################
# Policies
###########################
cmake_policy(VERSION 3.11.1)


include(GNUInstallDirs)


PROJECT(GPUEngine
   VERSION 0.0.0.0
   DESCRIPTION "Toolkit for general rendering."
   LANGUAGES CXX
)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(GNUInstallDirs)

set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

SET(GPUENGINE_MINIMAL_COMPATIBLE_VERSION "0.0.0.0")

SET(OUTPUT_LIBDIR ${PROJECT_BINARY_DIR}/lib)
SET(OUTPUT_BINDIR ${PROJECT_BINARY_DIR}/bin)

SET(GPUENGINE_BUILD_geAd     OFF  CACHE BOOL "Build addons (geAd directory).")
SET(GPUENGINE_BUILD_APPS     OFF  CACHE BOOL "Build applications (apps directory).")
SET(GPUENGINE_BUILD_EXAMPLES OFF  CACHE BOOL "Build examples (examples directory).")
SET(GPUENGINE_BUILD_TESTS    OFF  CACHE BOOL "Build and run tests (tests directory).")
SET(GPUENGINE_BUILD_GEGL     ON   CACHE BOOL "Build geGL package.")
SET(GPUENGINE_BUILD_GESG     OFF  CACHE BOOL "Build geSG package.")
SET(GPUENGINE_BUILD_GERG     OFF  CACHE BOOL "Build geRG package.")
SET(GPUENGINE_BUILD_GEUTIL   ON   CACHE BOOL "Build geUtil package.")
SET(GPUENGINE_BUILD_GEPARSER OFF  CACHE BOOL "Build geParser package.")
SET(GPUENGINE_BUILD_GEDE     OFF  CACHE BOOL "Build geDE package.")

SET(GPUENGINE_BUILD_APP_geViewerAssimp OFF CACHE BOOL "Build geViewerAssimp application.")


SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
#SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
#SET(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

SET(GPUENGINE_DEPS_CONFIG_FILE "" CACHE STRING "Optional configuration file that configures the dependencies.")
IF(GPUENGINE_DEPS_CONFIG_FILE)
   INCLUDE(${GPUENGINE_DEPS_CONFIG_FILE})
ENDIF()

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
   # 4275 - on – DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier' - Due to Intersector class which is defined only in header file.
   set(ignored_wrn "/wd4800 /wd4503 /wd4996 /wd4275")

   # enable multithreaded compilation
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP ${ignored_wrn}")

   # disable MSVC warning "LNK4221: This object file does not define any previously undefined public symbols,
   # so it will not be used by any link operation that consumes this library"
   SET(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} /ignore:4221")

   # avoid "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_HAS_EXCEPTIONS=0")

   # avoid MSVC defines of min and max
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DNOMINMAX")

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
   IF(GPUENGINE_REPLACE_GLEW)
     SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DREPLACE_GLEW")
   ENDIF()
ENDIF()

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_C_STANDARD 99)

IF(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-W)
  add_compile_options(-Wall)
  add_compile_options(-Wconversion)
  add_compile_options(-pedantic)
ENDIF()

IF(CMAKE_COMPILER_IS_GNUCC)
  add_compile_options(-W)
  add_compile_options(-Wall)
  add_compile_options(-Wconversion)
  add_compile_options(-pedantic)
ENDIF()

SET(CMAKE_MODULE_PATH "${GPUEngine_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")

# Dynamic vs Static Linkage
OPTION(GPUENGINE_DYNAMIC_LINKAGE "Build GPUEngine as libs for dynamic linkage. Use OFF for static libs." ON)

IF(WIN32)
  SET(GPUENGINE_DEPS_CONFIG_FILE CACHE FILEPATH "Optional config file that will setup GPUEngine dependencies.")
  IF(GPUENGINE_DEPS_CONFIG_FILE)
    INCLUDE("${GPUENGINE_DEPS_CONFIG_FILE}")
  ENDIF()
ENDIF()


##################################################
# Export Things
##################################################

SET(INSTALL_CM_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

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



add_subdirectory(geCore)

if(GPUENGINE_BUILD_GEUTIL)
  add_subdirectory(geUtil)
endif()

if(GPUENGINE_BUILD_GEGL)
  add_subdirectory(geGL)
endif()

if(GPUENGINE_BUILD_GESG)
  add_subdirectory(geSG)
endif()

if(GPUENGINE_BUILD_GERG)
  add_subdirectory(geRG)
endif()

if(GPUENGINE_BUILD_geAd)
  add_subdirectory(geAd)
endif()

if(GPUENGINE_BUILD_APPS)
  if(NOT GPUENGINE_BUILD_geAd OR NOT GPUENGINE_BUILD_GEGL)
    message(SEND_ERROR "GPUENGINE_BUILD_APPS requires GPUENGINE_BUILD_geAd and GPUENGINE_BUILD_GEGL set to ON.")
  endif()
  add_subdirectory(apps)
endif()

if(GPUENGINE_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

if(GPUENGINE_BUILD_TESTS)
  add_subdirectory(tests)
endif()
