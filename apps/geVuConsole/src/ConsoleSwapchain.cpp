#include "ConsoleSwapchain.h"

#include <geVu/DeviceContext.h>
#include <geVu/Texture.h>
#include <geVu/Conversions.h>


#include <algorithm>
#include <iostream>

#include <iomanip>

#include "img.h"

using namespace ge::vu;
using namespace std;

ConsoleSwapchain::ConsoleSwapchain(const ConsoleSwapchainCreateInfo& o):
  Swapchain(o.deviceContext) {
  this->createInfo = o;

  this->width = o.fontWidth * o.charWidth;
  this->height = o.fontHeight * o.charHeight;
}

ConsoleSwapchain::~ConsoleSwapchain() {
  destroyBuffer();
  destroyPipeline();

  destroyDepthBuffer();
  destroyColorBuffer();
  destroyRenderPass();
  destroyFramebuffers();
}

void ConsoleSwapchain::init() {
  
  createPipeline(); 
  
  createDepthBuffer();
  createColorBuffer();
  createRenderPass();
  createFramebuffers();
  
  createFont();
  createBuffer();

  createDescriptors();
}

void ConsoleSwapchain::next() {
  auto queue = deviceContext->getQueue();
  vk::SubmitInfo si;
  si.signalSemaphoreCount = 1;
  si.pSignalSemaphores = &presentSemaphore;
  queue.submit({si}, 0);
}

void ConsoleSwapchain::swap() {
  auto dev = deviceContext->getDevice();
  auto cmd = deviceContext->getCommandBuffer();
  auto queue = deviceContext->getQueue();

  

  cmd.pipelineBarrier(vk::PipelineStageFlagBits::eAllGraphics, vk::PipelineStageFlagBits::eComputeShader, vk::DependencyFlags(), {}, {}, {});

  cmd.bindPipeline(vk::PipelineBindPoint::eCompute, computePipeline);
  cmd.bindDescriptorSets(vk::PipelineBindPoint::eCompute, pipelineLayout, 0, { descriptor }, {});

  cmd.dispatch(createInfo.charWidth, createInfo.charHeight, 1);


  deviceContext->flushCommandBuffer();

  int* ptr = (int*)buffer->map();

  HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(hstdout, &csbi);
  
  SetConsoleTextAttribute(hstdout, 0x0F);
  SetConsoleCursorPosition(hstdout, COORD{ 0,0 });
  for (int y = 0; y < createInfo.charHeight;y++) {
    for (int x = 0; x < createInfo.charWidth; x++) {
      int i = x + y*createInfo.charWidth;
      unsigned char c = ptr[i];
      if (c == 10)c = ' ';
      cout << setfill('0') <<setw(2) <<hex <<ptr[i] <<" ";
      //cout << ptr[i] <<" ";

      //int color = (ptr[i] >> 16) & 0xF;
      //SetConsoleTextAttribute(hstdout, color);
      //cout << hex<< color;
      //cout << c;

      if (i % createInfo.charWidth == createInfo.charWidth-1)cout << "\n";
    }    
  }

  SetConsoleTextAttribute(hstdout, csbi.wAttributes);
  buffer->unmap();

}

void ConsoleSwapchain::resize(int w, int h) {
}

void ConsoleSwapchain::createDepthBuffer() {
  auto depthBufferFormat = depthStencilBitsToFormat(createInfo.depthBufferBits, createInfo.stencilBufferBits);
  depthBuffer = make_shared<Texture>(deviceContext);
  depthBuffer->createDepthRenderBuffer(depthBufferFormat, width, height);
}

void ConsoleSwapchain::createColorBuffer() {
  deviceContext->info("ConsoleSwapchain::createColorBuffer");
  auto device = deviceContext->getDevice();

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
  deviceContext->info("ConsoleSwapchain::createPipeline");
  auto dev = deviceContext->getDevice();

  vk::DescriptorSetLayoutBinding dslb[3];
  dslb[0].binding = 0;
  dslb[0].descriptorCount = 1;
  dslb[0].descriptorType = vk::DescriptorType::eStorageBuffer;
  dslb[0].stageFlags = vk::ShaderStageFlagBits::eCompute;

  dslb[1].binding = 1;
  dslb[1].descriptorCount = 1;
  dslb[1].descriptorType = vk::DescriptorType::eStorageImage;
  dslb[1].stageFlags = vk::ShaderStageFlagBits::eCompute;

  dslb[2].binding = 2;
  dslb[2].descriptorCount = 1;
  dslb[2].descriptorType = vk::DescriptorType::eStorageImage;
  dslb[2].stageFlags = vk::ShaderStageFlagBits::eCompute;
  
  vk::DescriptorSetLayoutCreateInfo dslci;
  dslci.bindingCount = 3;
  dslci.pBindings = dslb;
  descriptorSetLayout = dev.createDescriptorSetLayout(dslci);

  vk::PipelineLayoutCreateInfo plci;
  plci.setLayoutCount = 1;
  plci.pSetLayouts = &descriptorSetLayout;
  plci.pushConstantRangeCount = 0;
  plci.pPushConstantRanges = nullptr;
  pipelineLayout = dev.createPipelineLayout(plci);


  vk::PipelineShaderStageCreateInfo pssci;
  pssci.stage = vk::ShaderStageFlagBits::eCompute;
  pssci.module = deviceContext->createShaderModule("D:/prac/GPUEngine/apps/geVuConsole/resources/console.comp.spv");
  pssci.pName = "main";

  vk::ComputePipelineCreateInfo cpci;
  cpci.stage = pssci;
  cpci.layout = pipelineLayout;

  computePipeline = dev.createComputePipeline(deviceContext->getPipelineCache(), cpci);
}

void ConsoleSwapchain::createBuffer() {
  deviceContext->info("ConsoleSwapchain::createBuffer");
  auto device = deviceContext->getDevice();

  buffer = make_shared<Buffer>(deviceContext);
  buffer->createShaderStorage(sizeof(int) * createInfo.charWidth*createInfo.charHeight, false);
}

void ConsoleSwapchain::createFont() {
  deviceContext->info("ConsoleSwapchain::createFont");

  fontTexture = make_shared<Texture>(deviceContext);
  fontTexture->createColorSampled(vk::Format::eR8G8B8A8Unorm,img0.width,img0.height);
  fontTexture->setData(img0.data);
}

void ConsoleSwapchain::createDescriptors() {
  auto device = deviceContext->getDevice();

  vk::DescriptorPoolSize dps[2];
  dps[0].descriptorCount = 2;
  dps[0].type = vk::DescriptorType::eStorageImage;

  dps[1].descriptorCount = 1;
  dps[1].type = vk::DescriptorType::eStorageBuffer;

  vk::DescriptorPoolCreateInfo dpci;
  dpci.maxSets = 1;
  dpci.poolSizeCount = 2;
  dpci.pPoolSizes = dps;

  auto pool = device.createDescriptorPool(dpci);

  vk::DescriptorSetAllocateInfo dsai;
  dsai.descriptorPool = pool;
  dsai.descriptorSetCount = 1;
  dsai.pSetLayouts = &descriptorSetLayout;

  descriptor = device.allocateDescriptorSets(dsai)[0];

  vk::DescriptorImageInfo dii[2];
  dii[0].imageView = colorBuffer->getImageView();
  dii[0].imageLayout = vk::ImageLayout::eShaderReadOnlyOptimal;

  dii[1].imageView = fontTexture->getImageView();
  dii[1].imageLayout = vk::ImageLayout::eShaderReadOnlyOptimal;

  vk::DescriptorBufferInfo dbi;
  dbi.buffer = *buffer;
  dbi.offset = 0;
  dbi.range = buffer->getSize();

  vk::WriteDescriptorSet wds[3];
  wds[0].descriptorCount = 1;
  wds[0].dstSet = descriptor;
  wds[0].dstBinding = 0;
  wds[0].descriptorType = vk::DescriptorType::eStorageBuffer;
  wds[0].pBufferInfo = &dbi;

  wds[1].descriptorCount = 1;
  wds[1].dstSet = descriptor;
  wds[1].dstBinding = 1;
  wds[1].descriptorType = vk::DescriptorType::eStorageImage;
  wds[1].pImageInfo = &dii[0];

  wds[2].descriptorCount = 1;
  wds[2].dstSet = descriptor;
  wds[2].dstBinding = 2;
  wds[2].descriptorType = vk::DescriptorType::eStorageImage;
  wds[2].pImageInfo = &dii[1];

  device.updateDescriptorSets(3,wds,0,nullptr);
}

void ConsoleSwapchain::destroyBuffer() {
  buffer = nullptr;
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
