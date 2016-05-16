#pragma once

namespace ge{
  namespace util{
    class EventCallbackInterface;
    class Window{
      public:
        using EventCallbackPointer = std::shared_ptr<EventCallbackInterface>;
        void setEventCallback(
            EventType            const&eventType          ,
            EventCallbackPointer const&callback  = nullptr);
        bool hasEventCallback(
            EventType const&eventType)const;
        void callEventCallback(
            EventType        const&eventType,
            EventDataPointer const&eventData);

        void setEventCallback(

            )
    };
  }
}
