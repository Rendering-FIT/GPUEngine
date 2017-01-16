#pragma once
#include <geVu/geVuClasses.h>

class ge::vu::MemoryBlock {
public:
  vk::DeviceMemory memory = 0;
  vk::DeviceSize size = 0;
  vk::DeviceSize offset = 0;
  vk::MemoryPropertyFlags flags;
};