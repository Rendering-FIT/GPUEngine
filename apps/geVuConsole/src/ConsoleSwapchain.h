#pragma once

#include <geVu/geVuClasses.h>
#include <geVu/Swapchain.h>

class ConsoleSwapchainCreateInfo {
public:
  int charWidth = 100;
  int charHeight = 50;
  int fontWidth = 8;
  int fontHeight = 12;

  int depthBufferBits = 32;
  int stencilBufferBits = 0;

  ge::vu::DeviceContextShared deviceContext;
};


class ConsoleSwapchain : public ge::vu::Swapchain {
protected:
  ge::vu::TextureShared colorBuffer;
  ge::vu::TextureShared depthBuffer;

  vk::Pipeline computePipeline;

  ConsoleSwapchainCreateInfo createInfo;
public:
  ConsoleSwapchain(const ConsoleSwapchainCreateInfo &o = ConsoleSwapchainCreateInfo());
  virtual ~ConsoleSwapchain();

  virtual void init();
  virtual void next();
  virtual void swap();
  void resize(int w, int h) override;

protected:
  void createDepthBuffer();
  void createColorBuffer();
  void createRenderPass();
  void createFramebuffers();
  void createPipeline();

  void destroyPipeline();
  void destroyDepthBuffer();
  void destroyColorBuffer();
  void destroyRenderPass();
  void destroyFramebuffers();
};