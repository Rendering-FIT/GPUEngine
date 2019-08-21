#include <SDLWin.h>

#include<SDL.h>
#include<stdexcept>

class SDLWinImpl{
  public:
    SDLWinImpl(int w,int h,int version,SDLWin::ContextType type){
      if(SDL_Init(SDL_INIT_VIDEO)<0)
        throw std::runtime_error(std::string("SDLWin::SDL_Init failed - ")+SDL_GetError());
      window = SDL_CreateWindow("",0,0,w,h,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_HIDDEN);
      if(!window)throw std::runtime_error(std::string("SDLWin::SDL_CreateWindow failed - ") + SDL_GetError());

      int typeVal = SDL_GL_CONTEXT_PROFILE_CORE;
      if(type == SDLWin::ContextType::CORE)typeVal = SDL_GL_CONTEXT_PROFILE_CORE;
      if(type == SDLWin::ContextType::COMPATIBILITY)typeVal = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY;
      if(type == SDLWin::ContextType::ES)typeVal = SDL_GL_CONTEXT_PROFILE_ES;

      if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, typeVal)<0)
        throw std::runtime_error(std::string("SDLWin::SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK) - ")+SDL_GetError());
      if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, version/100)<0)
        throw std::runtime_error(std::string("SDLWin::SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION) - ")+SDL_GetError());
      if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, (version/10)%10)<0)
        throw std::runtime_error(std::string("SDLWin::SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION) - ")+SDL_GetError());
      if(SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8)<0)
        throw std::runtime_error(std::string("SDLWin::SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE) - ")+SDL_GetError());
      if(SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24)<0)
        throw std::runtime_error(std::string("SDLWin::SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE) - ")+SDL_GetError());

      context = SDL_GL_CreateContext(window);
      if(!context)throw std::runtime_error(std::string("SDLWin::SDL_GL_CreateContext - ")+SDL_GetError());
    }
    ~SDLWinImpl(){
      SDL_GL_DeleteContext(context);
      SDL_DestroyWindow(window);
      SDL_Quit();
    }
    void beginFrame(){
      SDL_Event event;
      while (SDL_PollEvent(&event));
    }
    void endFrame(){
      SDL_GL_SwapWindow(window);
    }
    SDL_Window*window = nullptr;
    SDL_GLContext context;
};

SDLWin::SDLWin(int w,int h,int version,ContextType type){
  try{
    impl = new SDLWinImpl(w,h,version,type);
  }catch(std::runtime_error&e){
    delete impl;
    throw e;
  }
}

SDLWin::~SDLWin(){
  delete impl;
}

void SDLWin::beginFrame(){
  impl->beginFrame();
}

void SDLWin::endFrame(){
  impl->endFrame();
}
