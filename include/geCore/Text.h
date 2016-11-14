#pragma once

#include<geCore/Export.h>
#include<iostream>

namespace ge{
  namespace core{
    GECORE_EXPORT std::string loadTextFile(std::string fileName);
    GECORE_EXPORT std::string processEscapeSequences(std::string data);
    GECORE_EXPORT bool isFloat(std::string text);
  }
}
