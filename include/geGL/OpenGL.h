#pragma once

#include<geGL/Export.h>

#include<stdint.h>
#include<stddef.h>
#include<geGL/Generated/OpenGLTypes.h>
#include<geGL/Generated/OpenGLConstants.h>
#include<memory>

namespace ge{
  namespace gl{
    namespace opengl{
      class FunctionTable;
      using FunctionTablePointer = std::shared_ptr<FunctionTable>;
      class FunctionProvider;
      using FunctionProviderPointer = std::shared_ptr<FunctionProvider>;
    }
  }
}


