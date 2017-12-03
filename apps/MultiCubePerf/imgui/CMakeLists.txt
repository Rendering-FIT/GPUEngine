find_package(SDL2)

set(include
	imconfig.h
	imgui.h
	imgui_impl_sdl_gl3.h
	imgui_internal.h
	stb_rect_pack.h
	stb_textedit.h
	stb_truetype.h
)

set(src
	imgui.cpp
	imgui_draw.cpp
	imgui_impl_sdl_gl3.cpp
)

add_library(imgui ${src} ${include})
target_link_libraries(imgui geGL SDL2::SDL2 SDL2::SDL2main)
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
