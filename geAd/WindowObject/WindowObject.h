#pragma once

#include<iostream>
#include<map>

#include<geAd/Export.h>

#define WINDOWOBJECT_WINDOWSIZE      NULL
#define WINDOWOBJECT_WIDTH           100
#define WINDOWOBJECT_HEIGHT          100
#define WINDOWOBJECT_FULLSCREEN      false
#define WINDOWOBJECT_IDLE            NULL
#define WINDOWOBJECT_MOUSE           NULL
#define WINDOWOBJECT_ANTTWEAKBAR     false
#define WINDOWOBJECT_WINDOWNAME      "SDL Window"
#define WINDOWOBJECT_OGL_VERSION     430
#define WINDOWOBJECT_STENCIL         8
#define WINDOWOBJECT_DEPTH           24
#define WINDOWOBJECT_MSG_BOX_TITLE   "Message Box"
#define WINDOWOBJECT_MSG_BOX_FLAGS   SDL_MESSAGEBOX_INFORMATION
#define WINDOWOBJECT_MSG_BOX_MSG     "Message"
#define WINDOWOBJECT_KEYS            256
#define WINDOWOBJECT_VERSION         430
#define WINDOWOBJECT_PROFILE         SDL_GL_CONTEXT_PROFILE_CORE
#define WINDOWOBJECT_CONTEXTFLAG     SDL_GL_CONTEXT_DEBUG_FLAG
#define WINDOWOBJECT_PROFILETEXT     "core"
#define WINDOWOBJECT_CONTEXTFLAGTEXT "debug"

#include<SDL2/SDL.h>

namespace ge{
  namespace util{
    struct GEAD_EXPORT ContextParam{
      unsigned    version;
      std::string profile;
      std::string flag;
    };
    struct GEAD_EXPORT WindowParam{
      unsigned size[2];
      bool     fullscreen;
    };

    class GEAD_EXPORT WindowObject
    {
      protected:
        unsigned _windowSize[2];//size of window
        bool     _isFullScreen;//true if fullscreen is on
        bool     _keyDown [WINDOWOBJECT_KEYS];//1 if key is down
        bool     _keyOffOn[WINDOWOBJECT_KEYS];//1 if key was pressed odd times
        bool     _keyHit  [WINDOWOBJECT_KEYS];
        bool     _mouseLeftDown;   //1 if left button of mouse is down
        bool     _mouseLeftOffOn;  //1 if left button of mouse was pressed odd times
        bool     _mouseRightDown;  //1 if right button of mouse is down
        bool     _mouseRightOffOn; //1 if right button of mouse was pressed odd times
        bool     _mouseMiddleDown; //1 if middle button of mouse is down
        bool     _mouseMiddleOffOn;//1 if middle button of mouse was pressd odd times
        int      _mousePosition     [2];//position of mouse cursor
        int      _mouseLastPosition [2];//prev. position of mouse
        int      _mouseDeltaPosition[2];//curr. position - prev. position of mouse
        bool     _warpMouse;//if true set mouse position to the center of the screen
        bool     _running;  //if true application is running
        bool     _useAntTweakBar;//use anttweakbar flag
        Uint32   _elapsedTime;//elapsed time
        Uint32   _lastMouseTime;//last mouse time
        Uint32   _lastIdleTime;//last idle time
        Uint32   _currentMouseTime;//current mouse time
        Uint32   _currentIdleTime;//current idle time
        std::map<SDL_Keycode,bool>_mapKeyDown;
        std::map<SDL_Keycode,bool>_mapKeyOffOn;
        std::map<SDL_Keycode,bool>_mapKeyHit;
        SDL_Window    *_mainWindow;
        SDL_GLContext  _mainContext;

        void(*_idle )(); //idle call back function
        void(*_mouse)();//mouse call back function
        void _constructor(
            unsigned width,
            unsigned height,
            bool     fullScreen,
            void(*Idle )(),
            void(*Mouse)(),
            bool              useAntTweakBar,
            unsigned          version,
            SDL_GLprofile     profile,
            SDL_GLcontextFlag contextFlag);
      public:
        WindowObject(
            unsigned       width          = WINDOWOBJECT_WIDTH,
            unsigned       height         = WINDOWOBJECT_HEIGHT,
            bool           fullScreen     = WINDOWOBJECT_FULLSCREEN,
            void(*Idle )()                = WINDOWOBJECT_IDLE,
            void(*Mouse)()                = WINDOWOBJECT_MOUSE,
            bool           useAntTweakBar = WINDOWOBJECT_ANTTWEAKBAR,
            unsigned       version        = WINDOWOBJECT_VERSION,
            std::string    profile        = WINDOWOBJECT_PROFILETEXT,
            std::string    contextFlag    = WINDOWOBJECT_CONTEXTFLAGTEXT
            );

        ~WindowObject();
        SDL_GLContext  getContext()const;
        SDL_Window    *getWindow ()const;
        void messageBox(
            std::string message = WINDOWOBJECT_MSG_BOX_MSG,
            std::string title   = WINDOWOBJECT_MSG_BOX_TITLE,
            Uint32      flags   = WINDOWOBJECT_MSG_BOX_FLAGS);
        void changeTitle(const char*title);
        void mainLoop    ();
        void stopMainLoop();
        void swap        ()const;
        void setIdle (void(*idle )());
        void setMouse(void(*mouse)());
        float     getDeltaIdleTime ()const;
        float     getDeltaMouseTime()const;
        int const* getMousePosition     ()const;
        int const* getDeltaMousePosition()const;
        void      setMouseWarp(bool wrapMouse);
        unsigned const* getWindowSize()const;

        bool wasKeyHit(int  key);
        bool isKeyDown(int  key);
        bool isKeyOn  (int  key);
        bool isLeftDown  ()const;
        bool isLeftOn    ()const;
        bool isRightDown ()const;
        bool isRightOn   ()const;
        bool isMiddleDown()const;
        bool isMiddleOn  ()const;
        void setKeyOn(int k);
    };
  }//util
}//ge

