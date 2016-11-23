#include "app.h"

#include "gui.h"

#include <iomanip>
#include <glm/gtx/rotate_vector.hpp>
#include <algorithm>

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

	setupStateStack();
	setupEvents();
}


void App::setupEvents() {
	window->setEventCallback(SDL_QUIT, [&](const SDL_Event &) {
		quit();
		return true;
	});
	window->setEventCallback(SDL_MOUSEMOTION, [&](const SDL_Event &e) {
		if (drag) {
			rotx += e.motion.xrel;
			roty += e.motion.yrel;
			roty = (std::min)(roty, 89);
			roty = (std::max)(roty, -89);
		}
		return true;
	});

	window->setEventCallback(SDL_MOUSEBUTTONDOWN, [&](const SDL_Event &e) {
		if (e.button.button == 1)
			drag = true;
		return true;
	});
	window->setEventCallback(SDL_MOUSEBUTTONUP, [&](const SDL_Event &e) {
		if (e.button.button == 1)
			drag = false;
		return true;
	});
	window->setEventCallback(SDL_MOUSEWHEEL, [&](const SDL_Event &e) {
		if (currentState == INTERACTIVE) {
			if (e.wheel.y < 0) zoom *= 1.1f;
			else zoom /= 1.1f;
		}
		return true;
	});
}

void App::setupStateStack() {
	maxCubes = options.cubeCount;
	currentCubes = maxCubes;

	maxTextures = options.textureCount;
	currentTextures = maxTextures;
	currentDrawMode = options.drawMode;
  /*
	waitFrames(1);
	pushWaitTime(2000);*/

	vector<DrawMode> modes({ INSTANCED, SINGLE_DRAW, MULTIDRAW_INDIRECT });
	if (options.includeMany) modes.push_back(MANY_DRAW);
	vector<int> texCounts({ 16,32,64,128,512,1024 });

  currentState = IDLE;
	switch (options.appMode) {
	case CALIBRATE:
		pushCalibrate(1000, maxTextures, currentDrawMode);
		break;
	case INTERACTIVE:
		pushInteractive(maxCubes, maxTextures, currentDrawMode);
		break;
	case TEST:
		pushTest(maxCubes, maxTextures, currentDrawMode);
		break;
	case CALIBRATE_ALL: {
		// calibrate different draw modes

		for (auto &m : modes) {
			pushCalibrate(1000, 0, m);
			pushWaitTime(2000);
		}

		// calibrate different texture counts
		for (auto &t : texCounts) {
			if (t <= maxTextures) {
				pushCalibrate(1000, t, SINGLE_DRAW);
				pushWaitTime(2000);
			}
		}
		break;
	}
	case TEST_ALL: {
		// test different texture counts
		for (auto &t : texCounts) {
			if (t <= maxTextures) {
				pushTest(maxCubes, t, INSTANCED);
				pushWaitTime(2000);
			}
		}
		// test different texture counts
		for (auto &m : modes) {
			pushTest(maxCubes, 0, m);
			pushWaitTime(2000);
		}
		break;
	}
  default:break;
	}
}

void App::updateState() {
	//std::cout << "current state" << int(currentState) << "\n";
	switch (currentState) {
	case INTERACTIVE:
		break;
	case TEST: {
		float fps = stats->getFps();
    (void)fps;
		float mspf = stats->getMs();
		if (angle == 0) {
			backFrontTime = mspf;
		}
		if (angle == 180) {
			frontBackTime = mspf;
		}
		if (angle == 360) {
			avgTime = stats->getAvg(120);
			printTestResult();
			currentState = IDLE;
		}
		angle += 3;
		break;
	}
	case CALIBRATE: {
		float fps = stats->getFps();

		if (fps < 60) {
			difCounter = glm::max(difCounter - 1, -10);
			if (difCounter == -10) {
        addCubes(-10);
			}
		}
		if (fps > 60) {
			difCounter = glm::min(difCounter + 1, 10);
			if (difCounter == 10) {
				if (fps > 150 && currentDrawMode != MANY_DRAW)addCubes(currentCubes);
				else if (fps > 75 && currentDrawMode != MANY_DRAW)addCubes(1000);
				else if (fps > 61) addCubes(100);
				else addCubes(10);
				currentCubes = glm::min(currentCubes, maxCubes);
			}
		}
		if (difCounter == 0)zeroCounter++;
		if (zeroCounter == 5 || currentCubes == maxCubes) {
			printCalibrateResult();
			currentState = IDLE;
		}

		if (getSide() != currentSide && currentState != IDLE) {
			recomputeMatrices(currentCubes);
			currentSide = getSide();
			currentState = WAIT_FRAMES;
			waitFramesRemaining = 10;
			stateStack.insert(stateStack.begin(), [&]() {
				currentState = CALIBRATE;
			});
		}


		break;
	}
	case WAIT_TIME: {
		if (SDL_GetTicks() - waitTimeStart > waitTimeTotal) {
			currentState = IDLE;
		}
		break;
	}
	case WAIT_FRAMES:
		waitFramesRemaining--;
		if (waitFramesRemaining <= 0) {
			currentState = IDLE;
		}
		break;
	case IDLE:
		if (stateStack.size() == 0) {
			quit();
		}
		else {
			stateStack.at(0)();
			stateStack.erase(stateStack.begin());
		}
		break;
	default: {}
	}
}

void App::updateCamera() {
	vec3 eye;
	if (currentState == INTERACTIVE) {
		eye = vec3(-zoom, 0, 0);
		eye = rotate(eye, -radians(float(roty)), vec3(0, 0, 1));
		eye = rotate(eye, -radians(float(rotx)), vec3(0, 1, 0));
	}
	else {
		int side = getSide();
		zoom = float(side) * 2.2f;
		float a = radians(angle + 45);
		eye = zoom*vec3(cos(a), 1, sin(a));
	}

	view = lookAt(eye, vec3(0, 0, 0), vec3(0, 1, 0));
	int w = window->getWidth();
	int h = window->getHeight();
	projection = perspective(radians(60.f), float(w) / float(h), 1.0f, 10000.f);
}

void App::pushInteractive(int cubes, int textures, DrawMode mode) {
	stateStack.push_back([this, cubes, textures, mode]() {
		interactive(cubes, textures, mode);
	});
}

void App::pushTest(int cubes, int textures, DrawMode mode) {
	stateStack.push_back([this, cubes, textures, mode]() {
		test(cubes, textures, mode);
	});
}

void App::pushCalibrate(int cubes, int textures, DrawMode mode) {
	stateStack.push_back([this, cubes, textures, mode]() {
		calibrate(cubes, textures, mode);
	});
}

void App::pushWaitFrames(int frames) {
	stateStack.push_back([this, frames]() {
		waitFrames(frames);
	});
}

void App::pushWaitTime(int ms) {
	stateStack.push_back([this, ms]() {
		waitTime(ms);
	});
}


void App::interactive(int cubes, int textures, DrawMode mode) {
	currentState = INTERACTIVE;
	currentCubes = cubes;
	currentTextures = textures;
	currentDrawMode = mode;
  zoom = float(getSide()) * 2.8f;
  rotx = 45;
  roty = 45;
}

void App::calibrate(int cubes, int textures, DrawMode mode) {
	currentState = CALIBRATE;
	currentCubes = cubes;
	currentTextures = textures;
	currentDrawMode = mode;
	angle = 0;
}

void App::test(int cubes, int textures, DrawMode mode) {
	currentState = TEST;
	currentCubes = cubes;
	currentTextures = textures;
	currentDrawMode = mode;
	angle = 0;
}

void App::waitFrames(int frames) {
	currentState = WAIT_FRAMES;
	waitFramesRemaining = frames;
}

void App::waitTime(int ms) {
	currentState = WAIT_TIME;
	waitTimeTotal = ms;
}

void App::addCubes(int count){
  currentCubes += count;
}

glm::mat4 App::getMatrix(int id){
  int side = (int)ceil(cbrtf(float(currentCubes)));
  vec3 offset = vec3(float(side));
  int x = id % side;
  int y = (id / side) % side;
  int z = id / (side*side);
  return translate(mat4(), vec3(x, y, z)*2.0f - offset);
}

int App::getSide() {
	return (int)ceil(cbrtf(float(currentCubes)));
}

void App::printCalibrateResult() {
	float mspc = float(1e6 / stats->getFps()) / float(currentCubes);
	cout.precision(3);
	cout.setf(ios_base::fixed);
	cout << currentRendererToString() << " calibrate 60 fps, " << currentTextures << " textures,";
	if (currentCubes == maxCubes) cout << " max cubes reached,";
	cout << currentCubes << " cubes, " << mspc << " us per cube\n";
}

void App::printTestResult() {
	cout.precision(3);
	cout.setf(ios_base::fixed);
	cout << currentRendererToString() << " test, " << currentCubes << " cubes, "
		<< currentTextures << " textures, "
		<< "back-front:" << backFrontTime << "ms, front-back:" << frontBackTime << "ms, 360-avg: "
		<< avgTime << "ms, one cube: " << 1000 * avgTime / float(currentCubes) << "us\n";
}

void App::printOpenGLVersion() {
	auto c = glGetString(GL_VENDOR);
	cout << c << "\n";
	c = glGetString(GL_VERSION);
	cout << c << "\n";
	c = glGetString(GL_RENDERER);
	cout << c << "\n";
}

std::string App::drawModeToString(DrawMode mode) {
	switch (mode) {
	case SINGLE_DRAW:
		return "single   ";
	case MANY_DRAW:
		return "many     ";
	case INSTANCED:
		return "instanced";
	case MULTIDRAW_INDIRECT:
		return "multiDraw";
	}
	return "";
}

std::string App::currentRendererToString() {
	string ret;
	if (options.rg) {
		ret += "geRG";
	}
	else if (options.vk) {
		ret += "NeiVu";
	}
	else {
		ret += "geGL";
	};
	ret += "-" + drawModeToString(currentDrawMode);
	return ret;
}

GLuint App::generateTexture(int size) {
	int width = size;
	int height = size;
  uint *data = generateTextureData(size);
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

uint * App::generateTextureData(int size){
  uint *data = new uint[size * size];
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
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      if (((x >> 4) & 1) == ((y >> 4) & 1))
        data[y * size + x] = colors[c1];
      else
        data[y * size + x] = colors[c2];
    }
  }
  return data;
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
	return false;
}

int App::run() {
	init();
	(*mainLoop)();
	return 0;
}

void App::quit() {
	mainLoop->removeWindow("mainWindow");
}

