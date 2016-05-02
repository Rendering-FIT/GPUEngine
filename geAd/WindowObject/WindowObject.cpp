#include<geAd/WindowObject/WindowObject.h>

#include<iostream>
#include<cassert>

using namespace ge::util;

SDLEventProc::SDLEventProc(bool pooling){
  assert(this!=nullptr);
  SDL_Init(SDL_INIT_VIDEO);
  this->m_pooling = pooling;
}

void SDLEventProc::addWindow(
    std::string               const&name  ,
    std::shared_ptr<SDLWindow>const&window){
  assert(this!=nullptr);
  assert(window!=nullptr);
  this->m_windows[name] = window;
  this->m_id2Name[window->getId()] = name;
}

bool SDLEventProc::hasWindow(std::string const&name)const{
  assert(this!=nullptr);
  return this->m_windows.count(name)!=0;
}

void SDLEventProc::removeWindow(std::string const&name){
  assert(this!=nullptr);
  this->m_id2Name.erase(this->getWindow(name)->getId());
  this->m_windows.erase(name);
}

std::shared_ptr<SDLWindow>const&SDLEventProc::getWindow(
    std::string const&name)const{
  assert(this!=nullptr);
  assert(this->m_windows.count(name)!=0);
  return this->m_windows.find(name)->second;
}

void SDLEventProc::operator()(){
  assert(this!=nullptr);
  this->m_running = true;
  SDL_Event event;
  while(this->m_running){
    if(this->m_windows.size() == 0){
      this->m_running = false;
      break;
    }
    if(!this->m_pooling)
      SDL_WaitEvent(&event);
    while(true){
      if(this->m_pooling)
        if(!SDL_PollEvent(&event))break;
      auto windowIter = this->m_id2Name.find(event.window.windowID);
      if(windowIter == this->m_id2Name.end())continue;
      auto window = this->m_windows[windowIter->second];
      if(window->hasEventCallback(event.type))
        window->callEventCallback(event.type,event);
      if(!this->m_pooling)
        if(!SDL_PollEvent(&event))break;
    }
    for(auto const&x:this->m_windows)
      if(x.second->hasIdleCallback())
        x.second->callIdleCallback();
  }
}

SDLWindow::SDLWindow(uint32_t width,uint32_t height){
  assert(this!=nullptr);
  Uint32 flags = SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN;
  this->m_window  = SDL_CreateWindow("",0,0,width,height,flags);
}

SDLWindow::~SDLWindow(){
  assert(this!=nullptr);
  SDL_DestroyWindow(this->m_window);
}

bool SDLWindow::createContext(
    std::string const&name   ,
    uint32_t          version,
    Profile           profile,
    Flag              flags  ){
  assert(this!=nullptr);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, version/100    );
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,(version%100)/10);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK ,profile         );
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS        ,flags           );
  SharedSDLContext ctx = std::shared_ptr<SDL_GLContext>(
      new SDL_GLContext,
      [&](SDL_GLContext*ctx){if(*ctx)SDL_GL_DeleteContext(*ctx);delete ctx;});
  *ctx = SDL_GL_CreateContext(this->m_window);
  if(*ctx == nullptr)
    return false;
  this->m_contexts[name] = ctx;
  return true;
}


void SDLWindow::setContext(
    std::string const&name     ,
    SDLWindow   const&other    ,
    std::string const&otherName){
  assert(this!=nullptr);
  assert(other.m_contexts.count(otherName)!=0);
  this->m_contexts[name] = other.m_contexts.find(otherName)->second;
}

void SDLWindow::makeCurrent(std::string const&name)const{
  assert(this!=nullptr);
  assert(this->m_contexts.count(name)!=0);
  SDL_GL_MakeCurrent(this->m_window,*this->m_contexts.find(name)->second);
}

void SDLWindow::swap()const{
  assert(this!=nullptr);
  SDL_GL_SwapWindow(this->m_window);
}

unsigned SDLWindow::getId()const{
  assert(this!=nullptr);
  return SDL_GetWindowID(this->m_window);
}

void SDLWindow::setEventCallback(
    EventType        const&eventType,
    EventCallback    const&callback ,
    CallbackUserData const&userData ){
  assert(this!=nullptr);
  this->m_eventCallbacks[eventType] = EventCallbackWithData(callback,userData);
}

void SDLWindow::setIdleCallback(
    Callback         const&callback,
    CallbackUserData const&userData){
  assert(this!=nullptr);
  this->m_idleCallback = CallbackWithData(callback,userData);
}

bool SDLWindow::hasEventCallback(
    EventType const&eventType)const{
  assert(this!=nullptr);
  auto ii = this->m_eventCallbacks.find(eventType);
  return ii!=this->m_eventCallbacks.end() && std::get<CALLBACK>(ii->second)!=nullptr;
}

bool SDLWindow::hasIdleCallback()const{
  assert(this!=nullptr);
  return std::get<CALLBACK>(this->m_idleCallback)!=nullptr;
}

void SDLWindow::callEventCallback(
    EventType const&eventType,
    SDL_Event const&event    ){
  assert(this!=nullptr);
  assert(this->m_eventCallbacks.count(eventType)!=0);
  assert(std::get<CALLBACK>(this->m_eventCallbacks[eventType])!=nullptr);
  auto const&cwd = this->m_eventCallbacks[eventType];
  std::get<CALLBACK>(cwd)(std::get<USERDATA>(cwd),event);
}

void SDLWindow::callIdleCallback(){
  assert(this!=nullptr);
  assert(std::get<CALLBACK>(this->m_idleCallback)!=nullptr);
  std::get<CALLBACK>(this->m_idleCallback)(std::get<USERDATA>(this->m_idleCallback));
}


void SDLWindow::setSize(uint32_t width,uint32_t heght){
  assert(this!=nullptr);
  SDL_SetWindowSize(this->m_window,width,heght);
}

uint32_t SDLWindow::getWidth()const{
  assert(this!=nullptr);
  int size[2];
  SDL_GetWindowSize(this->m_window,size+0,size+1);
  return size[0];
}

uint32_t SDLWindow::getHeight()const{
  assert(this!=nullptr);
  int size[2];
  SDL_GetWindowSize(this->m_window,size+0,size+1);
  return size[1];
}

