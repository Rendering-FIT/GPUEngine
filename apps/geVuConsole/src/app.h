#pragma once

#include <geVu/geVu.h>

#include <geAd/SDLWindow/SDLWindow.h>
#include <functional>
#include <cmath>
#include <glm/glm.hpp>


#include <geSG/Scene.h>

#include <geVuSG/geVuSG.h>

class App {
public:
  App();
  int run();
  void quit();
  virtual void init();
  virtual void draw();
  virtual void resize(int w, int h);
protected:

  void setupEvents();
  void updateCamera();
  // camera
  glm::mat4 view;
  glm::mat4 projection;
  float angle = 0;
  float zoom = 10;

  // manipulator	
  int rotx = 0;
  int roty = 0;
  bool drag = false;

  //
  bool stop = false;

  std::string path;

  ge::vu::ContextShared context;
  ge::vu::DeviceContextShared deviceContext;
  ge::vu::SwapchainShared swapchain;

  ge::vusg::PhongTechniqueShared renderer;
  std::shared_ptr<ge::sg::Scene> scene;
};
