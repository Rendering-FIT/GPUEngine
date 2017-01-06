#include "app.h"

#include <glm/gtx/rotate_vector.hpp>
#include <algorithm>

#include <SDL2/SDL_syswm.h>

#include "AssimpModelLoader/AssimpModelLoader.h"
#include <geSG/MatrixTransform.h>
#include <geSG/Node.h>
#include "ste/DAG.h"

#include <glm/gtx/string_cast.hpp>

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
  deviceContext = context->createDeviceContext(0);

  SDL_SysWMinfo info;
  SDL_VERSION(&info.version);
  SDL_GetWindowWMInfo(window->getWindow(), &info);

  SwapchainCreateInfo sci;
  sci.hinstance = (HINSTANCE)GetModuleHandle(NULL);
  sci.hwnd = (HWND)info.info.win.window;
  swapchain = deviceContext->createSwapchain(sci);
}

void App::init() {
  scene = std::shared_ptr<ge::sg::Scene>(AssimpModelLoader::loadScene("D:/prac/modely/texCube/texCube.obj"));

  deviceContext->flushCommandBuffer();
  deviceContext->getDevice().waitIdle();

  vk::CommandBufferAllocateInfo cbai;
  cbai.commandPool = deviceContext->getCommandPool();
  cbai.commandBufferCount = 1;
  commandBuffer = deviceContext->getDevice().allocateCommandBuffers(cbai)[0];
}

void App::createDrawCommand() {
  int width = window->getWidth();
  int height = window->getHeight();

  commandBuffer.reset(vk::CommandBufferResetFlags());
  
  commandBuffer.begin(vk::CommandBufferBeginInfo(vk::CommandBufferUsageFlagBits::eSimultaneousUse));

  vk::ClearValue const clearValues[2] = {
    vk::ClearColorValue(std::array<float, 4>({ 0.2f, 0.2f, 0.2f, 0.2f })),
    vk::ClearDepthStencilValue(1.0f, 0u) };

  vk::RenderPassBeginInfo rpbi;
  rpbi.clearValueCount = 2;
  rpbi.pClearValues = clearValues;
  rpbi.framebuffer = swapchain->getCurrentFrameBuffer();
  rpbi.renderArea = vk::Rect2D(vk::Offset2D(0, 0), vk::Extent2D((uint32_t)width, (uint32_t)height));
  rpbi.renderPass = swapchain->getRenderPass();
  
  deviceContext->changeImageLayout(commandBuffer, swapchain->getCurrentImage(),
    vk::ImageLayout::ePresentSrcKHR, vk::ImageLayout::eColorAttachmentOptimal);
  
  commandBuffer.beginRenderPass(rpbi, vk::SubpassContents::eInline);
  
  vk::Viewport viewport;
  viewport.width = (float)width;
  viewport.height = (float)height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  commandBuffer.setViewport(0, 1, &viewport);

  vk::Rect2D scissor;
  scissor.offset = vk::Offset2D(0, 0);
  scissor.extent = vk::Extent2D(width, height);

  commandBuffer.setScissor(0, 1, &scissor);

  commandBuffer.endRenderPass();
  commandBuffer.end();
}

void App::draw() {
  swapchain->next();

  createDrawCommand();

  vk::PipelineStageFlags flags = vk::PipelineStageFlagBits::eBottomOfPipe;
  vk::SubmitInfo si;
  si.waitSemaphoreCount = (1);
  si.pWaitSemaphores = (&swapchain->getSemaphore());
  si.pWaitDstStageMask = (&flags);
  si.commandBufferCount = (1);
  si.pCommandBuffers = (&commandBuffer);

  deviceContext->getQueue().submit(si,0);

  swapchain->swap();

  deviceContext->getQueue().waitIdle();
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

