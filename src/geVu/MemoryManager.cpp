#include <geVu/MemoryManager.h>

#include <geVu/DeviceContext.h>

using namespace ge::vu;

MemoryManager::MemoryManager(DeviceContextShared & deviceContext):deviceContext(deviceContext){
}

MemoryBlock ge::vu::MemoryManager::allocMemory(vk::MemoryRequirements req, vk::MemoryPropertyFlags memoryFlags){
  deviceContext->info("MemoryManager::allocMemory", req.size, vk::to_string(memoryFlags));
  auto &dev = deviceContext->getDevice();
  
  auto memIndex = memoryTypeBitsToIndex(req.memoryTypeBits, memoryFlags);
  vk::MemoryAllocateInfo mai;
  mai.allocationSize = req.size;
  mai.memoryTypeIndex = memIndex;

  MemoryBlock memoryBlock;
  memoryBlock.memory = dev.allocateMemory(mai);
  memoryBlock.offset = 0;
  memoryBlock.size = req.size;
  memoryBlock.flags = memoryFlags;
  return memoryBlock;
}

MemoryBlock MemoryManager::allocMemory(vk::Image img, vk::MemoryPropertyFlags memoryFlags) {
  auto &dev = deviceContext->getDevice();
  auto memReq = dev.getImageMemoryRequirements(img);
  return allocMemory(memReq, memoryFlags);
}

MemoryBlock ge::vu::MemoryManager::allocMemory(vk::Buffer img, vk::MemoryPropertyFlags memoryFlags){
  auto &dev = deviceContext->getDevice();
  auto memReq = dev.getBufferMemoryRequirements(img);
  return allocMemory(memReq, memoryFlags);
}

void * ge::vu::MemoryManager::mapMemory(MemoryBlock & memoryBlock){
  if (memoryBlock.memory && !(memoryBlock.flags&vk::MemoryPropertyFlagBits::eDeviceLocal)) {
    return deviceContext->getDevice().mapMemory(memoryBlock.memory, memoryBlock.offset, memoryBlock.size, vk::MemoryMapFlags());
  }
  return nullptr;
}

void ge::vu::MemoryManager::unmapMemory(MemoryBlock & memoryBlock){
  if (!memoryBlock.memory)return;
  auto &dev = deviceContext->getDevice();
  dev.unmapMemory(memoryBlock.memory);
}

void ge::vu::MemoryManager::freeMemory(MemoryBlock memoryBlock){
  if (!memoryBlock.memory)return;

  auto &dev = deviceContext->getDevice();
  dev.freeMemory(memoryBlock.memory);
}

uint32_t MemoryManager::memoryTypeBitsToIndex(uint32_t typeBits, vk::MemoryPropertyFlags requirements) {
  vk::PhysicalDeviceMemoryProperties prop = deviceContext->getPhysicalDevice().getMemoryProperties();
  auto mt = prop.memoryTypes;
  for (uint32_t i = 0; i < prop.memoryTypeCount; i++) {
    if ((typeBits & 1) && ((mt[i].propertyFlags&requirements) == requirements)) {
      return i;
    }
    typeBits >>= 1;
  }
  return -1;
}