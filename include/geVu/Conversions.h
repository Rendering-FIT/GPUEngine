#pragma once

#include <gevu/geVuClasses.h>


namespace ge {
  namespace vu {
    size_t formatToSize(vk::Format format);
    vk::Format depthStencilBitsToFormat(int depthBits, int stencilBits);
  }
}