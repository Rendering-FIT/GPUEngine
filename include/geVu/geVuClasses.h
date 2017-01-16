#pragma once

#ifdef WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <vulkan/vulkan.hpp>

#include "geVu/Export.h"

#define geVu_class(x) class GEVU_EXPORT x; typedef std::shared_ptr<x> x##Shared; typedef std::weak_ptr<x> x##Weak;

namespace ge {
	namespace vu {
    geVu_class(Context);
    geVu_class(ContextCreateInfo);
    geVu_class(DeviceContext);
    geVu_class(DeviceContextCreateInfo);
    geVu_class(Buffer);
    geVu_class(Texture);
    geVu_class(MemoryBlock);
    geVu_class(MemoryManager);
    geVu_class(MemoryManagerAdvanced);
    geVu_class(SwapchainCreateInfo);
    geVu_class(Swapchain);
    geVu_class(Pipeline);
    geVu_class(VertexArray);
	};
};

