#pragma once

#include <geVu/geVuClasses.h>

class ge::vu::Pipeline {
public:
  std::vector<vk::PipelineShaderStageCreateInfo> stages;

  std::vector<vk::VertexInputBindingDescription> vertexBindings;
  std::vector<vk::VertexInputAttributeDescription> vertexAttributes;

  vk::PipelineInputAssemblyStateCreateInfo primitive;
  vk::PipelineTessellationStateCreateInfo tessellation;
  vk::PipelineViewportStateCreateInfo viewport;
  vk::PipelineRasterizationStateCreateInfo rasterisation;
  vk::PipelineMultisampleStateCreateInfo multisample;
  vk::PipelineDepthStencilStateCreateInfo depthStencil;
  vk::StencilOpState stencilFrontOp;
  vk::StencilOpState stencilBackOp;
  std::vector<vk::PipelineColorBlendAttachmentState> attachments;
  std::vector<vk::DynamicState> dynamicStates;


  vk::PipelineLayout layout;
  vk::RenderPass renderPass;
  uint32_t subpass = 0;

  vk::Pipeline pipeline;

protected:
  DeviceContextShared deviceContext;

public:
  Pipeline(DeviceContextShared &deviceContext);
  ~Pipeline();

  operator vk::Pipeline() { return pipeline;}

  void create();
  void addStage(vk::ShaderStageFlagBits stage, vk::ShaderModule shader, const char* main = "main");
  void addAttribute(int bufferBinding, int location, vk::Format format, int offset);
  void addVertexBuffer(int bufferBinding, int stride);
};