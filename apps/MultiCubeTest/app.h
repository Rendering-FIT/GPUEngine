#pragma once

#include <limits>
#include <string>
#include <geGL/geGL.h>
#include <geAd/SDLWindow/SDLWindow.h>
#include <geGL/OpenGLCommands.h>
#include <geGL/OpenGLContext.h>
#include <functional>
#include <geUtil/CameraObject.h>
#include <cmath>

#include "gui.h"
#include "stats.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 tc;
};

enum DrawMode { SINGLE_DRAW, MANY_DRAW, INSTANCED, MULTIDRAW_INDIRECT };
enum AppMode { CALIBRATE_ALL, CALIBRATE, WAIT, WAIT_TIME, TEST, TEST_ALL, INTERATIVE };

struct Options {	
	DrawMode drawMode = SINGLE_DRAW;	
	AppMode appMode = INTERATIVE;
	bool rg = false;
	int cubeCount = 100;
	int textureCount = 1024;
	int textureSize = 128;
};


class App : public ge::gl::Context {
public:
	App(Options const& o = Options());
	int run();
	void quit();
	bool handleEvent(SDL_Event const&e);
	virtual void init() {}
	virtual void draw() {}
protected:
	void createCubes(int count);
	std::string drawModeToString(DrawMode mode);

	GLuint generateTexture(int size);
	void generateCubeVertices(std::vector<Vertex> &vertexData);

	std::shared_ptr<ge::gl::Context> gl;
	std::shared_ptr<ge::ad::SDLMainLoop> mainLoop;
	std::shared_ptr<ge::ad::SDLWindow> window;
	SDL_Window* windowHandle;

	std::shared_ptr<ge::util::CameraObject> camera;

	std::shared_ptr<Stats> stats;

	glm::mat4 view;
	glm::mat4 projection;

	Options options;
};