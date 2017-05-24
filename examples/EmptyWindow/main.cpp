#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geAd/SDLWindow/SDLWindow.h>
#include<geGL/StaticCalls.h>

class Application{
  public:
    std::shared_ptr<ge::ad::SDLMainLoop>mainLoop = nullptr;
    std::shared_ptr<ge::ad::SDLWindow>  window   = nullptr;
    bool init();
    void idle();
};

int main(int,char*[]){
  Application app;
  if(!app.init())return EXIT_FAILURE;
  (*app.mainLoop)();
  return EXIT_SUCCESS;
}

void Application::idle(){
  ge::gl::glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  this->window->swap();
}

bool Application::init(){
  this->mainLoop = std::make_shared<ge::ad::SDLMainLoop>();
  this->mainLoop->setIdleCallback(std::bind(&Application::idle,this));

  this->window   = std::make_shared<ge::ad::SDLWindow>();
  if(!this->window->createContext("rendering",330,ge::ad::SDLWindow::CORE)){
    std::cerr<<"Error: Can not create OpenGL context."<<std::endl;
    return false;
  }
  this->mainLoop->addWindow("primaryWindow",this->window);

  this->window->makeCurrent("rendering");
  ge::gl::init();

  ge::gl::glEnable(GL_DEPTH_TEST);
  ge::gl::glDepthFunc(GL_LEQUAL);
  ge::gl::glDisable(GL_CULL_FACE);
  ge::gl::glClearColor(0,1,0,1);
  return true;
}
