cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "Simple_QTgeGL")
set(APP_NAME "Simple_QTgeGL")

set( CMAKE_AUTORCC ON )
set( CMAKE_AUTOUIC ON )
set( CMAKE_AUTOMOC ON )

SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

SET(CMAKE_MODULE_PATH "CMakeModules;${CMAKE_MODULE_PATH}")

project(${PROJECT_NAME})

find_package(Qt5 COMPONENTS Quick )
if(NOT TARGET geGL)
   find_package(GPUEngine COMPONENTS geGL)
endif()   

if(NOT TARGET Qt5::Quick OR NOT TARGET geGL)
   return()
endif()

set(DEFAULT_RESOERCES_PATH "${CMAKE_CURRENT_LIST_DIR}/resources")

set(APP_RES "${DEFAULT_RESOERCES_PATH}" CACHE PATH "Relative or absolute path to Application resources.")

set(HEADER_PATH src)
set(SOURCE_PATH src)
get_filename_component(src_abs ${SOURCE_PATH} ABSOLUTE)

set(SOURCE_FILES
   src/main.cpp
   src/BasicQuickRenderer.h src/BasicQuickRenderer.cpp
   src/QuickRenderer.h src/QuickRenderer.cpp
)


add_executable(${APP_NAME} ${SOURCE_FILES})
target_link_libraries(${APP_NAME} Qt5::Quick geGL )
target_include_directories(${APP_NAME} PUBLIC "src/")
set_target_properties(${APP_NAME} PROPERTIES COMPILE_DEFINITIONS "APP_RESOURCES=\"${APP_RES}\"")
set_property(TARGET ${APP_NAME} PROPERTY FOLDER "examples")