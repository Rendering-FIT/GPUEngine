#pragma once

#include<geAd/SDLWindow/EventDataInterface.h>

namespace ge{
  namespace util{
    class EventCallbackInterface{
      public:
        virtual ~EventCallbackInterface(){}
        virtual void operator()(EventDataPointer const&) = 0;
    };
  }
}
