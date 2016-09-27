#pragma once

#include<geUtil/Export.h>
#include<geUtil/ArgumentManager/ArgumentManager.h>
#include<geDE/VariableRegister.h>

namespace ge{
  namespace de{
    class FunctionRegister;
  }
  namespace util{
    GEUTIL_EXPORT void copyArgumentManager2VariableRegister(
        std::shared_ptr<de::VariableRegister> const&vr,
        ge::util::ArgumentManager const&argm   ,
        std::shared_ptr<de::FunctionRegister>const&tr);
  }
}

