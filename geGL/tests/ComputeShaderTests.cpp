#include<catch.hpp>
#include<SDLWin.h>
#include<geGL/geGL.h>
#include<geGL/StaticCalls.h>
#include<numeric>

using namespace ge::gl;
using namespace std;

TEST_CASE("Compute shader tests Tests"){
  SDLWin win;
  win.beginFrame();
  ge::gl::init();
  {
    auto cs = std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
    R".(
    #version 450
    layout(local_size_x=64)in;

    layout(binding=0,std430)buffer Data{uint data[];};

    void main(){
      data[gl_GlobalInvocationID.x] = gl_GlobalInvocationID.x;
    }
    ).");
    auto prg = std::make_shared<ge::gl::Program>(cs);
    prg->use();
    auto data = std::vector<uint32_t>(64*2);
    for(auto&x:data)
      x = 10;
    auto test = data;
    auto buf = std::make_shared<ge::gl::Buffer>(data);
    buf->bindBase(GL_SHADER_STORAGE_BUFFER,0);
    glDispatchCompute(2,1,1);
    glFinish();
    buf->getData(data.data());
    std::iota(test.begin(),test.end(),0);
    REQUIRE(test == data);
  }
  {
    auto cs = std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
    R".(
    #version 450
    layout(local_size_x=64)in;
  
    layout(binding=0,std430)buffer Data{uvec4 data[];};
  
    void main(){
      data[gl_GlobalInvocationID.x] = uvec4(gl_GlobalInvocationID.x*4)+uvec4(0u,1u,2u,3u);
    }
    ).");
    auto prg = std::make_shared<ge::gl::Program>(cs);
    prg->use();
    auto data = std::vector<uint32_t>(64*4);
    for(auto&x:data)
      x = 10;
    auto test = data;
    auto buf = std::make_shared<ge::gl::Buffer>(data);
    buf->bindBase(GL_SHADER_STORAGE_BUFFER,0);
    glDispatchCompute(1,1,1);
    glFinish();
    buf->getData(data.data());
    std::iota(test.begin(),test.end(),0);
    REQUIRE(test == data);
  }
  {
    auto cs = std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
    R".(
    #version 450
    layout(local_size_x=64)in;
  
    layout(binding=0,std430)buffer Data{vec4 data[];};
  
    void main(){
      data[gl_GlobalInvocationID.x] = vec4(gl_GlobalInvocationID.x*4.f)+vec4(0.1f,1.1f,2.1f,3.1f);
    }
    ).");
    auto prg = std::make_shared<ge::gl::Program>(cs);
    prg->use();
    auto data = std::vector<float>(64*4);
    for(auto&x:data)
      x = 10.f;
    auto test = data;
    auto buf = std::make_shared<ge::gl::Buffer>(data);
    buf->bindBase(GL_SHADER_STORAGE_BUFFER,0);
    glDispatchCompute(1,1,1);
    glFinish();
    buf->getData(data.data());
    for(size_t i=0;i<test.size();++i)
      test[i] = 0.1f + i;
    REQUIRE(test == data);
  }
  {
    auto cs = std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
    R".(
    #version 450
    layout(local_size_x=64)in;
  
    layout(binding=0,std430)buffer Data{uint counter[4];};
  
    void main(){
      atomicAdd(counter[0],gl_GlobalInvocationID.x);
    }
    ).");
    auto prg = std::make_shared<ge::gl::Program>(cs);
    prg->use();
    auto data = std::vector<uint32_t>(4);
    for(auto&x:data)x = 0;
    auto buf = std::make_shared<ge::gl::Buffer>(data);
    buf->bindBase(GL_SHADER_STORAGE_BUFFER,0);
    glDispatchCompute(1,1,1);
    glFinish();
    buf->getData(data.data());
    REQUIRE(data.at(0) == 2016);
  }


  win.endFrame();
}
