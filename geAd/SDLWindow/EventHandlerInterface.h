#pragma once

#include<geAd/SDLWindow/EventDataInterface.h>

namespace ge{
  namespace util{
    class EventHandlerInterface{
      public:
        virtual ~EventHandlerInterface(){}
        virtual bool operator()(EventDataPointer const&) = 0;
    };
  }
}
