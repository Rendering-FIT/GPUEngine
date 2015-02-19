cmake_minimum_required(VERSION 2.8.0)

PROJECT(GPUEngine)

SET(GPUENGINE_MAJOR_VERSION 0)
SET(GPUENGINE_MINOR_VERSION 0)
SET(GPUENGINE_PATCH_VERSION 0)
SET(GPUENGINE_REVISION_VERSION 0)
SET(GPUENGINE_VERSION ${GPUENGINE_MAJOR_VERSION}.${GPUENGINE_MINOR_VERSION}.${GPUENGINE_PATCH_VERSION}.${GPUENGINE_REVISION_VERSION})

SET(GPUENGINE_MINIMAL_COMPATIBLE_VERSION "0.0.0.0")

SET(OUTPUT_LIBDIR ${PROJECT_BINARY_DIR}/lib)
SET(OUTPUT_BINDIR ${PROJECT_BINARY_DIR}/bin)

FIND_PATH(GLM_INCLUDE_DIR glm/glm.hpp)

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
       SET("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_BINDIR}")
   ELSE()
       SET("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_LIBDIR}")
   ENDIF()
ENDFOREACH()

IF(MSVC)
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
ENDIF()

IF(CMAKE_COMPILER_IS_GNUCXX)
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
ENDIF()

SET(CMAKE_MODULE_PATH "${GPUEngine_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
# Dynamic vs Static Linking
OPTION(DYNAMIC_GPUENGINE "Set to ON to build GPUEngine for dynamic linking.  Use OFF for static." ON)
IF   (DYNAMIC_GPUENGINE)
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
    ADD_DEFINITIONS(-DGE_LIBRARY)
ELSE ()
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
    ADD_DEFINITIONS(-DGE_LIBRARY_STATIC)
ENDIF()

FIND_PACKAGE(OPENGL      REQUIRED)
FIND_PACKAGE(GLEW        REQUIRED)
FIND_PACKAGE(X11)
FIND_PACKAGE(SDL2)
FIND_PACKAGE(AntTweakBar)

INCLUDE_DIRECTORIES(
    ${GPUEngine_SOURCE_DIR}/include
  )


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
              "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/GEMacros.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/GPUEngineConfigVersion.cmake"
        DESTINATION ${INSTALL_CM_DIR}
        )
        
        

add_subdirectory(src)
add_subdirectory(apps)