#include<geGL/OpenGL.h>
#include<geGL/DefaultLoader.h>
#include<cassert>
#include<string>

namespace ge{
  namespace gl{
    GEGL_EXPORT void init(std::shared_ptr<FunctionLoaderInterface>const&loader){
      auto table = ge::gl::createTable(loader);
      ge::gl::setDefaultFunctionTable(table);
      ge::gl::setDefaultContext(ge::gl::createContext(table));
    }
    GEGL_EXPORT void init(GET_PROC_ADDRESS getProcAddress){
      auto loader = std::make_shared<DefaultLoader>(getProcAddress);
      init(loader);
    }


#if defined(_MSC_VER)
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
    class GEGL_EXPORT OpenGLFunctionLoader{
      protected:
        bool _triedToLoadOpenGL = false;
        bool _triedToLoadGetProcAddress = false;
        HMODULE _openglLib = nullptr;
        using PROC = int(*)();
        using WGLGETPROCADDRESS = PROC(__stdcall*)(LPCSTR);
        WGLGETPROCADDRESS _wglGetProcAddress = nullptr;
      public:
        void*operator()(char const*name){
          assert(this != nullptr);
          const std::string libName = "opengl32.dll";
          const std::string getProcAddressName = "wglGetProcAddress";
          if (!this->_triedToLoadOpenGL){
            this->_triedToLoadOpenGL = true;
            this->_openglLib = LoadLibrary(TEXT(libName.c_str()));
          }
          if (!this->_triedToLoadGetProcAddress){
            this->_triedToLoadGetProcAddress = true;
            if (this->_openglLib)
              this->_wglGetProcAddress = (WGLGETPROCADDRESS)GetProcAddress(this->_openglLib, TEXT(getProcAddressName.c_str()));
            else throw std::runtime_error(std::string("geGL::OpenGLFunctionLoader::operator() - cannot open ") + libName);
          }
          if (!this->_wglGetProcAddress){
            throw std::runtime_error(std::string("geGL::OpenGLFunctionLoader::operator() - cannot load ") + getProcAddressName);
            return nullptr;
          }
          auto ret = (void*)this->_wglGetProcAddress(name);
          if (ret) return ret;
          return (void*)GetProcAddress(this->_openglLib, TEXT(name));
        }
        ~OpenGLFunctionLoader(){
          if (this->_openglLib)FreeLibrary(this->_openglLib);
          this->_openglLib = nullptr;
        }
    };
#else
#include <dlfcn.h>
#if __APPLE__
      /** Wraps function dlopen() and print dlerror() message if error occured. */
      void* dl_open_lib(char const *lib_name) {
          void* lib = dlopen(lib_name, RTLD_LAZY);
          if (lib == NULL)
              fprintf(stderr, "dlopen(): %s\n", dlerror());
          return lib;
      }
      
      /** Wraps function dlclose() and print dlerror() message if error occured. */
      int dl_close_lib(void *lib) {
          int code = dlclose(lib);
          if (code)
              fprintf(stderr, "dlclose(): %s\n", dlerror());
          return code;
      }
      
      /* About macOS frameworks:
       Some dynamic libraries are packed into frameworks in macOS. Function dlopen() is able to detect and search
       for frameworks if input path looks like framework path (e.g. /stuff/Foo.framework/Foo). Load them (or only
       it's part by adding additional subpath) by passing full framework name in format 'Foo.framework/Foo' for
       framework named 'Foo'. Default fallback search paths (if DYLD_FALLBACK_FRAMEWORK_PATH was not set) ensure
       that framework is searched in usual directories (for more information see '$ man dlopen'):
           $HOME/Library/Frameworks, /Library/Frameworks, /Network/Library/Frameworks, /System/Library/Frameworks
       */
      
      /** Loads framework by name using dl_open_lib(). This function is shortcut to easily load frameworks
       with just it's name. If framework name is NULL or empty string, the unchanged parameter is passed.
       Full framework name is computed only if given framework's name has length at least one character. */
      void* dl_open_framework(const char *fw_name) {
          if (fw_name == NULL)
              return dl_open_lib(NULL);
          const size_t fs = strlen(fw_name);
          if (fs <= 0)
              return dl_open_lib("");
          const char *e = ".framework/";
          const size_t es = strlen(e);
          char *s = (char *)malloc(fs * 2 + es);
          s = strncat(s, fw_name, fs);
          s = strncat(s, e, es);
          s = strncat(s, fw_name, fs);
          void* lib = dl_open_lib(s);
          if (s) free(s);
          return lib;
      }
      
      class GEGL_EXPORT OpenGLFunctionLoader {
      protected:
          bool _triedToLoadOpenGL = false;
          void* openglLib = nullptr;
      public:
          void* operator() (char const*name) {
              if (!this->_triedToLoadOpenGL) {
                  
                  /* Load OpenGL framework at default framework search directories.
                   (Default OpenGL path: '/System/Library/Frameworks/OpenGL.framework') */
                  const std::string frameworkName = "OpenGL";
                  this->openglLib = dl_open_framework(frameworkName.c_str());
                  if (!this->openglLib)
                      throw std::runtime_error("geGL::OpenGLFunctionLoader::operator() - cannot open " + frameworkName);
                  
                  this->_triedToLoadOpenGL = true;
              }
              /* GL functions on OSX have been weak linked since OSX 10.2; this means that
               you can call them directly and unimplemented extensions will resolve to NULL.
               Note that this means that you must parse the extension string to determine if
               a function is valid or not, or your program will crash.
               Source: https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions#MacOSX
               */
              
              // TODO: glGetProcAddress (SDL?)
              return dlsym(this->openglLib, name);
          }
          ~OpenGLFunctionLoader() {
              if (openglLib) dl_close_lib(this->openglLib);
              this->openglLib = nullptr;
          }
      };
#else
      class GEGL_EXPORT OpenGLFunctionLoader{
      protected:
          bool _triedToLoadOpenGL = false;
          bool _triedToLoadGetProcAddress = false;
          void*openglLib = nullptr;
          using PROC = void(*)();
          using GETPROCTYPE = PROC(*)(uint8_t const*);
          GETPROCTYPE _glXGetProcAddress = nullptr;
      public:
          void*operator()(char const*name){
              const std::string libName = "libGL.so.1";
              const std::string getProcAddressName = "glXGetProcAddress";
              if(!this->_triedToLoadOpenGL){
                  this->_triedToLoadOpenGL = true;
                  this->openglLib = dlopen(libName.c_str(), RTLD_LAZY);
              }
              if(!this->_triedToLoadGetProcAddress){
                  this->_triedToLoadGetProcAddress = true;
                  if(this->openglLib)
                      reinterpret_cast<void*&>(this->_glXGetProcAddress) = dlsym(this->openglLib,getProcAddressName.c_str());
                  else throw std::runtime_error("geGL::OpenGLFunctionLoader::operator() - cannot open "+libName);
              }
              if(!this->_glXGetProcAddress){
                  throw std::runtime_error("geGL::OpenGLFunctionLoader::operator() - cannot load " + getProcAddressName);
                  return nullptr;
              }
              return (void*)this->_glXGetProcAddress((uint8_t const*)(name));
          }
          ~OpenGLFunctionLoader(){
              if(openglLib)dlclose(this->openglLib);
              this->openglLib = nullptr;
          }
      };
#endif
#endif

    GEGL_EXPORT void*getProcAddress(char const*name){
      static OpenGLFunctionLoader loader{};
      return loader(name);
    }
  }
}


