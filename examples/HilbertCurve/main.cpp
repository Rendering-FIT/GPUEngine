#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geAd/SDLWindow/SDLWindow.h>

struct Application{
  std::shared_ptr<ge::gl::Context>    gl             = nullptr;
  std::shared_ptr<ge::ad::SDLMainLoop>mainLoop       = nullptr;
  std::shared_ptr<ge::ad::SDLWindow>  window         = nullptr;
  std::shared_ptr<ge::gl::Program>    hilbertProgram = nullptr;
  std::shared_ptr<ge::gl::VertexArray>vao            = nullptr;
  uint32_t                            hilbertLevel   = 5      ;
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
  this->gl->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  this->vao->bind();
  this->hilbertProgram->use();
  this->hilbertProgram->set1ui("hilbertLevel",this->hilbertLevel);
  this->gl->glDrawArrays(GL_LINE_STRIP,0,1<<(2*this->hilbertLevel));
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

  ge::gl::init(SDL_GL_GetProcAddress);
  this->gl = ge::gl::getDefaultContext();
  ge::gl::setHighDebugMessage();

  this->gl->glEnable(GL_DEPTH_TEST);
  this->gl->glDepthFunc(GL_LEQUAL);
  this->gl->glDisable(GL_CULL_FACE);
  this->gl->glClearColor(0,0,0,1);
  auto vp0 = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,R".(
#version 450 core
uniform uint hilbertLevel = 3;
void main(){
  const uint hilbertMapping = 0x7E2BD481;
  const uint hilbertOffset = 0x4B8778B4;
  uint currentSquare = 0;
  uvec2 coord = uvec2(0,0);
  for(int l=int(hilbertLevel)-1;l>=0;l--){
    coord<<=1;
    uint ii = ((gl_VertexID>>(l<<1))&3)<<1;
    coord+=uvec2((hilbertOffset>>(currentSquare+ii))&1,(hilbertOffset>>(currentSquare+ii+1))&1);
    currentSquare = ((hilbertMapping>>(currentSquare+ii))&3)<<3;
  }
  gl_Position = vec4((vec2(coord)/vec2((1<<hilbertLevel)-1)*2-1)*0.9,0,1);
}
).");
  auto fp0 = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,R".(
#version 450 core
out vec4 fColor;
void main(){
  fColor = vec4(1);
}
).");
  this->hilbertProgram = std::make_shared<ge::gl::Program>(vp0,fp0);
  this->vao = std::make_shared<ge::gl::VertexArray>();
  return true;
}
