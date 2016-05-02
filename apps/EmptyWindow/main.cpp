#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geUtil/NamespaceWithUsers.h>
#include<geUtil/copyArgumentManager2Namespace.h>
#include<geUtil/ArgumentManager/ArgumentManager.h>
#include<geAd/WindowObject/WindowObject.h>

struct Data{
  std::shared_ptr<ge::core::TypeRegister>           typeRegister = nullptr;
  std::shared_ptr<ge::util::sim::NamespaceWithUsers>sData        = nullptr;
  std::shared_ptr<ge::gl::OpenGLFunctionProvider>   gl           = nullptr;
  std::shared_ptr<ge::util::SDLEventProc>           mainLoop     = nullptr;
  std::shared_ptr<ge::util::SDLWindow>              window       = nullptr;
};

void init(Data*data);
void windowEvent(Data*data,SDL_Event event);
void idle(Data*data);
void mouse();


int main(int argc,char*argv[]){
  Data data;
  data.typeRegister = std::make_shared<ge::core::TypeRegister>();
  data.sData        = std::make_shared<ge::util::sim::NamespaceWithUsers>("*");
  auto argm = std::make_shared<ge::util::ArgumentManager>(argc-1,argv+1);
  ge::util::sim::copyArgumentManager2Namespace(data.sData,&*argm,data.typeRegister);

  data.mainLoop = std::make_shared<ge::util::SDLEventProc>();
  data.window   = std::make_shared<ge::util::SDLWindow>();
  data.window->createContext("rendering");
  data.window->setIdleCallback((ge::util::SDLWindow::Callback)idle,&data);
  data.window->setEventCallback(SDL_WINDOWEVENT,(ge::util::SDLWindow::EventCallback)windowEvent,&data);
  data.mainLoop->addWindow("primaryWindow",data.window);
  init(&data);
  (*data.mainLoop)();

  return EXIT_SUCCESS;
}

void idle(Data*data){
  data->gl->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  data->window->swap();
}

void windowEvent(Data*data,SDL_Event event){
  if(event.window.event==SDL_WINDOWEVENT_CLOSE){
    data->mainLoop->removeWindow("primaryWindow");
  }
}

void init(Data*data){
  data->window->makeCurrent("rendering");
  ge::gl::init();
  data->gl = std::make_shared<ge::gl::OpenGLFunctionProvider>(ge::gl::prepareOpenGLFunctionTable((ge::gl::GET_PROC_ADDRESS)SDL_GL_GetProcAddress));

  data->gl->glEnable(GL_DEPTH_TEST);
  data->gl->glDepthFunc(GL_LEQUAL);
  data->gl->glDisable(GL_CULL_FACE);
  data->gl->glClearColor(0,1,0,1);
}
