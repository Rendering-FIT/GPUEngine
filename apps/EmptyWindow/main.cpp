#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geAd/SDLWindow/SDLWindow.h>

class Application{
  public:
    std::shared_ptr<ge::gl::Context>    gl       = nullptr;
    std::shared_ptr<ge::ad::SDLMainLoop>mainLoop = nullptr;
    std::shared_ptr<ge::ad::SDLWindow>  window   = nullptr;
    bool init();
    static void idle(void*);
};

int main(int,char*[]){
  Application app;
  if(!app.init())return EXIT_FAILURE;
  (*app.mainLoop)();
  return EXIT_SUCCESS;
}

void Application::idle(void*d){
  auto app = (Application*)d;
  app->gl->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  app->window->swap();
}

bool Application::init(){
  this->mainLoop = std::make_shared<ge::ad::SDLMainLoop>();
  this->mainLoop->setIdleCallback(Application::idle,this);

  this->window   = std::make_shared<ge::ad::SDLWindow>();
  if(!this->window->createContext("rendering",330,ge::ad::SDLWindow::CORE)){
    std::cerr<<"Error: Can not create OpenGL context."<<std::endl;
    return false;
  }
  this->mainLoop->addWindow("primaryWindow",this->window);

  this->window->makeCurrent("rendering");
  ge::gl::init(SDL_GL_GetProcAddress);
  this->gl = ge::gl::getDefaultContext();

  this->gl->glEnable(GL_DEPTH_TEST);
  this->gl->glDepthFunc(GL_LEQUAL);
  this->gl->glDisable(GL_CULL_FACE);
  this->gl->glClearColor(0,1,0,1);
  return true;
}
