#pragma once
namespace ge {
  namespace vu {
    class Context;
    class ContextOptions;
  };
};

#ifdef WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#include <vulkan/vulkan.hpp>

class ge::vu::ContextOptions {
public:
};

class ge::vu::Context {
public:
};