#pragma once

#include<iostream>
#include<map>
#include<memory>

#include<geAd/Export.h>
#include<SDL2/SDL.h>

#include<geAd/SDLWindow/EventDataInterface.h>
#include<geAd/SDLWindow/SDLEventProc.h>
#include<geAd/SDLWindow/EventDataInterface.h>
#include<geAd/SDLWindow/EventCallbackInterface.h>
#include<geAd/SDLWindow/SDLEventData.h>

namespace ge{
  namespace util{
    class EventCallbackInterface;
    class GEAD_EXPORT SDLWindow{
      public:
        using WindowId             = uint32_t;
        using EventType            = uint32_t;
        using EventCallbackPointer = std::shared_ptr<EventCallbackInterface>;
        enum Profile{
          CORE          = SDL_GL_CONTEXT_PROFILE_CORE         ,
          COMPATIBILITY = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY,
          ES            = SDL_GL_CONTEXT_PROFILE_ES           ,
        };
        enum Flag{
          NONE               = 0                                     ,
          DEBUG              = SDL_GL_CONTEXT_DEBUG_FLAG             ,
          FORWARD_COMPATIBLE = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG,
          ROBUST_ACCESS      = SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG     ,
          RESET_ISOLATION    = SDL_GL_CONTEXT_RESET_ISOLATION_FLAG   ,
        };

        SDLWindow(uint32_t width = 1024,uint32_t height = 768);
        ~SDLWindow();
        bool createContext(
            std::string const&name    = "context",
            uint32_t          version = 450u     ,
            Profile           profile = CORE     ,
            Flag              flags   = NONE     );
        void setContext(
            std::string const&name     ,
            SDLWindow   const&other    ,
            std::string const&otherName);
        void makeCurrent(std::string const&name)const;
        void swap()const;
        WindowId getId()const;

        void setEventCallback(
            EventType            const&eventType          ,
            EventCallbackPointer const&callback  = nullptr);
        bool hasEventCallback(
            EventType const&eventType)const;
        void callEventCallback(
            EventType        const&eventType,
            EventDataPointer const&eventData);
        void setSize(uint32_t width,uint32_t heght);
        uint32_t getWidth()const;
        uint32_t getHeight()const;
        enum Fullscreen{
          WINDOW             = 0                            ,
          FULLSCREEN         = SDL_WINDOW_FULLSCREEN        ,
          FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP,
        };
        void setFullscreen(Fullscreen const&type);
      protected:
        using SharedSDLContext = std::shared_ptr<SDL_GLContext>;
        SDL_Window*                             m_window         = nullptr;
        std::map<std::string,SharedSDLContext>  m_contexts                ;
        std::map<EventType,EventCallbackPointer>m_eventCallbacks          ;
    };
  }//util
}//ge

