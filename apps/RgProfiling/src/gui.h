#pragma once

#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"

#include <string>
/* Useful 'macros' to help with imgui */

void textColor(float r, float g, float b, float a);
void label(std::string const&text, int x=0, int y=0, int width = 200, int height = 100);
void fpsLabel(int x = 0, int y = 0, int width = 200, int height = 20);