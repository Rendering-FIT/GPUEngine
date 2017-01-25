
set(MODULE_NAME "AssimpModelLoader")
set(MODULE_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

#If target was already defined then return. Perhaps it was included from another package.
IF(TARGET ${MODULE_NAME})
   return()
ENDIF()

set(${MODULE_NAME}_HEADER_FILES
   ${MODULE_DIR}/src/AssimpModelLoader.h
   ${MODULE_DIR}/src/UnicodeIOSystem.h
   ${MODULE_DIR}/src/UnicodeIOStream.h
)

set(${MODULE_NAME}_SOURCE_FILES
   ${MODULE_DIR}/src/AssimpModelLoader.cpp
   ${MODULE_DIR}/src/UnicodeIOStream.cpp
)

############################################
# Platform dependent IO system

if(WIN32)
   set(${MODULE_NAME}_SOURCE_FILES ${${MODULE_NAME}_SOURCE_FILES}
      ${MODULE_DIR}/src/UnicodeIOSystem_win32.cpp
   )
else()
   set(${MODULE_NAME}_SOURCE_FILES ${${MODULE_NAME}_SOURCE_FILES}
      ${MODULE_DIR}/src/UnicodeIOSystem_other.cpp
   )
endif(WIN32)

find_package(assimp)
#find_package(GPUEngine COMPONENTS geSG)
find_package(glm)

add_library(${MODULE_NAME} INTERFACE )


target_sources(${MODULE_NAME} INTERFACE ${${MODULE_NAME}_SOURCE_FILES})
target_include_directories(${MODULE_NAME} INTERFACE "${MODULE_DIR}/src/" ${ASSIMP_INCLUDE_DIRS})
#set_property(TARGET geGL APPEND PROPERTY INTERFACE_LINK_LIBRARIES "${${_dep}_LIBRARY}")
target_link_libraries(${MODULE_NAME} INTERFACE ste geSG glm)
                        
target_link_libraries(${MODULE_NAME} INTERFACE optimized ${ASSIMP_LIBRARY_DIRS}/assimp.lib
                        debug ${ASSIMP_LIBRARY_DIRS}/assimpd.lib
)
