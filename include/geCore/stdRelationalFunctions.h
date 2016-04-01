#pragma once

namespace ge{
  namespace core{
    class FunctionRegister;
    GECORE_EXPORT void registerStdRelationalFunctions(
        std::shared_ptr<FunctionRegister>const&fr);
  }
}
