#pragma once

#include<geGL/Export.h>
#include<iostream>

namespace ge{
  namespace gl{
    GEGL_EXPORT std::string getNoiseSource();
    GEGL_EXPORT std::string getGradientSource();
  }
}
