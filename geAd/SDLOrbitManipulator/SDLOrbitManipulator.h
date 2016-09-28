#ifndef GE_AD_SDL_ORBIT_MANIPULATOR_H
#define GE_AD_SDL_ORBIT_MANIPULATOR_H

#include <geUtil/OrbitManipulator.h>
#include <geAd/Export.h>

union SDL_Event;
namespace ge { namespace ad {
   class SDLWindow;
} }


namespace ge {
namespace ad {


class GEAD_EXPORT SDLOrbitManipulator : public ge::util::OrbitManipulator
{
protected:

   ge::ad::SDLWindow *_window;
   unsigned _mouseRotationButtonMask;
   glm::ivec2 _lastMousePosition;

public:

   inline SDLOrbitManipulator();
   inline SDLOrbitManipulator(ge::ad::SDLWindow* window,unsigned mouseRotationButtonMask);
   virtual ~SDLOrbitManipulator();

   void connect(ge::ad::SDLWindow* window,unsigned mouseRotationButtonMask);
   void disconnect();
   inline void connect(const std::shared_ptr<ge::ad::SDLWindow>& window,unsigned mouseRotationButtonMask)  { connect(window.get(),mouseRotationButtonMask); }

protected:
   bool mouseButtonCallback(const SDL_Event& event);
   bool mouseMotionCallback(const SDL_Event& event);
};


// inline methods
inline SDLOrbitManipulator::SDLOrbitManipulator() : _window(nullptr)  {}
inline SDLOrbitManipulator::SDLOrbitManipulator(ge::ad::SDLWindow *window,unsigned mouseRotationButtonMask)
   : _window(window), _mouseRotationButtonMask(mouseRotationButtonMask)  {}

}
}

#endif /* GE_AD_SDL_ORBIT_MANIPULATOR_H */
