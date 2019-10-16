#ifdef _MSC_VER

#include <geGL/private/windows_OpenGLFunctionLoader.h>
#include <cassert>
#include <iostream>

using namespace std;

void* ge::gl::OpenGLFunctionLoader::operator()(char const* name)
{
  assert(this != nullptr);
  const string libName            = "opengl32.dll";
  const string getProcAddressName = "wglGetProcAddress";
  if (!triedToLoadOpenGL) {
    triedToLoadOpenGL = true;
    openglLib         = LoadLibrary(TEXT(libName.c_str()));
  }
  if (!triedToLoadGetProcAddress) {
    triedToLoadGetProcAddress = true;
    if (openglLib)
      wglGetProcAddress = (WGLGETPROCADDRESS)GetProcAddress(
          openglLib, TEXT(getProcAddressName.c_str()));
    else
      throw runtime_error(
          string("geGL::OpenGLFunctionLoader::operator() - cannot open ") +
          libName);
  }
  if (!wglGetProcAddress) {
    throw runtime_error(
        string("geGL::OpenGLFunctionLoader::operator() - cannot load ") +
        getProcAddressName);
    return nullptr;
  }
  auto ret = (void*)wglGetProcAddress(name);
  if (ret) return ret;
  return (void*)GetProcAddress(openglLib, TEXT(name));
}

ge::gl::OpenGLFunctionLoader::~OpenGLFunctionLoader()
{
  if (openglLib) FreeLibrary(openglLib);
  openglLib = nullptr;
}

#endif
