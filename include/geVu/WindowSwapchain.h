#pragma once

#include <geVu/geVuClasses.h>
#include <geVu/Swapchain.h>

class ge::vu::WindowSwapchainCreateInfo {
public:
#ifdef WIN32
  HWND hwnd;
  HINSTANCE hinstance;
#endif
  int depthBufferBits = 32;
  int stencilBufferBits = 0;
  bool vsync = true;
  int imageCount = 2;
  DeviceContextShared deviceContext;
};


class ge::vu::WindowSwapchain: public Swapchain {
protected:
  WindowSwapchainCreateInfo createInfo;

  vk::SurfaceKHR surface;
  vk::SurfaceFormatKHR surfaceFormat;
  vk::SwapchainKHR swapchain;
  std::vector<vk::Image> swapchainImages;
  std::vector<vk::ImageView> swapchainImageViews;
  
  TextureShared depthBuffer;

public:
  WindowSwapchain(const WindowSwapchainCreateInfo &o = WindowSwapchainCreateInfo());
  virtual ~WindowSwapchain();

  void init() override;
  void next() override;
  void swap() override;
  void resize(int w, int h) override;
protected:
  void createSurface();
  void createSwapchain();
  void createDepthBuffer();
  void createRenderPass();
  void createFramebuffers();

  void destroySurface();
  void destroySwapchain();
  void destroyDepthBuffer();
  void destroyRenderPass();
  void destroyFramebuffers();
};