#pragma once
#include <geVu/geVuClasses.h>

#include <geVu/Context.h>

#include <geVu/Logger.h>

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

  MemoryManagerShared memoryManager;

public:
  DeviceContext(const DeviceContextCreateInfo &o = DeviceContextCreateInfo());
  void createMemoryManager();

  bool isLayerSupported(std::string name);
  bool isExtensionSupported(std::string name);

  SwapchainShared createSwapchain(SwapchainCreateInfo &sci);

  vk::Instance getInstance() { return context->getInstance(); }
  vk::PhysicalDevice getPhysicalDevice() { return physicalDevice; }
  vk::Device getDevice() { return device; }
  int getUnivesalQueueIndex() { return universalQueueIndex; }


  vk::CommandBuffer getCommandBuffer() { return commandBuffer; }
  vk::CommandPool getCommandPool() { return commandPool; }
  vk::Queue getQueue() { return queue; }

  MemoryManagerShared getMemoryManager() { return memoryManager; }
  vk::PipelineCache getPipelineCache() { return pipelineCache; }

  bool isVerbose() { return verbose; }
  bool isValidation() { return validation; }


  template<class...Args>
  void info(Args...args) {if(verbose) ge::vu::log(std::cout,args...); }

  template<class...Args>
  void error(Args...args) { ge::vu::log(std::cerr, args...); }


  void changeImageLayout(vk::CommandBuffer buffer, vk::Image image,
    vk::ImageLayout oldLayout, vk::ImageLayout newLayout,
    vk::ImageAspectFlags imageAspect = vk::ImageAspectFlagBits::eColor,
    int mipBase = 0, int mipCount = 1,
    int layerBase = 0, int layerCount = 1);
  void flushCommandBuffer();


  vk::ShaderModule createShaderModule(std::string str);
  vk::ShaderModule createShaderModule(std::vector<char> &data);

protected:
  void createPhysicalDevice();
  void createDevice();
  void createCommandPool();
  void createCommandBuffer();
  void createPipelineCache();
};