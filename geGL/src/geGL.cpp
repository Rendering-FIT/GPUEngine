#include<GPUEngine/geGL/OpenGL.h>
#include<GPUEngine/geGL/DefaultLoader.h>
#include<GPUEngine/geCore/ErrorPrinter/ErrorPrinter.h>
#include<cassert>

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
            else ge::core::printError(GE_CORE_FCENAME, "cannot open " + libName);
          }
          if (!this->_wglGetProcAddress){
            ge::core::printError(GE_CORE_FCENAME, "cannot load " + getProcAddressName);
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
#include<dlfcn.h>
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
            this->openglLib = dlopen(libName.c_str(),RTLD_LAZY);
          }
          if(!this->_triedToLoadGetProcAddress){
            this->_triedToLoadGetProcAddress = true;
            if(this->openglLib)
              reinterpret_cast<void*&>(this->_glXGetProcAddress) = dlsym(this->openglLib,getProcAddressName.c_str());
            else ge::core::printError(GE_CORE_FCENAME,"cannot open "+libName);
          }
          if(!this->_glXGetProcAddress){
            ge::core::printError(GE_CORE_FCENAME,"cannot load "+getProcAddressName);
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

    GEGL_EXPORT void*getProcAddress(char const*name){
      static OpenGLFunctionLoader loader{};
      return loader(name);
    }
  }
}


