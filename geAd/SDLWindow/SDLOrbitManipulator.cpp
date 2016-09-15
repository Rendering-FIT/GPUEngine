#include <geAd/SDLWindow/SDLWindow.h>
#include <geAd/SDLWindow/SDLOrbitManipulator.h>

using namespace ge::ad;


SDLOrbitManipulator::~SDLOrbitManipulator()
{
   disconnect();
}


void SDLOrbitManipulator::connect(ge::ad::SDLWindow* window,unsigned mouseRotationButtonMask)
{
   disconnect();

   if(mouseRotationButtonMask!=0) {
      _window=window;
      _mouseRotationButtonMask=mouseRotationButtonMask;
      _window->setEventCallback(SDL_MOUSEBUTTONDOWN,mouseButtonCallback,this);
      _window->setEventCallback(SDL_MOUSEBUTTONUP,mouseButtonCallback,this);
      _window->setEventCallback(SDL_MOUSEMOTION,mouseMotionCallback,this);
   }
}


void SDLOrbitManipulator::disconnect()
{
   if(_window) {
      _window->setEventCallback(SDL_MOUSEBUTTONDOWN,nullptr);
      _window->setEventCallback(SDL_MOUSEBUTTONUP,nullptr);
      _window->setEventCallback(SDL_MOUSEMOTION,nullptr);
   }
}


bool SDLOrbitManipulator::mouseButtonCallback(const SDL_Event& event,void* data)
{
   const SDL_MouseButtonEvent& e=reinterpret_cast<const SDL_MouseButtonEvent&>(event);
   SDLOrbitManipulator &d=*static_cast<SDLOrbitManipulator*>(data);

   if((SDL_BUTTON(e.button) & d._mouseRotationButtonMask) != 0) {
      if(e.type==SDL_MOUSEBUTTONDOWN) {
         d._lastMousePosition=glm::ivec2(e.x,e.y);
      }
      else if(e.type==SDL_MOUSEBUTTONUP) {
         glm::vec2 size(d._window->getWidth(),d._window->getHeight());
         glm::vec2 delta=glm::vec2(glm::ivec2(e.x,e.y)-d._lastMousePosition)/size;
         d.rotate(delta.x,delta.y);
      }
      return true;
   }

   return false;
}


bool SDLOrbitManipulator::mouseMotionCallback(const SDL_Event& event,void* data)
{
   const SDL_MouseMotionEvent& e=reinterpret_cast<const SDL_MouseMotionEvent&>(event);
   SDLOrbitManipulator &d=*static_cast<SDLOrbitManipulator*>(data);

   if((e.state&d._mouseRotationButtonMask) != 0) {
      glm::ivec2 currentMousePosition(e.x,e.y);
      glm::vec2 size(d._window->getWidth(),d._window->getHeight());
      glm::vec2 delta=glm::vec2(currentMousePosition-d._lastMousePosition)/size;
      d._lastMousePosition=currentMousePosition;
      d.rotate(delta.x,delta.y);
      return true;
   }

   return false;
}
