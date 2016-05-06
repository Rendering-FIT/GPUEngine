#pragma once

#include<geAd/SDLWindow/EventDataInterface.h>

namespace ge{
  namespace util{
    class SDLEventData: public EventDataInterface{
      public:
        SDL_Event event;
    };
  }
}
