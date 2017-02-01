#include "geVu/Buffer.h"

#include <geVu/DeviceContext.h>
#include <geVu/MemoryManager.h>

using namespace ge::vu;
using namespace std;

Buffer::Buffer(DeviceContextShared deviceContext) :
  deviceContext(deviceContext) {

}

Buffer::~Buffer() {
  deviceContext->info("Buffer::~Buffer");
  auto dev = deviceContext->getDevice();
  if (buffer) {
    deviceContext->getMemoryManager()->freeMemory(memoryBlock);
    dev.destroyBuffer(buffer);
  }
}


void ge::vu::Buffer::create(vk::DeviceSize size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags memoryFlags) {
  deviceContext->info("Buffer::create", vk::to_string(usage), vk::to_string(memoryFlags));
  auto device = deviceContext->getDevice();

  vk::BufferCreateInfo bci;
  bci.usage = usage;
  bci.size = size;

  buffer = device.createBuffer(bci);

  memoryBlock = deviceContext->getMemoryManager()->allocMemory(buffer, memoryFlags);

  device.bindBufferMemory(buffer, memoryBlock.memory, memoryBlock.offset);

  this->usage = usage;
  this->size = size;
}

void ge::vu::Buffer::createVertexBuffer(vk::DeviceSize size) {
  create(size, vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferDst, vk::MemoryPropertyFlagBits::eDeviceLocal);
}

void ge::vu::Buffer::createIndexBuffer(vk::DeviceSize size) {
  create(size, vk::BufferUsageFlagBits::eIndexBuffer | vk::BufferUsageFlagBits::eTransferDst, vk::MemoryPropertyFlagBits::eDeviceLocal);
}

void ge::vu::Buffer::createStaggingBuffer(vk::DeviceSize size) {
  create(size, vk::BufferUsageFlagBits::eTransferSrc | vk::BufferUsageFlagBits::eTransferDst, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
}

void Buffer::createShaderStorage(vk::DeviceSize size, bool deviceLocal) {
  create(size, vk::BufferUsageFlagBits::eStorageBuffer,
         deviceLocal ? vk::MemoryPropertyFlagBits::eDeviceLocal :
           vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent
  );
}

void ge::vu::Buffer::setSubData(void* data, vk::DeviceSize size, vk::DeviceSize offset) {
  assert(size <= this->size - offset);
  if (memoryBlock.flags & vk::MemoryPropertyFlagBits::eDeviceLocal) {
    deviceContext->info("Buffer::setSubData staging transfer");
    // device - use staging buffer
    auto stagingBuffer = make_shared<Buffer>(deviceContext);
    stagingBuffer->create(size, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
    char* ptr = (char*)stagingBuffer->map();
    memcpy(ptr + offset, data, size);
    stagingBuffer->unmap();
    deviceContext->getCommandBuffer().copyBuffer(*stagingBuffer, buffer, {vk::BufferCopy(0, offset, size)});
    deviceContext->flushCommandBuffer();
  } else {
    // host - can map and write
    char* ptr = (char*)map();
    memcpy(ptr + offset, data, size);
    unmap();
  }
}

void* ge::vu::Buffer::map() {
  return deviceContext->getMemoryManager()->mapMemory(memoryBlock);
}

void ge::vu::Buffer::unmap() {
  deviceContext->getMemoryManager()->unmapMemory(memoryBlock);
}
