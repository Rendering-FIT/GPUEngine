#pragma once

#ifdef WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <vulkan/vulkan.hpp>

#include "geVu/Export.h"

#define classShared(x) class GEVU_EXPORT x; typedef std::shared_ptr<x> x##Shared; typedef std::weak_ptr<x> x##Weak;

namespace ge {
	namespace vu {
		classShared(Context);
		classShared(ContextCreateInfo);
		classShared(DeviceContext);
		classShared(DeviceContextCreateInfo);
		classShared(Buffer);
		classShared(Texture);
		classShared(MemoryManager);
		classShared(MemoryManagerSimple);
		classShared(Swapchain);
		classShared(Pipeline);
	};
};

