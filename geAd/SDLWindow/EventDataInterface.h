#pragma once

namespace ge{
  namespace util{
    class EventDataInterface{
      public:
        virtual ~EventDataInterface(){}
    };
    using EventDataPointer = EventDataInterface const*;
  }
}
