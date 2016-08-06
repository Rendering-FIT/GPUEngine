#pragma once

#include<memory>
#include<geDE/Export.h>

namespace ge{
  namespace de{
    class TypeRegister;
    GEDE_EXPORT void registerBasicTypes(std::shared_ptr<TypeRegister>const&tr);
  }
}
