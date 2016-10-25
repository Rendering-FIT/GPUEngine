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
enum AppMode { CALIBRATE_ALL, CALIBRATE, WAIT_FRAMES, WAIT_TIME, TEST, TEST_ALL, INTERACTIVE, IDLE };

struct Options {
	DrawMode drawMode = SINGLE_DRAW;
	AppMode appMode = INTERACTIVE;
	bool rg = false;
	bool vk = false;
	bool includeMany = false;
	int cubeCount = 100;
	int textureCount = 1024;
	int textureSize = 128;
};


class App : public ge::gl::Context {
public:
	App(Options const& o = Options());
	int run();
	void quit();
	virtual void init() {}
	virtual void draw() {}
	bool handleEvent(const SDL_Event &e);
protected:
	void setupEvents();
	void setupStateStack();
	void updateState();
	void updateCamera();

	void pushInteractive(int cubes, int textures, DrawMode mode);
	void pushTest(int cubes, int textures, DrawMode mode);
	void pushCalibrate(int cubes, int textures, DrawMode mode);
	void pushWaitFrames(int frames);
	void pushWaitTime(int ms);

	virtual void interactive(int cubes, int textures, DrawMode mode);
	virtual void calibrate(int cubes, int textures, DrawMode mode);
	virtual void test(int cubes, int textures, DrawMode mode);
	void waitFrames(int frames);
	void waitTime(int ms);

	virtual void recomputeMatrices(int cubes) {}

	int getSide();

	void printCalibrateResult();
	void printTestResult();
	void printOpenGLVersion();

	std::string drawModeToString(DrawMode mode);
	std::string currentRendererToString();

	GLuint generateTexture(int size);
	void generateCubeVertices(std::vector<Vertex> &vertexData);

	// waitTime vars
	unsigned int waitTimeStart = 0;
	unsigned int waitTimeTotal = 0;

	// waitFrames vars
	unsigned int waitFramesRemaining = 0;

	// test vars
	float frontBackTime = 0;
	float backFrontTime = 0;
	float avgTime = 0;

	// calibrate vars
	int difCounter = 0;
	int zeroCounter = 0;

	// app state
	int maxTextures = 0;
	int currentTextures = 0;
	int maxCubes = 0;
	int currentCubes = 0;
	int currentSide = 0;
	DrawMode currentDrawMode;
	AppMode currentState;
	std::vector<std::function<void()>> stateStack;

	// camera
	glm::mat4 view;
	glm::mat4 projection;
	float angle = 0;
	float zoom = 10;

	// manipulator	
	int rotx = 0;
	int roty = 0;
	bool drag = false;

	Options options;

	std::shared_ptr<Stats> stats;
	std::shared_ptr<ge::ad::SDLMainLoop> mainLoop;
	std::shared_ptr<ge::ad::SDLWindow> window;
	SDL_Window* windowHandle;
};