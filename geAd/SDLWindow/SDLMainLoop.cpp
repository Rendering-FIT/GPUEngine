#include<geAd/SDLWindow/SDLMainLoop.h>
#include<geAd/SDLWindow/SDLWindow.h>
#include<geCore/ErrorPrinter.h>
#include<cassert>

using namespace ge::ad;

SDLMainLoop::SDLMainLoop(bool pooling){
  assert(this!=nullptr);
  if(SDL_Init(SDL_INIT_VIDEO)<0)
    ge::core::printError(GE_CORE_FCENAME,SDL_GetError(),pooling);
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
  window->m_mainLoop = this;
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

void SDLMainLoop::removeWindow(uint32_t const&id){
  assert(this!=nullptr);
  assert(this->m_id2Name.count(id)!=0);
  auto name = this->m_id2Name.at(id);
  this->m_id2Name.erase(id);
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
      if(SDL_WaitEvent(&event)==0){
        ge::core::printError(GE_CORE_FCENAME,SDL_GetError());
        return;
      }
    while(true){
      if(this->m_pooling)
        if(!SDL_PollEvent(&event))break;

      bool handledByEventHandler = false;

      if(this->hasEventHandler())
        handledByEventHandler = this->callEventHandler(event);

      if(!handledByEventHandler){
        auto windowIter = this->m_id2Name.find(event.window.windowID);
        bool handledByEventCallback = false;
        if(windowIter != this->m_id2Name.end()){
          auto const&window = this->m_name2Window[windowIter->second];
          if(window->hasEventCallback(event.type))
            handledByEventCallback = window->callEventCallback(event.type,event);
        }
        if(!handledByEventCallback){
          if(event.type == SDL_WINDOWEVENT){
            bool handledByWindowEventCallback = false;
            if(windowIter != this->m_id2Name.end()){
              auto const&window = this->m_name2Window.at(windowIter->second);
              if(window->hasWindowEventCallback(event.window.event))
                handledByWindowEventCallback = window->callWindowEventCallback(event.window.event,event);
            }
            (void)handledByWindowEventCallback;
          }
        }
      }

      if(!this->m_pooling)
        if(!SDL_PollEvent(&event))break;
    }
    if(this->hasIdleCallback())
      this->callIdleCallback();
  }
}

void SDLMainLoop::setIdleCallback(
    std::function<void()>const&callback){
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
  this->m_idleCallback();
}

void SDLMainLoop::setEventHandler(
    std::function<bool(SDL_Event const&)>const&handler){
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
  return this->m_eventHandler(event);
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

