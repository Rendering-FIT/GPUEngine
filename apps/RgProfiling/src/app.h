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

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 tc;
};

class App : public ge::gl::Context {
public:
	App();
	int run();
	void quit();
	virtual void init() {}
	virtual void draw() {}
	bool handleEvent(const SDL_Event &e);
protected:
	void updateCamera();
  void setupEvents();
  // generator
	GLuint generateTexture(int size);
  unsigned int* generateTextureData(int size);
	void generateCubeVertices(std::vector<Vertex> &vertexData);

	// camera
	glm::mat4 view;
	glm::mat4 projection;
	float angle = 0;
	float zoom = 30;

	// manipulator	
	int rotx = 0;
	int roty = 0;
	bool drag = false;

	std::shared_ptr<ge::ad::SDLMainLoop> mainLoop;
	std::shared_ptr<ge::ad::SDLWindow> window;
	SDL_Window* windowHandle;
};
