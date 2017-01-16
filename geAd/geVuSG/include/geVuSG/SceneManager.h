#pragma once

#include <geVu/geVu.h>
#include <geVuSG/geVuSGClasses.h>

#include <geSG/Mesh.h>

#include <unordered_map>

class ge::vusg::SceneManager {
protected:

  std::unordered_map<ge::sg::AttributeDescriptor*, ge::vu::BufferShared> buffers;
  
  std::unordered_map<ge::sg::Mesh*, ge::vu::VertexArray> vertexArrays;

  std::unordered_map<ge::sg::Mesh*, ge::vusg::DrawableShared> drawables;

  std::unordered_map<std::tuple<vk::PipelineLayout, ge::sg::MaterialImageComponent*>, vk::DescriptorSet> descriptors;


  ge::vu::DeviceContextShared deviceContext;
public:
  SceneManager(ge::vu::DeviceContextShared &deviceContext);

  DrawableShared getDrawable(ge::sg::Mesh* mesh);
  vk::DescriptorSet getDescriptor(vk::PipelineLayout pipelineLayout, ge::sg::MaterialImageComponent* img);

protected:
  void processMesh(ge::sg::Mesh* mesh);

  int semanticToBinding(ge::sg::AttributeDescriptor::Semantic semantic);
  vk::PrimitiveTopology sgPrimitiveToVkPrimitive(ge::sg::Mesh::PrimitiveType type);
};