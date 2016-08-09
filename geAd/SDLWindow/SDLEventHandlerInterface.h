#pragma once

#include<SDL2/SDL.h>

namespace ge{
  namespace ad{
    class SDLEventHandlerInterface{
      public:
        virtual ~SDLEventHandlerInterface(){}
        virtual bool operator()(SDL_Event const&) = 0;
    };
  }
}
