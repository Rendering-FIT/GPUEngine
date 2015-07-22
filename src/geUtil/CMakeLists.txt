IF   (DYNAMIC_GPUENGINE)
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
    ADD_DEFINITIONS(-DGEUTIL_LIBRARY)
ELSE ()
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
    ADD_DEFINITIONS(-DGE_LIBRARY_STATIC)
ENDIF()

set(LIB_NAME geUtil)

project(${LIB_NAME})

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})
set(GL_INCLUDES
  ${HEADER_PATH}/Export.h
  ${HEADER_PATH}/algorithms.h
  ${HEADER_PATH}/ArgumentObject.h
  ${HEADER_PATH}/CameraObject.h
  ${HEADER_PATH}/CameraPath.h
  ${HEADER_PATH}/HighResolutionTimer.h
  ${HEADER_PATH}/FPSPrinter.h
  ${HEADER_PATH}/macros.h
  ${HEADER_PATH}/Progress.h
  ${HEADER_PATH}/geUtil.h
  )

set(GL_SOURCES
  ArgumentObject.cpp  
  CameraObject.cpp
  CameraPath.cpp
  HighResolutionTimer.cpp
  FPSPrinter.cpp
  Progress.cpp
  )

if(ANTTWEAKBAR_FOUND AND SDL2_FOUND)
   set(GL_INCLUDES ${GL_INCLUDES} ${HEADER_PATH}/WindowObject.h)
   set(GL_SOURCES ${GL_SOURCES} WindowObject.cpp)
endif()

ADD_LIBRARY(${LIB_NAME}
    ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
    ${GL_INCLUDES}
    ${GL_SOURCES}
)

find_package(GLEW   REQUIRED)
find_package(OPENGL REQUIRED)

set(Internal_deps geGL)
set(Internal_inc ${GLM_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})

IF(ANTTWEAKBAR_FOUND)
   list(APPEND Internal_inc ${ANTTWEAKBAR_INCLUDE_DIR})
   target_link_libraries(${LIB_NAME} ${ANTTWEAKBAR_LIBRARY})
ENDIF()

IF(SDL2_FOUND)
   list(APPEND Internal_inc ${SDL2_INCLUDE_DIR})
   target_link_libraries(${LIB_NAME} ${SDL2_LIBRARY})
ENDIF()

set(includes_to_export ${GPUEngine_SOURCE_DIR}/include)
#include_directories(${includes_to_export})
target_link_libraries(${LIB_NAME} ${GLEW_LIBRARY} ${OPENGL_LIBRARY} ${Internal_deps})
set_target_properties(${LIB_NAME} PROPERTIES
	INCLUDE_DIRECTORIES "${Internal_inc}"
	INTERFACE_INCLUDE_DIRECTORIES "${includes_to_export}"
)


install(FILES
    ${GL_INCLUDES}
    DESTINATION include/${LIB_NAME}
  )

install(TARGETS ${LIB_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
  )


#########################################
#Export

configure_file(
   geUtilConfig.cmake.in
   geUtilConfig.cmake
   @ONLY
)

# INSTALL_CM_DIR is defined in master CMakeLists file

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/geUtilConfig.cmake"
        DESTINATION "${INSTALL_CM_DIR}/geUtil"
        )
