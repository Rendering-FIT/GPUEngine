#include "app.h"

#include <glm/gtx/rotate_vector.hpp>
#include <algorithm>

#include <SDL2/SDL_syswm.h>

using namespace std;
using namespace ge::ad;
using namespace glm;

using namespace ge::vu;

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
  mainLoop->addWindow("mainWindow", window);

  windowHandle = SDL_GetWindowFromID(window->getId());

  setupEvents();

  context = make_shared<Context>();
  device = context->createDeviceContext(0);

  SDL_SysWMinfo info;
  SDL_VERSION(&info.version);
  SDL_GetWindowWMInfo(window->getWindow(), &info);

  SwapchainCreateInfo sci;
  sci.hinstance = (HINSTANCE)GetModuleHandle(NULL);
  sci.hwnd = (HWND)info.info.win.window;
  device->createSwapchain(sci);
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

bool App::handleEvent(SDL_Event const & e) {
  SDL_Event ev = e;
  //ImGui_ImplSdlGL3_ProcessEvent(&ev);
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

