#include<geAd/SDLWindow/SDLEventProc.h>
#include<geAd/SDLWindow/SDLWindow.h>
#include<geAd/SDLWindow/CallbackInterface.h>
#include<geAd/SDLWindow/SDLEventData.h>
#include<cassert>

using namespace ge::util;

SDLEventProc::SDLEventProc(bool pooling){
  assert(this!=nullptr);
  SDL_Init(SDL_INIT_VIDEO);
  this->m_pooling = pooling;
}

SDLEventProc::~SDLEventProc(){
  SDL_Quit();
}

void SDLEventProc::addWindow(
    std::string  const&name  ,
    SharedWindow const&window){
  assert(this!=nullptr);
  assert(window!=nullptr);
  this->m_name2Window[name] = window;
  this->m_id2Name[window->getId()] = name;
}

bool SDLEventProc::hasWindow(std::string const&name)const{
  assert(this!=nullptr);
  return this->m_name2Window.count(name)!=0;
}

void SDLEventProc::removeWindow(std::string const&name){
  assert(this!=nullptr);
  this->m_id2Name.erase(this->getWindow(name)->getId());
  this->m_name2Window.erase(name);
}

SDLEventProc::SharedWindow const&SDLEventProc::getWindow(
    std::string const&name)const{
  assert(this!=nullptr);
  assert(this->m_name2Window.count(name)!=0);
  return this->m_name2Window.find(name)->second;
}

void SDLEventProc::operator()(){
  assert(this!=nullptr);
  this->m_running = true;
  SDL_Event event;
  SDLEventData eventData;
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

      eventData.event = event;
      bool handledByEventHandler = false;

      if(this->hasEventHandler())
        handledByEventHandler = this->callEventHandler(&eventData);

      if(!handledByEventHandler){
        auto windowIter = this->m_id2Name.find(event.window.windowID);
        if(windowIter == this->m_id2Name.end())continue;
        auto window = this->m_name2Window[windowIter->second];
        if(window->hasEventCallback(event.type))
          window->callEventCallback(event.type,&eventData);
      }

      if(!this->m_pooling)
        if(!SDL_PollEvent(&event))break;
    }
    if(this->hasIdleCallback())
      this->callIdleCallback();
  }
}

void SDLEventProc::setIdleCallback(
    CallbackPointer  const&callback){
  assert(this!=nullptr);
  this->m_idleCallback = callback;
}

bool SDLEventProc::hasIdleCallback()const{
  assert(this!=nullptr);
  return this->m_idleCallback != nullptr;
}

void SDLEventProc::callIdleCallback(){
  assert(this!=nullptr);
  assert(this->m_idleCallback != nullptr);
  (*this->m_idleCallback)();
}


void SDLEventProc::setEventHandler(
    EventHandlerPointer const&handler){
  assert(this!=nullptr);
  this->m_eventHandler = handler;
}

bool SDLEventProc::hasEventHandler()const{
  assert(this!=nullptr);
  return this->m_eventHandler != nullptr;
}

bool SDLEventProc::callEventHandler(EventDataPointer const&event){
  assert(this!=nullptr);
  assert(this->m_eventHandler != nullptr);
  return (*this->m_eventHandler)(event);
}


SDLEventProc::ConstNameIterator SDLEventProc::nameBegin()const{
  assert(this!=0);
  return this->m_name2Window.begin();
}

SDLEventProc::ConstNameIterator SDLEventProc::nameEnd  ()const{
  assert(this!=0);
  return this->m_name2Window.end();
}

SDLEventProc::ConstIdIterator SDLEventProc::idBegin()const{
  assert(this!=0);
  return this->m_id2Name.begin();
}

SDLEventProc::ConstIdIterator SDLEventProc::idEnd  ()const{
  assert(this!=0);
  return this->m_id2Name.end();
}

size_t SDLEventProc::getNofWindows()const{
  assert(this!=0);
  return this->m_name2Window.size();
}

