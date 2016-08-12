#include<geAd/SDLWindow/SDLWindow.h>
#include<geAd/SDLWindow/SDLMainLoop.h>
#include<geAd/SDLWindow/SDLEventCallbackInterface.h>

#include<iostream>
#include<cassert>

using namespace ge::ad;

SDLWindow::SDLWindow(uint32_t width,uint32_t height){
  assert(this!=nullptr);
  Uint32 flags = SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN;
  this->m_window  = SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,flags);
  this->setWindowEventCallback(SDL_WINDOWEVENT_CLOSE,SDLWindow::m_defaultCloseCallback,this);
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
    EventType               const&eventType,
    SDLEventCallbackPointer const&callback ){
  assert(this!=nullptr);
  if(callback==nullptr){
    this->m_eventCallbacks.erase(eventType);
    return;
  }
  this->m_eventCallbacks[eventType] = callback;
}

void SDLWindow::setEventCallback(
    EventType const&eventType,
    bool(*callback)(SDL_Event const&,void*),
    void*data){
  assert(this!=nullptr);
  if(callback==nullptr){
    this->m_eventCallbacks.erase(eventType);
    return;
  }
  class BasicEventCallback: public SDLEventCallbackInterface{
    public:
      void*data;
      bool(*fce)(SDL_Event const&,void*);
      BasicEventCallback(bool(*f)(SDL_Event const&,void*),void*d){
        assert(this!=nullptr);
        this->fce = f;
        this->data = d;
      }
      virtual bool operator()(SDL_Event const&event)override{
        assert(this!=nullptr);
        assert(this->fce!=nullptr);
        return this->fce(event,this->data);
      }
  };
  this->m_eventCallbacks[eventType] = std::make_shared<BasicEventCallback>(callback,data);
}

void SDLWindow::setWindowEventCallback(
    uint8_t                 const&eventType,
    SDLEventCallbackPointer const&callback){
  assert(this!=nullptr);
  if(callback==nullptr){
    this->m_windowEventCallbacks.erase(eventType);
    return;
  }
  this->m_windowEventCallbacks[eventType] = callback;
}

void SDLWindow::setWindowEventCallback(
    uint8_t const&eventType,
    bool(*callback)(SDL_Event const&,void*),
    void*data){
  assert(this!=nullptr);
  if(callback==nullptr){
    this->m_windowEventCallbacks.erase(eventType);
    return;
  }
  class BasicEventCallback: public SDLEventCallbackInterface{
    public:
      void*data;
      bool(*fce)(SDL_Event const&,void*);
      BasicEventCallback(bool(*f)(SDL_Event const&,void*),void*d){
        assert(this!=nullptr);
        this->fce = f;
        this->data = d;
      }
      virtual bool operator()(SDL_Event const&event)override{
        assert(this!=nullptr);
        assert(this->fce!=nullptr);
        return this->fce(event,this->data);
      }
  };
  this->m_windowEventCallbacks[eventType] = std::make_shared<BasicEventCallback>(callback,data);
}


bool SDLWindow::hasEventCallback(
    EventType const&eventType)const{
  assert(this!=nullptr);
  auto ii = this->m_eventCallbacks.find(eventType);
  return ii!=this->m_eventCallbacks.end() && ii->second != nullptr;
}

bool SDLWindow::callEventCallback(
    EventType const&eventType,
    SDL_Event const&event    ){
  assert(this!=nullptr);
  assert(this->m_eventCallbacks.count(eventType)!=0);
  assert(this->m_eventCallbacks.at(eventType) != nullptr);
  return (*this->m_eventCallbacks.at(eventType))(event);
}

bool SDLWindow::hasWindowEventCallback(
    uint8_t const&eventType)const{
  assert(this!=nullptr);
  auto ii = this->m_windowEventCallbacks.find(eventType);
  return ii!=this->m_windowEventCallbacks.end() && ii->second != nullptr;
}

bool SDLWindow::callWindowEventCallback(
    uint8_t   const&eventType,
    SDL_Event const&eventData){
  assert(this!=nullptr);
  assert(this->m_windowEventCallbacks.count(eventType)!=0);
  assert(this->m_windowEventCallbacks.at(eventType) != nullptr);
  return (*this->m_windowEventCallbacks.at(eventType))(eventData);
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
  if(SDL_SetWindowFullscreen(this->m_window,type))
    std::cerr<<SDL_GetError()<<std::endl;
}

SDLWindow::Fullscreen SDLWindow::getFullscreen(){
  auto flags = SDL_GetWindowFlags(this->m_window);
  if(flags&FULLSCREEN)return FULLSCREEN;
  if(flags&FULLSCREEN_DESKTOP)return FULLSCREEN_DESKTOP;
  return WINDOW;
}

bool SDLWindow::m_defaultCloseCallback(SDL_Event const&,void*d){
  assert(d!=nullptr);
  auto _this = (SDLWindow*)d;
  assert(_this->m_mainLoop!=nullptr);
  _this->m_mainLoop->removeWindow(_this->getId());
  return true;
}
