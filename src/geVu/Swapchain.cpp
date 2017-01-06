#include <geVu/Swapchain.h>

#include <geVu/DeviceContext.h>
#include <geVu/Texture.h>

#include <algorithm>
#include <iostream>

using namespace ge::vu;
using namespace std;

Swapchain::Swapchain(const SwapchainCreateInfo & o) :createInfo(o) {
  deviceContext = o.deviceContext;
  
  createSurface();
  createSwapchain();
  createDepthBuffer();
  createRenderPass();
  createFramebuffers();
}

Swapchain::~Swapchain() {
  deviceContext->getDevice().destroySwapchainKHR(swapchain);
  deviceContext->getInstance().destroySurfaceKHR(surface);
}

void ge::vu::Swapchain::next(){
  if(semaphore)
    deviceContext->getDevice().destroySemaphore(semaphore);
  semaphore = deviceContext->getDevice().createSemaphore(vk::SemaphoreCreateInfo());
  auto i = deviceContext->getDevice().acquireNextImageKHR(swapchain, UINT64_MAX, semaphore, 0);
  currentImage = i.value;
}

void ge::vu::Swapchain::swap(){
  vk::PresentInfoKHR pi;
  pi.swapchainCount = (1);
  pi.pSwapchains = &swapchain;
  pi.pImageIndices = &currentImage;
  deviceContext->getQueue().presentKHR(pi);
}

void Swapchain::createSurface() {
#ifdef WIN32
  vk::Win32SurfaceCreateInfoKHR wsci;
  wsci.hinstance = createInfo.hinstance;
  wsci.hwnd = createInfo.hwnd;
  surface = deviceContext->getInstance().createWin32SurfaceKHR(wsci);
  auto surfaceFormats = deviceContext->getPhysicalDevice().getSurfaceFormatsKHR(surface);
  surfaceFormat = surfaceFormats[0];
  

  assert(deviceContext->getPhysicalDevice().getSurfaceSupportKHR(deviceContext->getUnivesalQueueIndex(), surface));

#else
  //@TODO
  assert("No pinguins" && 0);
#endif
}

void Swapchain::createSwapchain() {
  auto &physicalDevice = deviceContext->getPhysicalDevice();
  auto &device = deviceContext->getDevice();

  auto surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
  auto presentModes = physicalDevice.getSurfacePresentModesKHR(surface);



  auto isModeSupported = [&](vk::PresentModeKHR mode) {
    return find(presentModes.begin(), presentModes.end(), mode) != presentModes.end();
  };

  vk::PresentModeKHR presentMode = vk::PresentModeKHR::eImmediate;

  if (createInfo.vsync) {
    if (isModeSupported(vk::PresentModeKHR::eFifo))
      presentMode = vk::PresentModeKHR::eFifo;
    if (isModeSupported(vk::PresentModeKHR::eFifoRelaxed))
      presentMode = vk::PresentModeKHR::eFifoRelaxed;
  }
  else {
    if (isModeSupported(vk::PresentModeKHR::eMailbox))
      presentMode = vk::PresentModeKHR::eMailbox;
  }

  imageCount = createInfo.imageCount;
  imageCount = (std::min)(imageCount, surfaceCapabilities.maxImageCount);
  imageCount = (std::max)(imageCount, surfaceCapabilities.minImageCount);

  auto transform = surfaceCapabilities.currentTransform;

  vk::SwapchainCreateInfoKHR sci;
  sci.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
  sci.imageArrayLayers = 1;
  sci.imageColorSpace = surfaceFormat.colorSpace;
  sci.imageExtent = surfaceCapabilities.currentExtent;
  sci.imageFormat = surfaceFormat.format;
  sci.imageSharingMode = vk::SharingMode::eExclusive;
  sci.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;
  sci.minImageCount = imageCount;
  sci.oldSwapchain = swapchain;
  sci.pQueueFamilyIndices = NULL;
  sci.presentMode = presentMode;
  sci.preTransform = transform;
  sci.queueFamilyIndexCount = 0;
  sci.surface = surface;

  swapchain = device.createSwapchainKHR(sci);

  swapchainImages = device.getSwapchainImagesKHR(swapchain);

  width = surfaceCapabilities.currentExtent.width;
  height = surfaceCapabilities.currentExtent.height;

  for (auto &img : swapchainImages) {
    vk::ImageViewCreateInfo ivci;
    ivci.format = surfaceFormat.format;
    ivci.image = img;
    ivci.subresourceRange = vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1);
    ivci.viewType = vk::ImageViewType::e2D;
    deviceContext->changeImageLayout(deviceContext->getCommandBuffer(), img, vk::ImageLayout::eUndefined, vk::ImageLayout::ePresentSrcKHR);
    swapchainImageViews.emplace_back(device.createImageView(ivci));
  }
}

void Swapchain::createDepthBuffer() {
  auto depthBufferFormat = bitsToFormat(createInfo.depthBufferBits, createInfo.stencilBufferBits);
  depthBuffer = make_shared<Texture>(deviceContext);
  depthBuffer->createDepthBuffer(depthBufferFormat, width, height);
  depthBuffer->setLayout(deviceContext->getCommandBuffer(), vk::ImageLayout::eDepthStencilAttachmentOptimal);
}

vk::Format ge::vu::Swapchain::bitsToFormat(int depthBits, int stencilBits){
  if (depthBits == 32) {
    if (stencilBits == 8)
      return vk::Format::eD32SfloatS8Uint;
    else
      return vk::Format::eD32Sfloat;
  }else if(depthBits == 24){
    return vk::Format::eD24UnormS8Uint;
  } else if (depthBits == 16) {
    if (stencilBits == 8)
      return vk::Format::eD16UnormS8Uint;
    else
      return vk::Format::eD16Unorm;
  }
}

void Swapchain::createRenderPass() {
  vk::AttachmentDescription attachments[2];
  attachments[0].format = surfaceFormat.format;
  attachments[0].loadOp = vk::AttachmentLoadOp::eClear;
  attachments[0].storeOp = vk::AttachmentStoreOp::eStore;
  attachments[0].stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
  attachments[0].stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
  attachments[0].initialLayout = vk::ImageLayout::eColorAttachmentOptimal;
  attachments[0].finalLayout = vk::ImageLayout::ePresentSrcKHR;

  attachments[1].format = depthBuffer->getFormat();
  attachments[1].loadOp = vk::AttachmentLoadOp::eClear;
  attachments[1].storeOp = vk::AttachmentStoreOp::eDontCare;
  attachments[1].stencilLoadOp = vk::AttachmentLoadOp::eClear;
  attachments[1].stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
  attachments[1].initialLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
  attachments[1].finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

  vk::AttachmentReference colorReference(0, vk::ImageLayout::eColorAttachmentOptimal);
  vk::AttachmentReference depthReference(1, vk::ImageLayout::eDepthStencilAttachmentOptimal);

  vk::SubpassDescription subpass;
  subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &colorReference;
  subpass.pDepthStencilAttachment = &depthReference;

  vk::RenderPassCreateInfo rpci;
  rpci.attachmentCount = 2;
  rpci.pAttachments = attachments;
  rpci.subpassCount = 1;
  rpci.pSubpasses = &subpass;

  renderPass = deviceContext->getDevice().createRenderPass(rpci, 0);
}

void Swapchain::createFramebuffers() {
  vk::ImageView attachments[2];
  attachments[1] = depthBuffer->getImageView();

  vk::FramebufferCreateInfo fbci;
  fbci.renderPass = renderPass;
  fbci.attachmentCount = 2;
  fbci.pAttachments = attachments;
  fbci.width = width;
  fbci.height = height;
  fbci.layers = 1;

  for (int i = 0; i < swapchainImages.size(); i++) {
    attachments[0] = swapchainImageViews[i];
    framebuffers.emplace_back(deviceContext->getDevice().createFramebuffer(fbci));
  }
}