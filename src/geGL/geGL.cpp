#include<geGL/OpenGL.h>
#include<geGL/DefaultLoader.h>
#include<geCore/ErrorPrinter.h>

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
    class GEGL_EXPORT LoaderOpenGLFunction{
      public:
        void*operator()(char const*name){
          (void)name;
          assert(false&&"TODO");
          return nullptr;
        }
    };
#else
#include<dlfcn.h>
    class GEGL_EXPORT LoaderOpenGLFunction{
      protected:
        bool _triedToLoadOpenGL = false;
        bool _triedToLoadGetProcAddress = false;
        void*openglLib = nullptr;
        using PROC = void(*)();
        using GETPROCTYPE = PROC(*)(uint8_t const*);
        GETPROCTYPE _glXGetProcAddress = nullptr;
      public:
        void*operator()(char const*name){
          if(!this->_triedToLoadOpenGL){
            this->_triedToLoadOpenGL = true;
            this->openglLib = dlopen("libGL.so.1",RTLD_LAZY);
          }
          if(!this->_triedToLoadGetProcAddress){
            this->_triedToLoadGetProcAddress = true;
            if(this->openglLib)
              reinterpret_cast<void*&>(this->_glXGetProcAddress) = dlsym(this->openglLib,"glXGetProcAddress");
            else ge::core::printError(GE_CORE_FCENAME,"cannot open libGL.so.1");
          }
          if(!this->_glXGetProcAddress){
            ge::core::printError(GE_CORE_FCENAME,"cannot load glXGetProcAddress");
            return nullptr;
          }
          return (void*)this->_glXGetProcAddress((uint8_t const*)(name));
        }
        ~LoaderOpenGLFunction(){
          if(openglLib)dlclose(this->openglLib);
          this->openglLib = nullptr;
        }
    };
#endif

    GEGL_EXPORT void*getProcAddress(char const*name){
      static LoaderOpenGLFunction loader{};
      return loader(name);
    }
  }
}


