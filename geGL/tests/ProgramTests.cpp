#include<catch.hpp>
#include<SDLWin.h>
#include<geGL/geGL.h>
#include<geGL/StaticCalls.h>
#include<numeric>

using namespace ge::gl;
using namespace std;

TEST_CASE("Program context 3.3 test"){
  auto win = SDLWin(1,1,330);
  win.beginFrame();
  ge::gl::init();
  {
    auto vs = make_shared<Shader>(GL_VERTEX_SHADER,R".(
    #version 330

    uniform vec4 pos;

    void main(){
      gl_Position = vec4(pos);
    }

    ).");
    auto fs = make_shared<Shader>(GL_FRAGMENT_SHADER,R".(
    #version 330

    layout(location=0)out vec4 fColor;

    void main(){
      fColor = vec4(1);
    }

    ).");
    std::cerr << "#######################################" << std::endl;
    auto prg = make_shared<Program>(vs,fs);
    prg->getUniformLocation("pos");

  }
  win.endFrame();
}

TEST_CASE("Program buffer interface"){
  SDLWin win;
  win.beginFrame();
  ge::gl::init();
  {
    auto cs = std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
    R".(
    #version 450
    layout(local_size_x=64)in;
  
    layout(binding=3,std430)buffer Data0{uint  data0[];};
    layout(binding=5,std430)buffer Data1{uvec2 data1[];};
    layout(binding=6,std430)buffer Data2{uvec3 data2[];};
    layout(binding=7,std430)buffer Data3{uvec4 data3[];};
    layout(binding=8,std430)buffer Data4{uint data4a;uint data4b;};
  
    void main(){
      data0[gl_GlobalInvocationID.x] = 
      data1[gl_GlobalInvocationID.x].x +
      data2[gl_GlobalInvocationID.x].x +
      data3[gl_GlobalInvocationID.x].x +
      data4a + data4b;
    }
    ).");
    auto prg = std::make_shared<ge::gl::Program>(cs);
    auto const id = prg->getId();

    {
      GLint activeResources = 0;
      GLint maxNameLength   = 0;
      glGetProgramInterfaceiv(id,GL_BUFFER_VARIABLE,GL_ACTIVE_RESOURCES,&activeResources);
      glGetProgramInterfaceiv(id,GL_BUFFER_VARIABLE,GL_MAX_NAME_LENGTH,&maxNameLength);
      std::cerr << "GL_BUFFER_VARIABLE" << std::endl;
      std::cerr << "  GL_ACTIVE_RESOURCES: " << activeResources << std::endl;
      std::cerr << "  GL_MAX_NAME_LENGTH : " << maxNameLength << std::endl;

      std::vector<char>buf(maxNameLength);
      for(GLint i=0;i<activeResources;++i){
        glGetProgramResourceName(id,GL_BUFFER_VARIABLE,i,buf.size(),nullptr,buf.data());
        std::cerr << buf.data() << std::endl;

        {
          GLenum const props[] = {
            GL_BLOCK_INDEX  ,
            GL_ARRAY_STRIDE ,
            GL_OFFSET       ,
            GL_MATRIX_STRIDE,
            GL_IS_ROW_MAJOR ,
          };
          std::string const propNames[] = {
            "GL_BLOCK_INDEX  ",
            "GL_ARRAY_STRIDE ",
            "GL_OFFSET       ",
            "GL_MATRIX_STRIDE",
            "GL_IS_ROW_MAJOR ",
          };
          GLsizei const nprops = sizeof(props)/sizeof(props[0]);
          GLint propVal[nprops];
          glGetProgramResourceiv(id,GL_BUFFER_VARIABLE,i,nprops,props,nprops,nullptr,propVal);

          for(size_t i=0;i<nprops;++i)
            std::cerr << "  " << propNames[i] <<": " << propVal[i] << std::endl;
        }
      }
    }
    std::cerr << "" << std::endl;
    {
      GLint activeResources;
      GLint maxNameLength  ;
      glGetProgramInterfaceiv(id,GL_SHADER_STORAGE_BLOCK,GL_ACTIVE_RESOURCES,&activeResources);
      glGetProgramInterfaceiv(id,GL_SHADER_STORAGE_BLOCK,GL_MAX_NAME_LENGTH ,&maxNameLength  );
      std::cerr << "GL_SHADER_STORAGE_BLOCK" << std::endl;
      std::cerr << "  GL_ACTIVE_RESOURCES: " << activeResources << std::endl;
      std::cerr << "  GL_MAX_NAME_LENGTH : " << maxNameLength << std::endl;

      std::vector<char>buf(maxNameLength);
      for(GLint i=0;i<activeResources;++i){
        glGetProgramResourceName(id,GL_SHADER_STORAGE_BLOCK,i,buf.size(),nullptr,buf.data());
        std::cerr << buf.data() << std::endl;

        {
          GLenum const props[] = {
            GL_BUFFER_BINDING      ,
            GL_BUFFER_DATA_SIZE    ,
            GL_NUM_ACTIVE_VARIABLES,
            GL_ACTIVE_VARIABLES    ,
          };
          std::string const propNames[] = {
            "GL_BUFFER_BINDING      ",
            "GL_BUFFER_DATA_SIZE    ",
            "GL_NUM_ACTIVE_VARIABLES",
            "GL_ACTIVE_VARIABLES    ",
          };
          GLsizei const nprops = sizeof(props)/sizeof(props[0]);
          GLint propVal[nprops];
          glGetProgramResourceiv(id,GL_SHADER_STORAGE_BLOCK,i,nprops,props,nprops,nullptr,propVal);

          for(size_t i=0;i<nprops;++i)
            std::cerr << "  " << propNames[i] <<": " << propVal[i] << std::endl;

        }

      }
    }



    REQUIRE(prg->getBufferBinding("Data0") == 3);
    REQUIRE(prg->getBufferBinding("Data1") == 5);
    REQUIRE(prg->getBufferBinding("Data2") == 6);
    REQUIRE(prg->getBufferBinding("Data3") == 7);
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
    REQUIRE(prg->getBufferBinding("Data0") == 3);
    REQUIRE(prg->getBufferBinding("Data1") == 5);
    REQUIRE(prg->getBufferBinding("Data2") == 7);
  }
  win.endFrame();
}
