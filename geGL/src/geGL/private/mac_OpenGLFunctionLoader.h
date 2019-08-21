#pragma once

#ifdef __APPLE__

class ge::gl::OpenGLFunctionLoader {
 public:
  void* operator()(char const* name);
  ~OpenGLFunctionLoader();

 protected:
  bool  triedToLoadOpenGL = false;
  void* openglLib          = nullptr;
};
#endif
