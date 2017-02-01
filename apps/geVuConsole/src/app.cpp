#include "app.h"

#include <glm/gtx/rotate_vector.hpp>
#include <algorithm>

#include <AssimpModelLoader.h>

#include <glm/gtx/string_cast.hpp>

#include <geSG/Animation.h>
#include <geSG/AnimationChannel.h>
#include <regex>
#include "FreeImageImageLoader.h"

#include <FreeImagePlus.h>

#include "ConsoleSwapchain.h"


using namespace std;
using namespace glm;


using namespace ge::vu;
using namespace ge::vusg;

struct DrawArraysIndirectCommand {
  uint count;
  uint primCount;
  uint first;
  uint baseInstance;
};

App::App() {
  ContextCreateInfo cci;
  cci.validation = true;
  cci.verbose = false;

  context = make_shared<Context>(cci);
  deviceContext = context->createDeviceContext(0);

  ConsoleSwapchainCreateInfo csci;
  csci.deviceContext = deviceContext;
  swapchain = make_shared<ConsoleSwapchain>(csci);
  swapchain->init();

  deviceContext->flushCommandBuffer();

  renderer = make_shared<PhongTechnique>(deviceContext, swapchain);

  roty = 45;
  zoom = 15;
}

void App::init() {
  //string model = "D:/prac/modely/sponza3/sponza.fbx";
  //string model = "D:/prac/modely/texCube/texCube.obj";
  //string model = "D:/prac/modely/Excavator/bagrOld.fbx";
  string model = "D:/prac/modely/Excavator/bagr.fbx";

  path = std::regex_replace(model, std::regex("[^/]+$"), "");
  //scene = std::shared_ptr<ge::sg::Scene>(AssimpModelLoader::loadScene("D:/prac/modely/texCube/texCube.obj"));  
  //scene = std::shared_ptr<ge::sg::Scene>(AssimpModelLoader::loadScene("D:/prac/modely/Excavator/bagrOld.fbx"));
  //scene = std::shared_ptr<ge::sg::Scene>(AssimpModelLoader::loadScene("D:/prac/modely/Anim/anim.fbx"));
  //scene = std::shared_ptr<ge::sg::Scene>(AssimpModelLoader::loadScene("D:/prac/modely/texCube/texCube.fbx"));
  scene = std::shared_ptr<ge::sg::Scene>(AssimpModelLoader::loadScene(model.c_str()));
  renderer->setScene(scene);

  deviceContext->flushCommandBuffer();

  for (auto& mod : scene->models) {
    for (auto& mat : mod->materials) {
      for (auto& comp : mat->materialComponents) {
        if (comp->getType() == ge::sg::MaterialComponent::ComponentType::IMAGE) {
          auto imgComp = static_pointer_cast<ge::sg::MaterialImageComponent>(comp);
          string texPath = path + imgComp->filePath;
          texPath = std::regex_replace(texPath, std::regex("\\\\"), "/");
          auto fimg = FreeImageImageLoader::loadImage(texPath.c_str());
          auto fip = fimg->getImageImpl();
          assert(fimg);
          fip->convertTo32Bits();
          imgComp->image = shared_ptr<FreeImageImage>(fimg);
        }
      }
    }
  }

  manager = make_shared<ge::sg::AnimationManager>();
  for (auto& a : scene->animations) {
    a->mode = ge::sg::Animation::Mode::LOOP;

    manager->playAnimation(a, chrono::steady_clock::now());
  }
}


int last = 0;

void App::draw() {
  updateCamera();
  
  manager->update(chrono::steady_clock::now());

  renderer->projection = projection;
  renderer->view = view;
  std::cout << "frame\n";
  renderer->frame();
  std::cout << "frame end\n";

  //quit();
}

void App::resize(int w, int h) {
  swapchain->resize(w, h);
}


void App::updateCamera() {
  rotx++;
  vec3 eye;
  eye = vec3(-zoom, 0, 0);
  eye = rotate(eye, -radians(float(roty)), vec3(0, 0, 1));
  eye = rotate(eye, -radians(float(rotx)), vec3(0, 1, 0));

  view = lookAt(eye, vec3(0, 0, 0), vec3(0, 1, 0));
  int w = swapchain->getWidth();
  int h = swapchain->getHeight();
  projection = perspective(radians(60.f), float(w) / float(h), 0.1f, 1000.f);
}


int App::run() {
  init();

  while (!stop) {
    draw();
  }
  return 0;
}

void App::quit() {
  stop = true;
}
