#pragma once
#include <geVu/geVuClasses.h>

class ge::vu::MemoryBlock {
public:
  vk::DeviceMemory memory;
  vk::DeviceSize size;
  vk::DeviceSize offset;
};