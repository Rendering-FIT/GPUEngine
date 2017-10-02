
set(MODULE_NAME "FreeImageImageLoader")
set(MODULE_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

#If target was already defined then return. Perhaps it was included from another package.
IF(TARGET ${MODULE_NAME})
   return()
ENDIF()

set(${MODULE_NAME}_HEADER_FILES
   ${MODULE_DIR}/src/FreeImageImageLoader.h
)

set(${MODULE_NAME}_SOURCE_FILES
   ${MODULE_DIR}/src/FreeImageImageLoader.cpp
)


find_package(FreeImage)
find_package(FreeImagePlus)

IF(NOT TARGET geSG)
  find_package(GPUEngine COMPONENTS geSG)
ENDIF()

add_library(${MODULE_NAME} INTERFACE)

target_sources(${MODULE_NAME} INTERFACE ${${MODULE_NAME}_SOURCE_FILES})
target_include_directories(${MODULE_NAME} INTERFACE "${MODULE_DIR}/src/" ${FREEIMAGE_INCLUDE_PATH} ${FREEIMAGEPLUS_INCLUDE_PATH})
target_link_libraries(${MODULE_NAME} INTERFACE 
                        general geSG ${FREEIMAGE_LIBRARIES} ${FREEIMAGEPLUS_LIBRARIES}
)
