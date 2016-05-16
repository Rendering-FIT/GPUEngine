#include<geAd/SDLWindow/SDLWindow.h>
#include<geAd/SDLWindow/SDLEventProc.h>
#include<geAd/SDLWindow/EventCallbackInterface.h>

#include<iostream>
#include<cassert>

using namespace ge::util;

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

SDLWindow::WindowId SDLWindow::getId()const{
  assert(this!=nullptr);
  return SDL_GetWindowID(this->m_window);
}

void SDLWindow::setEventCallback(
    EventType            const&eventType,
    EventCallbackPointer const&callback ){
  assert(this!=nullptr);
  this->m_eventCallbacks[eventType] = callback;
}

bool SDLWindow::hasEventCallback(
    EventType const&eventType)const{
  assert(this!=nullptr);
  auto ii = this->m_eventCallbacks.find(eventType);
  return ii!=this->m_eventCallbacks.end() && ii->second != nullptr;
}

void SDLWindow::callEventCallback(
    EventType        const&eventType,
    EventDataPointer const&event    ){
  assert(this!=nullptr);
  assert(this->m_eventCallbacks.count(eventType)!=0);
  assert(this->m_eventCallbacks[eventType] != nullptr);
  (*this->m_eventCallbacks[eventType])(event);
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

void SDLWindow::setFullscreen(Fullscreen const&type){
  SDL_SetWindowFullscreen(this->m_window,type);
}
