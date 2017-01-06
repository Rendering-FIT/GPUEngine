#pragma once
#include <geVu/geVuClasses.h>

#include <geVu/Context.h>

class ge::vu::DeviceContextCreateInfo {
public:
  ContextShared context;
  int deviceIndex;
  bool validation = true;
  bool verbose = true;
  int queueCount = 1;
};

class ge::vu::DeviceContext : public std::enable_shared_from_this<ge::vu::DeviceContext> {
protected:
  void createPhysicalDevice();
  void createDevice();
  void createCommandPool();
  void createCommandBuffer();
  void createPipelineCache();

  DeviceContextCreateInfo createInfo;
  bool validation;
  bool verbose;
  ContextShared context;
  vk::PhysicalDevice physicalDevice;
  vk::Device device;
  int universalQueueIndex = -1;

  vk::CommandBuffer commandBuffer;
  vk::CommandPool commandPool;
  vk::PipelineCache pipelineCache;
  vk::Queue queue;

public:
  DeviceContext(const DeviceContextCreateInfo &o = DeviceContextCreateInfo());

  bool isLayerSupported(std::string name);
  bool isExtensionSupported(std::string name);

  SwapchainShared createSwapchain(SwapchainCreateInfo &sci);

  vk::Instance getInstance() { return context->getInstance(); }
  vk::PhysicalDevice getPhysicalDevice() { return physicalDevice; }
  vk::Device getDevice() { return device; }
  int getUnivesalQueueIndex() { return universalQueueIndex; }

  void changeImageLayout(vk::CommandBuffer buffer, vk::Image image,
    vk::ImageLayout oldLayout, vk::ImageLayout newLayout,
    vk::ImageAspectFlagBits imageAspect = vk::ImageAspectFlagBits::eColor,
    int mipCount = 1, int mipBase = 0,
    int layerBase = 0, int layerCount = 1);

  vk::CommandBuffer getCommandBuffer() { return commandBuffer; }
  void flushCommandBuffer();

};