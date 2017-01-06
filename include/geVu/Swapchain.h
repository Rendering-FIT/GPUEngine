#pragma once

#include <geVu/geVuClasses.h>

class ge::vu::SwapchainCreateInfo {
public:
#ifdef WIN32
  HWND hwnd;
  HINSTANCE hinstance;
#endif
  int depthBufferBits = 24;
  int stencilBufferBits = 0;
  bool vsync = true;
  int imageCount = 2;
  DeviceContextShared deviceContext;
};


class ge::vu::Swapchain {
protected:
  void createSurface();
  void createSwapchain();
  void createDepthBuffer();

  SwapchainCreateInfo createInfo;
  uint32_t imageCount;
  uint32_t width;
  uint32_t height;

  vk::SurfaceKHR surface;
  vk::SurfaceFormatKHR surfaceFormat;
  vk::SwapchainKHR swapchain;
  std::vector<vk::Image> swapchainImages;
  std::vector<vk::ImageView> swapchainImageViews;

  vk::Image depthBufferImage;
  vk::ImageView depthBufferView;
  vk::Format depthBufferFormat;
  vk::DeviceMemory depthBufferMemory;

  DeviceContextShared deviceContext;

public:
  Swapchain(const SwapchainCreateInfo &o = SwapchainCreateInfo());
  ~Swapchain();
};