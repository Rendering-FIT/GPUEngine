#pragma once

#include<SDL2/SDL.h>

namespace ge{
  namespace util{
    class SDLEventCallbackInterface{
      public:
        virtual ~SDLEventCallbackInterface(){}
        virtual bool operator()(SDL_Event const&) = 0;
    };
  }
}
