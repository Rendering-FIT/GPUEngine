#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geAd/SDLWindow/SDLWindow.h>

struct Data{
  std::shared_ptr<ge::gl::Context>        gl       = nullptr;
  std::shared_ptr<ge::ad::SDLMainLoop>    mainLoop = nullptr;
  std::shared_ptr<ge::ad::SDLWindow>      window   = nullptr;
  static void init(Data*data);
  class IdleCallback: public ge::ad::SDLCallbackInterface{
    public:
      Data*data;
      IdleCallback(Data*data){this->data = data;}
      virtual void operator()()override;
      virtual ~IdleCallback(){}
  };
  class WindowEventCallback: public ge::ad::SDLEventCallbackInterface{
    public:
      Data*data;
      WindowEventCallback(Data*data){this->data = data;}
      virtual bool operator()(SDL_Event const&)override;
      virtual ~WindowEventCallback(){}
  };
};



int main(int,char*[]){
  Data data;

  data.mainLoop = std::make_shared<ge::ad::SDLMainLoop>();
  data.mainLoop->setIdleCallback(std::make_shared<Data::IdleCallback>(&data));

  data.window   = std::make_shared<ge::ad::SDLWindow>();
  if(!data.window->createContext("rendering",330,ge::ad::SDLWindow::CORE)){
     std::cout<<"Error: Can not create OpenGL context."<<std::endl;
     return EXIT_FAILURE;
  }
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

bool Data::WindowEventCallback::operator()(SDL_Event const&event){
  if(event.window.event==SDL_WINDOWEVENT_CLOSE){
    this->data->mainLoop->removeWindow("primaryWindow");
    return true;
  }
  return false;
}

void Data::init(Data*data){
  data->window->makeCurrent("rendering");
  ge::gl::init(SDL_GL_GetProcAddress);
  data->gl = ge::gl::getDefaultContext();

  data->gl->glEnable(GL_DEPTH_TEST);
  data->gl->glDepthFunc(GL_LEQUAL);
  data->gl->glDisable(GL_CULL_FACE);
  data->gl->glClearColor(0,1,0,1);
}
