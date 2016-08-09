#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geAd/SDLWindow/SDLWindow.h>

struct Data{
  std::shared_ptr<ge::gl::opengl::Context>gl       = nullptr;
  std::shared_ptr<ge::ad::SDLMainLoop>    mainLoop = nullptr;
  std::shared_ptr<ge::ad::SDLWindow>      window   = nullptr;
  std::shared_ptr<ge::gl::Program>program0 = nullptr;
  std::shared_ptr<ge::gl::VertexArray>vao = nullptr;
  std::shared_ptr<ge::gl::Buffer>vbo = nullptr;
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
  data.window->createContext("rendering",450u,ge::ad::SDLWindow::CORE,ge::ad::SDLWindow::DEBUG);
  data.window->setEventCallback(SDL_WINDOWEVENT,std::make_shared<Data::WindowEventCallback>(&data));
  data.mainLoop->addWindow("primaryWindow",data.window);
  data.init(&data);
  (*data.mainLoop)();

  return EXIT_SUCCESS;
}

void Data::IdleCallback::operator()(){
  this->data->gl->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  this->data->vao->bind();
  this->data->program0->use();
  this->data->gl->glDrawArrays(GL_LINE_STRIP,0,4);
  this->data->vao->unbind();

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
  data->gl = ge::gl::opengl::getDefaultContext();
  ge::gl::setHighDebugMessage();

  data->gl->glEnable(GL_DEPTH_TEST);
  data->gl->glDepthFunc(GL_LEQUAL);
  data->gl->glDisable(GL_CULL_FACE);
  data->gl->glClearColor(0,1,0,1);
  auto vp0 = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,
      "#version 450\n",
      "layout(location=0)in float h;\n"
      "void main(){gl_Position = vec4(gl_VertexID/10.,h,0,1);}");
  auto fp0 = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,
      "#version 450\n",
      "out vec4 fColor;\n"
      "void main(){fColor = vec4(1);}");
  data->program0 = std::make_shared<ge::gl::Program>(vp0,fp0);

  data->vao = std::make_shared<ge::gl::VertexArray>();
  float d[2]={0,.5};
  data->vbo = std::make_shared<ge::gl::Buffer>(sizeof(float)*2,d);
  data->vao->addAttrib(data->vbo,0,1,GL_FLOAT);

  data->vbo->realloc(sizeof(float)*4);
  float dd[4]={.5,0,.5,0};
  data->vbo->setData(dd);
}
