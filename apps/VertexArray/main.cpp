#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geGL/Shader.h>
#include<geGL/Program.h>
#include<geDE/NamespaceWithUsers.h>
#include<geUtil/copyArgumentManager2Namespace.h>
#include<geUtil/ArgumentManager/ArgumentManager.h>
#include<geAd/SDLWindow/SDLWindow.h>
#include<geAd/SDLWindow/SDLEventProc.h>
#include<geAd/SDLWindow/EventHandlerInterface.h>
#include<geAd/SDLWindow/EventCallbackInterface.h>
#include<geAd/SDLWindow/CallbackInterface.h>
#include<geAd/SDLWindow/SDLEventData.h>

struct Data{
  std::shared_ptr<ge::de::TypeRegister>             typeRegister = nullptr;
  std::shared_ptr<ge::de::NamespaceWithUsers>       sData        = nullptr;
  std::shared_ptr<ge::gl::opengl::FunctionProvider> gl           = nullptr;
  std::shared_ptr<ge::util::SDLEventProc>           mainLoop     = nullptr;
  std::shared_ptr<ge::util::SDLWindow>              window       = nullptr;
  std::shared_ptr<ge::gl::Program>program0 = nullptr;
  std::shared_ptr<ge::gl::VertexArray>vao = nullptr;
  std::shared_ptr<ge::gl::Buffer>vbo = nullptr;
  static void init(Data*data);
  class IdleCallback: public ge::util::CallbackInterface{
    public:
      Data*data;
      IdleCallback(Data*data){this->data = data;}
      virtual void operator()()override;
      virtual ~IdleCallback(){}
  };
  class WindowEventCallback: public ge::util::EventCallbackInterface{
    public:
      Data*data;
      WindowEventCallback(Data*data){this->data = data;}
      virtual bool operator()(ge::util::EventDataPointer const&)override;
      virtual ~WindowEventCallback(){}
  };
};



int main(int argc,char*argv[]){
  Data data;
  data.typeRegister = std::make_shared<ge::de::TypeRegister>();
  data.sData        = std::make_shared<ge::de::NamespaceWithUsers>("*");
  auto argm = std::make_shared<ge::util::ArgumentManager>(argc-1,argv+1);
  ge::util::sim::copyArgumentManager2Namespace(data.sData,&*argm,data.typeRegister);

  data.mainLoop = std::make_shared<ge::util::SDLEventProc>();
  data.mainLoop->setIdleCallback(std::make_shared<Data::IdleCallback>(&data));

  data.window   = std::make_shared<ge::util::SDLWindow>();
  data.window->createContext("rendering",450u,ge::util::SDLWindow::CORE,ge::util::SDLWindow::DEBUG);
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

bool Data::WindowEventCallback::operator()(ge::util::EventDataPointer const&event){
  auto sdlEventData = (ge::util::SDLEventData const*)(event);
  if(sdlEventData->event.window.event==SDL_WINDOWEVENT_CLOSE){
    this->data->mainLoop->removeWindow("primaryWindow");
    return true;
  }
  return false;
}

void Data::init(Data*data){
  data->window->makeCurrent("rendering");

  ge::gl::init(std::make_shared<ge::gl::opengl::DefaultLoader>((ge::gl::opengl::GET_PROC_ADDRESS)SDL_GL_GetProcAddress));
  data->gl = ge::gl::opengl::getDefaultFunctionProvider();
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
