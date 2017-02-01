#pragma once

#include <gevu/geVuClasses.h>


namespace ge {
  namespace vu {
    size_t GEVU_EXPORT formatToSize(vk::Format format);
    vk::Format GEVU_EXPORT depthStencilBitsToFormat(int depthBits, int stencilBits);
  }
}