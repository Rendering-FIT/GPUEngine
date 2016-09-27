#include "stats.h"

#include <iostream>
#include <algorithm>

Stats::Stats(int history){
	this->history = history;
	data = new float[history];
	std::fill(data,data+history,0.0f);

	glCreateQueries(GL_TIMESTAMP, 2, queries);
}

Stats::~Stats(){
	delete[] data;
}

void Stats::startFrame(){
	glQueryCounter(queries[0], GL_TIMESTAMP);
}

void Stats::endFrame(){
	glQueryCounter(queries[1], GL_TIMESTAMP);

	GLuint64 time1, time2;
	glGetQueryObjectui64v(queries[0], GL_QUERY_RESULT, &time1);
	glGetQueryObjectui64v(queries[1], GL_QUERY_RESULT, &time2);
	float dt = float(time2 - time1)*1e-6f;

	for (int i = history - 1; i >0; i--) {
		data[i] = data[i-1];
	}
	frames++;
	data[0] = dt;
}

float Stats::getAvg(){
	float sum = 0;
	int i = 0;
	for (; i < std::min(history, frames); i++) {
		sum += data[i];
	}
	if (i) sum /= i;
	return sum;
}

float Stats::getMax(){
	float m = 0;
	for (int i = 0; i < std::min(history, frames); i++) {
		m = std::max(data[i],m);
	}
	return m;
}

float Stats::getMin(){
	float m = FLT_MAX;
	for (int i = 0; i < std::min(history, frames); i++) {
		m = std::min(data[i], m);
	}
	return m;
}

void Stats::draw(){
	std::string msg;
	float vmax = getMax();
	float vmin = getMin();
	msg += "fps: " + std::to_string(1e3f/data[0]) + "(" + std::to_string((int)roundf(ImGui::GetIO().Framerate))+ ")\n";
	msg += "avg: " + std::to_string(getAvg()) + " ms\nmin: " + std::to_string(vmin) + " ms\nmax: " + std::to_string(vmax) + " ms\n";

	textColor(1, 1, 0, 1);
	label(msg);
	
	float top = ceil(vmax / 20.0f) * 20.0f; 
	ImGui::Begin("plot", 0, ImVec2(200, 60), 0,
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);
	ImGui::SetWindowPos(ImVec2(0,60));
	ImGui::PlotLines("", data, history,0,0,0,top,ImVec2(200,40));
	ImGui::End();
}
