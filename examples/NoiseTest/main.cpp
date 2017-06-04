#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geGL/StaticCalls.h>
#include<geGL/GLSLNoise.h>
#include<geUtil/Timer.h>
#include<geAd/SDLWindow/SDLWindow.h>

struct Application{
  std::shared_ptr<ge::ad::SDLMainLoop>mainLoop            = nullptr;
  std::shared_ptr<ge::ad::SDLWindow>  window              = nullptr;
  std::shared_ptr<ge::gl::Program>    hilbertProgram      = nullptr;
  std::shared_ptr<ge::gl::VertexArray>vao                 = nullptr;
  uint32_t                            hilbertLevel        = 5      ;
  ge::util::Timer<float>              timer                        ;
  size_t                              framesPerEvaluation = 60     ;
  float                               timeAccumulator     = 0.f    ;
  size_t                              elapsedFrames       = 0      ;
  bool init();
  void idle();
  template<bool DOWN>
  bool key(SDL_Event const&);
};

int main(int,char*[]){
  Application app;
  if(!app.init())return EXIT_FAILURE;
  (*app.mainLoop)();
  return EXIT_SUCCESS;
}

void Application::idle(){
  assert(this);
  ge::gl::glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  this->vao->bind();
  this->hilbertProgram->use();
  ge::gl::glFinish();
  this->timer.reset();
  ge::gl::glDrawArrays(GL_TRIANGLE_STRIP,0,4);
  ge::gl::glFinish();
  this->timeAccumulator += this->timer.elapsedFromStart();
  this->elapsedFrames++;
  if((this->elapsedFrames % this->framesPerEvaluation) == 0){
    std::cout << static_cast<float>(this->elapsedFrames)/this->timeAccumulator << std::endl;
  }

  this->vao->unbind();

  this->window->swap();
}

template<bool DOWN>bool Application::key(SDL_Event const&event){
  if(DOWN){
    if(event.key.keysym.sym=='a')this->hilbertLevel++;
    if(event.key.keysym.sym=='d')this->hilbertLevel--;
    uint32_t maxLevel = 10;
    uint32_t minLevel = 1;
    if(this->hilbertLevel< minLevel)this->hilbertLevel=maxLevel;
    if(this->hilbertLevel> maxLevel)this->hilbertLevel=minLevel;
  }
  return true;
}

bool Application::init(){
  this->mainLoop = std::make_shared<ge::ad::SDLMainLoop>();
  this->mainLoop->setIdleCallback(std::bind(&Application::idle,this));

  this->window   = std::make_shared<ge::ad::SDLWindow>(512,512);
  this->window->createContext("rendering",450u,ge::ad::SDLWindow::CORE,ge::ad::SDLWindow::DEBUG);
  this->window->setEventCallback(SDL_KEYDOWN,std::bind(&Application::key<true >,this,std::placeholders::_1));
  this->window->setEventCallback(SDL_KEYUP  ,std::bind(&Application::key<false>,this,std::placeholders::_1));
  this->mainLoop->addWindow("primaryWindow",this->window);

  this->window->makeCurrent("rendering");

  ge::gl::init();
  ge::gl::setHighDebugMessage();

  ge::gl::glEnable(GL_DEPTH_TEST);
  ge::gl::glDepthFunc(GL_LEQUAL);
  ge::gl::glDisable(GL_CULL_FACE);
  ge::gl::glClearColor(0,0,0,1);
  auto vp0 = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,R".(
#version 450 core
void main(){
  gl_Position = vec4(-1.f+2.f*(gl_VertexID&1),-1.f+2.f*(gl_VertexID>>1),0,1);
}
).");
  auto fp0 = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,
      "#version 450 core\n",
      ge::gl::getNoiseSource(),
R".(
out vec4 fColor;
void main(){
  fColor = vec4(noiseU(uvec2(gl_FragCoord.xy))*.5+.5);
}
).");
  this->hilbertProgram = std::make_shared<ge::gl::Program>(vp0,fp0);
  this->vao = std::make_shared<ge::gl::VertexArray>();
  return true;
}
