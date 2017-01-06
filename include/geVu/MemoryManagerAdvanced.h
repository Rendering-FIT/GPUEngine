#pragma once
#include <geVu/geVuClasses.h>

#include <geVu/MemoryManager.h>

class ge::vu::MemoryManagerAdvanced: public ge::vu::MemoryManager {
public:
  MemoryManagerAdvanced(DeviceContextShared &deviceContext);
};