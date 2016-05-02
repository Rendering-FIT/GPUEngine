#pragma once

#include<iostream>
#include<map>
#include<memory>

#include<geAd/Export.h>
#include<SDL2/SDL.h>

namespace ge{
  namespace util{
    
    class SDLWindow;
    class GEAD_EXPORT SDLEventProc{
      public:
        SDLEventProc(bool pooling = true);
        void addWindow(
            std::string               const&name  ,
            std::shared_ptr<SDLWindow>const&window);
        void removeWindow(std::string const&name);
        bool hasWindow(std::string const&name)const;
        std::shared_ptr<SDLWindow>const&getWindow(std::string const&name)const;
        void operator()();
      protected:
        bool                                            m_pooling = true ;
        bool                                            m_running = false;
        std::map<std::string,std::shared_ptr<SDLWindow>>m_windows        ;
        std::map<uint32_t,std::string>                  m_id2Name        ;
    };

    class GEAD_EXPORT SDLWindow{
      public:
        using EventType        = uint32_t;
        using CallbackUserData = void*;
        using Callback         = void(*)(CallbackUserData);
        using EventCallback    = void(*)(CallbackUserData,SDL_Event);
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
            std::string const&name          ,
            uint32_t          version = 450u,
            Profile           profile = CORE,
            Flag              flags   = NONE);
        void setContext(
            std::string const&name     ,
            SDLWindow   const&other    ,
            std::string const&otherName);
        void makeCurrent(std::string const&name)const;
        void swap()const;
        unsigned getId()const;

        void setEventCallback(
            EventType        const&eventType          ,
            EventCallback    const&callback  = nullptr,
            CallbackUserData const&userData  = nullptr);
        void setIdleCallback(
            Callback         const&callback = nullptr,
            CallbackUserData const&userData = nullptr);
        bool hasEventCallback(
            EventType const&eventType)const;
        bool hasIdleCallback()const;
        void callEventCallback(
            EventType const&eventType,
            SDL_Event const&event    );
        void callIdleCallback();

        void setSize(uint32_t width,uint32_t heght);
        uint32_t getWidth()const;
        uint32_t getHeight()const;
      protected:
        using CallbackWithData      = std::tuple<Callback,void*>;
        using EventCallbackWithData = std::tuple<EventCallback,void*>;
        using SharedSDLContext      = std::shared_ptr<SDL_GLContext>;
        enum CallbackParts{
          CALLBACK = 0,
          USERDATA = 1,
        };
        SDL_Window*                             m_window         = nullptr;
        std::map<std::string,SharedSDLContext>  m_contexts                ;
        std::map<uint32_t,EventCallbackWithData>m_eventCallbacks          ;
        CallbackWithData                        m_idleCallback            ;
    };
  }//util
}//ge

