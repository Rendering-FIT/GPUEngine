#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geGL/StaticCalls.h>
#include<geAd/SDLWindow/SDLWindow.h>

struct Application{
  std::shared_ptr<ge::ad::SDLMainLoop>mainLoop = nullptr;
  std::shared_ptr<ge::ad::SDLWindow>  window   = nullptr;
  std::shared_ptr<ge::gl::Program>    program0 = nullptr;
  std::shared_ptr<ge::gl::VertexArray>vao      = nullptr;
  std::shared_ptr<ge::gl::Buffer>     vbo      = nullptr;
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

  this->vao->bind();
  this->program0->use();
  ge::gl::glDrawArrays(GL_LINE_STRIP,0,4);
  this->vao->unbind();

  this->window->swap();
}

bool Application::init(){
  this->mainLoop = std::make_shared<ge::ad::SDLMainLoop>();
  this->mainLoop->setIdleCallback(std::bind(&Application::idle,this));

  this->window   = std::make_shared<ge::ad::SDLWindow>();
  this->window->createContext("rendering",450u,ge::ad::SDLWindow::CORE,ge::ad::SDLWindow::DEBUG);
  this->mainLoop->addWindow("primaryWindow",this->window);

  this->window->makeCurrent("rendering");

  ge::gl::init();
  ge::gl::setHighDebugMessage();

  ge::gl::glEnable(GL_DEPTH_TEST);
  ge::gl::glDepthFunc(GL_LEQUAL);
  ge::gl::glDisable(GL_CULL_FACE);
  ge::gl::glClearColor(0,1,0,1);
  auto vp0 = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,
      "#version 450\n",
      "layout(location=0)in float h;\n"
      "void main(){gl_Position = vec4(gl_VertexID/10.,h,0,1);}");
  auto fp0 = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,
      "#version 450\n",
      "out vec4 fColor;\n"
      "void main(){fColor = vec4(1);}");
  this->program0 = std::make_shared<ge::gl::Program>(vp0,fp0);

  this->vao = std::make_shared<ge::gl::VertexArray>();
  float d[2]={0,.5};
  this->vbo = std::make_shared<ge::gl::Buffer>(sizeof(float)*2,d);
  this->vao->addAttrib(this->vbo,0,1,GL_FLOAT);

  this->vbo->realloc(sizeof(float)*4);
  float dd[4]={.5,0,.5,0};
  this->vbo->setData(dd);
  return true;
}
