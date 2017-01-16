#pragma once
#include <geVu/geVuClasses.h>

#include <geVu/MemoryBlock.h>

class ge::vu::MemoryManager : public std::enable_shared_from_this<ge::vu::MemoryManager> {
protected:
  DeviceContextShared deviceContext;

public:
  MemoryManager(DeviceContextShared &deviceContext);

  virtual MemoryBlock allocMemory(vk::MemoryRequirements req, vk::MemoryPropertyFlags memoryFlags);
  virtual MemoryBlock allocMemory(vk::Image img, vk::MemoryPropertyFlags memoryFlags);
  virtual MemoryBlock allocMemory(vk::Buffer img, vk::MemoryPropertyFlags memoryFlags);

  virtual void* mapMemory(MemoryBlock &memoryBlock);
  virtual void unmapMemory(MemoryBlock &memoryBlock);

  virtual void freeMemory(MemoryBlock memoryBlock);

  uint32_t MemoryManager::memoryTypeBitsToIndex(uint32_t typeBits, vk::MemoryPropertyFlags requirements);
};