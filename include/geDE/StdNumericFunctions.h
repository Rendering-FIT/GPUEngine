#pragma once

#include<geDE/Export.h>

namespace ge{
  namespace de{
    class FunctionRegister;
    GEDE_EXPORT void registerStdNumericFunctions(
        std::shared_ptr<FunctionRegister>const&fr);
  }
}
