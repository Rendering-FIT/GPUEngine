set(LIB_NAME geUtil)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

IF   (GPUENGINE_DYNAMIC)
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
    ADD_DEFINITIONS(-D"${LIB_NAME_UPPER}"_LIBRARY)
ELSE ()
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
    ADD_DEFINITIONS(-DGE_LIBRARY_STATIC)
ENDIF()


set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})

set(ARGUMENTMANAGER_SOURCES
  ArgumentManager/ArgData.cpp
  ArgumentManager/BaseData.cpp
  ArgumentManager/ArrayData.cpp
  ArgumentManager/StructData.cpp
  ArgumentManager/ArgumentManager.cpp
  )

set(ARGUMENTMANAGER_INCLUDES
  ${HEADER_PATH}/ArgumentManager/ArgData.h
  ${HEADER_PATH}/ArgumentManager/BaseData.h
  ${HEADER_PATH}/ArgumentManager/ArrayData.h
  ${HEADER_PATH}/ArgumentManager/StructData.h
  ${HEADER_PATH}/ArgumentManager/ArgumentManager.h
  )

set(LIBRARYLOADER_SOURCES
  LibraryLoader/LibraryLoader.cpp
  LibraryLoader/LibraryObjectLoader.cpp
  LibraryLoader/RuntimeClassMetaData.cpp
  LibraryLoader/RuntimeClassInterface.cpp
  )

set(LIBRARYLOADER_INCLUDES
  ${HEADER_PATH}/LibraryLoader/LibraryLoader.h
  ${HEADER_PATH}/LibraryLoader/LibraryObjectLoader.h
  ${HEADER_PATH}/LibraryLoader/ClassMetaData.h
  ${HEADER_PATH}/LibraryLoader/RuntimeClassMetaData.h
  ${HEADER_PATH}/LibraryLoader/RuntimeClassInterface.h
  )

set(GL_INCLUDES
  ${HEADER_PATH}/Export.h
  ${HEADER_PATH}/algorithms.h
  ${HEADER_PATH}/ArgumentObject.h
  ${HEADER_PATH}/CameraObject.h
  ${HEADER_PATH}/CameraPath.h
  ${HEADER_PATH}/FPSPrinter.h
  ${HEADER_PATH}/HighResolutionTimer.h
  ${HEADER_PATH}/Intersectors.h
  ${HEADER_PATH}/macros.h
  ${HEADER_PATH}/Progress.h
  ${HEADER_PATH}/Ray.h
  ${HEADER_PATH}/geUtil.h
  ${HEADER_PATH}/Namespace.h
  ${HEADER_PATH}/NamespaceWithUsers.h
  ${HEADER_PATH}/User.h
  ${HEADER_PATH}/copyArgumentManager2Namespace.h
  )


set(GL_SOURCES
  ArgumentObject.cpp  
  CameraObject.cpp
  CameraPath.cpp
  FPSPrinter.cpp
  HighResolutionTimer.cpp
  Intersectors.cpp
  Progress.cpp
  Namespace.cpp
  NamespaceWithUsers.cpp
  copyArgumentManager2Namespace.cpp
  )

if(ANTTWEAKBAR_FOUND AND SDL2_FOUND)
   set(GL_INCLUDES ${GL_INCLUDES} ${HEADER_PATH}/WindowObject.h)
   set(GL_SOURCES ${GL_SOURCES} WindowObject.cpp)
endif()

ADD_LIBRARY(${LIB_NAME}
    ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
    ${GL_INCLUDES}
    ${ARGUMENTMANAGER_INCLUDES}
    ${LIBRARYLOADER_INCLUDES}
    ${GL_SOURCES}
    ${ARGUMENTMANAGER_SOURCES}
    ${LIBRARYLOADER_SOURCES}
)

find_package(GLEW   REQUIRED)
find_package(OPENGL REQUIRED)
  
################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_deps - other than 'ge' packages goes here (e.g. glew), it configures this package intra project dependencies and also configures the config file
# External_export_libs - probably not used right now or ever
# External_export_includes - probably not used right now or ever
# Internal_inc - Additional include directories
# Includes_to_export - includes to be exported from this target in current project - which is kinda weird

set(Internal_deps geGL)
set(External_deps )
set(External_export_libs )
set(External_export_includes )
set(Internal_inc ${GPUEngine_SOURCE_DIR}/include ${GLM_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
set(Includes_to_export )

#Searched for in the top most CMakeList - don't ask me why.
IF(ANTTWEAKBAR_FOUND)
   list(APPEND Internal_inc ${ANTTWEAKBAR_INCLUDE_DIR})
   target_link_libraries(${LIB_NAME} ${ANTTWEAKBAR_LIBRARY})
ENDIF()

IF(SDL2_FOUND)
   list(APPEND Internal_inc ${SDL2_INCLUDE_DIR})
   target_link_libraries(${LIB_NAME} ${SDL2_LIBRARY})
ENDIF()

target_link_libraries(${LIB_NAME} ${GLEW_LIBRARY} ${OPENGL_LIBRARY} ${Internal_deps})
set_target_properties(${LIB_NAME} PROPERTIES
	INCLUDE_DIRECTORIES "${Internal_inc}"
	INTERFACE_INCLUDE_DIRECTORIES "${Includes_to_export}"
)

install(FILES
    ${ARGUMENTMANAGER_INCLUDES}
    DESTINATION include/${LIB_NAME}/ArgumentManager
  )

install(FILES
    ${LIBRARYLOADER_INCLUDES}
    DESTINATION include/${LIB_NAME}/LibraryLoader
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
   ../CMake/geConfig.cmake.in
   "${LIB_NAME}Config.cmake"
   @ONLY
)


configure_file(
   ../CMake/geExport.h.in
   "${GPUEngine_SOURCE_DIR}/include/${LIB_NAME}/Export.h"
   @ONLY
)

# INSTALL_CM_DIR is defined in master CMakeLists file

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake"
        DESTINATION "${INSTALL_CM_DIR}/${LIB_NAME}"
        )
