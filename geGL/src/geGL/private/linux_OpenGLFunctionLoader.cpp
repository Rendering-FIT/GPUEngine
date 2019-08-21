#ifdef __linux__

#include <geGL/private/linux_OpenGLFunctionLoader.h>

using namespace std;

void* ge::gl::OpenGLFunctionLoader::operator()(char const* name)
{
  const string libName            = "libGL.so.1";
  const string getProcAddressName = "glXGetProcAddress";
  if (!triedToLoadOpenGL) {
    triedToLoadOpenGL = true;
    openglLib         = dlopen(libName.c_str(), RTLD_LAZY);
  }
  if (!triedToLoadGetProcAddress) {
    triedToLoadGetProcAddress = true;
    if (openglLib)
      reinterpret_cast<void*&>(glXGetProcAddress) =
          dlsym(openglLib, getProcAddressName.c_str());
    else
      throw runtime_error(
          "geGL::OpenGLFunctionLoader::operator() - cannot open " + libName);
  }
  if (!glXGetProcAddress) {
    throw runtime_error(
        "geGL::OpenGLFunctionLoader::operator() - cannot load " +
        getProcAddressName);
    return nullptr;
  }
  return (void*)glXGetProcAddress((uint8_t const*)(name));
}

ge::gl::OpenGLFunctionLoader::~OpenGLFunctionLoader()
{
  if (openglLib) dlclose(openglLib);
  openglLib = nullptr;
}

#endif
