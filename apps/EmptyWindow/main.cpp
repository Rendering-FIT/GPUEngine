#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geUtil/NamespaceWithUsers.h>
#include<geUtil/copyArgumentManager2Namespace.h>
#include<geUtil/ArgumentManager/ArgumentManager.h>
#include<geAd/SDLWindow/SDLWindow.h>
#include<geAd/SDLWindow/SDLEventProc.h>
#include<geAd/SDLWindow/EventHandlerInterface.h>
#include<geAd/SDLWindow/EventCallbackInterface.h>
#include<geAd/SDLWindow/CallbackInterface.h>
#include<geAd/SDLWindow/SDLEventData.h>

struct Data{
  std::shared_ptr<ge::core::TypeRegister>           typeRegister = nullptr;
  std::shared_ptr<ge::util::sim::NamespaceWithUsers>sData        = nullptr;
  std::shared_ptr<ge::gl::opengl::FunctionProvider> gl           = nullptr;
  std::shared_ptr<ge::util::SDLEventProc>           mainLoop     = nullptr;
  std::shared_ptr<ge::util::SDLWindow>              window       = nullptr;
  static void init(Data*data);
  class IdleCallback: public ge::util::CallbackInterface{
    public:
      Data*data;
      IdleCallback(Data*data){this->data = data;}
      virtual void operator()()override;
      virtual ~IdleCallback(){}
  };
  class WindowEventCallback: public ge::util::EventCallbackInterface{
    public:
      Data*data;
      WindowEventCallback(Data*data){this->data = data;}
      virtual void operator()(ge::util::EventDataPointer const&)override;
      virtual ~WindowEventCallback(){}
  };
};



int main(int argc,char*argv[]){
  Data data;
  data.typeRegister = std::make_shared<ge::core::TypeRegister>();
  data.sData        = std::make_shared<ge::util::sim::NamespaceWithUsers>("*");
  auto argm = std::make_shared<ge::util::ArgumentManager>(argc-1,argv+1);
  ge::util::sim::copyArgumentManager2Namespace(data.sData,&*argm,data.typeRegister);

  data.mainLoop = std::make_shared<ge::util::SDLEventProc>();
  data.mainLoop->setIdleCallback(std::make_shared<Data::IdleCallback>(&data));

  data.window   = std::make_shared<ge::util::SDLWindow>();
  data.window->createContext("rendering",330,ge::util::SDLWindow::COMPATIBILITY);
  data.window->setEventCallback(SDL_WINDOWEVENT,std::make_shared<Data::WindowEventCallback>(&data));
  data.mainLoop->addWindow("primaryWindow",data.window);
  data.init(&data);
  (*data.mainLoop)();

  return EXIT_SUCCESS;
}

void Data::IdleCallback::operator()(){
  this->data->gl->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  this->data->window->swap();
}

void Data::WindowEventCallback::operator()(ge::util::EventDataPointer const&event){
  auto sdlEventData = (ge::util::SDLEventData const*)(event);
  if(sdlEventData->event.window.event==SDL_WINDOWEVENT_CLOSE){
    this->data->mainLoop->removeWindow("primaryWindow");
  }
}

void Data::init(Data*data){
  data->window->makeCurrent("rendering");
  ge::gl::init();
  data->gl = std::make_shared<ge::gl::opengl::FunctionProvider>(ge::gl::opengl::prepareFunctionTable((ge::gl::opengl::GET_PROC_ADDRESS)SDL_GL_GetProcAddress));

  data->gl->glEnable(GL_DEPTH_TEST);
  data->gl->glDepthFunc(GL_LEQUAL);
  data->gl->glDisable(GL_CULL_FACE);
  data->gl->glClearColor(0,1,0,1);
}
