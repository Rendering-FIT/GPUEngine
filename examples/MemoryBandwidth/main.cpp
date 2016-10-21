#include<limits>
#include<string>
#include<geGL/geGL.h>
#include<geAd/SDLWindow/SDLWindow.h>
#include<algorithm>

const size_t GIGA                  = 1<<30     ;
const size_t NANOSECONDS_IN_SECOND = 1000000000;
const size_t COMPUTE_UNITS         = 20        ;
const size_t WAVEFRONT_SIZE        = 64        ;

double median(std::function<double()>const&fce,size_t iteration = 10){
  assert(iteration>0);
  std::vector<double>values;
  for(size_t i=0;i<iteration;++i)
    values.push_back(fce());
  std::sort(values.begin(),values.end());
  return values.at(iteration/2);
}

double basicBufferTest(size_t FLOATS_PER_THREAD = 32){
  const size_t WAVEFRONTS_PER_COMPUTE_UNIT = 2048;
  const size_t WAVEFRONTS_PER_WORKGROUP    = 1   ;
  const size_t ITERATIONS                  = 50  ;
  const size_t NOF_THREADS               = WAVEFRONT_SIZE*COMPUTE_UNITS*WAVEFRONTS_PER_COMPUTE_UNIT;
  const size_t READBUFFER_SIZE_IN_FLOATS = NOF_THREADS*FLOATS_PER_THREAD;
  const size_t WORKGROUP_SIZE            = WAVEFRONTS_PER_WORKGROUP*WAVEFRONT_SIZE;
  const size_t NOF_WORKGROUPS            = NOF_THREADS/WORKGROUP_SIZE;

  const std::string compSrc = R".(
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
  auto program = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(
        GL_COMPUTE_SHADER,
        "#version 450\n",
        ge::gl::Shader::define("WORKGROUP_SIZE"   ,int(WORKGROUP_SIZE)),
        ge::gl::Shader::define("FLOATS_PER_THREAD",int(FLOATS_PER_THREAD)),
        compSrc));
  auto data = std::make_shared<ge::gl::Buffer>(READBUFFER_SIZE_IN_FLOATS*sizeof(float),nullptr,GL_DYNAMIC_COPY);
  auto query = std::make_shared<ge::gl::AsynchronousQuery>(GL_TIME_ELAPSED,GL_QUERY_RESULT,ge::gl::AsynchronousQuery::UINT64);
  auto gl = ge::gl::getDefaultContext();
  program->use();

  data->bindBase(GL_SHADER_STORAGE_BUFFER,0);
  gl->glFinish();
  query->begin();
  for(size_t i=0;i<ITERATIONS;++i)
    gl->glDispatchCompute(NOF_WORKGROUPS,1,1);
  query->end();
  gl->glFinish();
  auto elapsedTime = query->getui64();

  double throughput=
    double(ITERATIONS)*
    double(sizeof(float))*
    double(READBUFFER_SIZE_IN_FLOATS)/
    double(elapsedTime)*
    double(NANOSECONDS_IN_SECOND);
  return throughput/GIGA;
}

double basicTextureTest(size_t WGSX = 8,size_t WGSY = 8){
  const size_t ITERATIONS                  = 50  ;
  const size_t NOF_WORKGROUPS              = 1024;

  const std::string compSrc = R".(
layout(r32f,binding=0)uniform image2D readTexture;
layout(local_size_x=WGSX,local_size_y=WGSY)in;
void main(){
  float data = 0;
  data = imageLoad(readTexture,ivec2(gl_GlobalInvocationID.xy)).x;
  if(data==3233.323f)
    imageStore(readTexture,ivec2(gl_GlobalInvocationID.xy),vec4(1.f));
}).";
  auto program = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(
        GL_COMPUTE_SHADER,
        "#version 450\n",
        ge::gl::Shader::define("WGSX"   ,int(WGSX)),
        ge::gl::Shader::define("WGSY"   ,int(WGSY)),
        compSrc));
  auto texture = std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D,GL_R32F,1,NOF_WORKGROUPS*WGSX,NOF_WORKGROUPS*WGSY);
  auto query = std::make_shared<ge::gl::AsynchronousQuery>(GL_TIME_ELAPSED,GL_QUERY_RESULT,ge::gl::AsynchronousQuery::UINT64);
  auto gl = ge::gl::getDefaultContext();
  program->use();

  texture->bindImage(0,0);
  gl->glFinish();
  query->begin();
  for(size_t i=0;i<ITERATIONS;++i)
    gl->glDispatchCompute(NOF_WORKGROUPS,NOF_WORKGROUPS,1);
  query->end();
  gl->glFinish();
  auto elapsedTime = query->getui64();

  double throughput=
    double(ITERATIONS)*
    double(sizeof(float))*
    double(WGSX*WGSY*NOF_WORKGROUPS*NOF_WORKGROUPS)/
    double(elapsedTime)*
    double(NANOSECONDS_IN_SECOND);
  return throughput/GIGA;
}

int main(int,char*[]){
  auto window   = std::make_shared<ge::ad::SDLWindow>(512,512);
  window->createContext("rendering",450u,ge::ad::SDLWindow::CORE,ge::ad::SDLWindow::DEBUG);
  ge::gl::init(SDL_GL_GetProcAddress);
  ge::gl::setHighDebugMessage();

  //for(size_t i=1;i<=32;i<<=1)
  //  std::cout<<"buffer memory read bandwidth "<<i<<" floats/thread: "<<median(std::bind(basicBufferTest,i))<<" GB/second"<<std::endl;
  for(size_t x=1;x<=64;x<<=1)
    std::cout<<"texture image memory read bandwidth "<<x<<" x "<<64/x<<": floats/thread: "<<median(std::bind(basicTextureTest,x,64/x))<<" GB/second"<<std::endl;
  return EXIT_SUCCESS;
}

