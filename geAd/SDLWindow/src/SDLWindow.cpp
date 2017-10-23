#include<GPUEngine/geAd/SDLWindow/SDLWindow.h>
#include<GPUEngine/geAd/SDLWindow/SDLMainLoop.h>
#include<GPUEngine/geCore/ErrorPrinter/ErrorPrinter.h>

#include<iostream>
#include<cassert>

using namespace ge::ad;

/**
 * @brief Creates new SDLWindow
 *
 * @param width width of new window
 * @param height height of new window
 */
SDLWindow::SDLWindow(uint32_t width,uint32_t height){
  assert(this!=nullptr);
  Uint32 flags = SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE;
  this->m_window  = SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,flags);
  if(!this->m_window){
    ge::core::printError(GE_CORE_FCENAME,SDL_GetError(),width,height);
  }
  this->setWindowEventCallback(SDL_WINDOWEVENT_CLOSE,std::bind(&SDLWindow::m_defaultCloseCallback,this,std::placeholders::_1));
}

/**
 * @brief Destroys SDLWindow
 */
SDLWindow::~SDLWindow(){
  assert(this!=nullptr);
  //free contexts, otherwise it would cause memory leak on gpu (according to CodeXL)
  this->m_contexts.clear();
  SDL_DestroyWindow(this->m_window);
}

/**
 * @brief Creates new (GL) context for this window
 *
 * @param name new of new context
 * @param version context version 450, 440, 430, ...
 * @param profile context profile
 * @param flags context flags, debug context ...
 *
 * @return return true if context was created successfully
 */
bool SDLWindow::createContext(
    std::string const&name   ,
    uint32_t          version,
    Profile           profile,
    Flag              flags  ){
  assert(this!=nullptr);
  if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, version/100    )<0){
    ge::core::printError(GE_CORE_FCENAME,SDL_GetError(),name,version);
    return false;
  }
  if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,(version%100)/10)<0){
    ge::core::printError(GE_CORE_FCENAME,SDL_GetError(),name,version);
    return false;
  }
  if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK ,profile         )<0){
    ge::core::printError(GE_CORE_FCENAME,SDL_GetError(),name,version);
    return false;
  }
  if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS        ,flags           )<0){
    ge::core::printError(GE_CORE_FCENAME,SDL_GetError(),name,version);
    return false;
  }
  SharedSDLContext ctx = std::shared_ptr<SDL_GLContext>(
      new SDL_GLContext,
      [&](SDL_GLContext*ctx){if(*ctx)SDL_GL_DeleteContext(*ctx);delete ctx;});
  *ctx = SDL_GL_CreateContext(this->m_window);
  if(*ctx == nullptr){
    ge::core::printError(GE_CORE_FCENAME,SDL_GetError(),name,version);
    return false;
  }
  this->m_contexts[name] = ctx;
  return true;
}

/**
 * @brief Sets context in this window with other window context
 *
 * @param name name of this windows context
 * @param other other window
 * @param otherName name of other window context
 */
void SDLWindow::setContext(
    std::string const&name     ,
    SDLWindow   const&other    ,
    std::string const&otherName){
  assert(this!=nullptr);
  assert(other.m_contexts.count(otherName)!=0);
  this->m_contexts[name] = other.m_contexts.find(otherName)->second;
}

/**
 * @brief Makes context current for this window
 *
 * @param name name of context that will be current
 */
void SDLWindow::makeCurrent(std::string const&name)const{
  assert(this!=nullptr);
  assert(this->m_contexts.count(name)!=0);
  if(SDL_GL_MakeCurrent(this->m_window,*this->m_contexts.find(name)->second)<0){
    ge::core::printError(GE_CORE_FCENAME,SDL_GetError(),name);
  }
}

/**
 * @brief Swaps buffers (front and back buffers)
 */
void SDLWindow::swap()const{
  assert(this!=nullptr);
  SDL_GL_SwapWindow(this->m_window);
}

/**
 * @brief Returns window id
 *
 * @return window id
 */
SDLWindow::WindowId SDLWindow::getId()const{
  assert(this!=nullptr);
  return SDL_GetWindowID(this->m_window);
}

/**
 * @brief Sets callback for particular event in this event
 *
 * @param eventType event type (SDL_KEYDOWN, SDL_MOUSEMOTION, ...)
 * @param callback callback, callback has to return true if event was served
 */
void SDLWindow::setEventCallback(
    EventType const&eventType,
    std::function<bool(SDL_Event const&)>const&callback){
  assert(this!=nullptr);
  assert(this!=nullptr);
  if(callback==nullptr){
    this->m_eventCallbacks.erase(eventType);
    return;
  }
  this->m_eventCallbacks[eventType] = callback;
}

/**
 * @brief Sets callback for window event
 *
 * @param eventType (SDL_WINDOWEVENT_CLOSE, ...)
 * @param callback callback, callback has to return true if event was served
 */
void SDLWindow::setWindowEventCallback(
    uint8_t                              const&eventType,
    std::function<bool(SDL_Event const&)>const&callback ){
  assert(this!=nullptr);
  if(callback==nullptr){
    this->m_windowEventCallbacks.erase(eventType);
    return;
  }
  this->m_windowEventCallbacks[eventType] = callback;
}

/**
 * @brief Gets true if callback for particular event is present
 *
 * @param eventType event type (SDL_KEYDOWN, ...)
 *
 * @return returns true if this callback is present
 */
bool SDLWindow::hasEventCallback(
    EventType const&eventType)const{
  assert(this!=nullptr);
  auto ii = this->m_eventCallbacks.find(eventType);
  return ii!=this->m_eventCallbacks.end() && ii->second != nullptr;
}

/**
 * @brief Gets true if callback for particular window event is present
 *
 * @param eventType window event type (SDL_WINDOW_EVENT_CLOSE, ...)
 *
 * @return true if this window callback is present
 */
bool SDLWindow::hasWindowEventCallback(
    uint8_t const&eventType)const{
  assert(this!=nullptr);
  auto ii = this->m_windowEventCallbacks.find(eventType);
  return ii!=this->m_windowEventCallbacks.end() && ii->second != nullptr;
}

/**
 * @brief sets window size
 *
 * @param width new width of this window
 * @param height new height of this window
 */
void SDLWindow::setSize(uint32_t width,uint32_t heght){
  assert(this!=nullptr);
  SDL_SetWindowSize(this->m_window,width,heght);
}

/**
 * @brief gets window width
 *
 * @return window width
 */
uint32_t SDLWindow::getWidth()const{
  assert(this!=nullptr);
  int size[2];
  SDL_GetWindowSize(this->m_window,size+0,size+1);
  return size[0];
}

/**
 * @brief gets window height
 *
 * @return window height
 */
uint32_t SDLWindow::getHeight()const{
  assert(this!=nullptr);
  int size[2];
  SDL_GetWindowSize(this->m_window,size+0,size+1);
  return size[1];
}

/**
 * @brief sets fullscreen
 *
 * @param type fullscreen type
 */
void SDLWindow::setFullscreen(Fullscreen const&type){
  if(SDL_SetWindowFullscreen(this->m_window,type))
    ge::core::printError(GE_CORE_FCENAME,SDL_GetError());
}

/**
 * @brief gets fullscreen type
 *
 * @return fullscreen type
 */
SDLWindow::Fullscreen SDLWindow::getFullscreen(){
  auto flags = SDL_GetWindowFlags(this->m_window);
  if(flags&FULLSCREEN)return FULLSCREEN;
  if(flags&FULLSCREEN_DESKTOP)return FULLSCREEN_DESKTOP;
  return WINDOW;
}

SDL_GLContext SDLWindow::getContext(std::string const&name)const{
  auto const it = this->m_contexts.find(name);
  if(it == this->m_contexts.end())return nullptr;
  return *it->second;
}

/**
 * @brief gets window object as implemented by SDL
 *
 * @return window object
 */
bool SDLWindow::m_defaultCloseCallback(SDL_Event const&){
  assert(this!=nullptr);
  assert(this->m_mainLoop!=nullptr);
  this->m_mainLoop->removeWindow(this->getId());
  return true;
}

bool SDLWindow::m_callEventCallback(
    EventType const&eventType,
    SDL_Event const&event    ){
  assert(this!=nullptr);
  assert(this->m_eventCallbacks.count(eventType)!=0);
  assert(this->m_eventCallbacks.at(eventType) != nullptr);
  return this->m_eventCallbacks.at(eventType)(event);
}

bool SDLWindow::m_callWindowEventCallback(
    uint8_t   const&eventType,
    SDL_Event const&eventData){
  assert(this!=nullptr);
  assert(this->m_windowEventCallbacks.count(eventType)!=0);
  assert(this->m_windowEventCallbacks.at(eventType) != nullptr);
  return this->m_windowEventCallbacks.at(eventType)(eventData);
}


