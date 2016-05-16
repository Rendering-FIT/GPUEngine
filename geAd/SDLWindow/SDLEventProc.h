#pragma once

#include<iostream>
#include<map>
#include<memory>

#include<geAd/Export.h>
#include<SDL2/SDL.h>

#include<geAd/SDLWindow/CallbackInterface.h>
#include<geAd/SDLWindow/EventHandlerInterface.h>

namespace ge{
  namespace util{
    class SDLWindow;
    class SDLCallbackInterface;
    class GEAD_EXPORT SDLEventProc{
      public:
        using SharedWindow        = std::shared_ptr<SDLWindow>;
        using WindowId            = uint32_t;
        using Name2Window         = std::map<std::string,SharedWindow>;
        using ConstNameIterator   = Name2Window::const_iterator;
        using Id2Name             = std::map<WindowId,std::string>;
        using ConstIdIterator     = Id2Name::const_iterator;
        using CallbackPointer     = std::shared_ptr<CallbackInterface>;
        using EventHandlerPointer = std::shared_ptr<EventHandlerInterface>;

        SDLEventProc(bool pooling = true);
        ~SDLEventProc();
        void addWindow(
            std::string  const&name  ,
            SharedWindow const&window);
        void removeWindow(std::string const&name);
        bool hasWindow(std::string const&name)const;
        SharedWindow const&getWindow(std::string const&name)const;
        void operator()();
        void setIdleCallback(
            CallbackPointer const&callback = nullptr);
        bool hasIdleCallback()const;
        void callIdleCallback();
        void setEventHandler(
            EventHandlerPointer const&handler = nullptr);
        bool hasEventHandler()const;
        bool callEventHandler(EventDataPointer const&eventData);
        ConstNameIterator nameBegin()const;
        ConstNameIterator nameEnd  ()const;
        ConstIdIterator idBegin()const;
        ConstIdIterator idEnd  ()const;
        size_t getNofWindows()const;
      protected:
        CallbackPointer      m_idleCallback = nullptr;
        EventHandlerPointer  m_eventHandler = nullptr;
        bool                 m_pooling      = true   ;
        bool                 m_running      = false  ;
        Name2Window          m_name2Window           ;
        Id2Name              m_id2Name               ;
    };
  }
}
