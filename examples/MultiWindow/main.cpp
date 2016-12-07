#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geGL/StaticCalls.h>
#include<geAd/SDLWindow/SDLWindow.h>

using namespace ge::gl;
using namespace ge::ad;

int main(int,char*[]){
  auto mainLoop = std::make_shared<SDLMainLoop>();
  auto window0  = std::make_shared<SDLWindow>(1024,768);
  auto window1  = std::make_shared<SDLWindow>(800,600);
  if(!window0->createContext("rendering")){
    std::cerr<<"Error: Can not create OpenGL context."<<std::endl;
    return EXIT_FAILURE;
  }
  window1->setContext("rendering",*window0,"rendering");
  mainLoop->addWindow("window0",window0);
  mainLoop->addWindow("window1",window1);

  ge::gl::init(SDL_GL_GetProcAddress);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDisable(GL_CULL_FACE);

  mainLoop->setIdleCallback([&]{
    window0->makeCurrent("rendering");
    glClearColor(0,1,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    window0->swap();
    window1->makeCurrent("rendering");
    glClearColor(1,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    window1->swap();
  });

  (*mainLoop)();
  return EXIT_SUCCESS;
}

