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

App::App() {
  mainLoop = make_shared<SDLMainLoop>();
  mainLoop->setIdleCallback(std::bind(&App::draw, this));
  mainLoop->setEventHandler(std::bind(&App::handleEvent, this, std::placeholders::_1));

  window = make_shared<SDLWindow>();
  window->createContext("rendering", 440u, SDLWindow::CORE, SDLWindow::DEBUG);
  mainLoop->addWindow("mainWindow", window);
  window->makeCurrent("rendering");



  ge::gl::init(SDL_GL_GetProcAddress);

  this->setFunctionTable(getDefaultContext()->getFunctionTable());
  setHighDebugMessage();

  windowHandle = SDL_GetWindowFromID(window->getId());

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
    if (e.wheel.y < 0) zoom *= 1.1f;
    else zoom /= 1.1f;
    return true;
  });
}

void App::updateCamera() {
  vec3 eye;
  eye = vec3(-zoom, 0, 0);
  eye = rotate(eye, -radians(float(roty)), vec3(0, 0, 1));
  eye = rotate(eye, -radians(float(rotx)), vec3(0, 1, 0));
  
  view = lookAt(eye, vec3(0, 0, 0), vec3(0, 1, 0));
  int w = window->getWidth();
  int h = window->getHeight();
  projection = perspective(radians(60.f), float(w) / float(h), 1.0f, 10000.f);
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

uint * App::generateTextureData(int size) {
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

