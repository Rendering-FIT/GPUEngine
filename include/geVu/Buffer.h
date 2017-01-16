#pragma once

#include <geVu/geVuClasses.h>
#include <geVu/MemoryBlock.h>

class ge::vu::Buffer {
protected:
  vk::Buffer buffer;
  vk::BufferUsageFlags usage;
  vk::DeviceSize size;
  MemoryBlock memoryBlock;

  DeviceContextShared deviceContext;
public:
  Buffer(DeviceContextShared deviceContext);
  ~Buffer();

  void create(vk::DeviceSize size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags memoryFlags);

  void createVertexBuffer(vk::DeviceSize size);
  void createIndexBuffer(vk::DeviceSize size);

  void setSubData(void* data, vk::DeviceSize size, vk::DeviceSize offset);

  void* map();
  void unmap();

  operator vk::Buffer() { return buffer;}
};