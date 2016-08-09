#include<geAd/SDLWindow/SDLMainLoop.h>
#include<geAd/SDLWindow/SDLWindow.h>
#include<geAd/SDLWindow/SDLCallbackInterface.h>
#include<cassert>

using namespace ge::ad;

SDLMainLoop::SDLMainLoop(bool pooling){
  assert(this!=nullptr);
  SDL_Init(SDL_INIT_VIDEO);
  this->m_pooling = pooling;
}

SDLMainLoop::~SDLMainLoop(){
  SDL_Quit();
}

void SDLMainLoop::addWindow(
    std::string  const&name  ,
    SharedWindow const&window){
  assert(this!=nullptr);
  assert(window!=nullptr);
  this->m_name2Window[name] = window;
  this->m_id2Name[window->getId()] = name;
}

bool SDLMainLoop::hasWindow(std::string const&name)const{
  assert(this!=nullptr);
  return this->m_name2Window.count(name)!=0;
}

void SDLMainLoop::removeWindow(std::string const&name){
  assert(this!=nullptr);
  this->m_id2Name.erase(this->getWindow(name)->getId());
  this->m_name2Window.erase(name);
}

SDLMainLoop::SharedWindow const&SDLMainLoop::getWindow(
    std::string const&name)const{
  assert(this!=nullptr);
  assert(this->m_name2Window.count(name)!=0);
  return this->m_name2Window.find(name)->second;
}

void SDLMainLoop::operator()(){
  assert(this!=nullptr);
  this->m_running = true;
  SDL_Event event;
  while(this->m_running){
    if(this->m_name2Window.size() == 0){
      this->m_running = false;
      break;
    }
    if(!this->m_pooling)
      SDL_WaitEvent(&event);
    while(true){
      if(this->m_pooling)
        if(!SDL_PollEvent(&event))break;

      bool handledByEventHandler = false;

      if(this->hasEventHandler())
        handledByEventHandler = this->callEventHandler(event);

      if(!handledByEventHandler){
        auto windowIter = this->m_id2Name.find(event.window.windowID);
        if(windowIter == this->m_id2Name.end())continue;
        auto window = this->m_name2Window[windowIter->second];
        if(window->hasEventCallback(event.type))
          window->callEventCallback(event.type,event);
      }

      if(!this->m_pooling)
        if(!SDL_PollEvent(&event))break;
    }
    if(this->hasIdleCallback())
      this->callIdleCallback();
  }
}

void SDLMainLoop::setIdleCallback(
    SDLCallbackPointer const&callback){
  assert(this!=nullptr);
  this->m_idleCallback = callback;
}

bool SDLMainLoop::hasIdleCallback()const{
  assert(this!=nullptr);
  return this->m_idleCallback != nullptr;
}

void SDLMainLoop::callIdleCallback(){
  assert(this!=nullptr);
  assert(this->m_idleCallback != nullptr);
  (*this->m_idleCallback)();
}


void SDLMainLoop::setEventHandler(
    EventHandlerPointer const&handler){
  assert(this!=nullptr);
  this->m_eventHandler = handler;
}

bool SDLMainLoop::hasEventHandler()const{
  assert(this!=nullptr);
  return this->m_eventHandler != nullptr;
}

bool SDLMainLoop::callEventHandler(SDL_Event const&event){
  assert(this!=nullptr);
  assert(this->m_eventHandler != nullptr);
  return (*this->m_eventHandler)(event);
}


SDLMainLoop::ConstNameIterator SDLMainLoop::nameBegin()const{
  assert(this!=0);
  return this->m_name2Window.begin();
}

SDLMainLoop::ConstNameIterator SDLMainLoop::nameEnd  ()const{
  assert(this!=0);
  return this->m_name2Window.end();
}

SDLMainLoop::ConstIdIterator SDLMainLoop::idBegin()const{
  assert(this!=0);
  return this->m_id2Name.begin();
}

SDLMainLoop::ConstIdIterator SDLMainLoop::idEnd  ()const{
  assert(this!=0);
  return this->m_id2Name.end();
}

size_t SDLMainLoop::getNofWindows()const{
  assert(this!=0);
  return this->m_name2Window.size();
}

