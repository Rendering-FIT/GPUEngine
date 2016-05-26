set(LIB_NAME geUtil)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

if(GPUENGINE_DYNAMIC_LINKAGE)
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
   add_definitions(-D"${LIB_NAME_UPPER}"_LIBRARY)
else()
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
   add_definitions(-DGE_LIBRARY_STATIC)
endif()

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

set(UTIL_INCLUDES
   ${HEADER_PATH}/Export.h
   ${HEADER_PATH}/algorithms.h
   ${HEADER_PATH}/ArgumentObject.h
   ${HEADER_PATH}/CameraObject.h
   ${HEADER_PATH}/CameraPath.h
   ${HEADER_PATH}/FPSPrinter.h
   ${HEADER_PATH}/HighResolutionTimer.h
   ${HEADER_PATH}/Interpolator.h
   ${HEADER_PATH}/Intersector.h
   ${HEADER_PATH}/macros.h
   ${HEADER_PATH}/MatrixStack.h
   ${HEADER_PATH}/Progress.h
   ${HEADER_PATH}/Ray.h
   ${HEADER_PATH}/geUtil.h
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
   Progress.cpp
   NamespaceWithUsers.cpp
   copyArgumentManager2Namespace.cpp
)

if(ANTTWEAKBAR_FOUND AND SDL2_FOUND)
   set(UTIL_INCLUDES ${UTIL_INCLUDES} ${HEADER_PATH}/WindowObject.h)
   set(GL_SOURCES ${GL_SOURCES} WindowObject.cpp)
endif()

add_library(${LIB_NAME}
   ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
   ${UTIL_INCLUDES}
   ${ARGUMENTMANAGER_INCLUDES}
   ${LIBRARYLOADER_INCLUDES}
   ${GL_SOURCES}
   ${ARGUMENTMANAGER_SOURCES}
   ${LIBRARYLOADER_SOURCES}
)

################################################
# PACKAGES

find_package(glm)
find_package(GLEW)

################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_deps_Export - other than 'ge' packages goes here (e.g. glew), it configures this package extra project dependencies and also configures the config file
# External_libs - external libs or targets to link with
# Internal_inc - additional include directories
# Includes_to_export - includes to be exported from this target to application

set(Internal_deps geGL)
set(External_deps_Export glm GLEW)
set(External_libs glm GLEW)
set(Internal_inc ${GPUEngine_SOURCE_DIR}/include)
set(Includes_to_export ${GPUEngine_SOURCE_DIR}/include)


target_link_libraries(${LIB_NAME} ${GLEW_LIBRARY} ${OPENGL_LIBRARY} ${Internal_deps} ${External_libs})
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
   ${UTIL_INCLUDES}
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
