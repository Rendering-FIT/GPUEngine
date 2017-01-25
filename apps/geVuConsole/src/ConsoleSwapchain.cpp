#include "ConsoleSwapchain.h"

#include <geVu/DeviceContext.h>
#include <geVu/Texture.h>
#include <geVu/Conversions.h>


#include <algorithm>
#include <iostream>

using namespace ge::vu;
using namespace std;

ConsoleSwapchain::ConsoleSwapchain(const ConsoleSwapchainCreateInfo& o):
  Swapchain(o.deviceContext) {
  this->createInfo = o;

  this->width = o.fontWidth * o.charWidth;
  this->height = o.fontHeight * o.charHeight;
}

ConsoleSwapchain::~ConsoleSwapchain() {
  destroyPipeline(); 
  
  destroyDepthBuffer();
  destroyColorBuffer();
  destroyRenderPass();
  destroyFramebuffers();  
}

void ConsoleSwapchain::init() {
  createDepthBuffer();
  createColorBuffer();
  createRenderPass();
  createFramebuffers();
  
  createPipeline();
}

void ConsoleSwapchain::next() {
}

void ConsoleSwapchain::swap() {
  auto dev = deviceContext->getDevice();
  auto cmd = deviceContext->getCommandBuffer();
  auto queue = deviceContext->getQueue();



  cmd.pipelineBarrier(vk::PipelineStageFlagBits::eAllGraphics, vk::PipelineStageFlagBits::eComputeShader, vk::DependencyFlags(), {}, {}, {});

  cmd.bindPipeline(vk::PipelineBindPoint::eCompute,computePipeline);

  cmd.dispatch(1,1,1);


  vk::PipelineStageFlags flags = vk::PipelineStageFlagBits::eBottomOfPipe;
  vk::SubmitInfo si;
  si.waitSemaphoreCount = (0);
  si.pWaitSemaphores = nullptr;
  si.pWaitDstStageMask = (&flags);
  si.commandBufferCount = (1);
  si.pCommandBuffers = (&cmd);
  si.pSignalSemaphores = &presentSemaphore;
  si.signalSemaphoreCount = 1;

  queue.submit(si, 0);
}

void ConsoleSwapchain::resize(int w, int h) {
}

void ConsoleSwapchain::createDepthBuffer() {
  auto depthBufferFormat = depthStencilBitsToFormat(createInfo.depthBufferBits, createInfo.stencilBufferBits);
  depthBuffer = make_shared<Texture>(deviceContext);
  depthBuffer->createDepthRenderBuffer(depthBufferFormat, width, height);
}

void ConsoleSwapchain::createColorBuffer() {
  colorBuffer = make_shared<Texture>(deviceContext);
  colorBuffer->createColorAttachment(vk::Format::eR8G8B8A8Unorm, width, height);
}

void ConsoleSwapchain::createRenderPass() {
  vk::AttachmentDescription attachments[2];
  attachments[0].format = colorBuffer->getFormat();
  attachments[0].loadOp = vk::AttachmentLoadOp::eClear;
  attachments[0].storeOp = vk::AttachmentStoreOp::eStore;
  attachments[0].stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
  attachments[0].stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
  attachments[0].initialLayout = vk::ImageLayout::eUndefined;
  attachments[0].finalLayout = vk::ImageLayout::eShaderReadOnlyOptimal;

  attachments[1].format = depthBuffer->getFormat();
  attachments[1].loadOp = vk::AttachmentLoadOp::eClear;
  attachments[1].storeOp = vk::AttachmentStoreOp::eDontCare;
  attachments[1].stencilLoadOp = vk::AttachmentLoadOp::eClear;
  attachments[1].stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
  attachments[1].initialLayout = vk::ImageLayout::eUndefined;
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

void ConsoleSwapchain::createFramebuffers() {
  vk::ImageView attachments[2];
  attachments[0] = colorBuffer->getImageView();
  attachments[1] = depthBuffer->getImageView();

  vk::FramebufferCreateInfo fbci;
  fbci.renderPass = renderPass;
  fbci.attachmentCount = 2;
  fbci.pAttachments = attachments;
  fbci.width = width;
  fbci.height = height;
  fbci.layers = 1;

  framebuffers.emplace_back(deviceContext->getDevice().createFramebuffer(fbci));
}

void ConsoleSwapchain::createPipeline() {  
  auto dev = deviceContext->getDevice();

  vk::PipelineShaderStageCreateInfo pssci;
  pssci.stage = vk::ShaderStageFlagBits::eCompute;
  //pssci.module = deviceContext->createShaderModule();

  vk::ComputePipelineCreateInfo cpci;
  //cpci.stage = 

  dev.createComputePipeline(deviceContext->getPipelineCache(), cpci);
}

void ConsoleSwapchain::destroyPipeline() {
  auto dev = deviceContext->getDevice();
  dev.destroyPipeline(computePipeline);
}

void ConsoleSwapchain::destroyDepthBuffer() {
  depthBuffer = nullptr;
}

void ConsoleSwapchain::destroyColorBuffer() {
  colorBuffer = nullptr;
}

void ConsoleSwapchain::destroyRenderPass() {
  auto dev = deviceContext->getDevice();
  dev.destroyRenderPass(renderPass);
}

void ConsoleSwapchain::destroyFramebuffers() {
  auto dev = deviceContext->getDevice();
  for (auto& f:framebuffers)
    dev.destroyFramebuffer(f);
}
