#include <geVu/Pipeline.h>

#include <geVu/DeviceContext.h>

ge::vu::Pipeline::Pipeline(DeviceContextShared & deviceContext):
deviceContext(deviceContext){
  // default pipeline setting

  // input assembly
  primitive.primitiveRestartEnable = false;
  primitive.topology = vk::PrimitiveTopology::eTriangleList;

  //tessellation 
  tessellation.patchControlPoints = 0;

  //viewport 
  viewport.scissorCount = 1;
  viewport.viewportCount = 1;
  // no pointer - dynamic state

  //rasterisation
  rasterisation.cullMode = vk::CullModeFlagBits::eNone;
  rasterisation.depthBiasEnable = false;
  rasterisation.frontFace = vk::FrontFace::eCounterClockwise;
  rasterisation.lineWidth = 1.0f;
  rasterisation.polygonMode = vk::PolygonMode::eFill;
  rasterisation.rasterizerDiscardEnable = false;
  rasterisation.depthClampEnable = false;

  // multisample - use defaults
  //multisample. 

  // stencil
  stencilBackOp.failOp = vk::StencilOp::eKeep;
  stencilBackOp.passOp = vk::StencilOp::eKeep;
  stencilBackOp.depthFailOp = vk::StencilOp::eKeep;
  stencilBackOp.compareOp = vk::CompareOp::eAlways;
  stencilFrontOp.failOp = vk::StencilOp::eKeep;
  stencilFrontOp.passOp = vk::StencilOp::eKeep;
  stencilFrontOp.depthFailOp = vk::StencilOp::eKeep;
  stencilFrontOp.compareOp = vk::CompareOp::eAlways;

  // depth
  depthStencil.back = stencilBackOp;
  depthStencil.front = stencilFrontOp;

  depthStencil.depthCompareOp = vk::CompareOp::eLessOrEqual;
  depthStencil.depthBoundsTestEnable = false;
  depthStencil.depthTestEnable = true;
  depthStencil.depthWriteEnable = true;


  // attachments
  vk::PipelineColorBlendAttachmentState cbat;
  cbat.colorWriteMask = vk::ColorComponentFlagBits::eR |
    vk::ColorComponentFlagBits::eG |
    vk::ColorComponentFlagBits::eB |
    vk::ColorComponentFlagBits::eA;
  attachments.emplace_back(cbat);

  // default pipeline state
  dynamicStates.emplace_back(vk::DynamicState::eViewport);
  dynamicStates.emplace_back(vk::DynamicState::eScissor);
}

ge::vu::Pipeline::~Pipeline(){
  if (pipeline) {
    auto &device = deviceContext->getDevice();
    device.destroyPipeline(pipeline);
  }
}

void ge::vu::Pipeline::create(){
  auto &device = deviceContext->getDevice();

  if (pipeline) {
    device.destroyPipeline(pipeline);
  }

  auto dsi = vk::PipelineDynamicStateCreateInfo();
  dsi.dynamicStateCount = (uint32_t)dynamicStates.size();
  dsi.pDynamicStates = dynamicStates.data();

  auto cbsci = vk::PipelineColorBlendStateCreateInfo();
  cbsci.attachmentCount = (uint32_t)attachments.size();
  cbsci.pAttachments = attachments.data();


  auto vis = vk::PipelineVertexInputStateCreateInfo();
  vis.vertexAttributeDescriptionCount = (uint32_t)vertexAttributes.size();
  vis.pVertexAttributeDescriptions = vertexAttributes.data();
  vis.vertexBindingDescriptionCount = (uint32_t)vertexBindings.size();
  vis.pVertexBindingDescriptions = vertexBindings.data();

  auto gpci = vk::GraphicsPipelineCreateInfo();
  gpci.stageCount = (uint32_t)stages.size();
  gpci.pStages = stages.data();

  gpci.pVertexInputState = &vis;
  gpci.pInputAssemblyState = &primitive;
  gpci.pTessellationState = &tessellation;
  gpci.pViewportState = &viewport;
  gpci.pRasterizationState = &rasterisation;
  gpci.pMultisampleState = &multisample;
  gpci.pDepthStencilState = &depthStencil;
  gpci.pColorBlendState = &cbsci;
  gpci.pDynamicState = &dsi;

  gpci.renderPass = renderPass;
  gpci.layout = layout;
  gpci.subpass = subpass;

  gpci.basePipelineHandle = 0;
  gpci.basePipelineIndex = -1;

  pipeline = device.createGraphicsPipeline(deviceContext->getPipelineCache(), gpci);
}

void ge::vu::Pipeline::addStage(vk::ShaderStageFlagBits stage, vk::ShaderModule shader, const char * main){
  vk::PipelineShaderStageCreateInfo s;
  s.stage = stage;
  s.module = shader;
  s.pName = main;
  stages.emplace_back(s);
}

void ge::vu::Pipeline::addAttribute(int bufferBinding, int location, vk::Format format, int offset){
  vk::VertexInputAttributeDescription ad;
  ad.binding = bufferBinding;
  ad.format = format;
  ad.location = location;
  ad.offset = offset;
  vertexAttributes.push_back(ad);
}

void ge::vu::Pipeline::addVertexBuffer(int bufferBinding, int stride){
  vk::VertexInputBindingDescription bd;
  bd.binding = bufferBinding;
  bd.inputRate = vk::VertexInputRate::eVertex;
  bd.stride = stride;
  vertexBindings.emplace_back(bd);
}
