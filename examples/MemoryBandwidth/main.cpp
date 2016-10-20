#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geAd/SDLWindow/SDLWindow.h>

const size_t FLOATS_PER_THREAD = 32;
const size_t COMPUTE_UNITS = 20;
const size_t WAVEFRONT_SIZE = 64;
const size_t WAVEFRONTS_PER_COMPUTE_UNIT = 2048;
const size_t NOF_THREADS = WAVEFRONT_SIZE*COMPUTE_UNITS*WAVEFRONTS_PER_COMPUTE_UNIT;
const size_t READBUFFER_SIZE_IN_FLOATS = NOF_THREADS*FLOATS_PER_THREAD;
const size_t WORKGROUP_SIZE = 64;
const size_t NOF_WORKGROUPS = NOF_THREADS/WORKGROUP_SIZE;
const size_t BYTES_PER_FLOAT = 4;
const size_t GIGA = 1024*1024*1024;
const size_t NANOSECONDS_IN_SECOND = 1000000000;
const size_t ITERATIONS = 50;

struct Application{
  std::shared_ptr<ge::gl::Context>          gl       = nullptr;
  std::shared_ptr<ge::ad::SDLMainLoop>      mainLoop = nullptr;
  std::shared_ptr<ge::ad::SDLWindow>        window   = nullptr;
  std::shared_ptr<ge::gl::Program>          program  = nullptr;
  std::shared_ptr<ge::gl::Buffer>           data     = nullptr;
  std::shared_ptr<ge::gl::AsynchronousQuery>query    = nullptr;
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
  assert(this);
  this->gl->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  this->program->use();

  this->data->bindBase(GL_SHADER_STORAGE_BUFFER,0);
  this->gl->glFinish();
  this->query->begin();
  for(size_t i=0;i<ITERATIONS;++i)
    this->gl->glDispatchCompute(NOF_WORKGROUPS,1,1);
  this->query->end();
  this->gl->glFinish();
  auto elapsedTime = this->query->getui64();


  double throughput=
    (double)ITERATIONS*
    (double)BYTES_PER_FLOAT*
    (double)READBUFFER_SIZE_IN_FLOATS/
    (double)(elapsedTime)*
    (double)(NANOSECONDS_IN_SECOND);
  std::cout<<throughput/GIGA<<" GB/second"<<std::endl;


  this->window->swap();
}


bool Application::init(){
  this->mainLoop = std::make_shared<ge::ad::SDLMainLoop>();
  this->mainLoop->setIdleCallback(std::bind(&Application::idle,this));

  this->window   = std::make_shared<ge::ad::SDLWindow>(512,512);
  this->window->createContext("rendering",450u,ge::ad::SDLWindow::CORE,ge::ad::SDLWindow::DEBUG);
  this->mainLoop->addWindow("primaryWindow",this->window);

  this->window->makeCurrent("rendering");

  ge::gl::init(SDL_GL_GetProcAddress);
  this->gl = ge::gl::getDefaultContext();
  ge::gl::setHighDebugMessage();

  this->gl->glEnable(GL_DEPTH_TEST);
  this->gl->glDepthFunc(GL_LEQUAL);
  this->gl->glDisable(GL_CULL_FACE);
  this->gl->glClearColor(0,0,0,1);

  const std::string compSrc = R".(
#ifndef WORKGROUP_SIZE
#define WORKGROUP_SIZE 64
#endif//WORKGROUP_SIZE

#ifndef FLOATS_PER_THREAD
#define FLOATS_PER_THREAD 32
#endif//FLOATS_PER_THREAD

layout(std430,binding=0)buffer Data{float readBuffer[];};

layout(local_size_x=WORKGROUP_SIZE)in;

void main(){
  float data = 0;
  const uint N=FLOATS_PER_THREAD;
  for(uint i=0;i<N;++i)
    data += readBuffer[gl_WorkGroupID.x*N*gl_WorkGroupSize.x+gl_LocalInvocationID.x+gl_WorkGroupSize.x*i];

  if(data==3233.323f)
    readBuffer[gl_GlobalInvocationID.x]=1.f;
}).";
  this->program = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(
        GL_COMPUTE_SHADER,
        "#version 450\n",
        ge::gl::Shader::define("WORKGROUP_SIZE",int(WORKGROUP_SIZE)),
        ge::gl::Shader::define("FLOATS_PER_THREAD",int(FLOATS_PER_THREAD)),
        compSrc));
  this->data = std::make_shared<ge::gl::Buffer>(READBUFFER_SIZE_IN_FLOATS*sizeof(float),nullptr,GL_DYNAMIC_COPY);
  this->query = std::make_shared<ge::gl::AsynchronousQuery>(GL_TIME_ELAPSED,GL_QUERY_RESULT,ge::gl::AsynchronousQuery::UINT64);
  return true;
}
