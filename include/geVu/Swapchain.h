#pragma once

#include <geVu/geVuClasses.h>

class ge::vu::Swapchain {
protected:
  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t imageCount = 0;
  uint32_t currentBuffer = 0;

  vk::RenderPass renderPass;
  std::vector<vk::Framebuffer> framebuffers;

  vk::Semaphore presentSemaphore = 0;
  DeviceContextShared deviceContext;
public:
  Swapchain(DeviceContextShared const& deviceContext);
  virtual ~Swapchain();

  virtual void init() = 0;
  virtual void next() = 0;
  virtual void swap() = 0;
  virtual void resize(int w, int h) = 0;

  int getImageCount() { return imageCount; }
  virtual vk::Semaphore getSemaphore() { return presentSemaphore; }
  virtual vk::RenderPass getRenderPass() { return renderPass; }
  virtual vk::Framebuffer getCurrentFrameBuffer() { return framebuffers[currentBuffer]; }
  virtual vk::Framebuffer getFrameBuffer(int i) { return framebuffers[i]; }
  //virtual vk::Image getCurrentImage() { return swapchainImages[currentImage]; }
  virtual int getWidth() { return width; }
  virtual int getHeight() { return height; }
};
