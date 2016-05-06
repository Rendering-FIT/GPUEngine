#pragma once

#include<geGL/Export.h>
#include<memory>

namespace ge{
  namespace gl{
    namespace opengl{
      class FunctionTable;
      using FunctionTablePointer = FunctionTable*;//std::shared_ptr<FunctionTable>;
      class GEGL_EXPORT Capabilities{
        public:
          bool opengl200 = false;
          bool opengl210 = false;
          bool opengl300 = false;
          bool opengl310 = false;
          bool opengl320 = false;
          bool opengl330 = false;
          bool opengl400 = false;
          bool opengl410 = false;
          bool opengl420 = false;
          bool opengl430 = false;
          bool opengl440 = false;
          bool opengl450 = false;
      };

      GEGL_EXPORT void fillCapabilities(
          Capabilities&capabilities,
          FunctionTablePointer const&table);
    }
  }
}
