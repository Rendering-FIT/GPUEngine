#pragma once

#include<iostream>
#include<map>
#include<memory>
#include<functional>

#include<GPUEngine/geAd/SDLWindow/sdlwindow_export.h>
#include<SDL2/SDL.h>


namespace ge{
  namespace ad{
    class SDLWindow;
    class SDLWINDOW_EXPORT SDLMainLoop{
      public:
        using SharedWindow        = std::shared_ptr<SDLWindow>;
        using WindowId            = uint32_t;
        using Name2Window         = std::map<std::string,SharedWindow>;
        using ConstNameIterator   = Name2Window::const_iterator;
        using Id2Name             = std::map<WindowId,std::string>;
        using ConstIdIterator     = Id2Name::const_iterator;

        SDLMainLoop(bool pooling = true);
        ~SDLMainLoop();
        void addWindow(
            std::string  const&name  ,
            SharedWindow const&window);
        void removeWindow(std::string const&name);
        void removeWindow(uint32_t const&id);
        bool hasWindow(std::string const&name)const;
        SharedWindow const&getWindow(std::string const&name)const;
        void operator()();
        void setIdleCallback(
            std::function<void()>const&callback);
        bool hasIdleCallback()const;
        void setEventHandler(
            std::function<bool(SDL_Event const&)>const&handler);
        bool hasEventHandler()const;
        ConstNameIterator nameBegin()const;
        ConstNameIterator nameEnd  ()const;
        ConstIdIterator idBegin()const;
        ConstIdIterator idEnd  ()const;
        size_t getNofWindows()const;
      protected:
        std::function<bool(SDL_Event const&)>m_eventHandler = nullptr;
        std::function<void()>m_idleCallback = nullptr;
        bool                 m_pooling      = true   ;
        bool                 m_running      = false  ;
        Name2Window          m_name2Window           ;
        Id2Name              m_id2Name               ;
        void m_callIdleCallback();
        bool m_callEventHandler(SDL_Event const&event);

    };
  }
}
