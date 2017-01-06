#include <geVu/MemoryManager.h>

#include <geVu/DeviceContext.h>

using namespace ge::vu;

MemoryManager::MemoryManager(DeviceContextShared & deviceContext):deviceContext(deviceContext){
}

MemoryBlock MemoryManager::allocMemory(vk::Image img, vk::MemoryPropertyFlags memoryFlags) {
  auto &dev = deviceContext->getDevice();

  MemoryBlock memoryBlock;

  auto memReq = dev.getImageMemoryRequirements(img);
  auto memIndex = memoryTypeBitsToIndex(memReq.memoryTypeBits, memoryFlags);
  vk::MemoryAllocateInfo mai;
  mai.allocationSize = memReq.size;
  mai.memoryTypeIndex = memIndex;
  memoryBlock.memory = dev.allocateMemory(mai);
  memoryBlock.offset = 0;
  memoryBlock.size = memReq.size;
  return memoryBlock;
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