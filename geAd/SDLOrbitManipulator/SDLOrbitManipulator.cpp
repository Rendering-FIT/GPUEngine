#include <geAd/SDLWindow/SDLWindow.h>
#include <geAd/SDLOrbitManipulator/SDLOrbitManipulator.h>

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
      _window->setEventCallback(SDL_MOUSEBUTTONDOWN,std::bind(&SDLOrbitManipulator::mouseButtonCallback,this,std::placeholders::_1));
      _window->setEventCallback(SDL_MOUSEBUTTONUP,std::bind(&SDLOrbitManipulator::mouseButtonCallback,this,std::placeholders::_1));
      _window->setEventCallback(SDL_MOUSEMOTION,std::bind(&SDLOrbitManipulator::mouseMotionCallback,this,std::placeholders::_1));
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


bool SDLOrbitManipulator::mouseButtonCallback(const SDL_Event& event)
{
   const SDL_MouseButtonEvent& e=reinterpret_cast<const SDL_MouseButtonEvent&>(event);

   if((SDL_BUTTON(e.button) & this->_mouseRotationButtonMask) != 0) {
      if(e.type==SDL_MOUSEBUTTONDOWN) {
         this->_lastMousePosition=glm::ivec2(e.x,e.y);
      }
      else if(e.type==SDL_MOUSEBUTTONUP) {
         glm::vec2 size(this->_window->getWidth(),this->_window->getHeight());
         glm::vec2 delta=glm::vec2(glm::ivec2(e.x,e.y)-this->_lastMousePosition)/size;
         this->rotate(delta.x,delta.y);
      }
      return true;
   }

   return false;
}


bool SDLOrbitManipulator::mouseMotionCallback(const SDL_Event& event)
{
   const SDL_MouseMotionEvent& e=reinterpret_cast<const SDL_MouseMotionEvent&>(event);

   if((e.state&this->_mouseRotationButtonMask) != 0) {
      glm::ivec2 currentMousePosition(e.x,e.y);
      glm::vec2 size(this->_window->getWidth(),this->_window->getHeight());
      glm::vec2 delta=glm::vec2(currentMousePosition-this->_lastMousePosition)/size;
      this->_lastMousePosition=currentMousePosition;
      this->rotate(delta.x,delta.y);
      return true;
   }

   return false;
}
