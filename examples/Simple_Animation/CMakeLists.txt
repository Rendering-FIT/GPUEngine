cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "Simple_Animation")
set(APP_NAME "Simple_Animation")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

if(NOT TARGET geSG)
   find_package(GPUEngine COMPONENTS geSG)
endif()

if(NOT TARGET geSG)
   return()
endif()

set(HEADER_PATH src)
set(SOURCE_PATH src)
get_filename_component(src_abs ${SOURCE_PATH} ABSOLUTE)

set(SOURCE_FILES
   ${GPUEngine_SOURCE_DIR}/tests/animationTest.cpp
)


add_executable(${APP_NAME} ${SOURCE_FILES})
target_link_libraries(${APP_NAME} geSG)
set_property(TARGET ${APP_NAME} PROPERTY FOLDER "${examples_folder_name}")