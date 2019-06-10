# This CMakeLists is an example of and 3rd party aplication using our GPUEngine's geGL
# with Qt5 as GUI and windowing frontend. There shouldn't be needed any changes to use
# this as template for an outside project.
# Few cosmetic changes might be done though. You could remove if(NOT TARGET geGL) and
# leave only the inside (of the if). This is because here the geGL is already defined target but
# findpackage directive would expect the GPUEngine-config.cmake file which is for
# outside (downstream) projects and is created from INSTALL target of GPUEngine.
# You could also remove the FOLDER PROPERTY set on this application target.
# There it is to better organize things in GPUEngine when using IDE like MSVC


cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "Simple_QtgeGL")
set(APP_NAME "Simple_QtgeGL")
project(${PROJECT_NAME})

#You need these for automatic handling of Qt based classes (see Qt documentation).
#You can also use cmake commands like qt_wrap_cpp or qt_wrap_ui... for by hand approach.
set( CMAKE_AUTORCC ON )
set( CMAKE_AUTOUIC ON )
set( CMAKE_AUTOMOC ON )

SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")


SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")


find_package(Qt5 COMPONENTS Quick)
if(NOT TARGET geGL)
   find_package(GPUEngine COMPONENTS geGL)
endif()   

if(NOT TARGET geUtil)
   find_package(GPUEngine COMPONENTS geUtil)
endif()   
if(NOT TARGET Qt5::Quick OR NOT TARGET geGL)
   return()
endif()

set(DEFAULT_RESOERCES_PATH "${CMAKE_CURRENT_LIST_DIR}/resources")

set(${APP_NAME}_RESOURCES "${DEFAULT_RESOERCES_PATH}" CACHE PATH "Relative or absolute path to Application resources.")

set(HEADER_PATH src)
set(SOURCE_PATH src)
get_filename_component(src_abs ${SOURCE_PATH} ABSOLUTE)

set(SOURCE_FILES
   src/main.cpp
   src/BasicQuickRenderer.h src/BasicQuickRenderer.cpp
   src/QuickRendererBase.h src/QuickRendererBase.cpp
)


add_executable(${APP_NAME} ${SOURCE_FILES})
#preferable linking
target_link_libraries(${APP_NAME} Qt5::Quick geGL geUtil)

#another posiibilities to link Qt5 components in outside project (out of GPUE)
#  target_link_libraries(${APP_NAME} ${Qt5Quick_LIBRARIES} geGL )
#
#you can also use the wrapper FindQt5.cmake which introduces Qt5 target with components as dependencies
#which is located in GPUEngine CMakeModules folder
#  target_link_libraries(${APP_NAME} Qt5 geGL )

target_include_directories(${APP_NAME} PUBLIC "src/")
set_target_properties(${APP_NAME} PROPERTIES COMPILE_DEFINITIONS "APP_RESOURCES=\"${${APP_NAME}_RESOURCES}\"")
set_property(TARGET ${APP_NAME} PROPERTY FOLDER "${examples_folder_name}")


# setting up the MSVC helper var
get_target_property(Qt5dllPath Qt5::Quick IMPORTED_LOCATION_RELEASE)
get_filename_component(Qt5dllDir ${Qt5dllPath} DIRECTORY)
get_target_property(GPUEdllPath geGL IMPORTED_LOCATION_RELEASE)
set_target_properties(${APP_NAME} PROPERTIES VS_GLOBAL_DllPath "${OUTPUT_BINDIR};${Qt5dllDir}")