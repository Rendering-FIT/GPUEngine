#pragma once

#include<cstddef>
#include<vector>

namespace ge{
  namespace de{
    ///<constructor, destructor pointer
    using CDPtr = void(*)(void*);
    ///<type identificator
    using TypeId = size_t;
    ///<ticks of resources
    using Ticks = size_t;
    ///<function identificator
    using FunctionId = size_t;
    ///<function input index
    using InputIndex = size_t;
    ///<vector that describle composite type
    using TypeDescriptionVector = std::vector<size_t>;
  }
}
