#pragma once

#include <geVu/geVuClasses.h>

class ge::vu::SwapchainCreateInfo {
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


class ge::vu::Swapchain {
protected:
  SwapchainCreateInfo createInfo;
  uint32_t imageCount;
  uint32_t width;
  uint32_t height;

  vk::SurfaceKHR surface;
  vk::SurfaceFormatKHR surfaceFormat;
  vk::SwapchainKHR swapchain;
  std::vector<vk::Image> swapchainImages;
  std::vector<vk::ImageView> swapchainImageViews;
  uint32_t currentImage;

  vk::RenderPass renderPass;
  std::vector<vk::Framebuffer> framebuffers;

  vk::Semaphore semaphore = 0;
  
  TextureShared depthBuffer;

  DeviceContextShared deviceContext;

public:
  Swapchain(const SwapchainCreateInfo &o = SwapchainCreateInfo());
  ~Swapchain();

  void next();
  void swap();
  void resize(int w, int h);

  vk::Semaphore getSemaphore() { return semaphore; }
  vk::RenderPass getRenderPass() { return renderPass; }
  vk::Framebuffer getCurrentFrameBuffer() { return framebuffers[currentImage]; }
  vk::Image getCurrentImage() { return swapchainImages[currentImage]; }
  int getWidth() { return width; }
  int getHeight() { return height; }
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

  vk::Format bitsToFormat(int depthBits, int stencilBits);
};