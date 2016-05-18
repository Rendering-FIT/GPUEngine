#pragma once

#include<geDE/Export.h>

namespace ge{
  namespace de{
    class FunctionRegister;
    GECORE_EXPORT void registerStdNumericFunctions(
        std::shared_ptr<FunctionRegister>const&fr);
  }
}
