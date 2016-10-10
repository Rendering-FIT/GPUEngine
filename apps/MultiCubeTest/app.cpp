#include "app.h"

#include "gui.h"

using namespace std;
using namespace ge::gl;
using namespace ge::ad;
using namespace ge::util;
using namespace glm;

struct DrawArraysIndirectCommand {
	uint  count;
	uint  primCount;
	uint  first;
	uint  baseInstance;
};

App::App(Options const & o) {
	options = o;
	mainLoop = make_shared<SDLMainLoop>();
	mainLoop->setIdleCallback(std::bind(&App::draw, this));
	mainLoop->setEventHandler(std::bind(&App::handleEvent, this, std::placeholders::_1));

	window = make_shared<SDLWindow>();
	window->createContext("rendering", 450u, SDLWindow::CORE, SDLWindow::DEBUG);
	mainLoop->addWindow("mainWindow", window);
	window->makeCurrent("rendering");

	ge::gl::init(SDL_GL_GetProcAddress);

	this->setFunctionTable(getDefaultContext()->getFunctionTable());
	setHighDebugMessage();

	stats = make_shared<Stats>();


	windowHandle = SDL_GetWindowFromID(window->getId());
	ImGui_ImplSdlGL3_Init(windowHandle);
}


std::string App::drawModeToString(DrawMode mode) {
	switch (mode) {
	case SINGLE_DRAW:
		return "single draw";
	case MANY_DRAW:
		return "draw per cube";
	case INSTANCED:
		return "instanced";
	case MULTIDRAW_INDIRECT:
		return "multidraw";
	}
	return "";
}

GLuint App::generateTexture(int size) {
	int width = size;
	int height = size;
	uint *data = new uint[width * height];
	unsigned int colors[] = {
		0xFF000000,
		0xFFFF0000,
		0xFF00FF00,
		0xFF0000FF,
		0xFFFFFF00,
		0xFFFF00FF,
		0xFF00FFFF,
		0xFFFFFFFF
	};
	int c1 = rand() % 8;
	int c2 = rand() % 8;
	if (c2 == c1)c2 = (c2 + 1) % 8;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (((x >> 4) & 1) == ((y >> 4) & 1))
				data[y * width + x] = colors[c1];
			else
				data[y * width + x] = colors[c2];
		}
	}
	GLuint tex;
	glCreateTextures(GL_TEXTURE_2D, 1, &tex);
	glTextureImage2DEXT(tex, GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateTextureMipmap(tex);
	glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(tex, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_REPEAT);
	delete[] data;
	return tex;
}

void quad(vector<Vertex>& vertexData,
	vec3 p0, vec3 p1, vec3 p2, vec3 p3) {
	vec3 norm = normalize(cross(p1 - p0, p2 - p0));
	vertexData.emplace_back(Vertex{ p0,norm,vec2(0,0) });
	vertexData.emplace_back(Vertex{ p1,norm,vec2(1,0) });
	vertexData.emplace_back(Vertex{ p2,norm,vec2(1,1) });
	vertexData.emplace_back(Vertex{ p0,norm,vec2(0,0) });
	vertexData.emplace_back(Vertex{ p2,norm,vec2(1,1) });
	vertexData.emplace_back(Vertex{ p3,norm,vec2(0,1) });
}

void App::generateCubeVertices(std::vector<Vertex>& vertexData) {
	quad(vertexData, vec3(0, 1, 1), vec3(0, 0, 1), vec3(1, 0, 1), vec3(1, 1, 1));
	quad(vertexData, vec3(1, 1, 0), vec3(1, 0, 0), vec3(0, 0, 0), vec3(0, 1, 0));
	quad(vertexData, vec3(1, 1, 1), vec3(1, 0, 1), vec3(1, 0, 0), vec3(1, 1, 0));
	quad(vertexData, vec3(0, 1, 0), vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 1));
	quad(vertexData, vec3(0, 0, 1), vec3(0, 0, 0), vec3(1, 0, 0), vec3(1, 0, 1));
	quad(vertexData, vec3(0, 1, 1), vec3(1, 1, 1), vec3(1, 1, 0), vec3(0, 1, 0));
}

bool App::handleEvent(SDL_Event const & e) {
	SDL_Event ev = e;
	ImGui_ImplSdlGL3_ProcessEvent(&ev);

	switch (e.type) {
	case SDL_QUIT:
		quit();
		break;
	}
	return true;
}

int App::run() {
	init();
	(*mainLoop)();
	return 0;
}

void App::quit(){
	mainLoop->removeWindow("mainWindow");
}

