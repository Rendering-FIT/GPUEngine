#include<geAd/SDLWindow/SDLWindow.h>
#include<geAd/SDLWindow/SDLMainLoop.h>
#include<geGL/StaticCalls.h>
#include<geGL/geGL.h>

using namespace std;
using namespace ge::gl;
using namespace ge::ad;

std::string vSrc = R".(
#version 450
flat out uint vDirection;
void main() {
  uint triangleID = gl_VertexID/3;
  uint vertexIDInTriangle = gl_VertexID%3;
  vec2 vertexPosition = vec2(vertexIDInTriangle%2,vertexIDInTriangle/2);
  float scale = 1/6.;
  vec2 triangleOffset = vec2(triangleID*scale,0);
  gl_Position = vec4(vertexPosition*scale+triangleOffset,1,1);
  vDirection = triangleID;
}).";

std::string fSrc = R".(
#version 450
out vec4 fColor;
layout(binding=0)uniform samplerCube cube;
flat in uint vDirection;
void main(){
  vec3 directions[6]={
    vec3(-1,+0,+0),vec3(+1,+0,+0),
    vec3(+0,-1,+0),vec3(+0,+1,+0),
    vec3(+0,+0,-1),vec3(+0,+0,+1)
  };
  fColor=texture(cube,directions[vDirection]);
}
).";

int main(int,char*[]){
  auto mainLoop = make_shared<SDLMainLoop>();
  auto window = make_shared<SDLWindow>();

  window->createContext("rendering");
  mainLoop->addWindow("mainWindow", window);

  ge::gl::init();
  setHighDebugMessage();

  auto vs = make_shared<Shader>(GL_VERTEX_SHADER, vSrc);
  auto fs = make_shared<Shader>(GL_FRAGMENT_SHADER, fSrc);
  auto program = make_shared<Program>(vs, fs);
  auto vao = make_shared<VertexArray>();

  auto tex = make_shared<Texture>(GL_TEXTURE_CUBE_MAP,GL_RGBA,1,1,1);
  for(uint32_t i=0;i<6;++i){
    uint32_t color = 0xff000000+0xff*(((i+1)>>0)&1)+0xff00*(((i+1)>>1)&1)+0xff0000*(((i+1)>>2)&1);
    tex->setData2D(&color,GL_RGBA,GL_UNSIGNED_BYTE,0,GL_TEXTURE_CUBE_MAP_POSITIVE_X+i);
  }

  mainLoop->setIdleCallback([&]() {
    glClear(GL_COLOR_BUFFER_BIT);
    program->use();
    vao->bind();
    tex->bind(0);
    glDrawArrays(GL_TRIANGLES, 0, 3*6);
    window->swap();
  });

  (*mainLoop)();
  return 0;
}

