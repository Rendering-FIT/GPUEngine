#pragma once

#include <geVuSG/geVuSGClasses.h>

#include <geVu/geVu.h>

#include <geSG/Scene.h>

#include <glm/glm.hpp>

#include <geVuSG/Drawable.h>

class ge::vusg::PhongTechnique {
protected:
  std::shared_ptr<ge::sg::Scene> scene;

  vk::CommandBuffer commandBuffer;
  SceneManagerShared sceneManager;
  ge::vu::SwapchainShared swapchain;
  ge::vu::DeviceContextShared deviceContext;

  ge::vu::PipelineShared pipeline;
  vk::PipelineLayout pipelineLayout;
  vk::DescriptorSetLayout descriptorSetLayout;

  
public:
  PhongTechnique(ge::vu::DeviceContextShared &deviceContext, ge::vu::SwapchainShared &swapchain);
  ~PhongTechnique() {}

  
  void frame();

  void setScene(std::shared_ptr<ge::sg::Scene> &scene);

  // temporary, will be removed
  glm::mat4 projection;
  glm::mat4 view;
  glm::vec3 lightPosition;

protected:
  void createDrawCommand();
  void processNode(std::shared_ptr<ge::sg::MatrixTransformNode> node, glm::mat4 parentMatrix = glm::mat4());
  void createPipeline();
  void createPipelineLayout();
};