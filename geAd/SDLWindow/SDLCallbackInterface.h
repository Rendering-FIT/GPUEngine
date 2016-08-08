#pragma once

namespace ge{
  namespace util{
    class SDLCallbackInterface{
      public:
        virtual ~SDLCallbackInterface(){}
        virtual void operator()() = 0;
    };
  }
}
