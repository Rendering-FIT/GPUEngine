#include<GPUEngine/geAd/SDLWindow/SDLMainLoop.h>
#include<GPUEngine/geAd/SDLWindow/SDLWindow.h>
#include<GPUEngine/geCore/ErrorPrinter/ErrorPrinter.h>
#include<cassert>

using namespace ge::ad;

/**
 * @brief Creates new main loop
 *
 * @param pooling if set to false, idle will be called only when new event arrives
 */
SDLMainLoop::SDLMainLoop(bool pooling){
  assert(this!=nullptr);
  if(SDL_Init(SDL_INIT_VIDEO)<0)
    ge::core::printError(GE_CORE_FCENAME,SDL_GetError(),pooling);
  this->m_pooling = pooling;
}

/**
 * @brief Destroys main loop
 */
SDLMainLoop::~SDLMainLoop(){
  SDL_Quit();
}

/**
 * @brief Adds window to this main loop
 *
 * @param name name identificator of window
 * @param window SDLWindow
 */
void SDLMainLoop::addWindow(
    std::string  const&name  ,
    SharedWindow const&window){
  assert(this!=nullptr);
  assert(window!=nullptr);
  this->m_name2Window[name] = window;
  this->m_id2Name[window->getId()] = name;
  window->m_mainLoop = this;
}

/**
 * @brief Removes window from this main loop by window id
 *
 * @param id window id
 */
void SDLMainLoop::removeWindow(uint32_t const&id){
  assert(this!=nullptr);
  assert(this->m_id2Name.count(id)!=0);
  auto name = this->m_id2Name.at(id);
  this->m_id2Name.erase(id);
  this->m_name2Window.erase(name);
}

/**
 * @brief Removes window from this main loop
 *
 * @param name name identificator of window
 */
void SDLMainLoop::removeWindow(std::string const&name){
  assert(this!=nullptr);
  this->m_id2Name.erase(this->getWindow(name)->getId());
  this->m_name2Window.erase(name);
}

/**
 * @brief Has this main loop window with this name?
 *
 * @param name name of window
 *
 * @return true if this main loop has that window
 */
bool SDLMainLoop::hasWindow(std::string const&name)const{
  assert(this!=nullptr);
  return this->m_name2Window.count(name)!=0;
}

/**
 * @brief Gets window by its name
 *
 * @param name name of window
 *
 * @return return SDLWindow
 */
SDLMainLoop::SharedWindow const&SDLMainLoop::getWindow(
    std::string const&name)const{
  assert(this!=nullptr);
  assert(this->m_name2Window.count(name)!=0);
  return this->m_name2Window.find(name)->second;
}

/**
 * @brief Starts main loop
 */
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
        handledByEventHandler = this->m_callEventHandler(event);

      if(!handledByEventHandler){
        auto windowIter = this->m_id2Name.find(event.window.windowID);
        bool handledByEventCallback = false;
        if(windowIter != this->m_id2Name.end()){
          auto const&window = this->m_name2Window[windowIter->second];
          if(window->hasEventCallback(event.type))
            handledByEventCallback = window->m_callEventCallback(event.type,event);
        }
        if(!handledByEventCallback){
          if(event.type == SDL_WINDOWEVENT){
            bool handledByWindowEventCallback = false;
            if(windowIter != this->m_id2Name.end()){
              auto const&window = this->m_name2Window.at(windowIter->second);
              if(window->hasWindowEventCallback(event.window.event))
                handledByWindowEventCallback = window->m_callWindowEventCallback(event.window.event,event);
            }
            (void)handledByWindowEventCallback;
          }
        }
      }

      if(!this->m_pooling)
        if(!SDL_PollEvent(&event))break;
    }
    if(this->hasIdleCallback())
      this->m_callIdleCallback();
  }
}

/**
 * @brief sets idle callback
 *
 * @param callback idle callback
 */
void SDLMainLoop::setIdleCallback(
    std::function<void()>const&callback){
  assert(this!=nullptr);
  this->m_idleCallback = callback;
}

/**
 * @brief has idle callback
 *
 * @return true if this main loop has idle callback
 */
bool SDLMainLoop::hasIdleCallback()const{
  assert(this!=nullptr);
  return this->m_idleCallback != nullptr;
}

/**
 * @brief sets event handler callback
 * Event handler can serve every event, it is usefull for imgui, AntTweakBar
 * Event handlere has to return true if it served particular event
 *
 * @param handler callback
 */
void SDLMainLoop::setEventHandler(
    std::function<bool(SDL_Event const&)>const&handler){
  assert(this!=nullptr);
  this->m_eventHandler = handler;
}

/**
 * @brief has event handler callback
 *
 * @return event handler callback
 */
bool SDLMainLoop::hasEventHandler()const{
  assert(this!=nullptr);
  return this->m_eventHandler != nullptr;
}

/**
 * @brief begin iterator of names of registered windows
 *
 * @return begin iterator of names of registered windows
 */
SDLMainLoop::ConstNameIterator SDLMainLoop::nameBegin()const{
  assert(this!=0);
  return this->m_name2Window.begin();
}

/**
 * @brief end iterator of names of registered windows
 *
 * @return end iterator of names of registered windows
 */
SDLMainLoop::ConstNameIterator SDLMainLoop::nameEnd  ()const{
  assert(this!=0);
  return this->m_name2Window.end();
}

/**
 * @brief begin iterator of ids of registered windows
 *
 * @return begin iterator of ids of registerd windows
 */
SDLMainLoop::ConstIdIterator SDLMainLoop::idBegin()const{
  assert(this!=0);
  return this->m_id2Name.begin();
}

/**
 * @brief end iterator of ids of registered windows
 *
 * @return end iterator of ids of registered windows
 */
SDLMainLoop::ConstIdIterator SDLMainLoop::idEnd  ()const{
  assert(this!=0);
  return this->m_id2Name.end();
}

/**
 * @brief gets number of registered windows
 *
 * @return number of registered windows
 */
size_t SDLMainLoop::getNofWindows()const{
  assert(this!=0);
  return this->m_name2Window.size();
}

void SDLMainLoop::m_callIdleCallback(){
  assert(this!=nullptr);
  assert(this->m_idleCallback != nullptr);
  this->m_idleCallback();
}

bool SDLMainLoop::m_callEventHandler(SDL_Event const&event){
  assert(this!=nullptr);
  assert(this->m_eventHandler != nullptr);
  return this->m_eventHandler(event);
}



