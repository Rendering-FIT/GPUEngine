
set(MODULE_NAME "QtImageLoader")
set(MODULE_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

#If target was already defined then return. Perhaps it was included from another package.
IF(TARGET ${MODULE_NAME})
   return()
ENDIF()

set(${MODULE_NAME}_HEADER_FILES
   ${MODULE_DIR}/src/QtImageLoader.h
)

set(${MODULE_NAME}_SOURCE_FILES
   ${MODULE_DIR}/src/QtImageLoader.cpp
)


find_package(Qt5 COMPONENTS Gui)
#find_package(GPUEngine COMPONENTS geSG)

add_library(${MODULE_NAME} INTERFACE)

target_sources(${MODULE_NAME} INTERFACE ${${MODULE_NAME}_SOURCE_FILES})
target_include_directories(${MODULE_NAME} INTERFACE "${MODULE_DIR}/src/" )
target_link_libraries(${MODULE_NAME} INTERFACE 
                        general geSG Qt5::Gui
)