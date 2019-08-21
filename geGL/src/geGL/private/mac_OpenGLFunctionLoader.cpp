#ifdef __APPLE__

#include <dlfcn.h>
#include <geGL/private/mac_OpenGLFunctionLoader.h>

/* About macOS frameworks:
 Some dynamic libraries are packed into frameworks in macOS. Function dlopen()
 is able to detect and search for frameworks if input path looks like framework
 path (e.g. /stuff/Foo.framework/Foo). Load them (or only it's part by adding
 additional subpath) by passing full framework name in format
 'Foo.framework/Foo' for framework named 'Foo'. Default fallback search paths
 (if DYLD_FALLBACK_FRAMEWORK_PATH was not set) ensure that framework is searched
 in usual directories (for more information see '$ man dlopen'):
     $HOME/Library/Frameworks, /Library/Frameworks, /Network/Library/Frameworks,
 /System/Library/Frameworks
 */

/** Wraps function dlopen() and print dlerror() message if error occured. */
void *dl_open_lib(char const *lib_name)
{
  void *lib = dlopen(lib_name, RTLD_LAZY);
  if (lib == NULL) fprintf(stderr, "dlopen(): %s\n", dlerror());
  return lib;
}

/** Wraps function dlclose() and print dlerror() message if error occured. */
int dl_close_lib(void *lib)
{
  int code = dlclose(lib);
  if (code) fprintf(stderr, "dlclose(): %s\n", dlerror());
  return code;
}

/** Loads framework by name using dl_open_lib(). This function is shortcut to
 easily load frameworks with just it's name. If framework name is NULL or empty
 string, the unchanged parameter is passed.
 Full framework name is computed only if given framework's name has length at
 least one character. */
void *dl_open_framework(const char *fw_name)
{
  if (fw_name == NULL) return dl_open_lib(NULL);
  const size_t fs = strlen(fw_name);
  if (fs <= 0) return dl_open_lib("");
  const char * e  = ".framework/";
  const size_t es = strlen(e);
  char *       s  = (char *)malloc(fs * 2 + es);
  s               = strncat(s, fw_name, fs);
  s               = strncat(s, e, es);
  s               = strncat(s, fw_name, fs);
  void *lib       = dl_open_lib(s);
  if (s) free(s);
  return lib;
}

void *ge::gl::OpenGLFunctionLoader::operator()(char const *name)
{
  if (!triedToLoadOpenGL) {
    /* Load OpenGL framework at default framework search directories.
     (Default OpenGL path: '/System/Library/Frameworks/OpenGL.framework') */
    const std::string frameworkName = "OpenGL";
    openglLib                 = dl_open_framework(frameworkName.c_str());
    if (!openglLib)
      throw std::runtime_error(
          "geGL::OpenGLFunctionLoader::operator() - cannot open " +
          frameworkName);

    triedToLoadOpenGL = true;
  }
  /* GL functions on OSX have been weak linked since OSX 10.2; this means that
   you can call them directly and unimplemented extensions will resolve to NULL.
   Note that this means that you must parse the extension string to determine if
   a function is valid or not, or your program will crash.
   Source: https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions#MacOSX
   */

  // TODO: glGetProcAddress (SDL?)
  return dlsym(openglLib, name);
}

ge::gl::OpenGLFunctionLoader::~OpenGLFunctionLoader()
{
  if (openglLib) dl_close_lib(openglLib);
  openglLib = nullptr;
}

#endif
