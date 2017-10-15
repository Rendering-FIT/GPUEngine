#pragma once

#include<geGL/gegl_export.h>
#include<iostream>

namespace ge{
  namespace gl{
    GEGL_EXPORT std::string getNoiseSource();
    GEGL_EXPORT std::string getGradientSource();
  }
}
