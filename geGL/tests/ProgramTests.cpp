#include<catch.hpp>
#include<SDLWin.h>
#include<geGL/geGL.h>
#include<geGL/StaticCalls.h>
#include<numeric>

using namespace ge::gl;
using namespace std;

TEST_CASE("Program buffer interface"){
  SDLWin win;
  win.beginFrame();
  ge::gl::init();
  {
    auto cs = std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
    R".(
    #version 450
    layout(local_size_x=64)in;
  
    layout(binding=3,std430)buffer Data0{uint data0[];};
    layout(binding=5,std430)buffer Data1{uint data1[];};
    layout(binding=7,std430)buffer Data2{uint data2[];};
  
    void main(){
      data0[gl_GlobalInvocationID.x] = 
      data1[gl_GlobalInvocationID.x] +
      data2[gl_GlobalInvocationID.x];
    }
    ).");
    auto prg = std::make_shared<ge::gl::Program>(cs);
    auto const id = prg->getId();
    GLint bufferVariableActiveResources = 0;
    GLint bufferVariableMaxNameLength   = 0;
    ge::gl::glGetProgramInterfaceiv(id,GL_BUFFER_VARIABLE,GL_ACTIVE_RESOURCES,&bufferVariableActiveResources);
    ge::gl::glGetProgramInterfaceiv(id,GL_BUFFER_VARIABLE,GL_MAX_NAME_LENGTH,&bufferVariableMaxNameLength);
    std::cerr << bufferVariableActiveResources << std::endl;
    std::cerr << bufferVariableMaxNameLength << std::endl;

    std::vector<char>buf(bufferVariableMaxNameLength);
    for(GLint i=0;i<bufferVariableActiveResources;++i){
      glGetProgramResourceName(id,GL_BUFFER_VARIABLE,i,buf.size(),nullptr,buf.data());
      std::cerr << buf.data() << std::endl;
      GLenum props = GL_BUFFER_BINDING;
      GLint propVal;
      glGetProgramResourceiv(id,GL_SHADER_STORAGE_BLOCK,i,1,&props,1,nullptr,&propVal);
      std::cerr << "binding: " << propVal << std::endl;
    }
    REQUIRE(prg->getBufferBinding("data0") == 3);
    REQUIRE(prg->getBufferBinding("data1") == 5);
    REQUIRE(prg->getBufferBinding("data2") == 7);
  }
  win.endFrame();
}

TEST_CASE("Program buffer binding"){
  SDLWin win;
  win.beginFrame();
  ge::gl::init();
  {
    auto cs = std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
    R".(
    #version 450
    layout(local_size_x=64)in;
  
    layout(binding=3,std430)buffer Data0{uint data0[];};
    layout(binding=5,std430)buffer Data1{uint data1[];};
    layout(binding=7,std430)buffer Data2{uint data2[];};
  
    void main(){
      data0[gl_GlobalInvocationID.x] = 
      data1[gl_GlobalInvocationID.x] +
      data2[gl_GlobalInvocationID.x];
    }
    ).");
    auto prg = std::make_shared<ge::gl::Program>(cs);
    REQUIRE(prg->getBufferBinding("data0") == 3);
    REQUIRE(prg->getBufferBinding("data1") == 5);
    REQUIRE(prg->getBufferBinding("data2") == 7);
  }
  win.endFrame();
}
