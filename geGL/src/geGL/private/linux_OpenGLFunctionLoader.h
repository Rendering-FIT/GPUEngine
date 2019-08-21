#pragma once

#ifdef __linux__

namespace ge{
  namespace gl{
    class OpenGLFunctionLoader;
  }
}

#include <dlfcn.h>
#include <cstdlib>
#include <iostream>
#include <geGL/gegl_export.h>

class GEGL_EXPORT ge::gl::OpenGLFunctionLoader{
protected:
    bool triedToLoadOpenGL = false;
    bool triedToLoadGetProcAddress = false;
    void*openglLib = nullptr;
    using PROC = void(*)();
    using GETPROCTYPE = PROC(*)(uint8_t const*);
    GETPROCTYPE glXGetProcAddress = nullptr;
public:
    void*operator()(char const*name);
    ~OpenGLFunctionLoader();
};
#endif
