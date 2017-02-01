#include "app.h"

#include <glm/gtx/rotate_vector.hpp>
#include <algorithm>

#include <SDL2/SDL_syswm.h>

#include <AssimpModelLoader.h>

#include <glm/gtx/string_cast.hpp>

#include <geSG/Animation.h>
#include <geSG/AnimationChannel.h>
#include <regex>
#include "FreeImageImageLoader.h"

#include <FreeImagePlus.h>
#include "geSG/AnimationManager.h"

using namespace std;
using namespace ge::ad;
using namespace glm;

using namespace ge::vu;
using namespace ge::vusg;

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

  ContextCreateInfo cci;
  cci.validation = false;
  cci.verbose = false;

  context = make_shared<Context>(cci);
  deviceContext = context->createDeviceContext(0);

  SDL_SysWMinfo info;
  SDL_VERSION(&info.version);
  SDL_GetWindowWMInfo(window->getWindow(), &info);

  WindowSwapchainCreateInfo sci;
  sci.hinstance = (HINSTANCE)GetModuleHandle(NULL);
  sci.hwnd = (HWND)info.info.win.window;
  swapchain = deviceContext->createSwapchain(sci);
  deviceContext->flushCommandBuffer();

  renderer = make_shared<PhongTechnique>(deviceContext, swapchain);
}

void App::init() {
  //string model = "D:/prac/modely/sponza3/sponza.fbx";
  //string model = "D:/prac/modely/texCube/texCube.obj";
  string model = "D:/prac/modely/Excavator/bagr.fbx";
  //string model = "D:/prac/modely/Anim/anim.fbx";

  path = std::regex_replace(model, std::regex("[^/]+$"), "");
  scene = std::shared_ptr<ge::sg::Scene>(AssimpModelLoader::loadScene(model.c_str()));
  renderer->setScene(scene);

  deviceContext->flushCommandBuffer();

  int i = 0;
  for (auto &mod : scene->models) {
    for (auto &mat : mod->materials) {
      cout << "MATERIAL " << i++ << "\n";
      int c = 0;
      for (auto &comp : mat->materialComponents) {
        cout << " COMPONENT " << c++ << "\n";
        if (comp->getType() == ge::sg::MaterialComponent::ComponentType::IMAGE) {
          auto imgComp = static_pointer_cast<ge::sg::MaterialImageComponent>(comp);
          std::string texPath = path + imgComp->filePath;
          cout << "  " << imgComp->semantic << " " << imgComp->filePath << "\n";

          texPath = std::regex_replace(texPath, std::regex("\\\\"), "/");
          auto fimg = FreeImageImageLoader::loadImage(texPath.c_str());
          if (!fimg)cout << "img null " << texPath << "\n";
          auto fip = fimg->getImageImpl();
          assert(fimg);
          cout << "converting\n";
          fip->convertTo32Bits();
          imgComp->image = shared_ptr<FreeImageImage>(fimg);

          std::cout << "image loaded " << imgComp->filePath << "\n";
        }
        else {
          auto simp = static_pointer_cast<ge::sg::MaterialSimpleComponent>(comp);
          std::cout << "  " << simp->semantic << "\n";
        }
      }
    }
  }
  
  manager = make_shared<ge::sg::AnimationManager>();

  for (auto &a : scene->animations) {
    a->mode = ge::sg::Animation::Mode::LOOP;
    
    //manager->playAnimation(a,ge::core::time_point(std::chrono::milliseconds(0)));
    manager->playAnimation(a, chrono::steady_clock::now());
  }
}


int last = 0;

void App::draw() {
  updateCamera();

  //auto time = std::chrono::milliseconds(SDL_GetTicks());
  auto time = std::chrono::steady_clock::now();

  manager->update(time);

  renderer->projection = projection;
  renderer->view = view;
  renderer->frame();

  //quit();
}

void App::resize(int w, int h) {
  swapchain->resize(w, h);
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

  window->setEventCallback(SDL_KEYDOWN, [&](const SDL_Event &e) {
    switch (e.key.keysym.sym) {
    case SDLK_ESCAPE:
      quit();
      return true;
    }
    return false;
  });

  window->setEventCallback(SDL_MOUSEWHEEL, [&](const SDL_Event &e) {
    if (e.wheel.y < 0) zoom *= 1.1f;
    else zoom /= 1.1f;
    return true;
  });

  window->setEventCallback(SDL_WINDOWEVENT, [&](const SDL_Event &e) {
    switch (e.window.event) {
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      resize(e.window.data1, e.window.data2);
      return true;
    }
    return false;
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
  projection = perspective(radians(60.f), float(w) / float(h), 0.1f, 1000.f);
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

