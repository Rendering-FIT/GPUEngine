#pragma once

namespace ge{
  namespace ad{
    class SDLCallbackInterface{
      public:
        virtual ~SDLCallbackInterface(){}
        virtual void operator()() = 0;
    };
  }
}
