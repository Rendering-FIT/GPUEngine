#pragma once

#include<iostream>
#include<map>
#include<memory>
#include<functional>

#include<geAd/Export.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_video.h>

#include<geAd/SDLWindow/SDLMainLoop.h>
#include<geAd/SDLWindow/SDLEventCallbackInterface.h>

namespace ge{
  namespace ad{
    class SDLMainLoop;
    class GEAD_EXPORT SDLWindow{
      friend class SDLMainLoop;
      public:
        using WindowId             = uint32_t;
        using EventType            = uint32_t;
        using SDLEventCallbackPointer = std::shared_ptr<SDLEventCallbackInterface>;
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
            SDLEventCallbackPointer const&callback ,
            EventType               const&eventType);
        void setEventCallback(
            EventType const&eventType,
            bool(*callback)(SDL_Event const&,void*),
            void*data);
        void setEventCallback(
            EventType const&eventType,
            std::function<bool(SDL_Event const&)>const&callback = nullptr);
        void setWindowEventCallback(
            SDLEventCallbackPointer const&callback ,
            uint8_t                 const&eventType);
        void setWindowEventCallback(
            uint8_t const&eventType,
            bool(*callback)(SDL_Event const&,void*) = nullptr,
            void*data = nullptr);
        void setWindowEventCallback(
            uint8_t                              const&eventType          ,
            std::function<bool(SDL_Event const&)>const&callback  = nullptr);
        bool hasEventCallback(
            EventType const&eventType)const;
        bool callEventCallback(
            EventType const&eventType,
            SDL_Event const&eventData);
        bool hasWindowEventCallback(
            uint8_t const&eventType)const;
        bool callWindowEventCallback(
            uint8_t   const&eventType,
            SDL_Event const&eventData);
        void setSize(uint32_t width,uint32_t heght);
        uint32_t getWidth()const;
        uint32_t getHeight()const;
        enum Fullscreen{
          WINDOW             = 0                            ,
          FULLSCREEN         = SDL_WINDOW_FULLSCREEN        ,
          FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP,
        };
        void setFullscreen(Fullscreen const&type);
        Fullscreen getFullscreen();
      protected:
        using SharedSDLContext = std::shared_ptr<SDL_GLContext>           ;
        SDL_Window*                             m_window         = nullptr;
        std::map<std::string,SharedSDLContext>  m_contexts                ;
        std::map<EventType,SDLEventCallbackPointer>m_eventCallbacks       ;
        std::map<uint8_t,SDLEventCallbackPointer>m_windowEventCallbacks;
        SDLMainLoop*m_mainLoop;
        static bool m_defaultCloseCallback(SDL_Event const&,void*);
    };
  }//util
}//ge

