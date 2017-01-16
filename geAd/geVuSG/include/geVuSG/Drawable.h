#pragma once

#include <geVu/geVu.h>

#include <geVuSG/geVuSGClasses.h>
#include <geSG/Mesh.h>
#include <geSG/Material.h>


class ge::vusg::Drawable {
public:
  ge::vu::VertexArrayShared vertexArray;

  vk::PrimitiveTopology primitive = vk::PrimitiveTopology::eTriangleList;

  int vertexCount = 0;
  int instanceCount = 1;
  int firstVertex = 0;
  int firstInstance = 0;

  bool indexed = false;
  int firstIndex = 0;
  int vertexOffset = 0;
  
  void draw(vk::CommandBuffer cb);
};