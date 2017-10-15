#pragma once

#include<geGL/gegl_export.h>
#include<memory>

namespace ge{
  namespace gl{
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
  }
}
