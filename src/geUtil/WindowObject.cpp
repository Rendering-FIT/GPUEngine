#include<geUtil/WindowObject.h>

#include<iostream>
#include<AntTweakBar.h>
#include<GL/glew.h>

namespace ge{
  namespace util{

    void WindowObject::_constructor(
        unsigned Width,
        unsigned Height,
        bool FullScreen,
        void(*Idle)(),
        void(*Mouse)(),
        bool UseAntTweakBar,
        unsigned Version,
        SDL_GLprofile Profile,
        SDL_GLcontextFlag ContextFlag){
      this->_mapKeyDown.clear();
      this->_mapKeyOffOn.clear();
      this->_idle=Idle;//set idle function
      this->_mouse=Mouse;//set mouse function
      this->_windowSize[0]=Width;//width of window
      this->_windowSize[1]=Height;//height of window
      this->_isFullScreen=FullScreen;//set fullscreen flag
      this->_useAntTweakBar=UseAntTweakBar;


      SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);//initialise video
#ifdef USE_SDL2
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, Version/100    );
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,(Version%100)/10);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK ,Profile         );
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS        ,ContextFlag     );
#endif//USE_SDL2
      SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,8);
#ifdef USE_SDL2

      /*
         const unsigned ver[]={
         110,120,130,140,150,200,210,300,310,320,330,400,410,420,430,440};
         SDL_Window*w=SDL_CreateWindow("w",0,0,1,1,SDL_WINDOW_OPENGL);

         for(unsigned i=0;i<sizeof(ver)/sizeof(unsigned);++i){
         SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, ver[i]/100    );
         SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,(ver[i]%100)/10);
         SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK ,SDL_GL_CONTEXT_PROFILE_CORE);
         SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS        ,SDL_GL_CONTEXT_DEBUG_FLAG*1);
         SDL_GLContext cont=SDL_GL_CreateContext(w);
         if(cont){
         std::cerr<<"Version: "<<ver[i]<<std::endl;
         std::cerr<<glGetString(GL_VERSION )<<std::endl;
         std::cerr<<glGetString(GL_VENDOR  )<<std::endl;
         std::cerr<<glGetString(GL_RENDERER)<<std::endl;
         }
         if(cont)SDL_GL_DeleteContext(cont);
         }
         if(w)SDL_DestroyWindow(w);

         std::cerr<<"version end\n";
         */

      if(this->_isFullScreen)
        this->_mainWindow=SDL_CreateWindow(
            "SDL2",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            this->_windowSize[0],
            this->_windowSize[1],
            SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN);
      else
        this->_mainWindow=SDL_CreateWindow(
            "SDL2",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            this->_windowSize[0],
            this->_windowSize[1],
            SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
      this->_mainContext=SDL_GL_CreateContext(this->_mainWindow);
#else
      if(this->_isFullScreen)//is fullscreen?
        SDL_SetVideoMode(//set video
            this->WindowSize[0],//width
            this->WindowSize[1],//height
            24,//bit depth
            SDL_HWSURFACE|//hardware surface
            SDL_DOUBLEBUF|//double buffering
            SDL_OPENGL|//OpenGL
            SDL_FULLSCREEN);//fullscreen
      else
        SDL_SetVideoMode(//set video
            this->WindowSize[0],//width
            this->WindowSize[1],//height
            24,//bit depth
            SDL_HWSURFACE|//hardware surface
            SDL_DOUBLEBUF|//double buffering
            SDL_OPENGL);//OpenGL
#endif//USE_SDL2

      for(int i=0;i<256;++i){//loop over keys
        this->_keyDown[i]=0;//key is not down
        this->_keyOffOn[i]=0;//key is off
      }
      if(this->_useAntTweakBar){
        TwInit(TW_OPENGL_CORE,NULL);
        TwWindowSize(this->_windowSize[0],this->_windowSize[1]);
      }

      this->_mouseLeftDown=0;//left mouse button is not down
      this->_mouseLeftOffOn=0;//left mouse button is off
      this->_mouseRightDown=0;//right mouse button is not down
      this->_mouseRightOffOn=0;//right mouse button is off
      this->_mouseMiddleDown=0;//middle mouse button is not down
      this->_mouseMiddleOffOn=0;//middle mouse button is off
      for(int i=0;i<2;++i){
        this->_mousePosition[i]=this->_windowSize[i]/2;
        this->_mouseDeltaPosition[i]=0;
      }
      this->_warpMouse=false;
      this->_running=true;
    }

    WindowObject::WindowObject(
        unsigned Width,
        unsigned Height,
        bool FullScreen,
        void(*Idle)(),
        void(*Mouse)(),
        bool UseAntTweakBar,
        unsigned Version,
        SDL_GLprofile Profile,
        SDL_GLcontextFlag ContextFlag){
      this->_constructor(Width,Height,FullScreen,Idle,Mouse,UseAntTweakBar,Version,Profile,ContextFlag);
    }
    WindowObject::WindowObject(
        unsigned Width,
        unsigned Height,
        bool FullScreen,
        void(*Idle)(),
        void(*Mouse)(),
        bool UseAntTweakBar,
        unsigned Version,
        std::string Profile,
        std::string ContextFlag){
      SDL_GLprofile P=SDL_GL_CONTEXT_PROFILE_CORE;
      if(Profile=="core")P=SDL_GL_CONTEXT_PROFILE_CORE;
      if(Profile=="es")P=SDL_GL_CONTEXT_PROFILE_ES;
      if(Profile=="compatibility")P=SDL_GL_CONTEXT_PROFILE_COMPATIBILITY;
      SDL_GLcontextFlag C=SDL_GL_CONTEXT_DEBUG_FLAG;
      if(ContextFlag=="debug")C=SDL_GL_CONTEXT_DEBUG_FLAG;
      this->_constructor(Width,Height,FullScreen,Idle,Mouse,UseAntTweakBar,Version,P,C);
    }

    /*
       WindowObject::WindowObject(
       unsigned Width,
       unsigned Height,
       bool FullScreen,
       void(*Idle)(),
       void(*Mouse)(),
       bool UseAntTweakBar){
       this->MapKeyDown.clear();
       this->MapKeyOffOn.clear();
       this->Idle=Idle;//set idle function
       this->Mouse=Mouse;//set mouse function
       this->WindowSize[0]=Width;//width of window
       this->WindowSize[1]=Height;//height of window
       this->IsFullScreen=FullScreen;//set fullscreen flag
       this->UseAntTweakBar=UseAntTweakBar;


       SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);//initialise video
#ifdef USE_SDL2
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,SDL_GL_CONTEXT_DEBUG_FLAG);
#endif//USE_SDL2
SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,8);

#ifdef USE_SDL2
if(this->IsFullScreen)
this->MainWindow=SDL_CreateWindow(
"SDL2",
SDL_WINDOWPOS_CENTERED,
SDL_WINDOWPOS_CENTERED,
this->WindowSize[0],
this->WindowSize[1],
SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN);
else
this->MainWindow=SDL_CreateWindow(
"SDL2",
SDL_WINDOWPOS_CENTERED,
SDL_WINDOWPOS_CENTERED,
this->WindowSize[0],
this->WindowSize[1],
SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
this->MainContext=SDL_GL_CreateContext(this->MainWindow);
#else
if(this->IsFullScreen)//is fullscreen?
SDL_SetVideoMode(//set video
this->WindowSize[0],//width
this->WindowSize[1],//height
24,//bit depth
SDL_HWSURFACE|//hardware surface
SDL_DOUBLEBUF|//double buffering
SDL_OPENGL|//OpenGL
SDL_FULLSCREEN);//fullscreen
else
SDL_SetVideoMode(//set video
this->WindowSize[0],//width
this->WindowSize[1],//height
24,//bit depth
SDL_HWSURFACE|//hardware surface
SDL_DOUBLEBUF|//double buffering
SDL_OPENGL);//OpenGL
#endif//USE_SDL2
for(int i=0;i<256;++i){//loop over keys
this->KeyDown[i]=0;//key is not down
this->KeyOffOn[i]=0;//key is off
}
if(this->UseAntTweakBar){
TwInit(TW_OPENGL_CORE,NULL);
    TwWindowSize(this->WindowSize[0],this->WindowSize[1]);
}

this->MouseLeftDown=0;//left mouse button is not down
this->MouseLeftOffOn=0;//left mouse button is off
this->MouseRightDown=0;//right mouse button is not down
this->MouseRightOffOn=0;//right mouse button is off
this->MouseMiddleDown=0;//middle mouse button is not down
this->MouseMiddleOffOn=0;//middle mouse button is off
for(int i=0;i<2;++i){
  this->MousePosition[i]=this->WindowSize[i]/2;
  this->MouseDeltaPosition[i]=0;
}
this->WarpMouse=false;
this->Running=true;
}
*/
WindowObject::~WindowObject(){
  if(this->_useAntTweakBar){
    TwTerminate();
  }
  SDL_GL_DeleteContext(this->_mainContext);
}

SDL_GLContext WindowObject::getContext(){
  return this->_mainContext;
}
SDL_Window*WindowObject::getWindow(){
  return this->_mainWindow;
}
void WindowObject::messageBox(
    std::string Message,
    std::string Title,
    Uint32 flags){
  SDL_ShowSimpleMessageBox(flags,Title.c_str(),Message.c_str(),this->_mainWindow);
}


void WindowObject::mainLoop(){
  SDL_Event E;//event
  int HandledByAntTweakBar=0;
  while(this->_running){//endless loop
    while(SDL_PollEvent(&E)){//loop over events
      if(this->_useAntTweakBar)
        HandledByAntTweakBar=TwEventSDL(&E,
            SDL_MAJOR_VERSION,SDL_MINOR_VERSION);
      if(!HandledByAntTweakBar){//is event handled by AntTweakBar
        switch(E.type){//switch over event types
          case SDL_QUIT://quit main loop
            this->_running=false;//stop running
            break;//break quit case
#ifdef USE_SDL2
          case SDL_KEYDOWN://key down
            if(!this->_mapKeyDown.count(E.key.keysym.sym))
              this->_mapKeyDown.insert(std::pair<SDL_Keycode,int>(E.key.keysym.sym,0));
            if(!this->_mapKeyOffOn.count(E.key.keysym.sym))
              this->_mapKeyOffOn.insert(std::pair<SDL_Keycode,int>(E.key.keysym.sym,0));
            this->_mapKeyDown[E.key.keysym.sym]=1;
            this->_mapKeyOffOn[E.key.keysym.sym]^=1;
            if(E.key.keysym.sym==SDLK_1)exit(0);
            if(E.key.keysym.sym>=WINDOWOBJECT_KEYS)break;

            this->_keyDown [E.key.keysym.sym%WINDOWOBJECT_KEYS]=1;//key is down
            this->_keyOffOn[E.key.keysym.sym%WINDOWOBJECT_KEYS]^=1;//switch key state
            break;//break key down case
          case SDL_KEYUP://key up
            if(!this->_mapKeyDown.count(E.key.keysym.sym))
              this->_mapKeyDown.insert(std::pair<SDL_Keycode,int>(E.key.keysym.sym,0));
            if(!this->_mapKeyOffOn.count(E.key.keysym.sym))
              this->_mapKeyOffOn.insert(std::pair<SDL_Keycode,int>(E.key.keysym.sym,0));
            this->_mapKeyDown[E.key.keysym.sym]=0;
            this->_keyDown[E.key.keysym.sym%WINDOWOBJECT_KEYS]=0;//key is not down
            break;//break key up case
#else
          case SDL_KEYDOWN://key down
            if(!this->_mapKeyDown.count(E.key.keysym.sym))
              this->_mapKeyDown.insert(std::pair<SDLKey,int>(E.key.keysym.sym,0));
            if(!this->_mapKeyOffOn.count(E.key.keysym.sym))
              this->_mapKeyOffOn.insert(std::pair<SDLKey,int>(E.key.keysym.sym,0));
            this->_mapKeyDown[E.key.keysym.sym]=1;
            this->_mapKeyOffOn[E.key.keysym.sym]^=1;
            this->KeyDown[E.key.keysym.sym%WINDOWOBJECT_KEYS]=1;//key is down
            this->KeyOffOn[E.key.keysym.sym%WINDOWOBJECT_KEYS]^=1;//switch key state
            break;//break key down case
          case SDL_KEYUP://key up
            if(!this->_mapKeyDown.count(E.key.keysym.sym))
              this->_mapKeyDown.insert(std::pair<SDLKey,int>(E.key.keysym.sym,0));
            if(!this->_mapKeyOffOn.count(E.key.keysym.sym))
              this->_mapKeyOffOn.insert(std::pair<SDLKey,int>(E.key.keysym.sym,0));
            this->_mapKeyDown[E.key.keysym.sym]=0;
            this->_keyDown[E.key.keysym.sym%WINDOWOBJECT_KEYS]=0;//key is not down
            break;//break key up case
#endif
          case SDL_MOUSEMOTION://mouse motion
            this->_currentMouseTime=SDL_GetTicks();//current mouse time
            this->_mousePosition[0]=E.motion.x;//x position of mouse
            this->_mousePosition[1]=E.motion.y;//y position of mouse
            this->_mouseDeltaPosition[0]=//delta x position
              this->_mousePosition[0]-this->_mouseLastPosition[0];//curr.x-prev.x
            this->_mouseDeltaPosition[1]=//delta y position
              this->_mousePosition[1]-this->_mouseLastPosition[1];//curr.y-prev.y
            if(this->_mouse)this->_mouse();//call mouse function
            this->_lastMouseTime=this->_currentMouseTime;//current is now last
            if(	this->_mousePosition[0]-this->_windowSize[0]/2!=0||//change x
                this->_mousePosition[1]-this->_windowSize[1]/2!=0){//change y
              if(this->_warpMouse)//can we warp mouse position
#ifdef USE_SDL2
                SDL_WarpMouseInWindow(this->_mainWindow,this->_windowSize[0]/2,this->_windowSize[1]/2);//warp
#else
              SDL_WarpMouse(this->_windowSize[0]/2,this->_windowSize[1]/2);//warp
#endif
            }
            this->_mouseLastPosition[0]=this->_mousePosition[0];//copy x position
            this->_mouseLastPosition[1]=this->_mousePosition[1];//copy y position
            break;//break mouse motion case
          case SDL_MOUSEBUTTONDOWN://mouse button down
            if(E.motion.state&SDL_BUTTON_LMASK){
              this->_mouseLeftDown=1;//left mouse button is down
              this->_mouseLeftOffOn^=1;//switch left mouse button state
            }
            if(E.motion.state&SDL_BUTTON_RMASK){
              this->_mouseRightDown=1;//right mouse button is down
              this->_mouseRightOffOn^=1;//switch right mouse button state
            }
            if(E.motion.state&SDL_BUTTON_MMASK){
              this->_mouseMiddleDown=1;//middle mouse button is down
              this->_mouseMiddleOffOn^=1;//switch middle mouse button state
            }
            break;//break mouse button down case
          case SDL_MOUSEBUTTONUP:
            if(E.motion.state&SDL_BUTTON_LMASK)
              this->_mouseLeftDown=0;//left mouse button is not down
            if(E.motion.state&SDL_BUTTON_RMASK)
              this->_mouseRightDown=0;//right mouse button is not down
            if(E.motion.state&SDL_BUTTON_MMASK)
              this->_mouseMiddleDown=0;//middle mouse button is not down
            break;//break mouse button up case
          default://other events
            break;//break other events case
        }
      }
    }
    this->_currentIdleTime=SDL_GetTicks();//get current idle time
    if(this->_idle)//is there idle function?
      this->_idle();//call idel function
    this->_lastIdleTime=this->_currentIdleTime;//current is now last
  }

  if(this->_useAntTweakBar)
    TwTerminate();

  SDL_Quit();
}

void WindowObject::stopMainLoop(){
  this->_running=false;
}

void WindowObject::swap(){
  if(this->_useAntTweakBar)
    TwDraw();//draw tweak bar
#ifdef USE_SDL2
  SDL_GL_SwapWindow(this->_mainWindow);
#else
  SDL_GL_SwapBuffers();
#endif//USE_SDL2
}

void WindowObject::setIdle(void(*Idle)()){
  this->_idle=Idle;
}

void WindowObject::setMouse(void(*Mouse)()){
  this->_mouse=Mouse;
}

float WindowObject::getDeltaIdleTime(){
  return(this->_currentIdleTime-this->_lastIdleTime)*1e-3;
}

float WindowObject::getDeltaMouseTime(){
  return(this->_currentMouseTime-this->_lastMouseTime)*1e-3;
}

int*WindowObject::getMousePosition(){
  return this->_mousePosition;
}

int*WindowObject::getDeltaMousePosition(){
  return this->_mouseDeltaPosition;
}

void WindowObject::setMouseWarp(bool WarpMouse){
  this->_warpMouse=WarpMouse;
}

unsigned*WindowObject::getWindowSize(){
  return this->_windowSize;
}

int WindowObject::isKeyDown(char Key){
  return this->isKeyDown((int)Key);
}

int WindowObject::isKeyOn(char Key){
  return this->isKeyOn((int)Key);
}

int WindowObject::isKeyDown(int Key){
#ifdef USE_SDL2
  if(!this->_mapKeyDown.count((SDL_Keycode)Key))
    this->_mapKeyDown.insert(std::pair<SDL_Keycode,int>((SDL_Keycode)Key,0));
  return this->_mapKeyDown[(SDL_Keycode)Key];
#else
  if(!this->_mapKeyDown.count((SDLKey)Key))
    this->_mapKeyDown.insert(std::pair<SDLKey,int>((SDLKey)Key,0));
  return this->_mapKeyDown[(SDLKey)Key];
#endif//USE_SDL2
}

int WindowObject::isKeyOn(int Key){
#ifdef USE_SDL2
  if(!this->_mapKeyOffOn.count((SDL_Keycode)Key))
    this->_mapKeyOffOn.insert(std::pair<SDL_Keycode,int>((SDL_Keycode)Key,0));
  return this->_mapKeyOffOn[(SDL_Keycode)Key];
#else
  if(!this->_mapKeyOffOn.count((SDLKey)Key))
    this->_mapKeyOffOn.insert(std::pair<SDLKey,int>((SDLKey)Key,0));
  return this->_mapKeyOffOn[(SDLKey)Key];
#endif//USE_SDL2
}

int WindowObject::isLeftDown(){
  return this->_mouseLeftDown;
}

int WindowObject::isLeftOn(){
  return this->_mouseLeftOffOn;
}

int WindowObject::isRightDown(){
  return this->_mouseRightDown;
}

int WindowObject::isRightOn(){
  return this->_mouseRightOffOn;
}

int WindowObject::isMiddleDown(){
  return this->_mouseMiddleDown;
}

int WindowObject::isMiddleOn(){
  return this->_mouseMiddleOffOn;
}
void WindowObject::setKeyOn(int k){
  this->_keyOffOn[k]=1;
#ifdef USE_SDL2
  if(!this->_mapKeyOffOn.count((SDL_Keycode)k))
    this->_mapKeyOffOn.insert(std::pair<SDL_Keycode,int>((SDL_Keycode)k,0));
  this->_mapKeyOffOn[(SDL_Keycode)k]=1;
#else
  if(!this->_mapKeyOffOn.count((SDLKey)k))
    this->_mapKeyOffOn.insert(std::pair<SDLKey,int>((SDLKey)k,0));
  this->_mapKeyOffOn[(SDLKey)k]=1;
#endif//USE_SDL2
}
}//util
}//ge
