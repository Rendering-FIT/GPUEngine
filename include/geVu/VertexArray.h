#pragma once

#include <geVu/geVuClasses.h>

#include <vector>

class ge::vu::VertexArray {
protected:
  std::vector < std::tuple<int, BufferShared, vk::DeviceSize>> vertexBuffers;
  
  BufferShared indexBuffer;
  vk::DeviceSize indexBufferOffset;

public:
  VertexArray();
  void bind(vk::CommandBuffer cmd);


  void addVertexBuffer(int binding, BufferShared &buffer, vk::DeviceSize offset=0) {
    vertexBuffers.emplace_back(binding, buffer, offset);
  }

  void setIndexBuffer(BufferShared &buffer, vk::DeviceSize offset = 0) {
    indexBuffer = buffer, indexBufferOffset = offset;
  }

};