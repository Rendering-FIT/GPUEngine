#include <geVu/DeviceContext.h>
#include <iostream>
#include <vector>

#include <geVu/Context.h>
#include <geVu/Swapchain.h>
#include <geVu/MemoryManager.h>

using namespace ge::vu;
using namespace std;

DeviceContext::DeviceContext(const DeviceContextCreateInfo & o) {
  createInfo = o;
  context = o.context;
  validation = o.validation;
  verbose = o.verbose;

  createPhysicalDevice();
  createDevice();
  createCommandPool();
  createCommandBuffer();

  //memoryManager = make_shared<MemoryManager>(shared_from_this());
}

void ge::vu::DeviceContext::createMemoryManager(){
  memoryManager = make_shared<MemoryManager>(shared_from_this());
}

bool ge::vu::DeviceContext::isLayerSupported(std::string name) {
  auto n = physicalDevice.enumerateDeviceLayerProperties();
  for (auto &p : n) {
    if (p.layerName == name)return true;
  }
  return false;
}

bool ge::vu::DeviceContext::isExtensionSupported(std::string name) {
  auto n = physicalDevice.enumerateDeviceExtensionProperties();
  for (auto &p : n) {
    if (p.extensionName == name)return true;
  }
  return false;
}

SwapchainShared ge::vu::DeviceContext::createSwapchain(SwapchainCreateInfo & sci) {
  sci.deviceContext = shared_from_this();
  return make_shared<Swapchain>(sci);
}

void ge::vu::DeviceContext::changeImageLayout(vk::CommandBuffer buffer, vk::Image image, vk::ImageLayout oldLayout, vk::ImageLayout newLayout, vk::ImageAspectFlags imageAspect, int mipBase, int mipCount, int layerBase, int layerCount){


  vk::ImageMemoryBarrier imb;
  imb.oldLayout = oldLayout;
  imb.newLayout = newLayout;
  imb.image = image;
  imb.subresourceRange = vk::ImageSubresourceRange(imageAspect, mipBase, mipCount, 0, 1);

  auto layoutToFlags = [](vk::ImageLayout layout) {
    vk::AccessFlags ret;
    switch (layout) {
    case vk::ImageLayout::eTransferDstOptimal:
      ret = vk::AccessFlagBits::eTransferWrite;
      break;
    case vk::ImageLayout::eTransferSrcOptimal:
      ret = vk::AccessFlagBits::eTransferRead;
      break;
    case vk::ImageLayout::eColorAttachmentOptimal:
      ret = vk::AccessFlagBits::eColorAttachmentWrite;
      break;
    case vk::ImageLayout::eDepthStencilAttachmentOptimal:
      ret = vk::AccessFlagBits::eDepthStencilAttachmentWrite;
      break;
    case vk::ImageLayout::eShaderReadOnlyOptimal:
      ret = vk::AccessFlagBits::eShaderRead | vk::AccessFlagBits::eInputAttachmentRead;
      break;
    case vk::ImageLayout::ePresentSrcKHR:
      ret = vk::AccessFlagBits::eMemoryRead;
      break;
    }
    return ret;
  };

  imb.srcAccessMask = layoutToFlags(oldLayout);
  imb.dstAccessMask = layoutToFlags(newLayout);
  /*
  std::cout << "Change Layout " << image << " " << vk::to_string(oldLayout) << "->" << vk::to_string(newLayout) <<
    vk::to_string(imageAspect) << mipBase << "," << mipCount << "," << layerBase << "," << layerCount << " "
    <<vk::to_string(imb.srcAccessMask)<<" "<<vk::to_string(imb.dstAccessMask)<<"\n";
  */
  buffer.pipelineBarrier(
    vk::PipelineStageFlagBits::eTopOfPipe,
    vk::PipelineStageFlagBits::eTopOfPipe,
    vk::DependencyFlags(), 0, NULL, 0, NULL, 1, &imb);
}

void ge::vu::DeviceContext::flushCommandBuffer() {
  commandBuffer.end();
  vk::SubmitInfo si;
  si.commandBufferCount = 1;
  si.pCommandBuffers = &commandBuffer;

  queue.submit(si, 0);
  queue.waitIdle();

  //commandBuffer.reset(vk::CommandBufferResetFlagBits::eReleaseResources);
  commandBuffer.reset(vk::CommandBufferResetFlags());
  commandBuffer.begin(vk::CommandBufferBeginInfo(vk::CommandBufferUsageFlagBits::eSimultaneousUse));
}

void ge::vu::DeviceContext::createPhysicalDevice() {
  auto devices = context->getInstance().enumeratePhysicalDevices();
  int index = createInfo.deviceIndex;
  if (index < 0 || index >= devices.size()) {
    index = 0;
    if (verbose) std::cout << "Device index out of range\n";
  }
  physicalDevice = devices[index];
}

void ge::vu::DeviceContext::createDevice() {
  auto queueProps = physicalDevice.getQueueFamilyProperties();
  for (int i = 0; i < queueProps.size(); i++) {
    auto &q = queueProps[i];
    if (q.queueFlags & (vk::QueueFlagBits::eTransfer | vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eCompute)) {
      universalQueueIndex = i;
      break;
    }
  }
  assert(universalQueueIndex >= 0 && "Universal queue not found.");

  float priorities[1] = { 1.0 };
  vk::DeviceQueueCreateInfo dqci;
  dqci.queueCount = createInfo.queueCount;
  dqci.queueFamilyIndex = universalQueueIndex;
  dqci.pQueuePriorities = priorities;


  vector<const char*> enabledLayers;
  if (validation && isLayerSupported("VK_LAYER_LUNARG_standard_validation")) {
    enabledLayers.push_back("VK_LAYER_LUNARG_standard_validation");
  }

  vector<const char*> enabledExtensions;
  enabledExtensions.push_back("VK_KHR_swapchain");


  vk::DeviceCreateInfo dci;
  dci.queueCreateInfoCount = 1;
  dci.pQueueCreateInfos = &dqci;
  dci.enabledExtensionCount = (unsigned int)enabledExtensions.size();
  dci.ppEnabledExtensionNames = enabledExtensions.data();
  dci.enabledLayerCount = (unsigned int)enabledLayers.size();
  dci.ppEnabledLayerNames = enabledLayers.data();

  device = physicalDevice.createDevice(dci);
  queue = device.getQueue(universalQueueIndex, 0);
}

void ge::vu::DeviceContext::createCommandPool() {
  vk::CommandPoolCreateInfo cpci;
  cpci.queueFamilyIndex = universalQueueIndex;
  cpci.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
  commandPool = device.createCommandPool(cpci, 0);
}

void ge::vu::DeviceContext::createCommandBuffer() {
  vk::CommandBufferAllocateInfo cbai;
  cbai.commandPool = commandPool;
  cbai.commandBufferCount = 1;
  cbai.level = vk::CommandBufferLevel::ePrimary;

  commandBuffer = device.allocateCommandBuffers(cbai)[0];
  commandBuffer.begin(vk::CommandBufferBeginInfo(vk::CommandBufferUsageFlagBits::eSimultaneousUse));
}

void ge::vu::DeviceContext::createPipelineCache() {
  vk::PipelineCacheCreateInfo pipelineCacheInfo;
  pipelineCache = device.createPipelineCache(pipelineCacheInfo);
}