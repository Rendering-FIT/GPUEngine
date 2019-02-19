cmake_minimum_required(VERSION 3.12.1)

find_package(SDL2 CONFIG REQUIRED)

add_executable(tests TestsMain.cpp SDLWin.h SDLWin.cpp catch.hpp BufferTests.cpp ComputeShaderTests.cpp ProgramTests.cpp)

target_link_libraries(tests geGL::geGL SDL2::SDL2 SDL2::SDL2main)

