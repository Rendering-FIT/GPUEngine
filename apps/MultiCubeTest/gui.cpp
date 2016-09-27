#include "Gui.h"

using namespace ImGui;


void textColor(float r, float g, float b, float a){
	ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(r, g, b, a);
}

void label(std::string const & text, int x, int y, int width, int height) {
	static int id = 0;
	IMGUI_ONCE_UPON_A_FRAME{
		id = 0;
	}

		Begin(std::to_string(id++).c_str(), 0, ImVec2(width, height), 0,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
	SetWindowPos(ImVec2(x, y));
	Text(text.c_str());
	End();
}

void fpsLabel(int x, int y, int width, int height) {
	std::string s = "fps: " + std::to_string(ImGui::GetIO().Framerate);
	label(s, x, y, width, height);
}