#pragma once

#include<geCore/dtemplates.h>

namespace ge{
  namespace core{
    class GECORE_EXPORT Token{
      public:
        using Type = size_t;
        using Data = std::string;
        Token(Type const& type,Data const& rawData = "");
        Data rawData;
        Type type;
        Token();
    };
  }
}
