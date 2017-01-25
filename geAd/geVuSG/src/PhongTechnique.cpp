#include <geVu/Pipeline.h>

#include <geVuSG/PhongTechnique.h>
#include <geVuSG/SceneManager.h>
#include <geVuSG/Drawable.h>

#include <geSG/MatrixTransform.h>
#include <geSG/Node.h>
#include <ste/DAG.h>

#include <glm/gtx/string_cast.hpp>

using namespace ge::vu;
using namespace ge::vusg;
using namespace ge::sg;
using namespace std;

ge::vusg::PhongTechnique::PhongTechnique(ge::vu::DeviceContextShared & deviceContext, ge::vu::SwapchainShared &swapchain) :
  swapchain(swapchain), deviceContext(deviceContext) {
  sceneManager = make_shared<SceneManager>(deviceContext);

  vk::CommandBufferAllocateInfo cbai;
  cbai.commandPool = deviceContext->getCommandPool();
  cbai.commandBufferCount = 1;
  commandBuffer = deviceContext->getDevice().allocateCommandBuffers(cbai)[0];

  createPipelineLayout();
  createPipeline();
  
  deviceContext->flushCommandBuffer();
}


void ge::vusg::PhongTechnique::createDrawCommand() {
  int width = swapchain->getWidth();
  int height = swapchain->getHeight();

  commandBuffer.reset(vk::CommandBufferResetFlags());

  commandBuffer.begin(vk::CommandBufferBeginInfo(vk::CommandBufferUsageFlagBits::eSimultaneousUse));

  vk::ClearValue const clearValues[2] = {
    vk::ClearColorValue(std::array<float, 4>({ 0.2f, 0.2f, 0.2f, 0.2f })),
    vk::ClearDepthStencilValue(1.0f, 0u) };

  vk::RenderPassBeginInfo rpbi;
  rpbi.clearValueCount = 2;
  rpbi.pClearValues = clearValues;
  rpbi.framebuffer = swapchain->getCurrentFrameBuffer();
  rpbi.renderArea = vk::Rect2D(vk::Offset2D(0, 0), vk::Extent2D((uint32_t)width, (uint32_t)height));
  rpbi.renderPass = swapchain->getRenderPass();

  commandBuffer.beginRenderPass(rpbi, vk::SubpassContents::eInline);

  commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, *pipeline);

  commandBuffer.pushConstants<glm::mat4>(pipelineLayout, vk::ShaderStageFlagBits::eVertex, 0, { projection,view });

  vk::Viewport viewport;
  viewport.width = (float)width;
  viewport.height = (float)height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  commandBuffer.setViewport(0, 1, &viewport);

  vk::Rect2D scissor;
  scissor.offset = vk::Offset2D(0, 0);
  scissor.extent = vk::Extent2D(width, height);

  commandBuffer.setScissor(0, 1, &scissor);

  processNode(scene->rootNode);

  commandBuffer.endRenderPass();
  commandBuffer.end();
}

void ge::vusg::PhongTechnique::processNode(std::shared_ptr<ge::sg::MatrixTransformNode> node, glm::mat4 parentMatrix) {

  glm::mat4 currentMatrix = parentMatrix *(***node).getMatrix();

  commandBuffer.pushConstants<glm::mat4>(pipelineLayout, vk::ShaderStageFlagBits::eVertex, sizeof(glm::mat4) * 2, { currentMatrix });

  //std::cout << glm::to_string(currentMatrix)<<"\n";
  for (auto &mesh : (***node).meshes) {



    auto drawable = sceneManager->getDrawable(mesh.get());

    auto &material = mesh->material;
    auto diff = material->getComponent<MaterialImageComponent>(MaterialImageComponent::Semantic::diffuseTexture);
    auto desc = sceneManager->getDescriptor(descriptorSetLayout,diff.get());

    //auto desc = set;

    commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipelineLayout, 0, { desc }, {});

    drawable->draw(commandBuffer);
  }

  for (auto &c : node->children) {
    processNode(c, currentMatrix);
  }
}

void ge::vusg::PhongTechnique::createPipeline() {
  pipeline = make_shared<Pipeline>(deviceContext);

  pipeline->addStage(vk::ShaderStageFlagBits::eVertex,
    deviceContext->createShaderModule("D:/prac/GPUEngine/geAd/geVuSG/resources/phong.vert.spv"));
  pipeline->addStage(vk::ShaderStageFlagBits::eFragment,
    deviceContext->createShaderModule("D:/prac/GPUEngine/geAd/geVuSG/resources/phong.frag.spv"));
  pipeline->renderPass = swapchain->getRenderPass();
  pipeline->layout = pipelineLayout;
  pipeline->addAttribute(0, 0, vk::Format::eR32G32B32Sfloat, 0);
  pipeline->addAttribute(1, 1, vk::Format::eR32G32B32Sfloat, 0);
  pipeline->addAttribute(2, 2, vk::Format::eR32G32Sfloat, 0);
  pipeline->addVertexBuffer(0, sizeof(float) * 3);
  pipeline->addVertexBuffer(1, sizeof(float) * 3);
  pipeline->addVertexBuffer(2, sizeof(float) * 2);


  pipeline->create();
}

void ge::vusg::PhongTechnique::createPipelineLayout() {
  auto device = deviceContext->getDevice();

  vk::DescriptorSetLayoutBinding dslb;
  dslb.binding = 0;
  dslb.descriptorCount = 1;
  dslb.descriptorType = vk::DescriptorType::eCombinedImageSampler;
  dslb.stageFlags = vk::ShaderStageFlagBits::eFragment;

  vk::DescriptorSetLayoutCreateInfo dslci;
  dslci.bindingCount = 1;
  dslci.pBindings = &dslb;
  descriptorSetLayout = device.createDescriptorSetLayout(dslci);

  vk::PushConstantRange pc;
  pc.offset = 0;
  pc.size = sizeof(glm::mat4) * 3;
  pc.stageFlags = vk::ShaderStageFlagBits::eVertex;

  vk::PipelineLayoutCreateInfo plci;
  plci.setLayoutCount = 1;
  plci.pSetLayouts = &descriptorSetLayout;
  plci.pushConstantRangeCount = 1;
  plci.pPushConstantRanges = &pc;
  pipelineLayout = device.createPipelineLayout(plci);
}

void ge::vusg::PhongTechnique::frame() {
  auto &queue = deviceContext->getQueue();

  swapchain->next();

  createDrawCommand();

  vk::PipelineStageFlags flags = vk::PipelineStageFlagBits::eBottomOfPipe;
  vk::SubmitInfo si;
  si.waitSemaphoreCount = (1);
  si.pWaitSemaphores = (&swapchain->getSemaphore());
  si.pWaitDstStageMask = (&flags);
  si.commandBufferCount = (1);
  si.pCommandBuffers = (&commandBuffer);

  queue.submit(si, 0);
  queue.waitIdle();
  deviceContext->getDevice().waitIdle();
  swapchain->swap();

  queue.waitIdle();
}

void ge::vusg::PhongTechnique::setScene(std::shared_ptr<ge::sg::Scene> &scene) {
  this->scene = scene;
}
