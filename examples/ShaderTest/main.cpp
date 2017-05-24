#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geGL/StaticCalls.h>
#include<geAd/SDLWindow/SDLWindow.h>
#include<geGL/OpenGLCommands.h>
#include<geGL/OpenGLContext.h>

struct Application{
  std::shared_ptr<ge::ad::SDLMainLoop>mainLoop = nullptr;
  std::shared_ptr<ge::ad::SDLWindow>  window   = nullptr;
  std::shared_ptr<ge::gl::Program>    program0 = nullptr;
  std::shared_ptr<ge::gl::Program>    program1 = nullptr;
  std::shared_ptr<ge::gl::VertexArray>emptyVAO = nullptr;
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

  this->emptyVAO->bind();
  this->program0->use();
  ge::gl::glDrawArrays(GL_TRIANGLE_STRIP,0,3);
  this->program1->use();
  this->program1->set4f("color",0,1,1,0);
  ge::gl::glDrawArrays(GL_TRIANGLE_STRIP,0,3);
  this->emptyVAO->unbind();

  this->window->swap();
}

namespace ge{
  namespace core{
    template<>
      inline GLuint convertTo(std::shared_ptr<ge::gl::Shader>const&d){
        return d->getId();
        d->getType();
      }
    template<>
      inline GLuint convertTo(GLuint const& d){
        return d;
      }
  }
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
      "void main(){gl_Position = vec4(gl_VertexID%2,gl_VertexID/2,0,1);}");
  auto vp1 = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,
      "#version 450\n",
      "void main(){gl_Position = vec4(gl_VertexID%2-1,gl_VertexID/2-1,0,1);}");
  auto fp0 = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,
      "#version 450\n",
      "out vec4 fColor;\n"
      "void main(){fColor = vec4(1);}");
  this->program0 = std::make_shared<ge::gl::Program>(vp0,fp0);
  this->program1 = std::make_shared<ge::gl::Program>(vp1,fp0);

  //change fragment shader, both programs should be affected
  fp0->compile("#version 450\n",
      "out vec4 fColor;\n"
      "uniform vec4 color = vec4(0,0,1,0);\n"
      "void main(){fColor = color;}");

  this->emptyVAO = std::make_shared<ge::gl::VertexArray>();

  GLubyte const*d;
  auto cmd = ge::gl::createCommand(&ge::gl::Context::glGetString,&d,(GLuint)GL_VERSION);
  (*cmd)();
  std::cout<<d<<std::endl;

  
  auto sharedShader = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER);
  bool output = false;
  auto cmd2 = ge::gl::createCommand(&ge::gl::Context::glIsShader,&output,sharedShader);
  (*cmd2)();
  std::cout<<"isShader? "<<output<<std::endl;
  return true;
}
